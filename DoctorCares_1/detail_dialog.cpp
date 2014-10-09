#include "detail_dialog.h"
#include "ui_detail_dialog.h"
#include <QSqlRecord>
#include <QSqlQuery>
#include <QDebug>
#include <QFile>
#include <QTextStream>

detail_Dialog::detail_Dialog(QWidget *parent, QString approval_number) :
    QDialog(parent),
    ui(new Ui::detail_Dialog)
{
    ui->setupUi(this);

    //样式
    QFile file(":/qstylesheet.qss");
        if(file.open(QFile::ReadOnly))
        {
            QTextStream filetext(&file);
            QString stylesheet = filetext.readAll();
            ui->save_pushButton->setStyleSheet(stylesheet);
            ui->comfirm_pushButton->setStyleSheet(stylesheet);
            //ui->close_pushButton->setStyleSheet(stylesheet);
        }

ui->name_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,80)}");
ui->OTC_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,80)}");
ui->approval_number_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,80)}");
ui->label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,80)}");
ui->label_2->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,80)}");
ui->label_3->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,80)}");
ui->label_4->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,80)}");
ui->category_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,80)}");
//ui->label_9->setStyleSheet("QLabel{background-color:rgba(0,0,0,80)}");

//样式


    model = new QSqlQueryModel();

    app_number = approval_number;

    sql = "select * from MedicineInfo where approval_number = '";
    sql += app_number + "'";

    model->setQuery(sql);

    ui->nameDetail_textEdit->setText(model->record(0).value("name").toString());
    ui->OTCdetail_textEdit->setText(model->record(0).value("OTC").toString());
    ui->appDetail_label->setText(app_number);
    ui->categoryDetail_textEdit->setText(model->record(0).value("category").toString());
    ui->dosageDetail_textEdit->setText(model->record(0).value("dosage_form").toString());
    ui->packageDetail_textEdit->setText(model->record(0).value("package_insert").toString());
    ui->manufacturer_textEdit->setText(model->record(0).value("manufacturer").toString());
    ui->inventoryDetail_label->setText(model->record(0).value("inventory").toString());


}

detail_Dialog::~detail_Dialog()
{
    delete ui;
}

void detail_Dialog::on_save_pushButton_clicked()
{
    stringName.append(ui->nameDetail_textEdit->toPlainText());
    stringOTC.append(ui->OTCdetail_textEdit->toPlainText());
    stringCate.append(ui->categoryDetail_textEdit->toPlainText());
    stringDosa.append(ui->dosageDetail_textEdit->toPlainText());
    stringPack.append(ui->packageDetail_textEdit->toPlainText());
    stringManu.append(ui->manufacturer_textEdit->toPlainText());
    sql = "update MedicineInfo set name = '";
    sql += stringName + "', OTC = '";
    sql += stringOTC + "', category = '";
    sql += stringCate + "', dosage_form = '";
    sql += stringDosa + "', package_insert = '";
    sql += stringPack + "', manufacturer = '";
    sql += stringManu + "' where approval_number = '";
    sql += app_number + "'";
  //qDebug
    qDebug()<<sql;

}

void detail_Dialog::on_comfirm_pushButton_clicked()
{
    QSqlQuery query;
    query.exec(sql);
    QString string = "select * from MedicineInfo where name = '";
    string += stringName + "'";
    query.exec(string);
    if(query.next()){
        ui->remind_label->setText("修改成功！");
    }
}

void detail_Dialog::on_close_pushButton_clicked()
{
    this->close();
}
