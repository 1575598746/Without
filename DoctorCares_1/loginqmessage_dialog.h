#ifndef LOGINQMESSAGE_DIALOG_H
#define LOGINQMESSAGE_DIALOG_H

#include <QDialog>

namespace Ui {
class loginQmessage_Dialog;
}

class loginQmessage_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit loginQmessage_Dialog(QWidget *parent = 0, QString str = "");
    ~loginQmessage_Dialog();
    
private:
    Ui::loginQmessage_Dialog *ui;

private slots:
    void window_close();

};

#endif // LOGINQMESSAGE_DIALOG_H
