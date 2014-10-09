#include "customer_dialog.h"
#include "ui_customer_dialog.h"
#include "loginqmessage_dialog.h"
#include "customerdetail_dialog.h"
#include <QSqlRecord>
#include <QDebug>
#include <QScrollBar>
#include <QFile>
#include <QTextStream>

customer_Dialog::customer_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::customer_Dialog)
{
    ui->setupUi(this);

    model = new QSqlQueryModel();


//样式
    QFile file(":/qstylesheet.qss");
        if(file.open(QFile::ReadOnly))
        {
            QTextStream filetext(&file);
            QString stylesheet = filetext.readAll();
            //ui->close_pushButton->setStyleSheet(stylesheet);
            ui->query_pushButton->setStyleSheet(stylesheet);
            ui->detail_pushButton->setStyleSheet(stylesheet);
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

    ui->tableWidget->setStyleSheet("selection-background-color:skyblue;"); //设置选中背景色

    ui->tableWidget->setStyleSheet("background-color:rgba(0,0,0,80)");

    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:solid gray;}"); //设置表头背景色

    //设置水平、垂直滚动条样式
//    ui->tableWidget->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
//      "QScrollBar::handle{background:black; border:2px solid transparent; border-radius:5px;}"
//      "QScrollBar::handle:hover{background:solid gray;}"
//      "QScrollBar::sub-line{background:transparent;}"
//      "QScrollBar::add-line{background:transparent;}");

    ui->tableWidget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
      "QScrollBar::handle{background:black; border:2px solid transparent; border-radius:5px;}"
      "QScrollBar::handle:hover{background:solid gray;}"
      "QScrollBar::sub-line{background:transparent;}"
      "QScrollBar::add-line{background:transparent;}");

    ui->name_comboBox->setStyleSheet("QComboBox{border:2px solid gray;}"
      "QComboBox::down-arrow{border-image:url(:/down4.png);}"
      "QComboBox{background-color:rgba(0,0,0,50)}"
      );

    ui->manufacturer_comboBox->setStyleSheet("QComboBox{border:2px solid gray;}"
                                             "QComboBox::down-arrow{border-image:url(:/down4.png);}"
                                             "QComboBox{background-color:rgba(0,0,0,50)}");

    ui->category_comboBox->setStyleSheet("QComboBox{border:2px solid gray;}"
                                         "QComboBox::down-arrow{border-image:url(:/down4.png);}"
                                         "QComboBox{background-color:rgba(0,0,0,50)}");

    ui->package_insert_comboBox->setStyleSheet("QComboBox{border:2px solid gray;}"
                                               "QComboBox::down-arrow{border-image:url(:/down4.png);}"
                                               "QComboBox{background-color:rgba(0,0,0,50)}");

    ui->label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
    ui->label_2->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
    ui->label_3->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
    ui->label_4->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
//样式


    ui->tableWidget->setColumnCount(4); //设置列数为4

    QStringList header;
    header<</*tr("选择")<<*/tr("name")<<tr("manufacturer")<<tr("category")<<tr("package_insert");
    ui->tableWidget->setHorizontalHeaderLabels(header);

    init_tableWidget();

    init_ComboBoxes();

    head = NULL;
    sql = NULL;
    p = NULL;
    start = NULL;

    sql = (struct part1 *)malloc(sizeof(struct part1));
    sql->s = "select * from MedicineInfo where ";
    sql->next1 = NULL;
    sql->next2 = NULL;
    sql->prior1 = NULL;
    sql->prior2 = NULL;
    p = sql;
    head = sql;
    start = sql;
    for(int i = 1; i <= 9; i++){
        sql = (struct part1 *)malloc(sizeof(struct part1));
        sql->next1 = NULL;
        sql->next2 = NULL;
        sql->prior1 = p;
        sql->prior2 = p;
        p->next1 = sql;
        p->next2 = sql;
        p = sql;
    }

    p = start;
    sql = start;
    name = start;
    manu = start;
    cate = start;
    pack = start;
    end = start;

    int i;
    for(i = 1; i <= 2; i++){
     name = name->next1;
    }
    for(i = 1; i <= 4; i++){
     manu = manu->next1;
    }
    for(i = 1; i <= 6; i++){
     cate = cate->next1;
    }
    for(i = 1; i <= 8; i++){
     pack = pack->next1;
    }
    for(i = 1; i <= 9; i++){
     end = end->next1;
    }

    name->prior1->s = "name like '%";
                                               //name->next1->s = "' and ";
    manu->prior1->s = "manufacturer like '%";
                                               //sort->next1->s = "' and ";
    cate->prior1->s = "category like '%";
                                               //cate->next1->s = "' and ";
    pack->prior1->s = "package_insert like '%";



    pack->next1->s = "%'";

    connect(ui->tableWidget,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(tableWidget_item_click()));
    connect(this, SIGNAL(sendRefreshSignal(int)), this, SLOT(refresh(int)));
}



