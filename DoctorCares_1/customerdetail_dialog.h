#ifndef CUSTOMERDETAIL_DIALOG_H
#define CUSTOMERDETAIL_DIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlRecord>

namespace Ui {
class customerDetail_Dialog;
}

class customerDetail_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit customerDetail_Dialog(QWidget *parent = 0, QString approval_number = "");
    ~customerDetail_Dialog();
    
private slots:
    void on_getBack_pushButton_clicked();

private:
    Ui::customerDetail_Dialog *ui;

    QSqlQueryModel *model;

    QString sql;

    QString app_number;

    QString stringName;
    QString stringOTC;
    QString stringApp;
    QString stringCate;
    QString stringDosa;
    QString stringPack;
    QString stringManu;
    QString stringInve;
};

#endif // CUSTOMERDETAIL_DIALOG_H
