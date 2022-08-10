#include "pingwindow.h"
#include "./ui_pingwindow.h"
#include "sub_add_ping_object.h"

void PingWindow::timerTimeout()
{
    ui->Local_Time->setText(QTime::currentTime().toString());
}

PingWindow::PingWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PingWindow)
{
    ui->setupUi(this);
    Clock();
}

PingWindow::~PingWindow()
{
    delete ui;
}


void PingWindow::on_actionClose_triggered()
{
    QApplication::quit();
}


void PingWindow::on_actionAdd_IP_triggered()
{
    Sub_Add_Ping_Object add_object;
    add_object.setModal(true);
    add_object.exec();
    base = add_object.base;
}


void PingWindow::on_actionBild_triggered() //Нажатие на Сабменю Bild
{
    for(const auto& name_ip : base){
        QLabel *for_label = new QLabel;
        for_label->setText(name_ip.first);
        ui->status_layout->addWidget(for_label);
    }
}

void PingWindow::Clock(){
    QTimer *timer = new QTimer;
    time = new QTime;
    ui->Local_Time->setText(QTime::currentTime().toString());
    ui->Local_Time->setStyleSheet(" font-size:18pt; font-weight:700;");
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
    timer->start(1000);
}


