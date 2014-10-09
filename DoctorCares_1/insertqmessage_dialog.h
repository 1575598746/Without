#ifndef INSERTQMESSAGE_DIALOG_H
#define INSERTQMESSAGE_DIALOG_H

#include <QDialog>

namespace Ui {
class insertQMessage_Dialog;
}

class insertQMessage_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit insertQMessage_Dialog(QWidget *parent = 0, QString str = "");
    ~insertQMessage_Dialog();

signals:
    void sendSignal(bool);
    
private slots:
    void on_comfirm_pushButton_clicked();

    void on_negative_pushButton_clicked();

private:
    Ui::insertQMessage_Dialog *ui;
};

#endif // INSERTQMESSAGE_DIALOG_H
