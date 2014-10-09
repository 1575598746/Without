#include "checkdiary_dialog.h"
#include "ui_checkdiary_dialog.h"
#include <QSqlRecord>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QScrollBar>

CheckDiary_Dialog::CheckDiary_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckDiary_Dialog)
{
    ui->setupUi(this);

    QFile file(":/qstylesheet.qss");
        if(file.open(QFile::ReadOnly))
        {
            QTextStream filetext(&file);
            QString stylesheet = filetext.readAll();
            //ui->close_pushButton->setStyleSheet(stylesheet);
            ui->done_pushButton->setStyleSheet(stylesheet);
            ui->query_pushButton->setStyleSheet(stylesheet);
            ui->out_pushButton->setStyleSheet(stylesheet);
            ui->in_pushButton->setStyleSheet(stylesheet);
            ui->undone_pushButton->setStyleSheet(stylesheet);
            ui->ascend_pushButton->setStyleSheet(stylesheet);
            ui->descend_pushButton->setStyleSheet(stylesheet);
        }

        ui->tableWidget->setFrameShape(QFrame::NoFrame); //设置无边框

        ui->tableWidget->horizontalHeader()->setClickable(false); //设置表头不可点击（默认点击后进行排序）

        //设置表头字体加粗
        QFont font = this->font();
        font.setBold(true);
        ui->tableWidget->horizontalHeader()->setFont(font);

        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑

        ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度

        ui->tableWidget->setShowGrid(false); //设置不显示格子线

        ui->tableWidget->verticalHeader()->setVisible(false); //设置垂直头不可见

        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为时每次选择一行

        ui->tableWidget->setStyleSheet("selection-background-color:lightblue;"); //设置选中背景色

        ui->tableWidget->setStyleSheet("background-color:rgba(0,0,0,80)");

        ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色

        //设置水平、垂直滚动条样式
        ui->tableWidget->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:15px;}"
          "QScrollBar::handle{background:black; border:2px solid transparent; border-radius:5px;}"
          "QScrollBar::handle:hover{background:solid gray;}"
          "QScrollBar::sub-line{background:transparent;}"
          "QScrollBar::add-line{background:transparent;}");

        ui->tableWidget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 15px;}"
          "QScrollBar::handle{background:black; border:2px solid transparent; border-radius:5px;}"
          "QScrollBar::handle:hover{background:solid gray;}"
          "QScrollBar::sub-line{background:transparent;}"
          "QScrollBar::add-line{background:transparent;}");

        ui->yyyy_spinBox->setStyleSheet("QSpinBox{border:2px solid gray;}"
                                        "QSpinBox{background-color:solid white}"
                                        "QSpinBox::down-arrow{border-image:url(:/down4.png);}"
                                        "QSpinBox::up-arrow{border-image:url(:/up4.png);}");


        ui->mm_spinBox->setStyleSheet("QSpinBox{border:2px solid gray;}"
          "QSpinBox{background-color:solid white}"
          "QSpinBox::down-arrow{border-image:url(:/down4.png);}"
          "QSpinBox::up-arrow{border-image:url(:/up4.png);}");

        ui->dd_spinBox->setStyleSheet("QSpinBox{border:2px solid gray;}"
                                      "QSpinBox{background-color:solid white}"
                                      "QSpinBox::down-arrow{border-image:url(:/down4.png);}"
                                      "QSpinBox::up-arrow{border-image:url(:/up4.png);}");

        ui->remindDate_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");

    model = new QSqlQueryModel();
    dateModel = new QSqlQueryModel();

    dateModelFlag = 0;

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableWidget->setColumnCount(8);

    QStringList header;
    header<<tr("ID")<<tr("name")<<tr("manufacturer")<<tr("approval_number")<<tr("value")<<tr("operate")<<tr("status")<<tr("date");
    ui->tableWidget->setHorizontalHeaderLabels(header);

    init_tableWidget();

    ui->yyyy_spinBox->setMinimum(2014);       //设置最小值
    ui->yyyy_spinBox->setValue(2014);          //设置初始值
    ui->yyyy_spinBox->setRange(2014,3000);

    ui->mm_spinBox->setValue(1);
    ui->mm_spinBox->setRange(0,13);       //设置变化范围

    ui->dd_spinBox->setValue(1);
    ui->dd_spinBox->setRange(0,32);
    connect(ui->mm_spinBox, SIGNAL(valueChanged(int)), this, SLOT(mm_remind()));
    connect(ui->dd_spinBox, SIGNAL(valueChanged(int)), this, SLOT(dd_remind()));
}