void customer_Dialog::init_tableWidget(){
    model->setQuery("select * from MedicineInfo");
    rowNum = model->rowCount();
    ui->tableWidget->setRowCount(rowNum);
    for(int i = 0; i < rowNum; i++){
        //qDebug
        //qDebug()<<"进入循环";
     showTablewidget(i);
    }
}

void customer_Dialog::showTablewidget(int i)
{
    StringName = model->record(i).value("name").toString();
    StringManufacturer = model->record(i).value("manufacturer").toString();
    StringCategory = model->record(i).value("category").toString();
    StringPackage_insert = model->record(i).value("package_insert").toString();

        nameItem=new QTableWidgetItem(StringName);
        ui->tableWidget->setItem(i,0,nameItem);

        manufacturerItem=new QTableWidgetItem(StringManufacturer);
        ui->tableWidget->setItem(i,1,manufacturerItem);

        categoryItem=new QTableWidgetItem(StringCategory);
        ui->tableWidget->setItem(i,2,categoryItem);

        package_insertItem=new QTableWidgetItem(StringPackage_insert);
        ui->tableWidget->setItem(i,3,package_insertItem);
}

void customer_Dialog::tableWidget_item_click(){
   curRow=ui->tableWidget->currentRow();
   ui->name_comboBox->setEditText(model->record(curRow).value("name").toString());
   ui->manufacturer_comboBox->setEditText(model->record(curRow).value("manufacturer").toString());
   ui->category_comboBox->setEditText(model->record(curRow).value("category").toString());
   ui->package_insert_comboBox->setEditText(model->record(curRow).value("package_insert").toString());
}

customer_Dialog::~customer_Dialog()
{
    delete start;
    delete ui;
}

void customer_Dialog::on_query_pushButton_clicked()
{
        p = start;
        head = start;
        sql = start;

        QString Query = "";
        //qDebug
          qDebug()<<"process";



        //qDebug
          qDebug()<<"process";

        //model = new QSqlQueryModel();

        //qDebug
          qDebug()<<"process";

        QString name_text = ui->name_comboBox->currentText();
        QString cate_text = ui->category_comboBox->currentText();
        QString manu_text = ui->manufacturer_comboBox->currentText();
        QString pack_text = ui->package_insert_comboBox->currentText();


        //qDebug
          qDebug()<<name_text;
          qDebug()<<cate_text;
          qDebug()<<manu_text;
          qDebug()<<pack_text;


        QByteArray ba0 = name_text.toLocal8Bit();   //含中文的QString转char*; see "main.cpp";
        name->s = ba0.data();
        QByteArray ba1 = cate_text.toLocal8Bit();
        cate->s = ba1.data();
        QByteArray ba2 = manu_text.toLocal8Bit();
        manu->s = ba2.data();
        QByteArray ba3 = pack_text.toLocal8Bit();
        pack->s = ba3.data();


        //qDebug
        qDebug()<<name->s;
        qDebug()<<cate->s;
        qDebug()<<manu->s;
        qDebug()<<pack->s;


        if(strlen(name->s) == 0 && strlen(cate->s) == 0 && strlen(manu->s) == 0 && strlen(pack->s) == 0){
            Query = "select * from MedicineInfo";
        }
        else{
            Query = "";
            for(; p != NULL; p = p->next1){
                                                          //qDebug
                                                          qDebug()<<p->s;
                    if(strlen(p->s) == 0){
                                                          //qDebug
                                                          qDebug()<<"get in if";
                      head = p->next1;
                      p->prior1->prior2->next2 = head;
                      head->prior2 = p->prior1->prior2;

                      p = head;
                    }
                }



            for(; sql != NULL; sql = sql->next2){
                //qDebug
                  qDebug()<<"get in for";
             Query += sql->s;
             if(sql == name || sql == manu || sql == cate){
                 if(sql->next2 != end){
                  Query += "%' and ";
                 }
             }
            }


        }

        for(p = start; p != NULL; p = p->next1){
         p->next2 = p->next1;
         p->prior2 = p->prior1;
        }

        //qDebug
          qDebug()<<Query;

        model->setQuery(Query);
        rowNum = model->rowCount();
        if(rowNum == 0){
            loginQmessage_Dialog *a = new loginQmessage_Dialog(0,tr("无该药品信息！"));
            //a->setWindowFlags(Qt::FramelessWindowHint);
            a->setWindowTitle("提示");
            a->exec();
            emit sendRefreshSignal(2);
        }
        else
        {
            ui->tableWidget->clearContents();
            ui->tableWidget->setRowCount(rowNum);
            for(int i = 0; i < rowNum; i++){
                //qDebug
                  qDebug()<<"进入循环";
                  showTablewidget(i);
                //qDebug
                  qDebug()<<"查询结束";
            }
        }
    //内存泄露
}

