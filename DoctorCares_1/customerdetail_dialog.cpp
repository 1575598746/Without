#include "customerdetail_dialog.h"
#include "ui_customerdetail_dialog.h"
#include <QFile>
#include <QTextStream>

customerDetail_Dialog::customerDetail_Dialog(QWidget *parent, QString approval_number) :
    QDialog(parent),
    ui(new Ui::customerDetail_Dialog)
{
    ui->setupUi(this);

    //样式
        QFile file(":/qstylesheet.qss");
            if(file.open(QFile::ReadOnly))
            {
                QTextStream filetext(&file);
                QString stylesheet = filetext.readAll();
                //ui->getBack_pushButton->setStyleSheet(stylesheet);
            }

    ui->name_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,80)}");
    ui->OTC_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,80)}");
    ui->category_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,80)}");
    ui->label_2->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,80)}");
    ui->label_3->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,80)}");

    //ui->categoryDetail_textEdit->setStyleSheet("background-color:rgba(0,0,0,80)");

    model = new QSqlQueryModel();

    app_number = approval_number;

    sql = "select * from MedicineInfo where approval_number = '";
    sql += app_number + "'";

    model->setQuery(sql);

//样式
    ui->nameDetail_textEdit->setReadOnly(true);
    ui->nameDetail_textEdit->setStyleSheet("QTextEdit{ background:rgba(0,0,0,0%); border:1px; font:10pt}"
                                           "QTextEdit:!hover{background:rgba(0,0,0,0%);}"
                                           "QTextEdit:focus {border-image:none; border:1px groove lightgray; border-radius:2px}");
    ui->OTCdetail_textEdit->setReadOnly(true);
    ui->OTCdetail_textEdit->setStyleSheet("QTextEdit{ background:rgba(0,0,0,0%); border:1px; font:10pt}"
                                          "QTextEdit:!hover{background:rgba(0,0,0,0%);}"
                                          "QTextEdit:focus {border-image:none; border:1px groove lightgray; border-radius:2px}");
    ui->categoryDetail_textEdit->setReadOnly(true);
    ui->categoryDetail_textEdit->setStyleSheet("QTextEdit{ background:rgba(0,0,0,0%); border:1px; font:10pt}"
                                               "QTextEdit:!hover{background:rgba(0,0,0,0%);}"
                                               "QTextEdit:focus {border-image:none; border:1px groove lightgray; border-radius:2px}");
    ui->packageDetail_textEdit->setReadOnly(true);
    ui->packageDetail_textEdit->setStyleSheet("QTextEdit{ background:rgba(0,0,0,0%); border:1px; font:10pt}"
                                              "QTextEdit:!hover{background:rgba(0,0,0,0%);}"
                                              "QTextEdit:focus {border-image:none; border:1px groove lightgray; border-radius:2px}");
    ui->manufacturer_textEdit->setReadOnly(true);
    ui->manufacturer_textEdit->setStyleSheet("QTextEdit{ background:rgba(0,0,0,0%); border:1px; font:10pt}"
                                             "QTextEdit:!hover{background:rgba(0,0,0,0%);}"
                                             "QTextEdit:focus {border-image:none; border:1px groove lightgray; border-radius:2px}");

//样式
    ui->nameDetail_textEdit->setText(model->record(0).value("name").toString());
    ui->OTCdetail_textEdit->setText(model->record(0).value("OTC").toString());
    ui->categoryDetail_textEdit->setText(model->record(0).value("category").toString());
    ui->packageDetail_textEdit->setText(model->record(0).value("package_insert").toString());
    ui->manufacturer_textEdit->setText(model->record(0).value("manufacturer").toString());

}

customerDetail_Dialog::~customerDetail_Dialog()
{
    delete ui;
}

void customerDetail_Dialog::on_getBack_pushButton_clicked()
{
    this->close();
}
