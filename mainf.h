//---------------------------------------------------------------------------

#ifndef mainfH
#define mainfH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
class ListProduct;
class ListOrder;
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *orderGroupBox;
        TGroupBox *productGroupBox;
        TLabel *Label1;
        TEdit *countEdit;
        TComboBox *productComboBox;
        TBitBtn *addPoductBitBtn;
        TLabel *unitLabel;
        TLabel *priceLabel;
        TLabel *Label4;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *sumLabel;
        TLabel *Label7;
        TGroupBox *customerGroupBox;
        TLabel *Label5;
        TLabel *numberOrderLabel;
        TBitBtn *addCustomerBitBtn;
        TStringGrid *orderGrid;
        TEdit *customerEdit;
        TBitBtn *orderFormBitBtn;
        TComboBox *typeOrderComboBox;
        TLabel *Label6;
        TLabel *Label8;
        TBitBtn *editProductBitBtn;
        TBitBtn *removeProductBitBtn;
        void __fastcall countEditKeyPress(TObject *Sender, char &Key);
        void __fastcall productComboBoxChange(TObject *Sender);
        void __fastcall addPoductBitBtnClick(TObject *Sender);
        void __fastcall addCustomerBitBtnClick(TObject *Sender);
        void __fastcall customerEditChange(TObject *Sender);
        void __fastcall orderFormBitBtnClick(TObject *Sender);
        void __fastcall orderGridSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
        void __fastcall editProductBitBtnClick(TObject *Sender);
        void __fastcall removeProductBitBtnClick(TObject *Sender);
private:
        ListProduct *listProduct;
        ListOrder *listOrder;
        TStringList *catalog;
        String customer;
        String numberOrder;
        String nameProduct;
        String article;
        String unit;
        double price;
        void readListProduct();
        void calculateSum();
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
