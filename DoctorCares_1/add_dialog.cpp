#include "add_dialog.h"
#include "ui_add_dialog.h"
#include "diarythread.h"
#include <QFile>
#include <QTextStream>

Add_Dialog::Add_Dialog(QWidget *parent, int ID[], int Inventory[], int rowNum, int operationFlag, int *addOperationFlag) :
    QDialog(parent),
    ui(new Ui::Add_Dialog)
{
    ui->setupUi(this);

    QFile file(":/qstylesheet.qss");
        if(file.open(QFile::ReadOnly))
        {
            QTextStream filetext(&file);
            QString stylesheet = filetext.readAll();
            //ui->quit_pushButton->setStyleSheet(stylesheet);
            ui->done_pushButton->setStyleSheet(stylesheet);
            ui->revocation_pushButton->setStyleSheet(stylesheet);
            ui->confirm_pushButton->setStyleSheet(stylesheet);
        }

    ui->remind_label->setStyleSheet("QLabel{font:bold;font-size:14px;color:black;background-color:rgba(0,0,0,0)}");
    //ui->addQuantity_spinBox->setStyleSheet("QSpinBox{font:bold;font-size:14px;color:black;background-color:skyblue}");

    ui->addQuantity_spinBox->setStyleSheet("QSpinBox{border:2px solid gray;}"
      "QSpinBox{font:bold;font-size:30px;color:black;}"
      "QSpinBox{background-color:rgba(0,0,0,50)}"
      "QSpinBox::down-arrow{border-image:url(:/down4.png);background-color:rgba(0,0,0,150)}"
      "QSpinBox::up-arrow{border-image:url(:/up4.png);background-color:rgba(0,0,0,150)}");
//样式

//    ui->remind_label->setGeometry(QRect(328, 240, 329, 27*4));  //四倍行距
//    ui->remind_label->setWordWrap(true);
//    ui->remind_label->setAlignment(Qt::AlignTop);

    operation = operationFlag;

    addOperation1 = addOperationFlag;

    rowNumFlag = rowNum;


        batchIDNumber = new int[rowNumFlag];
        batchINNumber = new int[rowNumFlag];
        for(int i = 0; i < rowNumFlag; i++){
            batchIDNumber[i] = ID[i];
            batchINNumber[i] = Inventory[i];
        }
        batchInventoryNumber = new int[rowNumFlag];

        minIN = batchINNumber[0];

        for(int i = 1; i < rowNumFlag; i++){
            if(batchINNumber[i] < minIN){
                minIN = batchINNumber[i];
            }
        }
        //minID = batchIDNumber[i];

        if(operation == 0){
          connect(ui->addQuantity_spinBox, SIGNAL(valueChanged(int)), this, SLOT(remind()));
        }
    update = "";
    tempUpdate = "";
    StringIN = "";
    StringID = "";

    //equal = equalRow;
    equalNum = 0;
    flag = -1;

}

Add_Dialog::~Add_Dialog()
{
    delete this;
    delete ui;
}

void Add_Dialog::on_quit_pushButton_clicked()
{
    //addOperation[0] = 1;
    this->close();
}

void Add_Dialog::on_confirm_pushButton_clicked()
{
    if(ui->addQuantity_spinBox->value() == 0){
        loginQmessage_Dialog *a = new loginQmessage_Dialog(0, tr("操作数目为零！"));
        //a->setWindowFlags(Qt::FramelessWindowHint);
        a->setWindowTitle("提示");
        a->exec();
    }
    else if(operation == 1)
    {
//        delete diaryID;
        diaryID = new int[rowNumFlag];
            for(int i = 0; i < rowNumFlag; i++){
              //qDebug
                qDebug()<<"进入循环";
                diaryID[i] = batchIDNumber[i];
                batchInventoryNumber[i] = batchINNumber[i] + ui->addQuantity_spinBox->value();
                StringIN = "";
                StringID = "";
                StringIN = QString::number(batchInventoryNumber[i], 10);
                StringID = QString::number(batchIDNumber[i], 10);
                tempUpdate = "";
                tempUpdate += "update MedicineInfo set inventory = ";
                tempUpdate += StringIN;
                tempUpdate += " where ID = '";
                tempUpdate += StringID + "';";
              //qDebug
                qDebug()<<tempUpdate;
                update += tempUpdate;
              //qDebug
                qDebug()<<update;
            }
    }
    else if(operation == 0)
    {
//        delete diaryID;
        diaryID = new int[rowNumFlag];
        for(int j = 0; j < rowNumFlag; j++){
            //qDebug
              qDebug()<<"进入循环";
              batchInventoryNumber[j] = batchINNumber[j] - ui->addQuantity_spinBox->value();
              if(batchInventoryNumber[j] < 0){
                  batchInventoryNumber[j] = batchINNumber[j];

                  diaryID[j] = -1;
              }
              else{
                  diaryID[j] = batchIDNumber[j];
              }
        }
        for(int i = 0; i < rowNumFlag; i++){
            StringIN = "";
            StringID = "";
            StringIN = QString::number(batchInventoryNumber[i], 10);
            StringID = QString::number(batchIDNumber[i], 10);
            tempUpdate = "";
            tempUpdate += "update MedicineInfo set inventory = ";
            tempUpdate += StringIN;
            tempUpdate += " where ID = '";
            tempUpdate += StringID + "';";
          //qDebug
            qDebug()<<tempUpdate;
            update += tempUpdate;
          //qDebug
            qDebug()<<update;
        }

    }
    flag = 1;
}

void Add_Dialog::on_done_pushButton_clicked()
{
    if(flag == -1)
    {
        loginQmessage_Dialog *a = new loginQmessage_Dialog(0, tr("请选择操作或取消！"));
        //a->setWindowFlags(Qt::FramelessWindowHint);
        a->setWindowTitle("提示");
        a->exec();
    }
    else if(flag == 1){
        if(rowNumFlag == 1){
            addOperation1[0] = 0;
        }
        else{
            addOperation1[0] = 1;
        }
        int index = 0;
        for(int i = 0; i < rowNumFlag; i++){
            index = update.indexOf(";");
            query.exec(update.mid(0,index+1));
            update.remove(0,index+1);
          //qDebug
            qDebug()<<update;
        }

        if(operation == 1){
            //qDebug
              qDebug()<<"打开线程";
              DiaryThread *outDiaryThread = new DiaryThread(this, diaryID, rowNumFlag, ui->addQuantity_spinBox->value(), operation);
              outDiaryThread->start();
            //qDebug
              qDebug()<<"进入线程";
        }
        else if(operation == 0){
         //qDebug
           qDebug()<<"打开线程";
           DiaryThread *outDiaryThread = new DiaryThread(this, diaryID, rowNumFlag, ui->addQuantity_spinBox->value(), operation);
           outDiaryThread->start();
         //qDebug
           qDebug()<<"进入线程";
        }
        this->close();
    }
    else if(flag == 0)
    {
        this->close();
    }


}

void Add_Dialog::on_revocation_pushButton_clicked()
{
    ui->addQuantity_spinBox->setValue(0);

    flag = 0;
}

void Add_Dialog::remind()
{
    if(ui->addQuantity_spinBox->value() > minIN){
        ui->remind_label->setText("数量超出库存，若继续，\n库存不足的药品将被保留！");
    }
    else{
        ui->remind_label->setText("");
    }
}
