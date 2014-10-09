#include "instorage_dialog.h"
#include "ui_instorage_dialog.h"
#include <QVBoxLayout>
#include <checkdiary_dialog.h>
#include <QFont>
#include <QFile>
#include <QTextStream>
#include <QScrollBar>
#include "detail_dialog.h"




inStorage_Dialog::inStorage_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inStorage_Dialog)
{
    ui->setupUi(this);

    //样式
        QFile file(":/qstylesheet.qss");
            if(file.open(QFile::ReadOnly))
            {
                QTextStream filetext(&file);
                QString stylesheet = filetext.readAll();
                //ui->back_pushButton->setStyleSheet(stylesheet);
                ui->showAll_pushButton->setStyleSheet(stylesheet);
                ui->select_pushButton->setStyleSheet(stylesheet);
                ui->delete_pushButton->setStyleSheet(stylesheet);
                ui->add_pushButton->setStyleSheet(stylesheet);
                ui->batchAdd_pushButton->setStyleSheet(stylesheet);
                ui->out_pushButton->setStyleSheet(stylesheet);
                ui->batchOut_pushButton->setStyleSheet(stylesheet);
                ui->moveOut_pushButton->setStyleSheet(stylesheet);
                ui->showZero_pushButton->setStyleSheet(stylesheet);
                ui->detail_pushButton->setStyleSheet(stylesheet);
                ui->checkDiary_pushButton->setStyleSheet(stylesheet);
                ui->refresh_pushButton->setStyleSheet(stylesheet);
            }

        ui->inStorage_tableWidget->setFrameShape(QFrame::NoFrame); //设置无边框

        ui->inStorage_tableWidget->horizontalHeader()->setClickable(false); //设置表头不可点击（默认点击后进行排序）

        //设置表头字体加粗
        QFont font = this->font();
        font.setBold(true);
        ui->inStorage_tableWidget->horizontalHeader()->setFont(font);

        ui->inStorage_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑

        //ui->inStorage_tableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度

        ui->inStorage_tableWidget->setShowGrid(false); //设置不显示格子线

        ui->inStorage_tableWidget->verticalHeader()->setVisible(false); //设置垂直头不可见

        ui->inStorage_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为时每次选择一行

        ui->inStorage_tableWidget->setStyleSheet("selection-background-color:skyblue;"); //设置选中背景色

        ui->inStorage_tableWidget->setStyleSheet("background-color:rgba(0,0,0,80)");

        ui->inStorage_tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:solid gray;}"); //设置表头背景色

        //设置水平、垂直滚动条样式
        ui->inStorage_tableWidget->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
          "QScrollBar::handle{background:black; border:2px solid transparent; border-radius:5px;}"
          "QScrollBar::handle:hover{background:solid gray;}"
          "QScrollBar::sub-line{background:transparent;}"
          "QScrollBar::add-line{background:transparent;}");

        ui->inStorage_tableWidget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
          "QScrollBar::handle{background:black; border:2px solid transparent; border-radius:5px;}"
          "QScrollBar::handle:hover{background:solid gray;}"
          "QScrollBar::sub-line{background:transparent;}"
          "QScrollBar::add-line{background:transparent;}");

        ui->name_comboBox->setStyleSheet("QComboBox{border:2px solid gray;}"
          "QComboBox::down-arrow{border-image:url(:/down4.png);}"
                                         "QComboBox{background-color:(0,0,0,50))}"
          );

        ui->manufacturer_comboBox->setStyleSheet("QComboBox{border:2px solid gray;}"
                                                 "QComboBox::down-arrow{border-image:url(:/down4.png);}"
                                                 "QComboBox{background-color:(0,0,0,50)}");

        ui->category_comboBox->setStyleSheet("QComboBox{border:2px solid gray;}"
                                             "QComboBox::down-arrow{border-image:url(:/down4.png);}"
                                             "QComboBox{background-color:(0,0,0,50)}");

        ui->approval_number_comboBox->setStyleSheet("QComboBox{border:2px solid gray;}"
                                                   "QComboBox::down-arrow{border-image:url(:/down4.png);}"
                                                   "QComboBox{background-color:(0,0,0,50)}");

        ui->name_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->manufacturer_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->category_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->approval_number_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
        ui->label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
    //样式



    //ui->inStorage_tableWidget->setStyleSheet("QTableWidget {font:bold; font-size:20px; color:green; background:rgba(0,0,0,0,0%); selection-color:black; selection-background-color:gray; border-radius:8px; border:4px solid green;}");

    model = new QSqlQueryModel();


