#ifndef MANAGER_DIALOG_H
#define MANAGER_DIALOG_H

#include <QDialog>
#include "instorage_dialog.h"

namespace Ui {
class manager_Dialog;
}

class manager_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit manager_Dialog(QWidget *parent = 0);
    ~manager_Dialog();
    
private slots:
    void on_insert_pushButton_clicked();

    void on_inStorage_pushButton_clicked();

    void on_back_pushButton_clicked();

private:
    Ui::manager_Dialog *ui;

    inStorage_Dialog instorage_dialog;

};

#endif // MANAGER_DIALOG_H
