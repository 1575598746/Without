#include "insert_dialog.h"
#include "ui_insert_dialog.h"
#include <QSqlQuery>
#include <QDebug>
#include <QFile>
#include <QTextStream>

insert_Dialog::insert_Dialog(QWidget *parent,QString a,QString b,QString c,QString d) :
    QDialog(parent),
    ui(new Ui::insert_Dialog)
{
    ui->setupUi(this);

    //样式
    QFile file(":/qstylesheet.qss");
        if(file.open(QFile::ReadOnly))
        {
            QTextStream filetext(&file);
            QString stylesheet = filetext.readAll();
            ui->comfirm_pushButton->setStyleSheet(stylesheet);
            //ui->close_pushButton->setStyleSheet(stylesheet);
            ui->generateID_pushButton->setStyleSheet(stylesheet);
        }

        ui->label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->label_2->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->label_3->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->label_4->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->label_5->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->label_6->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->label_7->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        //ui->label_8->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->label_9->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->remind_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        //样式

    ui->pic_pushButton->setStyleSheet("background:rgba(0,0,0,0%);");

    name = a;
    manufacturer = b;
    approval_number = c;
    cate = d;

    if(name != ""){
     ui->name_lineEdit->setText(name);
    }
    if(manufacturer != ""){
     ui->manufacturer_lineEdit->setText(manufacturer);
    }
//    if(approval_number != ""){
//     ui->approval_number_lineEdit->setText(approval_number);
//    }
    if(cate != ""){
     ui->category_lineEdit->setText(cate);
    }

    model = new QSqlQueryModel();

    str = "insert into MedicineInfo values (";

    connect(ui->approval_number_lineEdit,SIGNAL(editingFinished()),this,SLOT(change()));
    connect(this,SIGNAL(sendSignal(bool)),this,SLOT(receiveSignal(bool)));

}

insert_Dialog::~insert_Dialog()
{
    delete ui;
}

void insert_Dialog::change()
{
    QSqlQuery query;
    QString str = "select * from MedicineInfo where approval_number = '";
    str += ui->approval_number_lineEdit->text() + "'";
    query.exec(str);
    if(ui->approval_number_lineEdit->text().isEmpty()){
        ui->pic_pushButton->setStyleSheet("QPushButton{border-image:url(:/cancel1.png);}");
    }
    else
    {
        if(!query.next())
            {
                qDebug()<<"a";
                ui->pic_pushButton->setStyleSheet("QPushButton{border-image:url(:/f0582.png);}");
            }
        else
            {
                qDebug()<<"b";
                ui->pic_pushButton->setStyleSheet("QPushButton{border-image:url(:/cancel1.png);}");
            }
    }
}

void insert_Dialog::on_generateID_pushButton_clicked()
{
    model->setQuery("select ID from MedicineInfo");
    int rowNum = model->rowCount();
    int maxID = -1;
    for(int i = 0; i < rowNum; i++){
        if(model->record(i).value("ID").toInt() > maxID){
            maxID = model->record(i).value("ID").toInt();
        }
    }
    QString stringRownum = QString::number(maxID+1, 10);
    ui->ID_lineEdit->setText(stringRownum);
//    model->setQuery("select ID from MedicineInfo order by ID desc");
//    int rowNum = model->record(0).value("ID").toInt() + 1;
//    QString stringRowNum = QString::number(rowNum, 10);
//    ui->ID_lineEdit->setText(stringRowNum);
}

void insert_Dialog::on_close_pushButton_clicked()
{
    this->close();
}

void insert_Dialog::on_comfirm_pushButton_clicked()
{
    QSqlQuery query;
    ID = ui->ID_lineEdit->text();

    OTC = ui->OTC_lineEdit->text();
    dosage_form = ui->dosage_form_lineEdit->text();
    package_insert = ui->package_insert_lineEdit->text();

    name = ui->name_lineEdit->text();
    manufacturer = ui->manufacturer_lineEdit->text();
    approval_number = ui->approval_number_lineEdit->text();
    cate = ui->category_lineEdit->text();
    inventory = QString::number(0,10);

    if(ID.isEmpty()||name.isEmpty()||manufacturer.isEmpty()||cate.isEmpty()||approval_number.isEmpty()){
        emit sendSignal(1);
    }
    else{
        emit sendSignal(0);
        str += "'" + ID + "','" + name + "','" + OTC + "','" + approval_number + "','" + cate + "','" + dosage_form + "','" + package_insert + "','" + manufacturer + "'," + inventory + ")";
        query.exec(str);
        qDebug()<<str;
        testStr = "select * from MedicineInfo where ID = '";
        testStr += ID + "'";
        query.exec(testStr);
        if(query.next()){
            loginQmessage_Dialog *a = new loginQmessage_Dialog(0,tr("添加成功！"));
            //a->setWindowFlags(Qt::FramelessWindowHint);
            a->setWindowTitle("提示");
            a->exec();
        }
        this->close();
    }
}

void insert_Dialog::receiveSignal(bool a){
    if(a == 1){
        ui->remind_label->setText("以上项为必填项!");
    }
    else if(a == 0){
        ui->remind_label->setText("");
    }
}