//    ui->inStorage_tableWidget->setFrameShape(QFrame::NoFrame);
    ui->inStorage_tableWidget->horizontalHeader()->setClickable(false);

//    QFont font = this->font();
//    font.setBold(true);
//    ui->inStorage_tableWidget->horizontalHeader()->setFont(font);


    timer = new QTimer(this);

    ui->lcdNumber->setNumDigits(8);						//显示八个数字，默认是显示5个数字
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);	//填充颜色，默认是白色的
    ui->lcdNumber->display(QTime::currentTime().toString("hh:mm:ss"));	//设置格式，还有其他形式的

    connect(timer,SIGNAL(timeout()),this,SLOT(clockChange()));
    timer->start(1000);

    ui->inStorage_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->inStorage_tableWidget->setColumnCount(5); //设置列数为5

    QStringList header;
    header<</*tr("选择")<<*/tr("name")<<tr("manufacturer")<<tr("category")<<tr("approval_number")<<tr("inventory");
    ui->inStorage_tableWidget->setHorizontalHeaderLabels(header);

    init_inStorage_tableWidget();

    init_ComboBoxes();

    head = NULL;
    sql = NULL;
    p = NULL;
    start = NULL;

    sql = (struct part *)malloc(sizeof(struct part));
    sql->s = "select * from MedicineInfo where ";
    sql->next1 = NULL;
    sql->next2 = NULL;
    sql->prior1 = NULL;
    sql->prior2 = NULL;
    p = sql;
    head = sql;
    start = sql;
    for(int i = 1; i <= 9; i++){
        sql = (struct part *)malloc(sizeof(struct part));
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
    appr = start;
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
     appr = appr->next1;
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
    appr->prior1->s = "approval_number like '%";



    appr->next1->s = "%'";

    curRow = -2;
    //listWidget初始化currentIndex==0,单击查询后由于未选中currentIndex==-1,
    //与构造函数中的值相同，故单击添加键时的判断会产生错误,即单击查询后，如果不选中item再单击添加可以进入添加界面；

    modelFlag = 0;
    addFlag = -1;
    outFlag = 0;
    operationFlag = -1;
    rowNum = 0;

    ID = NULL;
    Inventory = NULL;
    batchID = NULL;
    batchInventory = NULL;

    addOperationFlag1 = new int[1];
    addOperationFlag1[0] = -1;

    addOperationFlag2 = new int[1];
    addOperationFlag2[0] = -1;
//    equalRow = new int[1];
//    equalRow[0] = -1;

    add_dialog = NULL;
    batchAdd_dialog = NULL;

    //connect(ui->inStorage_tableWidget,SIGNAL(cellChanged(int,int)), this, SLOT(checkBoxChanged(int, int)));
    connect(ui->inStorage_tableWidget,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(inStorage_tableWidget_item_click()));
    connect(this, SIGNAL(sendRefreshSignal(int)), this, SLOT(refresh(int)));
}

void inStorage_Dialog::init_inStorage_tableWidget(){
    //ui->inStorage_tableWidget
    model->setQuery("select * from MedicineInfo");
    rowNum = model->rowCount();
    ui->inStorage_tableWidget->setRowCount(rowNum);
    for(int i = 0; i < rowNum; i++){
        //qDebug
        //qDebug()<<"进入循环";
     showTablewidget(i);
    }
}

