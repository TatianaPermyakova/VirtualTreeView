//---------------------------------------------------------------------------

#include <vcl.h>
#include "Form_main.h"
#include "sqlite3.h"
#include <string.h>
#include <cstdlib>
#include <vector>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma hdrstop
#pragma resource "*.dfm"
#pragma link "VirtualTrees"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	VirtualStringTree1->NodeDataSize = sizeof(MyBDStruct);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	VirtualStringTree1->NodeDataSize = sizeof(MyBDStruct);
}
//---------------------------------------------------------------------------

//Создаем обработчик события VSTGetText для отображения содержимого таблицы:
void __fastcall TForm1::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{        if(!Node)	return;
MyBDStruct *nodeData = (MyBDStruct*)Sender->GetNodeData(Node);
switch(Column)
{
	case 0: CellText = nodeData -> id; break;
	case 1: CellText = nodeData -> url; break;
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	VirtualStringTree1 -> Clear();
	// Открываем базу данных
	sqlite3* Database = 0;    // Объявляем переменную
	int open = sqlite3_open("History", &Database);

	if (Database == NULL)
	{
		Label1 -> Caption = "ERROR: failed to open Database";
		return;
	}

	const char * Get_records = "SELECT * from urls";

	// Шаг 1 (подготовка запроса)
	const char *errmsgGetRec;
	sqlite3_stmt *pStatementGetRec;
	int resultCheckRec = sqlite3_prepare_v2(Database, Get_records,-1,&pStatementGetRec,NULL);
	if(resultCheckRec != SQLITE_OK)
	{
		errmsgGetRec = sqlite3_errmsg(Database);
		Label1 -> Caption = errmsgGetRec;
	}

		while(sqlite3_step(pStatementGetRec) != SQLITE_DONE)
	{
			//int i;
			PVirtualNode entryNode = VirtualStringTree1 -> AddChild(VirtualStringTree1 -> RootNode);
			MyBDStruct *nodeData = (MyBDStruct*)VirtualStringTree1 -> GetNodeData(entryNode);

				nodeData -> id = sqlite3_column_int(pStatementGetRec, 0) ;
				nodeData -> url  = (wchar_t*)sqlite3_column_text16(pStatementGetRec, 2);


	}

	// Шаг 3 (завершение обработки запроса)
	sqlite3_finalize(pStatementGetRec);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTree1FreeNode(TBaseVirtualTree *Sender, PVirtualNode Node)

{
	MyBDStruct *nodeData = (MyBDStruct*)Sender -> GetNodeData(Node);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
	int selectedNodeID = NULL;
	PVirtualNode selectedNode = VirtualStringTree1 -> FocusedNode;
	selectedNodeID = selectedNode -> Index;

	int Count = VirtualStringTree1->SelectedCount;
	std::vector<PVirtualNode> selectedNodes;
	std::vector<MyBDStruct *> nodeData;
	std::vector<int> id;

	for (int i = 0; i < Count; i++)
	{
		  if (i==0) selectedNodes.push_back(VirtualStringTree1 -> GetFirstSelected());

		  else selectedNodes.push_back(VirtualStringTree1 -> GetNextSelected(selectedNodes[i-1] ));
		  nodeData.push_back((MyBDStruct *)VirtualStringTree1 -> GetNodeData(selectedNodes[i]));
		  id.push_back(nodeData[i]->id);
	}


	if (Count>0)
	{
		PVirtualNode selectedNext = VirtualStringTree1 -> GetNext(selectedNodes[Count-1]);
		VirtualStringTree1 -> AddToSelection(selectedNext);
		sqlite3* Database;
		sqlite3_open("History" ,&Database);

			for (int i = 0; i < Count; i++)
			{
				VirtualStringTree1 -> DeleteNode(selectedNodes [i]);

				char BUFF [20];
				itoa(id[i], BUFF, 20);

				sqlite3_stmt *pStatementDelRow;

				char delete_row [50] = "DELETE FROM urls WHERE id=";
				strcat(delete_row, BUFF);
				int result = sqlite3_prepare_v2(Database, delete_row, -1, &pStatementDelRow, NULL);

				result = sqlite3_step(pStatementDelRow);
				if(result != SQLITE_DONE)
				{
				   const char * errmsgDelRow = sqlite3_errmsg(Database);
				   Label1 -> Caption = errmsgDelRow;
				}
				sqlite3_finalize(pStatementDelRow);
			}

		sqlite3_close(Database);
		Label1 -> Caption = "Rows deleted";
	}

	}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
		VirtualStringTree1->BeginUpdate();

		sqlite3* Database;
		sqlite3_open("History" ,&Database);

		const char * drop_table = "DELETE FROM urls";
		//Шаг 1 (подготовка запроса)
		const char *errmsgDropTable;
		sqlite3_stmt *pStatementDropTable;

		int result = sqlite3_prepare_v2(Database,drop_table,-1,&pStatementDropTable,NULL); // UTF-8

		if(result != SQLITE_OK)
		{
			errmsgDropTable = sqlite3_errmsg(Database);
			Label1 -> Caption = errmsgDropTable;
		}

		//Шаг 2 (выполнение запроса)
		result = sqlite3_step(pStatementDropTable);
		if(result == SQLITE_DONE)
		{
			Label1 -> Caption = "Drop table - DONE!";
		}

		//Шаг 3 (завершение обработки запроса)
		sqlite3_finalize(pStatementDropTable);

		VirtualStringTree1->Clear();
		VirtualStringTree1->EndUpdate();

		sqlite3_close(Database);
}
//---------------------------------------------------------------------------

