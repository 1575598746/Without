#ifndef INSTORAGE_DIALOG_H
#define INSTORAGE_DIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlRecord>
#include <QListWidgetItem>
#include <QTextCodec>
#include <QTableWidgetItem>
#include <QCompleter>
#include <QModelIndexList>
#include <QTimer>
#include <QTime>

#include "add_dialog.h"
#include "loginqmessage_dialog.h"
#include "insertqmessage_dialog.h"
#include "insert_dialog.h"


namespace Ui {
class inStorage_Dialog;
}




class inStorage_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit inStorage_Dialog(QWidget *parent = 0);
    void init_inStorage_tableWidget();
    void init_ComboBoxes();
    QSqlQueryModel *model;
    ~inStorage_Dialog();

signals:
    void sendRefreshSignal(int);
    
private slots:
    void on_back_pushButton_clicked();

    void on_select_pushButton_clicked();

    void inStorage_tableWidget_item_click();

    void on_add_pushButton_clicked();

    void on_batchAdd_pushButton_clicked();

    void on_refresh_pushButton_clicked();

    void receiveSignal(bool);

    void refresh(int);

    void showTablewidget(int);

    void on_out_pushButton_clicked();

    void on_batchOut_pushButton_clicked();

    void clockChange();

//    void checkBoxChanged(int, int);

    void on_moveOut_pushButton_clicked();

    void on_checkDiary_pushButton_clicked();

    void on_delete_pushButton_clicked();

    void receiveDeleteSig(bool);

    void on_detail_pushButton_clicked();

    void on_showAll_pushButton_clicked();

private:
    Ui::inStorage_Dialog *ui;

    QSqlQueryModel *nameModel;
    QSqlQueryModel *categoryModel;
    QSqlQueryModel *approval_numberModel;
    QSqlQueryModel *manufacturerModel;

    Add_Dialog *add_dialog;
    Add_Dialog *batchAdd_dialog;

    struct part *head;
    struct part *sql;
    struct part *p;
    struct part *name;
    struct part *manu;
    struct part *cate;
    struct part *appr;
    struct part *start;
    struct part *end;

    int curRow;

    QString StringName;
    QString StringCategory;
    QString StringApproval_number;
    QString StringManufacturer;
    QString StringInventory;

//    QTableWidgetItem *checkedBox;
    QTableWidgetItem *nameItem;
    QTableWidgetItem *categoryItem;
    QTableWidgetItem *approval_numberItem;
    QTableWidgetItem *manufacturerItem;
    QTableWidgetItem *inventoryItem;

    QStringList nameList;
    QStringList categoryList;
    QStringList approval_numberList;
    QStringList manufacturerList;
    QStringList inventoryList;

    QCompleter *nameCompleter;
    QCompleter *categoryCompleter;
    QCompleter *approval_numberCompleter;
    QCompleter *manufacturerCompleter;

    int rowNum;
    int IDNum;
    int InventoryNum;

    int modelFlag;
    int addFlag;
    int outFlag;
    int operationFlag;
    int *addOperationFlag1;
    int *addOperationFlag2;

    int *ID;
    int *Inventory;
    int *tempID;
    int *tempInventory;
    int *batchID;
    int *batchInventory;

    int *equalRow;

    QTimer *timer;
};

struct part{
 char *s;
 struct part *prior1;
 struct part *prior2;
 struct part *next1;
 struct part *next2;
};



#endif // INSTORAGE_DIALOG_H