void inStorage_Dialog::init_ComboBoxes()
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

    approval_numberModel = new QSqlQueryModel();
    approval_numberModel->setQuery("select distinct approval_number from MedicineInfo");
    rowNum = approval_numberModel->rowCount();
    approval_numberList.append("");
    for(int i = 0; i < rowNum; i++){
        approval_numberList.append(approval_numberModel->record(i).value("approval_number").toString());
    }
    approval_numberCompleter = new QCompleter(approval_numberList, this);
    ui->approval_number_comboBox->clear();
    ui->approval_number_comboBox->addItems(approval_numberList);
    ui->approval_number_comboBox->setCompleter(approval_numberCompleter);

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

inStorage_Dialog::~inStorage_Dialog()
{

  //qDebug
    //qDebug()<<"delete";
    delete start;
    delete ui;
}

void inStorage_Dialog::on_back_pushButton_clicked()
{
    this->close();
}

void inStorage_Dialog::on_select_pushButton_clicked()
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
    QString appr_text = ui->approval_number_comboBox->currentText();


    //qDebug
      qDebug()<<name_text;
      qDebug()<<cate_text;
      qDebug()<<manu_text;
      qDebug()<<appr_text;


    QByteArray ba0 = name_text.toLocal8Bit();   //含中文的QString转char*; see "main.cpp";
    name->s = ba0.data();
    QByteArray ba1 = cate_text.toLocal8Bit();
    cate->s = ba1.data();
    QByteArray ba2 = manu_text.toLocal8Bit();
    manu->s = ba2.data();
    QByteArray ba3 = appr_text.toLocal8Bit();
    appr->s = ba3.data();


    //qDebug
    qDebug()<<name->s;
    qDebug()<<cate->s;
    qDebug()<<manu->s;
    qDebug()<<appr->s;


    if(strlen(name->s) == 0 && strlen(cate->s) == 0 && strlen(manu->s) == 0 && strlen(appr->s) == 0){
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
        insertQMessage_Dialog *a = new insertQMessage_Dialog(0,tr("无该药品信息，是否添加?"));
        //a->setWindowFlags(Qt::FramelessWindowHint);
        a->setWindowTitle("提示");
        connect(a,SIGNAL(sendSignal(bool)),this,SLOT(receiveSignal(bool)));        
        a->exec();
        emit sendRefreshSignal(2);
        addFlag = 2;
    }
    else
    {
        ui->inStorage_tableWidget->clearContents();
        ui->inStorage_tableWidget->setRowCount(rowNum);
        for(int i = 0; i < rowNum; i++){
            //qDebug
            qDebug()<<"进入循环";
//            delete checkedBox;
        showTablewidget(i);
        //qDebug
        qDebug()<<"查询结束";
        }
        modelFlag = 1;

    }

}
//内存泄露


void inStorage_Dialog::inStorage_tableWidget_item_click(){
   curRow=ui->inStorage_tableWidget->currentRow();
   ui->name_comboBox->setEditText(model->record(curRow).value("name").toString());
   ui->manufacturer_comboBox->setEditText(model->record(curRow).value("manufacturer").toString());
   ui->category_comboBox->setEditText(model->record(curRow).value("category").toString());
   ui->approval_number_comboBox->setEditText(model->record(curRow).value("approval_number").toString());

   ui->inventory_lineEdit->setText(model->record(curRow).value("inventory").toString());

 //qDebug
   qDebug()<<curRow;

   IDNum = model->record(curRow).value("ID").toInt();
 //qDebug
   qDebug()<<"ID "<<IDNum;
   InventoryNum = model->record(curRow).value("inventory").toInt();
 //qDebug
   qDebug()<<"IventoryNum "<<InventoryNum;
}

