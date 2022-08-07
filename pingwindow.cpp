#include "pingwindow.h"
#include "./ui_pingwindow.h"
#include "sub_add_ping_object.h"

PingWindow::PingWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PingWindow)
{
    ui->setupUi(this);
//    time = QTime::currentTime();
//    text = time.toString("hh:mm:ss");
//    QObject::connect(timer,SIGNAL(timeout()), this, SLOT(timer_overflow()));
//    ui->timlocal->setText(text);
//    time = 0;
//    timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(timer_slot()));
//    timer->start(1);
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


