#ifndef DETAIL_DIALOG_H
#define DETAIL_DIALOG_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class detail_Dialog;
}

class detail_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit detail_Dialog(QWidget *parent = 0, QString approval_number = "");
    ~detail_Dialog();
    
private slots:
    void on_save_pushButton_clicked();

    void on_comfirm_pushButton_clicked();

    void on_close_pushButton_clicked();

private:
    Ui::detail_Dialog *ui;

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

#endif // DETAIL_DIALOG_H
