#include <QtGui/QApplication>
#include "login_dialog.h"
#include "getuserdatabase.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("macintosh");


    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());  //�����ĵ�QStringתchar*;
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    getUserDatabase UserDatabase;
    UserDatabase.createConnection("UserIDStatus.db3");
    UserDatabase.createTables();
    UserDatabase.createDatabase();

    LogIn_Dialog w;
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB18030"));
    w.setWindowTitle("��¼");
    //w.setWindowFlags(Qt::FramelessWindowHint);
    w.show();
    
    return a.exec();
}
