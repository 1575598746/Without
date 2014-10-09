#include "loginqmessage_dialog.h"
#include "ui_loginqmessage_dialog.h"
#include <QFile>
#include <QTextStream>

loginQmessage_Dialog::loginQmessage_Dialog(QWidget *parent, QString str) :
    QDialog(parent),
    ui(new Ui::loginQmessage_Dialog)
{
    ui->setupUi(this);

    QFile file(":/qstylesheet.qss");
        if(file.open(QFile::ReadOnly))
        {
            QTextStream filetext(&file);
            QString stylesheet = filetext.readAll();
            ui->loginQmessage_pushButton->setStyleSheet(stylesheet);


        }
        ui->loginQmessage_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");


//    ui->loginQmessage_label->setGeometry(QRect(328, 240, 329, 27*4));  //ËÄ±¶ÐÐ¾à
//    ui->loginQmessage_label->setWordWrap(true);
//    ui->loginQmessage_label->setAlignment(Qt::AlignTop);

    ui->loginQmessage_label->setText(str);

    connect(ui->loginQmessage_pushButton, SIGNAL(clicked()), this, SLOT(window_close()));
}

loginQmessage_Dialog::~loginQmessage_Dialog()
{
    delete this;
    delete ui;
}

void loginQmessage_Dialog::window_close()
{
    this->close();
}