void inStorage_Dialog::on_add_pushButton_clicked()
{
  //qDebug
    qDebug()<<ui->inStorage_tableWidget->currentRow();

    if(ui->inStorage_tableWidget->currentRow() == curRow){
//        delete ID;
//        delete Inventory;
        ID = new int[1];
        Inventory = new int[1];
        ID[0] = IDNum;
        Inventory[0] = InventoryNum;


        add_dialog = new Add_Dialog(0, ID, Inventory, 1, 1, addOperationFlag1);
        //add_dialog->setWindowFlags(Qt::FramelessWindowHint);
        add_dialog->setWindowTitle("数量设定");
        add_dialog->exec();
        emit sendRefreshSignal(addOperationFlag1[0]);
        addFlag = 0;
      //qDebug
        qDebug()<<"入库后返回是否刷新的信号"<<addOperationFlag1[0];
        addOperationFlag1[0] = -1;

//        delete ID;
//        delete Inventory;
    }
    else{
        loginQmessage_Dialog *a = new loginQmessage_Dialog(0,tr("请先单击选中要添加的项！"));
        //a->setWindowFlags(Qt::FramelessWindowHint);
        a->setWindowTitle("提示");
        a->exec();
    }
}


void inStorage_Dialog::on_out_pushButton_clicked()
{
    if(ui->inStorage_tableWidget->currentRow() == curRow){
//        delete ID;
//        delete Inventory;
        ID = new int[1];
        Inventory = new int[1];
        ID[0] = IDNum;
        Inventory[0] = InventoryNum;


        add_dialog = new Add_Dialog(0, ID, Inventory, 1, 0, addOperationFlag1);
        //add_dialog->setWindowFlags(Qt::FramelessWindowHint);
        add_dialog->setWindowTitle("数量设定");
        add_dialog->exec();
        emit sendRefreshSignal(addOperationFlag1[0]);
        addFlag = 0;
      //qDebug
        qDebug()<<"入库后返回是否刷新的信号"<<addOperationFlag1[0];
        addOperationFlag1[0] = -1;

//        delete ID;
//        delete Inventory;
    }
    else{
        loginQmessage_Dialog *a = new loginQmessage_Dialog(0,tr("请先单击选中要添加的项！"));
        //a->setWindowFlags(Qt::FramelessWindowHint);
        a->setWindowTitle("提示");
        a->exec();
    }
}


void inStorage_Dialog::on_batchAdd_pushButton_clicked()
{
    if(modelFlag == 0)
    {
        loginQmessage_Dialog *a = new loginQmessage_Dialog(0,tr("请先完成查询操作！"));
        //a->setWindowFlags(Qt::FramelessWindowHint);
        a->setWindowTitle("提示");
        a->exec();
    }
    else
    {
//            delete batchID;
//            delete batchInventory;
            batchID = new int[rowNum];
            batchInventory = new int[rowNum];
            for(int i = 0; i < rowNum; i++){
                batchID[i] = model->record(i).value("ID").toInt();
                batchInventory[i] = model->record(i).value("inventory").toInt();
            }


            batchAdd_dialog = new Add_Dialog(0, batchID, batchInventory, rowNum, 1, addOperationFlag2);
            //batchAdd_dialog->setWindowFlags(Qt::FramelessWindowHint);
            batchAdd_dialog->setWindowTitle("数量设定");
            batchAdd_dialog->exec();
            emit sendRefreshSignal(addOperationFlag2[0]);
            addFlag = 1;
          //qDebug
            qDebug()<<"批量入库后返回是否刷新的信号"<<addOperationFlag2[0];
            addOperationFlag2[0] = -1;

//            delete ID;
//            delete Inventory;
    }
}


void inStorage_Dialog::on_batchOut_pushButton_clicked()
{
    if(modelFlag == 0)
    {
        loginQmessage_Dialog *a = new loginQmessage_Dialog(0,tr("请先完成查询操作！"));
        //a->setWindowFlags(Qt::FramelessWindowHint);
        a->setWindowTitle("提示");
        a->exec();
    }
    else
    {
//            delete batchID;
//            delete batchInventory;
            batchID = new int[rowNum];
            batchInventory = new int[rowNum];
            for(int i = 0; i < rowNum; i++){
                batchID[i] = model->record(i).value("ID").toInt();
                batchInventory[i] = model->record(i).value("inventory").toInt();
            }


            batchAdd_dialog = new Add_Dialog(0, batchID, batchInventory, rowNum, 0, addOperationFlag2);
            //batchAdd_dialog->setWindowFlags(Qt::FramelessWindowHint);
            batchAdd_dialog->setWindowTitle("数量设定");
            batchAdd_dialog->exec();
            emit sendRefreshSignal(addOperationFlag2[0]);
            addFlag = 1;
          //qDebug
            qDebug()<<"批量入库后返回是否刷新的信号"<<addOperationFlag2[0];
            addOperationFlag2[0] = -1;

//            delete ID;
//            delete Inventory;
    }
}


