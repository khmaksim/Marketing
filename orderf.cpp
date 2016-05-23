//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include "orderf.h"
#include "mainf.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOrderForm *OrderForm;
//---------------------------------------------------------------------------
__fastcall TOrderForm::TOrderForm(TComponent* Owner)
        : TForm(Owner)
{
        //запрет кнопки [] в заголовке окна
        HMENU MenuHandle = GetSystemMenu(Handle, false);
        if(MenuHandle)
                DeleteMenu(MenuHandle, SC_MAXIMIZE, MF_BYCOMMAND);
}
//---------------------------------------------------------------------------
//формирование заказа определенному заказчику
void __fastcall TOrderForm::orderComboBoxChange(TObject *Sender)
{
        orderRichEdit->Clear();
        orderRichEdit->Paragraph->Alignment = taCenter;
        //поиск номера заказа
        for(int i = 1; i < MainForm->orderGrid->RowCount; i++)
                if(orderComboBox->Text == MainForm->orderGrid->Cells[1][i])
                {
                        orderRichEdit->Lines->Add("З А К А З   №  " + MainForm->orderGrid->Cells[2][i]);
                        break;
                }
        orderRichEdit->Lines->Add("");
        orderRichEdit->Paragraph->Alignment = taLeftJustify;
        //поиск заказчика
        for(int i = 1; i < MainForm->orderGrid->RowCount; i++)
                if(orderComboBox->Text == MainForm->orderGrid->Cells[1][i])
                {
                        orderRichEdit->Lines->Add("Заказчик: " + MainForm->orderGrid->Cells[1][i]);
                        break;
                }
        double sum = 0;
        for(int i = 1; i < MainForm->orderGrid->RowCount; i++)
                if(orderComboBox->Text == MainForm->orderGrid->Cells[1][i])
                {
                        orderRichEdit->Lines->Add(MainForm->orderGrid->Cells[3][i] + " | " + MainForm->orderGrid->Cells[4][i] + " | " + MainForm->orderGrid->Cells[5][i] + " | " + MainForm->orderGrid->Cells[6][i] + " | " + MainForm->orderGrid->Cells[7][i]);
                        sum += MainForm->orderGrid->Cells[7][i].ToDouble() * MainForm->orderGrid->Cells[5][i].ToInt();
                }
        orderRichEdit->Lines->Add("Общая стоимость заказа:" + FloatToStr(sum));
}
//---------------------------------------------------------------------------
//сохранение заказа
void __fastcall TOrderForm::saveOrderBitBtnClick(TObject *Sender)
{
        writeFile();
}
//---------------------------------------------------------------------------
//открыть файл с заказом
void __fastcall TOrderForm::openBitBtnClick(TObject *Sender)
{
        readFile();
}
//---------------------------------------------------------------------------
//запись в файл
void TOrderForm::writeFile()
{
        String fileName;
        if(!orderComboBox->Text.IsEmpty())
        {
                for(int i = 1; i < MainForm->orderGrid->RowCount; i++)
                        if(orderComboBox->Text == MainForm->orderGrid->Cells[1][i])
                        {
                                String numberOrder = MainForm->orderGrid->Cells[2][i];
                                SaveDialog->FileName = "Заказ" + numberOrder.SubString(0, 6) + numberOrder.SubString(8, 6) + ".csv";         //имя сохраняемого файла
                                break;
                        }
        }
        else if(orderComboBox->Text.IsEmpty() && orderRichEdit->Text.IsEmpty())
        {
                MessageDlg("Заказ не сформирован!", mtInformation, TMsgDlgButtons() << mbOK, 0);
                return;
        }
        //вызов диалога сохранения файла
        if(SaveDialog->Execute())
        {
                fileName = SaveDialog->FileName;
                if(fileName.SubString(fileName.Length() - 3, 4) == ".csv")
                {
                        FILE *file;
                        if((file = fopen(fileName.c_str(), "w")) == NULL)
                        {
                                MessageDlg("Не удалось открыть файл для записи.", mtWarning, TMsgDlgButtons() << mbOK, 0);
                                return;
                        }
                        for(int i = 1; i < orderRichEdit->Lines->Text.Length(); i++)
                        {
                                if(orderRichEdit->Lines->Text[i] == '|')
                                        putc(';', file);
                                else
                                        putc(orderRichEdit->Lines->Text[i], file);
                        }
                        fclose(file);
                }
                else if(fileName.SubString(fileName.Length() - 4, 4) == ".rtf")
                        orderRichEdit->Lines->SaveToFile(SaveDialog->FileName);             //сохранение заказа
        }
}
//чтение файла
void TOrderForm::readFile()
{
         if(OpenDialog->Execute())
        {
                orderRichEdit->Clear();
                orderRichEdit->Lines->LoadFromFile(OpenDialog->FileName);
        }
}


