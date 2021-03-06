//---------------------------------------------------------------------------

#ifndef UpdateH
#define UpdateH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <windows.h>
#include <tlhelp32.h>

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TMemo *Mem_Info;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations

	struct column
	{
		unsigned char c_0;
		unsigned char c_1;
		unsigned char c_2;
		unsigned char c_3;
		unsigned char c_4;
		unsigned char c_5;
	} size_column;

    AnsiString table_head(column size_column);
	AnsiString table_head(column size_column, AnsiString delimetr);
	AnsiString table_row(column size_column, PROCESSENTRY32 ProcessEntry, int number);
	AnsiString table_row(column size_column, PROCESSENTRY32 ProcessEntry, int number,  AnsiString delimetr);
	AnsiString table_element(unsigned char length, AnsiString str, AnsiString delimetr);

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	void __fastcall GetActiveAppList (TStringList *slist);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