void inStorage_Dialog::on_refresh_pushButton_clicked()
{
    if(addFlag == 0)
    {
        QString stringID = QString::number(ID[0],10);
        QString string = "select * from MedicineInfo where ID = '";
        string += stringID + "'";
        model->setQuery(string);
//        if(outFlag == 1 && equalRow[0] == 1){
//          //qDebug
//            qDebug()<<"库存不足提示！";
//            QString string = "approval_number 为'";
//            string += model->record(0).value("approval_number").toString() + "'的药品库存不足！";
//            loginQmessage_Dialog *a = new loginQmessage_Dialog(0,string);
//            a->setWindowFlags(Qt::FramelessWindowHint);
//            a->exec();
//        }
        //qDebug
        qDebug()<<string;
        ui->inStorage_tableWidget->clearContents();
        ui->inStorage_tableWidget->setRowCount(1);
        showTablewidget(0);

        ui->name_comboBox->setEditText(model->record(0).value("name").toString());
        ui->manufacturer_comboBox->setEditText(model->record(0).value("manufacturer").toString());
        ui->category_comboBox->setEditText(model->record(0).value("category").toString());
        ui->approval_number_comboBox->setEditText(model->record(0).value("approval_number").toString());

        ui->inventory_lineEdit->setText(model->record(0).value("inventory").toString());
    }
    else if(addFlag == 1)
    {
        QString ID;
        QString string = "select * from MedicineInfo where ID in (";
        for(int i = 0; i < rowNum; i++){
            ID = QString::number(batchID[i], 10);
            string += "'" + ID + "'";
            if(i == rowNum - 1){
                string += ")";
                break;
            }
            else{
                string += ",";
            }
        }
        model->setQuery(string);
        rowNum = model->rowCount();
        ui->inStorage_tableWidget->clearContents();
        ui->inStorage_tableWidget->setRowCount(rowNum);
        for(int i = 0; i < rowNum; i++){
            showTablewidget(i);
        }
        ui->name_comboBox->setEditText(model->record(0).value("name").toString());
        ui->manufacturer_comboBox->setEditText(model->record(0).value("manufacturer").toString());
        ui->category_comboBox->setEditText(model->record(0).value("category").toString());
        ui->approval_number_comboBox->setEditText(model->record(0).value("approval_number").toString());

        ui->inventory_lineEdit->setText(model->record(0).value("inventory").toString());

        //ui->inStorage_tableWidget->setCurrentIndex(1);
    }
    else if(addFlag == 2){
        model->setQuery("select * from MedicineInfo");
        rowNum = model->rowCount();
        ui->inStorage_tableWidget->clearContents();
        ui->inStorage_tableWidget->setRowCount(rowNum);
        for(int i = 0; i < rowNum; i++){
            showTablewidget(i);
        }
        ui->name_comboBox->setEditText(model->record(rowNum-1).value("name").toString());
        ui->manufacturer_comboBox->setEditText(model->record(rowNum-1).value("manufacturer").toString());
        ui->category_comboBox->setEditText(model->record(rowNum-1).value("category").toString());
        ui->approval_number_comboBox->setEditText(model->record(rowNum-1).value("approval_number").toString());

        ui->inventory_lineEdit->setText(model->record(rowNum-1).value("inventory").toString());
    }
    else if(addFlag == 3){
        model->setQuery("select * from MedicineInfo");
        rowNum = model->rowCount();
        ui->inStorage_tableWidget->clearContents();
        ui->inStorage_tableWidget->setRowCount(rowNum);
        for(int i = 0; i < rowNum; i++){
            showTablewidget(i);
        }
    }
}

