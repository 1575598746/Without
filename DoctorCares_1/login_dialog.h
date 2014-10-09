#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

#include <QDialog>
#include <QButtonGroup>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QTime>

#include "loginqmessage_dialog.h"
#include "instorage_dialog.h"
#include "operator_dialog.h"

namespace Ui {
class LogIn_Dialog;
}

class LogIn_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LogIn_Dialog(QWidget *parent = 0);
    ~LogIn_Dialog();
    
private slots:
    void on_LogIn_pushButton_clicked();

    void on_Close_pushButton_clicked();

    void clockChange();

    void on_register_pushButton_clicked();

    void on_forget_pushButton_clicked();

    void on_Query_pushButton_clicked();

private:
    Ui::LogIn_Dialog *ui;
    QButtonGroup BG;
    inStorage_Dialog *instorage_dialog;
    operator_Dialog *operator_dialog;
    QTimer *timer;

};

#endif // LOGIN_DIALOG_H
