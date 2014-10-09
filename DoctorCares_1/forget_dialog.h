#ifndef FORGET_DIALOG_H
#define FORGET_DIALOG_H

#include <QDialog>

namespace Ui {
class forget_Dialog;
}

class forget_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit forget_Dialog(QWidget *parent = 0);
    ~forget_Dialog();
    
private slots:
    void on_comfirm_pushButton_clicked();

    void on_getBack_pushButton_clicked();

private:
    Ui::forget_Dialog *ui;

    QString stringID;
};

#endif // FORGET_DIALOG_H