void inStorage_Dialog::refresh(int a)
{
    if(a == 0)
    {
        QString stringID = QString::number(ID[0],10);
        QString string = "select * from MedicineInfo where ID = '";
        string += stringID + "'";
        model->setQuery(string);
        //qDebug
        qDebug()<<string;
        ui->inStorage_tableWidget->clearContents();
        ui->inStorage_tableWidget->setRowCount(1);
        showTablewidget(0);

        ui->name_comboBox->setEditText(model->record(0).value("name").toString());
        ui->manufacturer_comboBox->setEditText(model->record(0).value("manufacturer").toString());
        ui->category_comboBox->setEditText(model->record(0).value("category").toString());
        ui->approval_number_comboBox->setEditText(model->record(0).value("approval_number").toString());

        ui->inventory_lineEdit->setText(model->record(0).value("inventory").toString());
    }
    else if(a == 1)
    {
        QString ID;
        QString string = "select * from MedicineInfo where ID in (";
        for(int i = 0; i < rowNum; i++){
            ID = QString::number(batchID[i], 10);
            string += "'" + ID + "'";
            if(i == rowNum - 1){
                string += ")";
                break;
            }
            else{
                string += ",";
            }
        }
        model->setQuery(string);
        rowNum = model->rowCount();
        ui->inStorage_tableWidget->clearContents();
        ui->inStorage_tableWidget->setRowCount(rowNum);
        for(int i = 0; i < rowNum; i++){
            showTablewidget(i);
        }
        ui->name_comboBox->setEditText(model->record(0).value("name").toString());
        ui->manufacturer_comboBox->setEditText(model->record(0).value("manufacturer").toString());
        ui->category_comboBox->setEditText(model->record(0).value("category").toString());
        ui->approval_number_comboBox->setEditText(model->record(0).value("approval_number").toString());

        ui->inventory_lineEdit->setText(model->record(0).value("inventory").toString());

        //ui->inStorage_tableWidget->setCurrentIndex(1);
    }
    else if(a == 2){
        model->setQuery("select * from MedicineInfo");
        rowNum = model->rowCount();
        ui->inStorage_tableWidget->clearContents();
        ui->inStorage_tableWidget->setRowCount(rowNum);
        for(int i = 0; i < rowNum; i++){
            showTablewidget(i);
        }
        ui->name_comboBox->setEditText(model->record(rowNum-1).value("name").toString());
        ui->manufacturer_comboBox->setEditText(model->record(rowNum-1).value("manufacturer").toString());
        ui->category_comboBox->setEditText(model->record(rowNum-1).value("category").toString());
        ui->approval_number_comboBox->setEditText(model->record(rowNum-1).value("approval_number").toString());

        ui->inventory_lineEdit->setText(model->record(rowNum-1).value("inventory").toString());
    }
    else if(a == 3){
        model->setQuery("select * from MedicineInfo");
        rowNum = model->rowCount();
        ui->inStorage_tableWidget->clearContents();
        ui->inStorage_tableWidget->setRowCount(rowNum);
        for(int i = 0; i < rowNum; i++){
            showTablewidget(i);
        }
    }
    else if(a == 4){
        model->setQuery("select * from MedicineInfo");
        rowNum = model->rowCount();
        ui->inStorage_tableWidget->clearContents();
        ui->inStorage_tableWidget->setRowCount(rowNum);
        for(int i = 0; i < rowNum; i++){
            showTablewidget(i);
        }

        ui->name_comboBox->setEditText(model->record(curRow).value("name").toString());
        ui->manufacturer_comboBox->setEditText(model->record(curRow).value("manufacturer").toString());
        ui->category_comboBox->setEditText(model->record(curRow).value("category").toString());
        ui->approval_number_comboBox->setEditText(model->record(curRow).value("approval_number").toString());

        ui->inventory_lineEdit->setText(model->record(curRow).value("inventory").toString());
    }
}

void inStorage_Dialog::receiveSignal(bool a)
{
    if(1 == a){
        QString a = ui->name_comboBox->currentText();
        QString b = ui->manufacturer_comboBox->currentText();
        QString c = ui->approval_number_comboBox->currentText();
        QString d = ui->category_comboBox->currentText();
        insert_Dialog *insert = new insert_Dialog(0,a,b,c,d);
        //insert->setWindowFlags(Qt::FramelessWindowHint);
        insert->setWindowTitle("添加");
        insert->exec();

    }
}


