#include "register_dialog.h"
#include "ui_register_dialog.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>


register_Dialog::register_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::register_Dialog)
{
    ui->setupUi(this);

    QFile file(":/qstylesheet.qss");
        if(file.open(QFile::ReadOnly))
        {
            QTextStream filetext(&file);
            QString stylesheet = filetext.readAll();
            ui->commit_pushButton->setStyleSheet(stylesheet);
            //ui->close_pushButton->setStyleSheet(stylesheet);
            ui->getBack_pushButton->setStyleSheet(stylesheet);
        }

        ui->userName_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->role_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->passWord_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->again_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->ID_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->remindName_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->remindAgain_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->remindID_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->remindEmpty_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->sameID_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->manager_radioButton->setStyleSheet("QRadioButton{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->operator_radioButton->setStyleSheet("QRadioButton{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");




    BG.addButton(ui->manager_radioButton, 0);

    BG.addButton(ui->operator_radioButton, 1);


    ui->manager_radioButton->setChecked(true);

    ui->operator_radioButton->setChecked(true);

    connect(ui->again_lineEdit,SIGNAL(editingFinished()),this,SLOT(checkPassword()));
    connect(ui->name_lineEdit,SIGNAL(editingFinished()),this,SLOT(checkName()));
//    connect(ui->ID_lineEdit,SIGNAL(editingFinished()),this,SLOT(checkID()));
//    connect(ui->ID_lineEdit,SIGNAL(editingFinished()),this,SLOT(checkSameID()));
}

register_Dialog::~register_Dialog()
{
    delete ui;
}

void register_Dialog::on_commit_pushButton_clicked()
{
    QSqlQuery query;
    QSqlQuery query1;
    QString sql = "select * from UserID where IDnumber = '";
    sql += ui->ID_lineEdit->text() + "'";
    query1.exec(sql);
    QString string = "insert into UserID values (";
    name = ui->name_lineEdit->text();
    password = ui->passWord_lineEdit->text();
    IDnumber = ui->ID_lineEdit->text();
    if(ui->name_lineEdit->text().isEmpty() || ui->passWord_lineEdit->text().isEmpty() || ui->again_lineEdit->text().isEmpty() || ui->ID_lineEdit->text().isEmpty()){
        ui->remindEmpty_label->setText("以上均为必填！");
    }
    else if(ui->ID_lineEdit->text().length() != 18){
        ui->remindEmpty_label->setText("");
        ui->remindID_label->setText("请输入正确的身份证号码！");
    }
    else if(query1.next()){
        ui->remindEmpty_label->setText("");
        ui->remindID_label->setText("");
        ui->sameID_label->setText("此身份证号码已注册，请点击忘记密码！");
    }
    else{
        ui->remindEmpty_label->setText("");
        ui->remindID_label->setText("");
        ui->sameID_label->setText("");
        int BGcheck = BG.checkedId();
        switch(BGcheck){
        case 0:
            string += "'manager','" + name + "','" + password + "','" + IDnumber + "')";
            break;
        case 1:
            string += "'operator','" + name + "','" + password + "','" + IDnumber + "')";
            break;
        default:
            break;
        }
      //qDebug
        qDebug()<<string;
        query.exec(string);

            QString test = "select * from UserID where Username = '";
            test += name + "'";
          //qDebug
            qDebug()<<test;
            query.exec(test);
            if(query.next()){
                ui->remindEmpty_label->setText("注册成功！");
              //qDebug
                qDebug()<<"注册成功";
            }
        }
}

void register_Dialog::checkName()
{
    QSqlQuery query;
    QString sql = "";
    QString stringName = ui->name_lineEdit->text();
    sql += "select * from UserID where Username = '";
    sql += stringName + "'";
    query.exec(sql);
    if(query.next()){
        ui->remindName_label->setText("已使用的用户名！");
    }
    else{
        ui->remindName_label->setText("");
    }
}

void register_Dialog::checkPassword()
{
    if(ui->passWord_lineEdit->text() != ui->again_lineEdit->text()){
        ui->remindAgain_label->setText("两次输入不同！");
    }
    else{
        ui->remindAgain_label->setText("");
    }
}

//void register_Dialog::checkID()
//{
//    if(ui->ID_lineEdit->text().length() != 18){
//        ui->remindID_label->setText("请输入正确的身份证号码！");
//    }
//    else{
//        ui->remindID_label->setText("");
//    }
//}

//void register_Dialog::checkSameID()
//{
//    QSqlQuery query;
//    QString sql = "select * from Diary where IDnumber = '";
//    sql += ui->ID_lineEdit->text() + "'";
//    query.exec(sql);
//    if(query.next()){
//        ui->sameID_label->setText("此身份证号码已注册，请点击忘记密码！");
//    }
//    else{
//        ui->sameID_label->setText("");
//    }
//}

void register_Dialog::on_close_pushButton_clicked()
{
    this->close();
}

void register_Dialog::on_getBack_pushButton_clicked()
{
    this->close();
}
