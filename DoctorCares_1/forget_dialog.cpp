#include "forget_dialog.h"
#include "ui_forget_dialog.h"
#include <QSqlQuery>
#include <QDebug>
#include <QFile>
#include <QTextStream>

forget_Dialog::forget_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forget_Dialog)
{
    ui->setupUi(this);

    //��ʽ
    QFile file(":/qstylesheet.qss");
        if(file.open(QFile::ReadOnly))
        {
            QTextStream filetext(&file);
            QString stylesheet = filetext.readAll();
            ui->comfirm_pushButton->setStyleSheet(stylesheet);
            //ui->getBack_pushButton->setStyleSheet(stylesheet);
        }

        ui->label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->IDnumber_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->passwordRe_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        //��ʽ


}

forget_Dialog::~forget_Dialog()
{
    delete ui;
}

void forget_Dialog::on_comfirm_pushButton_clicked()
{
    stringID = ui->ID_lineEdit->text();
    if(stringID.length() == 0 || stringID.length() != 18){
        ui->passwordRe_label->setText("����д��ȷ�����֤�ţ�");
    }
    else{
        ui->passwordRe_label->setText("");
        QSqlQuery query;
        QString string = "select * from UserID where IDnumber = '";
        string += stringID + "'";
        query.exec(string);
        if(!query.next()){
            ui->passwordRe_label->setText("�����֤����δ��ע�ᣬ�뷵��ע��ҳ�棡");
        }
        else{
            ui->passwordRe_label->setText("");
            int length = stringID.length();
            QString password = stringID.mid(length-6,6);
          //qDebug
            qDebug()<<password;
            QString sql = "update UserID set Password = '";
            sql += password + "' where IDnumber = '";
            sql += stringID + "'";
          //qDebug
            qDebug()<<sql;
            query.exec(sql);
            ui->passwordRe_label->setText("��������Ѹ���Ϊ���֤�ź���λ��");
        }

    }

}

void forget_Dialog::on_getBack_pushButton_clicked()
{
    this->close();
}