void CheckDiary_Dialog::init_tableWidget(){
    model->setQuery("select * from Diary");
    rowNum = model->rowCount();
    ui->tableWidget->setRowCount(rowNum);
    for(int i = 0; i < rowNum; i++){
        //qDebug
        //qDebug()<<"进入循环";
     showTablewidget(model, i);
    }
}

void CheckDiary_Dialog::showTablewidget(QSqlQueryModel* a, int i)
{
    StringID = a->record(i).value("ID").toString();
    StringName = a->record(i).value("name").toString();
    StringManufacturer = a->record(i).value("manufacturer").toString();
    StringApproval_number = a->record(i).value("approval_number").toString();
    StringValue = a->record(i).value("value").toString();
    StringOperate = a->record(i).value("operate").toString();
    StringStatus = a->record(i).value("status").toString();
    StringDate = a->record(i).value("date").toString();

    IDItem = new QTableWidgetItem(StringID);
    ui->tableWidget->setItem(i,0,IDItem);

        nameItem=new QTableWidgetItem(StringName);
        ui->tableWidget->setItem(i,1,nameItem);

        manufacturerItem=new QTableWidgetItem(StringManufacturer);
        ui->tableWidget->setItem(i,2,manufacturerItem);

        approval_numberItem=new QTableWidgetItem(StringApproval_number);
        ui->tableWidget->setItem(i,3,approval_numberItem);

        valueItem=new QTableWidgetItem(StringValue);
        ui->tableWidget->setItem(i,4,valueItem);

        operateItem=new QTableWidgetItem(StringOperate);
        ui->tableWidget->setItem(i,5,operateItem);

        statusItem = new QTableWidgetItem(StringStatus);
        ui->tableWidget->setItem(i,6,statusItem);

        dateItem = new QTableWidgetItem(StringDate);
        ui->tableWidget->setItem(i,7,dateItem);
}

CheckDiary_Dialog::~CheckDiary_Dialog()
{
    delete ui;
}

void CheckDiary_Dialog::on_close_pushButton_clicked()
{
    this->close();
}

void CheckDiary_Dialog::on_query_pushButton_clicked()
{
    dateString = "select * from Diary where date = '";
    year = QString::number(ui->yyyy_spinBox->value(), 10);
    month = QString::number(ui->mm_spinBox->value(), 10);
    day = QString::number(ui->dd_spinBox->value(), 10);

    if(month.length() < 2 && day.length() == 2){
        dateString += year + "-0" + month + "-" + day + "'";
    }
    if(day.length() < 2 && month.length() == 2){
        dateString += year + "-" + month + "-0" + day + "'";
    }
    if(month.length() < 2 && day.length() < 2){
        dateString += year + "-0" + month + "-0" + day + "'";
    }
    if(month.length() == 2 && day.length() == 2){
        dateString += year + "-" + month + "-" + day + "'";
    }

    dateYear = year;
    if(month.length() < 2){
        dateMonth = "0" + month;
    }
    else{
        dateMonth = month;
    }
    if(day.length() < 2){
        dateDay = "0" + day;
    }
    else{
        dateDay = day;
    }

  //qDebug
    qDebug()<<dateString;

    dateModel->setQuery(dateString);
    dateRowNum = dateModel->rowCount();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(dateRowNum);
    for(int i = 0; i < dateRowNum; i++){
        showTablewidget(dateModel, i);
    }
    dateModelFlag = 1;

}

void CheckDiary_Dialog::mm_remind(){
    if(ui->mm_spinBox->value() > 12){
     ui->mm_spinBox->setValue(1);
    }
    else if(ui->mm_spinBox->value() < 1){
     ui->mm_spinBox->setValue(12);
    }
}

void CheckDiary_Dialog::dd_remind(){
    if(ui->dd_spinBox->value() > 31){
     ui->dd_spinBox->setValue(1);
    }
    else if(ui->dd_spinBox->value() < 1){
     ui->dd_spinBox->setValue(31);
    }
}

