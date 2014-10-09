#ifndef GETUSERDATABASE_H
#define GETUSERDATABASE_H

#include <QSqlDatabase>
#include <QMessageBox>

class getUserDatabase
{
public:
    getUserDatabase();
    bool createConnection(QString daname);
    void createTables();
    void createDatabase();
private:
    QSqlDatabase db1;
};

#endif // GETUSERDATABASE_H
