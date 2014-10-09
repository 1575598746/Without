#ifndef INSERT_DIALOG_H
#define INSERT_DIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include "loginqmessage_dialog.h"

namespace Ui {
class insert_Dialog;
}

class insert_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit insert_Dialog(QWidget *parent = 0, QString a = "", QString b = "", QString c = "", QString d = "");
    ~insert_Dialog();

signals:
    void sendSignal(bool);
    
private slots:
    void on_generateID_pushButton_clicked();

    void on_close_pushButton_clicked();

    void on_comfirm_pushButton_clicked();

    void change();

    void receiveSignal(bool);

private:
    Ui::insert_Dialog *ui;
    QSqlQueryModel *model;
    //QSqlQuery query;

    QString ID;
    QString name;
    QString manufacturer;
    QString approval_number;
    QString cate;
    QString OTC;
    QString dosage_form;
    QString package_insert;
    QString inventory;

    QString str;
    QString testStr;
};

#endif // INSERT_DIALOG_H
