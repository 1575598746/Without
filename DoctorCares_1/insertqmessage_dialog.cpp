#include "insertqmessage_dialog.h"
#include "ui_insertqmessage_dialog.h"
#include <QFile>
#include <QTextStream>

insertQMessage_Dialog::insertQMessage_Dialog(QWidget *parent, QString str) :
    QDialog(parent),
    ui(new Ui::insertQMessage_Dialog)
{
    ui->setupUi(this);

    //样式
    QFile file(":/qstylesheet.qss");
        if(file.open(QFile::ReadOnly))
        {
            QTextStream filetext(&file);
            QString stylesheet = filetext.readAll();
            ui->comfirm_pushButton->setStyleSheet(stylesheet);
            ui->negative_pushButton->setStyleSheet(stylesheet);
        }

        ui->insertQMessage_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
             //样式


    QString message = str;
    ui->insertQMessage_label->setText(message);
}

insertQMessage_Dialog::~insertQMessage_Dialog()
{
    delete ui;
}

void insertQMessage_Dialog::on_comfirm_pushButton_clicked()
{
    emit sendSignal(1);
    this->close();
}

void insertQMessage_Dialog::on_negative_pushButton_clicked()
{
    this->close();
}
