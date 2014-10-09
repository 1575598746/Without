#ifndef ADD_DIALOG_H
#define ADD_DIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>

#include "loginqmessage_dialog.h"

namespace Ui {
class Add_Dialog;
}

class Add_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Add_Dialog(QWidget *parent = 0, int ID[] = NULL, int Inventory[] = NULL, int rowNum = -1, int operationFlag = -1, int *addOperationFlag = NULL);
    ~Add_Dialog();

private slots:
    void on_quit_pushButton_clicked();

    void on_confirm_pushButton_clicked();

    void on_done_pushButton_clicked();

    void on_revocation_pushButton_clicked();

    void remind();

private:
    Ui::Add_Dialog *ui;

    int *IDNumber;
    int *INNumber;
    int *batchIDNumber;
    int *batchINNumber;

    int InventoryNumber;
    int *batchInventoryNumber;
    int flag;
    int rowNumFlag;
    int operation;
    int *addOperation1;
    int *addOperation2;

    int equalNum;
    int minIN;
    int minID;
    int *diaryID;

    QSqlQueryModel *model;
    QSqlQuery query;
    QString update;
    QString tempUpdate;
    QString StringIN;
    QString StringID;
};

#endif // ADD_DIALOG_H
