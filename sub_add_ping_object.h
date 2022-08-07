#ifndef SUB_ADD_PING_OBJECT_H
#define SUB_ADD_PING_OBJECT_H

#include <QDialog>
#include <QVector>
#include <QGridLayout>//
#include <QtWidgets>//
#include <QLineEdit>//
#include <QDebug>//
#include <QMessageBox>//

namespace Ui {
class Sub_Add_Ping_Object;
}

class Sub_Add_Ping_Object : public QDialog
{
    Q_OBJECT

public:
    explicit Sub_Add_Ping_Object(QWidget *parent = nullptr);
    ~Sub_Add_Ping_Object();

public:
    QVector<QPair<QString, QString>> base = {};

private slots:
    void on_buttonBox_accepted();

    void on_add_new_lineedit_clicked(); //Реакция на ADD в дочернем окне.

    void on_del_lineedit_clicked();//Реакция на DEL в дочернем окне.

private:
    Ui::Sub_Add_Ping_Object *ui;

private:
    QVector<QPair<QLineEdit*, QLineEdit*>> base_ref;
   int count_line_e = 0;//
};

#endif // SUB_ADD_PING_OBJECT_H
