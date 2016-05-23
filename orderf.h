//---------------------------------------------------------------------------

#ifndef orderfH
#define orderfH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TOrderForm : public TForm
{
__published:	// IDE-managed Components
        TComboBox *orderComboBox;
        TRichEdit *orderRichEdit;
        TBitBtn *saveOrderBitBtn;
        TLabel *Label1;
        TSaveDialog *SaveDialog;
        TBitBtn *openBitBtn;
        TOpenDialog *OpenDialog;
        void __fastcall orderComboBoxChange(TObject *Sender);
        void __fastcall saveOrderBitBtnClick(TObject *Sender);
        void __fastcall openBitBtnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        void writeFile();
        void readFile();
        __fastcall TOrderForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOrderForm *OrderForm;
//---------------------------------------------------------------------------
#endif
