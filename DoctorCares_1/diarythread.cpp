#include "diarythread.h"
#include <QDebug>
#include <QSqlRecord>

DiaryThread::DiaryThread(QObject *parent, int diaryID[], int rowNumFlag, int value, int operation) :
    QThread(parent)
{
    threadModel = new QSqlQueryModel();
    model = new QSqlQueryModel();
    rowNum = rowNumFlag;
    inDiaryID = new int[rowNumFlag];
    for(int i = 0; i < rowNumFlag; i++){
        inDiaryID[i] = diaryID[i];
    }
    outRowNum = 0;
    QString stringID;
    modelString = "select * from MedicineInfo where ID in (";
    for(int i = 0; i < rowNum; i++){
        if(inDiaryID[i] != -1){
            outRowNum++;
            stringID = QString::number(inDiaryID[i], 10);
            modelString += "'" + stringID + "'";
            if(i == rowNum - 1){
                modelString += ")";
                break;
            }
            else{
                modelString += ",";
            }
        }
    }
  //qDebug
    qDebug()<<modelString;

    threadModel->setQuery(modelString);
  //qDebug
    qDebug()<<"线程中的model";

    operateValue = value;

    operate = operation;
}

void DiaryThread::run()
{
  //qDebug
    qDebug()<<"线程开始运行";
    current_date = QDate::currentDate();
    QString date = current_date.toString("yyyy-MM-dd");
    QString stringValue = QString::number(operateValue, 10);
    QString string = "";

    model->setQuery("select keyID from Diary");
    int row = model->rowCount() + 1;
//    int maxID = -1;
//    for(int i = 0; i < rowNum; i++){
//        if(model->record(i).value("keyID").toInt() > maxID){
//            maxID = model->record(i).value("keyID").toInt();
//        }
//    }
    QString stringRownum = QString::number(row, 10);

    if(operate == 0){
        for(int i = 0; i < outRowNum; i++){
            string += "insert into Diary values (";
            string += "'" + threadModel->record(i).value("ID").toString() + "',";
            string += "'" + threadModel->record(i).value("name").toString() + "',";
            string += "'" + threadModel->record(i).value("manufacturer").toString() + "',";
            string += "'" + threadModel->record(i).value("approval_number").toString() + "',";
            string += stringValue + ",";
            string += "'出库',";
            string += "'1',";
            string += "'" + date + "',";
            string += "'" + stringRownum + "'";
            string += ");";
            stringRownum = QString::number(++row, 10);
        }
      //qDebug
        qDebug()<<string;

    }
    else if(operate == 1){
        for(int i = 0; i < outRowNum; i++){
            string += "insert into Diary values (";
            string += "'" + threadModel->record(i).value("ID").toString() + "',";
            string += "'" + threadModel->record(i).value("name").toString() + "',";
            string += "'" + threadModel->record(i).value("manufacturer").toString() + "',";
            string += "'" + threadModel->record(i).value("approval_number").toString() + "',";
            string += stringValue + ",";
            string += "'入库',";
            string += "'1',";
            string += "'" + date + "',";
            string += "'" + stringRownum + "'";
            string += ");";
            stringRownum = QString::number(++row, 10);
        }
      //qDebug
        qDebug()<<string; 
    }
    int index;
    for(int i = 0; i < outRowNum; i++){
        index = string.indexOf(";");
        query.exec(string.mid(0,index+1));
      //qDebug
        qDebug()<<string.mid(0,index+1);
        string.remove(0,index+1);
    }
}
