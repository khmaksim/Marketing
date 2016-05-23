//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream.h>
#include <sysutils.hpp>
#include <stdlib.h>
#include <fstream.h>
#pragma hdrstop

#include "mainf.h"
#include "orderf.h"
#include "product.h"
#include "listproduct.h"
#include "order.h"
#include "listorder.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
        //������ ������ [] � ��������� ����
        HMENU MenuHandle = GetSystemMenu(Handle, false);
        if(MenuHandle)
                DeleteMenu(MenuHandle, SC_MAXIMIZE, MF_BYCOMMAND);

        orderGrid->ColCount = 8;        //���������� ������� � ������� ������
        //�������� �������
        orderGrid->Cells[0][0] = "�";
        orderGrid->Cells[1][0] = "��������";
        orderGrid->Cells[2][0] = "����� ���.";
        orderGrid->Cells[3][0] = "������������ ������";
        orderGrid->Cells[4][0] = "�������";
        orderGrid->Cells[5][0] = "���-��";
        orderGrid->Cells[6][0] = "��.���.";
        orderGrid->Cells[7][0] = "����";
        //������ ��������
        orderGrid->ColWidths[0] = 15;
        orderGrid->ColWidths[1] = 150;
        orderGrid->ColWidths[2] = 60;
        orderGrid->ColWidths[3] = 240;
        orderGrid->ColWidths[4] = 45;
        orderGrid->ColWidths[5] = 40;
        orderGrid->ColWidths[6] = 40;
        orderGrid->ColWidths[7] = 65;
        this->readListProduct();        //������ ��������� ���������
        listProduct = new ListProduct();
        listOrder = new ListOrder();
}
//---------------------------------------------------------------------------
//������ �������� ���������
void TMainForm::readListProduct()
{
        catalog = new TStringList;
        ifstream inStream("catalog/catalog.txt", ios::in);
        if(!inStream)
        {
                ShowMessage("�� ������� ��������� ���� - �������.");
                return;
        }
        String line = "";
        char c;
        while(!inStream.eof())
        {
                c = inStream.get();
                if(c == '\n')
                {
                        catalog->Add(line);
                        line = "";
                        continue;
                }
                line += c;
        }
        inStream.close();
        int i = 0;
        while(i < catalog->Count)
        {
                productComboBox->Items->Add(catalog->Strings[i].SubString(0, catalog->Strings[i].Pos(";") - 1));
                i++;
        }
}
//---------------------------------------------------------------------------
//����������� ����� � ������� ��
void TMainForm::calculateSum()
{
        sumLabel->Font->Color = clRed;
        double sum = 0;
        for(int i = 1; i < orderGrid->RowCount; i++)
        {
                String strPrice = orderGrid->Cells[7][i];
                String strSum = "";
                //����� ����
                for(int j = 0; j < strPrice.Length(); j++)
                {
                        if(strPrice.c_str()[j] >= '0' && strPrice.c_str()[j] <= '9')
                                strSum += strPrice.c_str()[j];
                        if(strPrice.c_str()[j] == ',')
                                strSum += strPrice.c_str()[j];
                }
                sum += strSum.ToDouble() * orderGrid->Cells[5][i].ToInt();
                sumLabel->Caption = sum;
        }
}
//---------------------------------------------------------------------------
//������ ����� ��������, ����� ����
void __fastcall TMainForm::countEditKeyPress(TObject *Sender, char &Key)
{
        if((Key >= '0' && Key <= '9') || Key == VK_BACK)
                return;
        else
                Key = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::productComboBoxChange(TObject *Sender)
{
        for(int i = 0; i < catalog->Count; i++)
        {
                String item = catalog->Strings[i];
                if(item.Pos(productComboBox->Text))
                {
                        nameProduct = item.SubString(0, item.Pos(";") - 1);
                        for(int j = 0; j < 3; j++)
                        {
                                if(j == 0)
                                {
                                        item = item.SubString(item.Pos(";") + 1, item.Length() - item.Pos(";"));
                                        article = item.SubString(0, item.Pos(";") - 1);
                                }
                                if(j == 1)
                                {
                                        item = item.SubString(item.Pos(";") + 1, item.Length() - item.Pos(";"));
                                        unitLabel->Caption = unit = item.SubString(0, item.Pos(";") - 1);
                                }
                                if(j == 2)
                                {
                                        item = item.SubString(item.Pos(";") + 1, item.Length() - item.Pos(";"));
                                        priceLabel->Caption = price = item. ToDouble();
                                }
                        }
                }
        }
}
//---------------------------------------------------------------------------
//���������� ������ � ������� �������
void __fastcall TMainForm::addPoductBitBtnClick(TObject *Sender)
{
        if(productComboBox->Text.IsEmpty() || countEdit->Text.IsEmpty())
        {
                MessageDlg("�������� ������������ ����� �� ������\n � ������� ���������� ������� ������!", mtWarning, TMsgDlgButtons() << mbOK, 0);
                return;
        }

        if(!orderGrid->Cells[0][orderGrid->RowCount - 1].IsEmpty())
                orderGrid->RowCount++;
        orderGrid->Cells[0][orderGrid->RowCount - 1] = orderGrid->RowCount - 1;
        orderGrid->Cells[1][orderGrid->RowCount - 1] = customer;
        orderGrid->Cells[2][orderGrid->RowCount - 1] = numberOrder;
        orderGrid->Cells[3][orderGrid->RowCount - 1] = nameProduct;
        orderGrid->Cells[4][orderGrid->RowCount - 1] = article;
        orderGrid->Cells[5][orderGrid->RowCount - 1] = countEdit->Text;
        orderGrid->Cells[6][orderGrid->RowCount - 1] = unit;
        orderGrid->Cells[7][orderGrid->RowCount - 1] = price;
        Product product(nameProduct, article, countEdit->Text.ToInt(), unit, price);
        listProduct->addListProduct(product);
        //���������� ������ �������� ���������
        /*TStringList *nameProduct = listProduct->getNameProduct();
        for(int i = 0; i < nameProduct->Count; i++)
                ShowMessage(nameProduct->operator [](i));*/
        calculateSum();
        countEdit->Clear();             //������� ���� ����� ���������� 
}
//---------------------------------------------------------------------------
//���������� ���������
void __fastcall TMainForm::addCustomerBitBtnClick(TObject *Sender)
{
        if(customerEdit->Text.IsEmpty())
                MessageDlg("������� ���������!", mtWarning, TMsgDlgButtons() << mbOK, 0);
        else
        {
                customer = customerEdit->Text;
                numberOrder = Date().FormatString("yymmdd") + "/" + Time().FormatString("hhnnss");  //����� ������
                numberOrderLabel->Caption = numberOrder;
                productGroupBox->Enabled = true;
                Order order(numberOrder, customer);
                listOrder->addListOrder(order);
        }
}
//---------------------------------------------------------------------------
//���������� ������ ������, ���� ��� ���������
void __fastcall TMainForm::customerEditChange(TObject *Sender)
{
        if(customerEdit->Text.IsEmpty())
                productGroupBox->Enabled = false;
}
//---------------------------------------------------------------------------
//������������ ������
void __fastcall TMainForm::orderFormBitBtnClick(TObject *Sender)
{
        OrderForm->orderComboBox->Enabled = true;
        OrderForm->orderRichEdit->Clear();
        //��������� ������ ����������
        for(int i = 1; i < orderGrid->RowCount; i++)
        {
                for(int j = 0; j < OrderForm->orderComboBox->Items->Count; j++)
                        if(orderGrid->Cells[1][i] == OrderForm->orderComboBox->Items->Strings[j])
                                goto l1;
                OrderForm->orderComboBox->Items->Add(orderGrid->Cells[1][i]);
                l1: continue;
        }

        if(typeOrderComboBox->ItemIndex == 1)
        {
                OrderForm->orderComboBox->Enabled = false;
                OrderForm->orderRichEdit->Paragraph->Alignment = taCenter;
                OrderForm->orderRichEdit->Lines->Add("� � � � � � �   � � � � �");
                OrderForm->orderRichEdit->Lines->Add("");
                OrderForm->orderRichEdit->Paragraph->Alignment = taLeftJustify;
                for(int i = 0; i < OrderForm->orderComboBox->Items->Count; i++)
                {
                        //����� ��������� � ����� ������
                        for(int j = 1; j < orderGrid->RowCount; j++)
                                if(OrderForm->orderComboBox->Items->Strings[i] == orderGrid->Cells[1][j])
                                {
                                        OrderForm->orderRichEdit->Lines->Add("����� �" + orderGrid->Cells[2][j]);
                                        OrderForm->orderRichEdit->Lines->Add("��������: " + orderGrid->Cells[1][j]);
                                        break;
                                }
                        double sum = 0;
                        for(int j = 1; j < orderGrid->RowCount; j++)
                                if(OrderForm->orderComboBox->Items->Strings[i] == orderGrid->Cells[1][j])
                                {
                                        OrderForm->orderRichEdit->Lines->Add(orderGrid->Cells[3][j] + " | " + orderGrid->Cells[4][j] + " | " + orderGrid->Cells[5][j] + " | " + orderGrid->Cells[6][j] + " | " + orderGrid->Cells[7][j]);
                                        sum += orderGrid->Cells[7][j].ToDouble() * orderGrid->Cells[5][j].ToInt();
                                }
                        OrderForm->orderRichEdit->Lines->Add("����� ��������� ������:" + FloatToStr(sum));
                        OrderForm->orderRichEdit->Lines->Add("");
                }

        }
        OrderForm->ShowModal();
}
//---------------------------------------------------------------------------
//����� �������� �� �������
void __fastcall TMainForm::orderGridSelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
        for(int index = 0; index < productComboBox->Items->Count; index++)
                if(productComboBox->Items->operator [](index) == orderGrid->Cells[3][ARow])
                        productComboBox->ItemIndex = index;
        countEdit->Text = orderGrid->Cells[5][ARow]; 
}
//---------------------------------------------------------------------------
//�������������� ��������� ������
void __fastcall TMainForm::editProductBitBtnClick(TObject *Sender)
{
        if(productComboBox->Text.IsEmpty() || countEdit->Text.IsEmpty())
        {
                MessageDlg("�������� ������������ ����� �� ������\n � ������� ���������� ������� ������!", mtWarning, TMsgDlgButtons() << mbOK, 0);
                return;
        }
        orderGrid->Cells[3][orderGrid->Row] = productComboBox->Text;
        orderGrid->Cells[5][orderGrid->Row] = countEdit->Text;
        orderGrid->Cells[7][orderGrid->Row] = price;
        calculateSum();
        countEdit->Clear();             //������� ���� ����� ����������
}
//---------------------------------------------------------------------------
//�������� ���������� ������
void __fastcall TMainForm::removeProductBitBtnClick(TObject *Sender)
{
        if(orderGrid->Row < 1)
                return;
        if(orderGrid->RowCount == 1)
        {
                orderGrid->Rows[0]->Clear();
                return;
        }
        for(int i = orderGrid->Row; i < orderGrid->RowCount; i++)
                for(int j = 0; j < orderGrid->ColCount; j++)
                        orderGrid->Cells[j][i] = orderGrid->Cells[j][i+1];
        orderGrid->RowCount--;
}
//---------------------------------------------------------------------------