void inStorage_Dialog::showTablewidget(int i)
{
    StringName = model->record(i).value("name").toString();
    StringManufacturer = model->record(i).value("manufacturer").toString();
    StringCategory = model->record(i).value("category").toString();
    StringApproval_number = model->record(i).value("approval_number").toString();

    StringInventory = model->record(i).value("inventory").toString();

//    //qDebug
//    qDebug()<<"开始checkBox";
//        checkedBox = new QTableWidgetItem();
//        checkedBox->setCheckState(Qt::Unchecked);
//        ui->inStorage_tableWidget->setItem(i,0,checkedBox);
//        //qDebug
//        qDebug()<<"结束checkBox";

        nameItem=new QTableWidgetItem(StringName);
        ui->inStorage_tableWidget->setItem(i,0,nameItem);

        manufacturerItem=new QTableWidgetItem(StringManufacturer);
        ui->inStorage_tableWidget->setItem(i,1,manufacturerItem);

        categoryItem=new QTableWidgetItem(StringCategory);
        ui->inStorage_tableWidget->setItem(i,2,categoryItem);

        approval_numberItem=new QTableWidgetItem(StringApproval_number);
        ui->inStorage_tableWidget->setItem(i,3,approval_numberItem);

        inventoryItem=new QTableWidgetItem(StringInventory);
        ui->inStorage_tableWidget->setItem(i,4,inventoryItem);
}


//void inStorage_Dialog::checkBoxChanged(int row, int col)
//{
//    int num;
//    if(ui->inStorage_tableWidget->item(row,col)->checkState() == Qt::Checked){
//        ID = (int *)realloc(ID, 1*sizeof(int));
//        Inventory = (int *)realloc(Inventory, 1*sizeof(int));
//        num = sizeof(ID)/sizeof(int);
//        ID[num] = model->record(row).value("ID").toInt();
//        Inventory[num] = model->record(row).value("Inventory").toInt();
//      //qDebug
//        for(int a = 0; a < num; a++){
//            qDebug()<<ID[a]<<"||";
//        }
//        for(int a = 0; a < num; a++){
//            qDebug()<<Inventory[a]<<"||";
//        }
//    }
//    else if(ui->inStorage_tableWidget->item(row,col)->checkState() == Qt::Unchecked){
//        int i;
//        num = sizeof(ID)/sizeof(int);
//        tempID = (int *)realloc(tempID, (num-1)*sizeof(int));
//        tempInventory = (int *)realloc(tempInventory, (num-1)*sizeof(int));
//        for(i = 0; i < num; i++){
//            if(ID[i] == model->record(row).value("ID").toInt()){
//             break;
//            }
//        }
//        for(int j = 0; j < num; j++){
//            if(j != i){
//                tempID[j] = ID[j];
//                tempInventory[j] = Inventory[j];
//            }
//            else{
//                continue;
//            }
//        }
//        ID = (int *)realloc(ID, (num-1)*sizeof(int));
//        Inventory = (int *)realloc(Inventory, (num-1)*sizeof(int));
//        for(int i = 0; i < num - 1; i++){
//            ID[i] = tempID[i];
//            Inventory[i] = tempInventory[i];
//        }
//      //qDebug
//        for(int a = 0; a < num; a++){
//            qDebug()<<ID[a]<<"||";
//        }
//        for(int a = 0; a < num; a++){
//            qDebug()<<Inventory[a]<<"||";
//        }
//    }
//}

void inStorage_Dialog::clockChange()
{
    ui->lcdNumber->display(QTime::currentTime().toString("hh:mm:ss"));
}

