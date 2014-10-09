#ifndef DIARYTHREAD_H
#define DIARYTHREAD_H

#include <QThread>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class DiaryThread : public QThread
{
    Q_OBJECT
public:
    explicit DiaryThread(QObject *parent = 0, int diaryID[] = NULL, int rowNumFlag = -1, int value = -1, int operation = -1);
    
signals:
    
protected:
    void run();

private:
    QSqlQuery query;
    QSqlQueryModel *threadModel;
    QSqlQueryModel *model;
    QDate current_date;

    QString modelString;

    int *inDiaryID;
    int operateValue;
    int operate;
    int rowNum;
    int outRowNum;
};

#endif // DIARYTHREAD_H
