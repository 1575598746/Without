#ifndef CUSTOMER_DIALOG_H
#define CUSTOMER_DIALOG_H

#include <QDialog>
#include <QTableWidgetItem>
#include <QSqlQueryModel>
#include <QCompleter>

namespace Ui {
class customer_Dialog;
}

class customer_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit customer_Dialog(QWidget *parent = 0);
    void init_tableWidget();
    void showTablewidget(int);
    void init_ComboBoxes();
    QSqlQueryModel *model;
    ~customer_Dialog();
    
signals:
    void sendRefreshSignal(int);

private slots:
    void on_query_pushButton_clicked();

    void on_close_pushButton_clicked();

    void on_detail_pushButton_clicked();

    void tableWidget_item_click();

    void refresh(int);

private:
    Ui::customer_Dialog *ui;
    int curRow;
    int rowNum;

    QSqlQueryModel *nameModel;
    QSqlQueryModel *categoryModel;
    QSqlQueryModel *package_insertModel;
    QSqlQueryModel *manufacturerModel;

    struct part1 *head;
    struct part1 *sql;
    struct part1 *p;
    struct part1 *name;
    struct part1 *manu;
    struct part1 *cate;
    struct part1 *pack;
    struct part1 *start;
    struct part1 *end;

    QString StringName;
    QString StringCategory;
    QString StringPackage_insert;
    QString StringManufacturer;

    QTableWidgetItem *nameItem;
    QTableWidgetItem *categoryItem;
    QTableWidgetItem *package_insertItem;
    QTableWidgetItem *manufacturerItem;

    QStringList nameList;
    QStringList categoryList;
    QStringList package_insertList;
    QStringList manufacturerList;

    QCompleter *nameCompleter;
    QCompleter *categoryCompleter;
    QCompleter *package_insertCompleter;
    QCompleter *manufacturerCompleter;
};

struct part1{
 char *s;
 struct part1 *prior1;
 struct part1 *prior2;
 struct part1 *next1;
 struct part1 *next2;
};

#endif // CUSTOMER_DIALOG_H
