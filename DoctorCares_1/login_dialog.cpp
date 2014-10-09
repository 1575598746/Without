#include "login_dialog.h"
#include "ui_login_dialog.h"

#include "register_dialog.h"
#include "forget_dialog.h"
#include "customer_dialog.h"
#include "operator_dialog.h"
#include <QFile>
#include <QTextStream>


LogIn_Dialog::LogIn_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogIn_Dialog)
{
    ui->setupUi(this);

    QFile file(":/qstylesheet.qss");
        if(file.open(QFile::ReadOnly))
        {
            QTextStream filetext(&file);
            QString stylesheet = filetext.readAll();
            //ui->Close_pushButton->setStyleSheet(stylesheet);
            ui->Query_pushButton->setStyleSheet(stylesheet);
            ui->forget_pushButton->setStyleSheet(stylesheet);
            ui->LogIn_pushButton->setStyleSheet(stylesheet);
            ui->register_pushButton->setStyleSheet(stylesheet);

        }
        ui->Username_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->Password_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");

        ui->Manager_radioButton->setStyleSheet("QRadioButton{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->Operator_radioButton->setStyleSheet("QRadioButton{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");



    ui->Username_lineEdit->setPlaceholderText("Username");
    ui->Username_lineEdit->setFocus();
    ui->Password_lineEdit->setPlaceholderText("Password");
    ui->Password_lineEdit->setFocus();

    ui->lcdNumber->setNumDigits(8);						//��ʾ�˸����֣�Ĭ������ʾ5������
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);	//�����ɫ��Ĭ���ǰ�ɫ��
    ui->lcdNumber->display(QTime::currentTime().toString("hh:mm:ss"));	//���ø�ʽ������������ʽ��

    instorage_dialog = NULL;

    timer = new QTimer(this);

    BG.addButton(ui->Manager_radioButton, 0);

    BG.addButton(ui->Operator_radioButton, 1);

    ui->Manager_radioButton->setChecked(true);

    ui->Operator_radioButton->setChecked(true);

    connect(timer,SIGNAL(timeout()),this,SLOT(clockChange()));
    timer->start(1000);
}

LogIn_Dialog::~LogIn_Dialog()
{
    delete ui;
}

void LogIn_Dialog::on_LogIn_pushButton_clicked()
{
    QString Username = ui->Username_lineEdit->text();
    QString Password = ui->Password_lineEdit->text();
    QString sql ="";
    int BGcheck = BG.checkedId();
    QSqlQuery query;

    if(ui->Username_lineEdit->text().isEmpty()||ui->Password_lineEdit->text().isEmpty())
    {
        loginQmessage_Dialog *a = new loginQmessage_Dialog(0,tr("��Ч�����룡"));
        //a->setWindowFlags(Qt::FramelessWindowHint);
        a->setWindowTitle("��ʾ");
        a->exec();
    }
    else
    {
        switch(BGcheck)
        {
        case 0:
                sql += "select * from UserID where Username = '";
                sql += Username + "' and UserStatus = 'manager'";
                query.exec(sql);
                if(query.next()){
                    sql = "";
                    sql += "select * from (select Password from UserID where Username = '";
                    sql += Username + "' and UserStatus = 'manager') T where Password = '";
                    sql += Password + "'";
                    query.exec(sql);
                    if(query.next()){
                        delete instorage_dialog;
                        instorage_dialog = new inStorage_Dialog();
                        //instorage_dialog->setWindowFlags(Qt::FramelessWindowHint);
                        instorage_dialog->setWindowTitle("����Ա");
                        instorage_dialog->exec();
                    }
                    else
                    {
                        loginQmessage_Dialog *a = new loginQmessage_Dialog(0,tr("�����������"));
                        //a->setWindowFlags(Qt::FramelessWindowHint);
                        a->setWindowTitle("��ʾ");
                        a->exec();
                    }
                }
                else
                {
                    loginQmessage_Dialog *a = new loginQmessage_Dialog(0,tr("�޶�ӦȨ�޵��û�����"));
                    //a->setWindowFlags(Qt::FramelessWindowHint);
                    a->setWindowTitle("��ʾ");
                    a->exec();
                }
        break;
        case 1:
            sql += "select * from UserID where Username = '";
            sql += Username + "' and UserStatus = 'operator'";
            query.exec(sql);
            if(query.next()){
                sql = "";
                sql += "select * from (select Password from UserID where Username = '";
                sql += Username + "' and UserStatus = 'operator') T where Password = '";
                sql += Password + "'";
                query.exec(sql);
                if(query.next()){
                    //delete operator_dialog;
                    operator_dialog = new operator_Dialog();
                    //operator_dialog->setWindowFlags(Qt::FramelessWindowHint);
                    operator_dialog->setWindowTitle("����Ա");
                    operator_dialog->exec();
                }
                else
                {
                    loginQmessage_Dialog *a = new loginQmessage_Dialog(0,tr("�����������"));
                    //a->setWindowFlags(Qt::FramelessWindowHint);
                    a->setWindowTitle("��ʾ");
                    a->exec();
                }
            }
            else
            {
                loginQmessage_Dialog *a = new loginQmessage_Dialog(0,tr("�޶�ӦȨ�޵��û�����"));
                //a->setWindowFlags(Qt::FramelessWindowHint);
                a->setWindowTitle("��ʾ");
                a->exec();
            }
        break;
        default:
        break;
        }
    }
}

void LogIn_Dialog::clockChange()
{
    ui->lcdNumber->display(QTime::currentTime().toString("hh:mm:ss"));
}

void LogIn_Dialog::on_Close_pushButton_clicked()
{
    this->close();
}

void LogIn_Dialog::on_register_pushButton_clicked()
{
    register_Dialog *dialog = new register_Dialog();
    //dialog->setWindowFlags(Qt::FramelessWindowHint);
    dialog->setWindowTitle("ע��");
    dialog->exec();
}

void LogIn_Dialog::on_forget_pushButton_clicked()
{
    forget_Dialog *dialog = new forget_Dialog();
    //dialog->setWindowFlags(Qt::FramelessWindowHint);
    dialog->setWindowTitle("��������");
    dialog->exec();
}

void LogIn_Dialog::on_Query_pushButton_clicked()
{
    customer_Dialog * dialog = new customer_Dialog();
    //dialog->setWindowFlags(Qt::FramelessWindowHint);
    dialog->setWindowTitle("�ͻ�");
    dialog->exec();
}
