#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "coliseu.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    coliseu romano;
    //int wtps;
    //int rtps;
protected:
    void paintEvent(QPaintEvent *e);
private slots:
    void on_buttom_on_clicked();
};

#endif // DIALOG_H
