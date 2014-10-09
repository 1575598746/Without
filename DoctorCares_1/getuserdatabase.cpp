#include "getuserdatabase.h"

getUserDatabase::getUserDatabase()
{
}

bool getUserDatabase::createConnection(QString dbname)
{
    db1 = QSqlDatabase::addDatabase("QSQLITE");
    db1.setDatabaseName(dbname);
    if(!db1.open())
    {
     QMessageBox::critical(0,"cannot open database","Unabel to connect",QMessageBox::Cancel);
     return false;
    }
    return true;
}

void getUserDatabase::createTables()
{

}

void getUserDatabase::createDatabase()
{

}

