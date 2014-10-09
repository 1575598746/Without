#ifndef REGISTER_DIALOG_H
#define REGISTER_DIALOG_H

#include <QDialog>
#include <QButtonGroup>
#include <QSqlQuery>

namespace Ui {
class register_Dialog;
}

class register_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit register_Dialog(QWidget *parent = 0);
    ~register_Dialog();
    
private slots:
    void on_commit_pushButton_clicked();

    void checkName();

    void checkPassword();

    void on_close_pushButton_clicked();

//    void checkID();

//    void checkSameID();

    void on_getBack_pushButton_clicked();

private:
    Ui::register_Dialog *ui;
    QButtonGroup BG;

    QString name;
    QString password;
    QString IDnumber;
};

#endif // REGISTER_DIALOG_H
