#include "manager_dialog.h"
#include "ui_manager_dialog.h"

manager_Dialog::manager_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manager_Dialog)
{
    ui->setupUi(this);


}

manager_Dialog::~manager_Dialog()
{
    delete ui;
}

void manager_Dialog::on_insert_pushButton_clicked()
{

}

void manager_Dialog::on_inStorage_pushButton_clicked()
{
    instorage_dialog.setWindowFlags(Qt::FramelessWindowHint);
    instorage_dialog.exec();
}



void manager_Dialog::on_back_pushButton_clicked()
{
    this->close();
}
