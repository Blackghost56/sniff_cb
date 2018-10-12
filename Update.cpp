//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Update.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;



//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	TStringList *slist = new TStringList();
	try { GetActiveAppList(slist); Mem_Info->Lines->Text = slist->Text; }
	__finally { delete slist; }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GetActiveAppList (TStringList *slist)
{
	// Set column size
	size_column.c_0 = 3;
	size_column.c_1 = 30;
	size_column.c_2 = 7;
	size_column.c_3 = 7;
	size_column.c_4 = 10;
	size_column.c_5 = 10;
	// ---------------

	if (!slist) return;
	slist->Clear();

	//MODULEENTRY32 test;

	PROCESSENTRY32 ProcessEntry;
	ProcessEntry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE Hndl = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
	if(Hndl == INVALID_HANDLE_VALUE) return;
	//if (((int)(Hndl)) == (-1)) return;

	AnsiString fname = table_head(size_column, '|');
	slist->Add(fname);
	try {
		int i = 0;
		bool Loop = Process32First(Hndl, &ProcessEntry);
		while (Loop)
		{
			Loop = Process32Next(Hndl, &ProcessEntry);
			fname = table_row(size_column, ProcessEntry, i, '|');
			//fname = AnsiString(i) + AnsiString(ProcessEntry.szExeFile).Trim() + '\t' +AnsiString(ProcessEntry.th32ProcessID).Trim();
			i++;
			//if (fname.IsEmpty()) continue;
			slist->Add(fname);
		}
		/*
		for (bool loop = Process32First(Hndl, &ProcessEntry); loop; loop = Process32Next(Hndl, &ProcessEntry))
		{
			//fname = AnsiString(ProcessEntry.szExeFile).Trim().UpperCase();
			fname = AnsiString(ProcessEntry.szExeFile).Trim();
			if (fname.IsEmpty()) continue;
			slist->Add(fname);
		}  */
	} // try
	catch (...) { slist->Clear(); }
	CloseHandle(Hndl);
}

AnsiString TForm1::table_element(unsigned char length, AnsiString str, AnsiString delimetr)
{
	if (str.Length() < (length + 1)) {
		while (str.Length() < (length + 1))
		{
			str += ' ';  
		}
	}
	str += delimetr;

	return str;
}


AnsiString TForm1::table_row(column size_column, PROCESSENTRY32 ProcessEntry, int number)
{
	 AnsiString str;
	 AnsiString delimetr = '|';               // Set defualt delimetr

	 str = table_row(size_column, ProcessEntry, number, delimetr);

	 return str;	 
}


AnsiString TForm1::table_row(column size_column, PROCESSENTRY32 ProcessEntry, int number, AnsiString delimetr)
{
	 AnsiString str;

	 str += delimetr;

	 str += table_element(size_column.c_0, AnsiString(number), delimetr);
	 str += table_element(size_column.c_1, AnsiString(ProcessEntry.szExeFile).Trim(), delimetr);
	 str += table_element(size_column.c_2, AnsiString(ProcessEntry.th32ProcessID).Trim(), delimetr);
	 str += table_element(size_column.c_3, AnsiString(ProcessEntry.th32ParentProcessID).Trim(), delimetr);
	 str += table_element(size_column.c_4, AnsiString(ProcessEntry.cntThreads).Trim(), delimetr);
	 str += table_element(size_column.c_5, AnsiString(ProcessEntry.pcPriClassBase).Trim(), delimetr);

	 return str;
}


AnsiString TForm1::table_head(column size_column)
{
	AnsiString str;
	AnsiString delimetr = '|';  		// Set defult delimetr

	str += table_head(size_column, delimetr); 
	
	return str;
}


AnsiString TForm1::table_head(column size_column, AnsiString delimetr)
{
	AnsiString str;

	str += delimetr;

	str += table_element(size_column.c_0, AnsiString("#"), delimetr);                   //
	str += table_element(size_column.c_1, AnsiString("Name"), delimetr);                // szExeFile
	str += table_element(size_column.c_2, AnsiString("PID"), delimetr);                 // th32ProcessID
	str += table_element(size_column.c_3, AnsiString("PPID"), delimetr);                // th32ParentProcessID
	str += table_element(size_column.c_4, AnsiString("Thread"), delimetr);              // cntThreads
	str +=  table_element(size_column.c_5, AnsiString("pcPriClassBase"), delimetr);     // pcPriClassBase 
	
	return str;
}
