#ifndef CHECKDIARY_DIALOG_H
#define CHECKDIARY_DIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QTableWidgetItem>

namespace Ui {
class CheckDiary_Dialog;
}

class CheckDiary_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CheckDiary_Dialog(QWidget *parent = 0);
    void init_tableWidget();
    ~CheckDiary_Dialog();
    QString dateString;
    
private slots:
    void on_close_pushButton_clicked();

    void on_query_pushButton_clicked();

    void mm_remind();

    void dd_remind();

    void on_ascend_pushButton_clicked();

    void on_descend_pushButton_clicked();

    void on_undone_pushButton_clicked();

    void on_done_pushButton_clicked();

    void on_in_pushButton_clicked();

    void on_out_pushButton_clicked();

private:
    Ui::CheckDiary_Dialog *ui;

    QSqlQueryModel *model;
    QSqlQueryModel *dateModel;

    int dateModelFlag;

    int rowNum;
    int dateRowNum;

    int *ID;
    QString tempID;

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

    void showTablewidget(QSqlQueryModel *a, int i);
};

#endif // CHECKDIARY_DIALOG_H