void CheckDiary_Dialog::on_ascend_pushButton_clicked()
{
        ID = new int[rowNum];
        for(int i = 0; i < rowNum; i++){
            ID[i] = model->record(i).value("ID").toInt();
        }
        QString string = "select * from Diary where ID in (";
        for(int i = 0; i < rowNum; i++){
            tempID = QString::number(ID[i], 10);
            string += "'" + tempID + "'";
            if(i == rowNum - 1){
                string += ")";
                break;
            }
            else{
                string += ",";
            }
        }
        string += " order by date";

      //qDebug
        qDebug()<<string;

        QSqlQueryModel *dateAscModel = new QSqlQueryModel();
        dateAscModel->setQuery(string);
        int dateArowNum = dateAscModel->rowCount();
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(dateArowNum);
        for(int i = 0; i < dateArowNum; i++){
            showTablewidget(dateAscModel, i);
        }

}

void CheckDiary_Dialog::on_descend_pushButton_clicked()
{
    ID = new int[rowNum];
    for(int i = 0; i < rowNum; i++){
        ID[i] = model->record(i).value("ID").toInt();
    }
    QString string = "select * from Diary where ID in (";
    for(int i = 0; i < rowNum; i++){
        tempID = QString::number(ID[i], 10);
        string += "'" + tempID + "'";
        if(i == rowNum - 1){
            string += ")";
            break;
        }
        else{
            string += ",";
        }
    }
    string += " order by date desc";

  //qDebug
    qDebug()<<string;

    QSqlQueryModel *dateDscModel = new QSqlQueryModel();
    dateDscModel->setQuery(string);
    int dateDrowNum = dateDscModel->rowCount();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(dateDrowNum);
    for(int i = 0; i < dateDrowNum; i++){
        showTablewidget(dateDscModel, i);
    }
}

void CheckDiary_Dialog::on_undone_pushButton_clicked()
{
    if(dateModelFlag == 1){
        ui->remindDate_label->setText("");

        QString string = "select * from Diary where date = '";
        string += dateYear + "-" + dateMonth + "-" + dateDay + "'";
        string += " and status = '1'";

      //qDebug
        qDebug()<<string;

        dateModel->setQuery(string);
        int rowNum = dateModel->rowCount();
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(rowNum);
        for(int i = 0; i < rowNum; i++){
            showTablewidget(dateModel, i);
        }
    }
    else{
        ui->remindDate_label->setText("请先确定时间范围");
    }
}

void CheckDiary_Dialog::on_done_pushButton_clicked()
{
    if(dateModelFlag == 1){
        ui->remindDate_label->setText("");

        QString string = "select * from Diary where date = '";
        string += dateYear + "-" + dateMonth + "-" + dateDay + "'";
        string += " and status = '0'";

      //qDebug
        qDebug()<<string;

        dateModel->setQuery(string);
        int rowNum = dateModel->rowCount();
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(rowNum);
        for(int i = 0; i < rowNum; i++){
            showTablewidget(dateModel, i);
        }
    }
    else{
        ui->remindDate_label->setText("请先确定时间范围");
    }
}

void CheckDiary_Dialog::on_in_pushButton_clicked()
{
    if(dateModelFlag == 1){
        ui->remindDate_label->setText("");

        QString string = "select * from Diary where date = '";
        string += dateYear + "-" + dateMonth + "-" + dateDay + "'";
        string += " and operate = '入库'";

      //qDebug
        qDebug()<<string;

        dateModel->setQuery(string);
        int rowNum = dateModel->rowCount();
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(rowNum);
        for(int i = 0; i < rowNum; i++){
            showTablewidget(dateModel, i);
        }
    }
    else{
        ui->remindDate_label->setText("请先确定时间范围");
    }
}

void CheckDiary_Dialog::on_out_pushButton_clicked()
{
    if(dateModelFlag == 1){
        ui->remindDate_label->setText("");

        QString string = "select * from Diary where date = '";
        string += dateYear + "-" + dateMonth + "-" + dateDay + "'";
        string += " and operate = '出库'";

      //qDebug
        qDebug()<<string;

        dateModel->setQuery(string);
        int rowNum = dateModel->rowCount();
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(rowNum);
        for(int i = 0; i < rowNum; i++){
            showTablewidget(dateModel, i);
        }
    }
    else{
        ui->remindDate_label->setText("请先确定时间范围");
    }
}