void customer_Dialog::init_ComboBoxes()
{
    int rowNum = -1;

    nameModel = new QSqlQueryModel();
    nameModel->setQuery("select distinct name from MedicineInfo");
    rowNum = nameModel->rowCount();
    nameList.append("");
    for(int i = 0; i < rowNum; i++){
        nameList.append(nameModel->record(i).value("name").toString());
    }
    nameCompleter = new QCompleter(nameList, this);
    ui->name_comboBox->clear();
    ui->name_comboBox->addItems(nameList);
    ui->name_comboBox->setCompleter(nameCompleter);

    categoryModel = new QSqlQueryModel();
    categoryModel->setQuery("select distinct category from MedicineInfo");
    rowNum = categoryModel->rowCount();
    categoryList.append("");
    for(int i = 0; i < rowNum; i++){
        categoryList.append(categoryModel->record(i).value("category").toString());
    }
    categoryCompleter = new QCompleter(categoryList, this);
    ui->category_comboBox->clear();
    ui->category_comboBox->addItems(categoryList);
    ui->category_comboBox->setCompleter(categoryCompleter);

    package_insertModel = new QSqlQueryModel();
    package_insertModel->setQuery("select distinct package_insert from MedicineInfo");
    rowNum = package_insertModel->rowCount();
    package_insertList.append("");
    for(int i = 0; i < rowNum; i++){
        package_insertList.append(package_insertModel->record(i).value("package_insert").toString());
    }
    package_insertCompleter = new QCompleter(package_insertList, this);
    ui->package_insert_comboBox->clear();
    ui->package_insert_comboBox->addItems(package_insertList);
    ui->package_insert_comboBox->setCompleter(package_insertCompleter);

    manufacturerModel = new QSqlQueryModel();
    manufacturerModel->setQuery("select distinct manufacturer from MedicineInfo");
    rowNum = manufacturerModel->rowCount();
    manufacturerList.append("");
    for(int i = 0; i < rowNum; i++){
        manufacturerList.append(manufacturerModel->record(i).value("manufacturer").toString());
    }
    manufacturerCompleter = new QCompleter(manufacturerList, this);
    ui->manufacturer_comboBox->clear();
    ui->manufacturer_comboBox->addItems(manufacturerList);
    ui->manufacturer_comboBox->setCompleter(manufacturerCompleter);
}

void customer_Dialog::on_close_pushButton_clicked()
{
    this->close();
}

void customer_Dialog::on_detail_pushButton_clicked()
{
    if(curRow == ui->tableWidget->currentRow()){
        QString approval_number = model->record(curRow).value("approval_number").toString();
        customerDetail_Dialog *dialog = new customerDetail_Dialog(0,approval_number);
        //dialog->setWindowFlags(Qt::FramelessWindowHint);
        dialog->setWindowTitle("详细信息");
        dialog->exec();
    }
    else{
        loginQmessage_Dialog *a = new loginQmessage_Dialog(0,tr("请先选中某行！"));
        //a->setWindowFlags(Qt::FramelessWindowHint);
        a->setWindowTitle("提示");
        a->exec();
    }
}

void customer_Dialog::refresh(int addFlag)
{
    if(addFlag == 2){
        model->setQuery("select * from MedicineInfo");
        rowNum = model->rowCount();
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(rowNum);
        for(int i = 0; i < rowNum; i++){
            showTablewidget(i);
        }
        ui->name_comboBox->setEditText(model->record(rowNum-1).value("name").toString());
        ui->manufacturer_comboBox->setEditText(model->record(rowNum-1).value("manufacturer").toString());
        ui->category_comboBox->setEditText(model->record(rowNum-1).value("category").toString());
        ui->package_insert_comboBox->setEditText(model->record(rowNum-1).value("package_insert").toString());
    }
}
