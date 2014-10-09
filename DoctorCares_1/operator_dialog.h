#ifndef OPERATOR_DIALOG_H
#define OPERATOR_DIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QTableWidgetItem>
#include <QSqlQuery>

namespace Ui {
class operator_Dialog;
}

class operator_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit operator_Dialog(QWidget *parent = 0);
    void init_tableWidget();
    ~operator_Dialog();
    QString dateString;

signals:
    void refreshSignal(int);
    
private slots:
    void showTablewidget(int);

    void on_query_pushButton_clicked();

    void mm_remind();

    void dd_remind();

    void on_close_pushButton_clicked();

    void on_done_pushButton_clicked();

    void tableWidget_item_click();

    void receiveRefreshSig(int);

private:
    Ui::operator_Dialog *ui;
    QSqlQueryModel *model;
    QSqlQuery query;
    int rowNum;
    int curRow;

    int dateModelFlag;

    QString StringID;
    QString StringName;
    QString StringManufacturer;
    QString StringApproval_number;
    QString StringValue;
    QString StringOperate;
    QString StringStatus;
    QString StringDate;

    QTableWidgetItem *IDItem;
    QTableWidgetItem *nameItem;
    QTableWidgetItem *manufacturerItem;
    QTableWidgetItem *approval_numberItem;
    QTableWidgetItem *valueItem;
    QTableWidgetItem *operateItem;
    QTableWidgetItem *statusItem;
    QTableWidgetItem *dateItem;

    QString dateYear;
    QString dateMonth;
    QString dateDay;

    QString year;
    QString month;
    QString day;
};

#endif // OPERATOR_DIALOG_H