void inStorage_Dialog::on_moveOut_pushButton_clicked()
{
    rowNum = model->rowCount();
    int *intID = new int[rowNum-1];
    QString string = "";
    QString stringID = "";

    int curRow=ui->inStorage_tableWidget->currentRow();
  //qDebug
    qDebug()<<curRow;

    int IDNum = model->record(curRow).value("ID").toInt();
  //qDebug
    qDebug()<<"ID "<<IDNum;


    for(int i = 0, j = 0; i < rowNum - 1, j < rowNum; i++, j++){
      //qDebug
        qDebug()<<"进入循环";
        if(i != curRow){
            //qDebug
              qDebug()<<"进入循环 1";
            intID[i] = model->record(j).value("ID").toInt();
        }
        else{
            //qDebug
              qDebug()<<"进入循环 2";
            intID[i] = model->record(++j).value("ID").toInt();
        }
    }

    string += "select * from MedicineInfo where ID in (";
    for(int j = 0; j < rowNum-1; j++){
      //qDebug
        qDebug()<<"进入字符串循环";
        stringID = QString::number(intID[j], 10);
        string += "'" + stringID + "'";
        if(j == rowNum - 2){
          //qDebug
            qDebug()<<"进入字符串循环 1";
            string += ")";
            break;
        }
        else{
          //qDebug
            qDebug()<<"进入字符串循环 2";
            string += ",";
        }
    }

  //qDebug
    qDebug()<<string;

    model->setQuery(string);
    rowNum = model->rowCount();
    ui->inStorage_tableWidget->clearContents();
    ui->inStorage_tableWidget->setRowCount(rowNum);
    for(int i = 0; i < rowNum; i++){
        showTablewidget(i);
    }
}

void inStorage_Dialog::on_checkDiary_pushButton_clicked()
{
    CheckDiary_Dialog *dialog = new CheckDiary_Dialog();
    //dialog->setWindowFlags(Qt::FramelessWindowHint);
    dialog->setWindowTitle("操作记录");
    dialog->exec();
}

void inStorage_Dialog::on_delete_pushButton_clicked()
{
    if(curRow == ui->inStorage_tableWidget->currentRow()){
        insertQMessage_Dialog *dialog = new insertQMessage_Dialog(0,tr("将会从数据库中删除此条数据，是否继续？"));
        //dialog->setWindowFlags(Qt::FramelessWindowHint);
        dialog->setWindowTitle("提示");
        connect(dialog,SIGNAL(sendSignal(bool)),this,SLOT(receiveDeleteSig(bool)));
        dialog->exec();
    }
    else{
        loginQmessage_Dialog *a = new loginQmessage_Dialog(0,tr("请先选中某行！"));
        //a->setWindowFlags(Qt::FramelessWindowHint);
        a->setWindowTitle("提示");
        a->exec();
    }
}

void inStorage_Dialog::receiveDeleteSig(bool a)
{
    if(a == 1){
        QSqlQuery query;
        QString approval_number = model->record(curRow).value("approval_number").toString();
        QString sql = "delete from MedicineInfo where approval_number = '";
        sql += approval_number + "'";
      //qDebug
        qDebug()<<sql;
        query.exec(sql);
        emit sendRefreshSignal(3);
        addFlag = 3;
    }
}

void inStorage_Dialog::on_detail_pushButton_clicked()
{
    if(curRow == ui->inStorage_tableWidget->currentRow()){
        QString approval_number = model->record(curRow).value("approval_number").toString();
        detail_Dialog *dialog = new detail_Dialog(0,approval_number);
        //dialog->setWindowFlags(Qt::FramelessWindowHint);
        dialog->setWindowTitle("详细信息");
        dialog->exec();
        emit sendRefreshSignal(4);
        addFlag = 4;
    }
    else{
        loginQmessage_Dialog *a = new loginQmessage_Dialog(0,tr("请先选中某行！"));
        //a->setWindowFlags(Qt::FramelessWindowHint);
        a->setWindowTitle("提示");
        a->exec();
    }
}

void inStorage_Dialog::on_showAll_pushButton_clicked()
{
    ui->name_comboBox->setEditText("");
    ui->manufacturer_comboBox->setEditText("");
    ui->category_comboBox->setEditText("");
    ui->approval_number_comboBox->setEditText("");
}
