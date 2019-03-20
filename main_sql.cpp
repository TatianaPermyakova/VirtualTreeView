#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <iostream>
#include <stdio.h>

#include "sqlite3.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{

sqlite3* Database = 0; // Объявляем переменную

// Открываем базу данных
int open = sqlite3_open("Databases.db", &Database);

cout << open << endl;
system ("PAUSE");

const char * Table_list = "select * from sqlite_master where type = 'table'";

// Шаг 1 (подготовка запроса)
const char *errmsgCheck;
sqlite3_stmt *pStatementCheck;
int resultCheck = sqlite3_prepare_v2(Database, Table_list,-1,&pStatementCheck,NULL);
if(resultCheck != SQLITE_OK)
{
	errmsgCheck = sqlite3_errmsg(Database);
	cout << errmsgCheck;
}

// Смотрим какие есть таблицы в БД
   cout << "Table list:" << endl;
while(true)
{
	resultCheck = sqlite3_step(pStatementCheck);
	if(resultCheck != SQLITE_ROW)   {
	cout<< "last record" << endl;
	break;
	}

	unsigned char *n = (unsigned char *)sqlite3_column_text(pStatementCheck, 2 /*номер столбца*/);
	cout << n << endl;
}
system ("PAUSE");
// Шаг 3 (завершение обработки запроса)
sqlite3_finalize(pStatementCheck);


// Создаем свою таблицу
const char * create_table = " CREATE TABLE IF NOT EXISTS colleagues (ID INTEGER NOT NULL, first_name TEXT NOT NULL, last_name TEXT NOT NULL);";
//  const char * create_table = " DROP TABLE colleagues;";
// Шаг 1 (подготовка запроса)
const char *errmsgCreate;
sqlite3_stmt *pStatementCreate;
int resultCreate = sqlite3_prepare_v2(Database, create_table,-1,&pStatementCreate,NULL);
if(resultCreate != SQLITE_OK)
{
	errmsgCreate = sqlite3_errmsg(Database);
	cout << errmsgCreate << endl;
}

// Создание таблицы

resultCreate = sqlite3_step(pStatementCreate);
if(resultCreate != SQLITE_OK)
{
	cout << "Table created" << endl;
}

system ("PAUSE");
// Шаг 3 (завершение обработки запроса)
sqlite3_finalize(pStatementCreate);

// Заполняем таблицу данными
const char * create_records = " INSERT INTO COLLEAGUES VALUES (0,Ivan,Ivanov);";

// Шаг 1 (подготовка запроса)
const char *errmsgCreateRec;
sqlite3_stmt *pStatementCreateRec;
int resultCreateRec = sqlite3_prepare_v2(Database, create_records,-1,&pStatementCreateRec,NULL);
if(resultCreateRec != SQLITE_OK)
{
	errmsgCreateRec = sqlite3_errmsg(Database);
	cout << errmsgCreateRec << endl;
}

// Заполнение таблицы

resultCreateRec = sqlite3_step(pStatementCreateRec);
if(resultCreateRec != SQLITE_OK)
{
	cout << "Records created" << endl;
}

system ("PAUSE");

// Шаг 3 (завершение обработки запроса)
sqlite3_finalize(pStatementCreateRec);

const char * Check_records_1 = "SELECT * from colleagues";

// Шаг 1 (подготовка запроса)
const char *errmsgCheckRec;
sqlite3_stmt *pStatementCheckRec;
int resultCheckRec = sqlite3_prepare_v2(Database, Check_records_1,-1,&pStatementCheckRec,NULL);
if(resultCheckRec != SQLITE_OK)
{
	errmsgCheckRec = sqlite3_errmsg(Database);
	cout << errmsgCheckRec << endl;
}

// Смотрим какие есть таблицы в БД
   cout << "colleagues:" << endl;
while(true)
{
	resultCheck = sqlite3_step(pStatementCheckRec);
	if(resultCheckRec != SQLITE_ROW)   {
	cout<< "last record" << endl;
	break;
	}

	unsigned char *n = (unsigned char *)sqlite3_column_text(pStatementCheckRec, 1 /*номер столбца*/);
	cout << n << endl;
}
system ("PAUSE");
// Шаг 3 (завершение обработки запроса)
sqlite3_finalize(pStatementCheckRec);

//const char * Table_check = "select * from colleagues;";
//
//// Шаг 1 (подготовка запроса)
//const char *errmsgTableCheck1;
//sqlite3_stmt *pStatementTableCheck1;
//int resultTableCheck1 = sqlite3_prepare_v2(Database, Table_check,-1,&pStatementTableCheck1,NULL);
//if(resultTableCheck1 != SQLITE_OK)
//{
//	errmsgTableCheck1 = sqlite3_errmsg(Database);
//	cout << errmsgTableCheck1;
//}
//
//// Выводим содержание таблицы
//   cout << "colleagues:" << endl;
//while(true)
//{
//	resultTableCheck1 = sqlite3_step(pStatementTableCheck1);
//	if(resultTableCheck1 != SQLITE_ROW)   {
//	cout<< "last record" << endl;
//	break;
//	}
//
//	unsigned char *n = (unsigned char *)sqlite3_column_text(pStatementTableCheck1, 1 /*номер столбца*/);
//	cout << n << endl;
//}
//system ("PAUSE");
//// Шаг 3 (завершение обработки запроса)
//sqlite3_finalize(pStatementTableCheck1);
//
//
//// Удаляем строку из таблицы
//
//const char * delete_row = "DELETE FROM colleague WHERE ID = 0;";
//
//// Шаг 1 (подготовка запроса)
//const char *errmsgDelRow;
//sqlite3_stmt *pStatementDelRow;
//int resultDelRow = sqlite3_prepare_v2(Database, create_table,-1,&pStatementDelRow,NULL);
//if(resultDelRow != SQLITE_OK)
//{
//	errmsgDelRow = sqlite3_errmsg(Database);
//	cout << errmsgDelRow;
//}
//
//// Удаление строки
//
//resultDelRow = sqlite3_step(pStatementDelRow);
//if(resultDelRow != SQLITE_OK)
//{
//	cout << "Row deleted" << endl;
//}
//
//system ("PAUSE");
//
//// Шаг 3 (завершение обработки запроса)
//sqlite3_finalize(pStatementDelRow);

// Закрываем базу данных:
int close = sqlite3_close(Database);

cout << close << endl;
system ("PAUSE");
}


