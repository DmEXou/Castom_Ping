#include "pingwindow.h"
#include "./ui_pingwindow.h"
#include "sub_add_ping_object.h"

bool PingWindow::ping_(const QString& ip){
    QStringList parameters;

    #if defined(WIN32)
    parameters << "-n" << "1" << "-l" << "0" << "-w" << "200";
    #else
    parameters << "-c 1";
    #endif

    parameters << ip;
    int exitCode = QProcess::execute("ping", parameters);
    qDebug() << parameters;
    if (exitCode == 0) {
        return true;
    } else {
        return false;
    }
}

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


void PingWindow::on_actionAdd_IP_triggered() //Надатие на Сабменю Add ip
{
    Sub_Add_Ping_Object add_object;
    add_object.setModal(true);
    add_object.exec();
    base = add_object.base;
}

QString PingWindow::TEST(const QString& ip){
    QString color_lable;
    if(ping_(ip)){
        color_lable = "rgb(50, 150, 10)";
    }
    else{
        color_lable = "rgb(255, 0, 0)";
    }
    color_lable.push_front("color: ");
    return color_lable;
}

void PingWindow::on_actionBild_triggered() //Нажатие на Сабменю Bild
{
    for(const auto& name_ip : base){
        QLabel *for_label = new QLabel;
        //for_label->setStyleSheet("128, 128, 128");
        for_label->setStyleSheet(TEST(name_ip.second));
        for_label->setText(name_ip.first);
        ui->status_layout->addWidget(for_label);
    }

//    for(const auto& name_ip : base){

//        std::future<QString> f;
//        f = std::async(TEST(name_ip.second), name_ip.second);
//    }

    //std::vector<std::future<std::string>> fv = {};
    //fv.resize(base.size());

    //        if(ping_(name_ip.second)){
    //            color_lable = "rgb(50, 150, 10)";
    //        }
    //        else{
    //            color_lable = "rgb(255, 0, 0)";
    //        }
    //        color_lable.push_front("color: ");
}

void PingWindow::Clock(){
    QTimer *timer = new QTimer;
    time = new QTime;
    ui->Local_Time->setText(QTime::currentTime().toString());
    ui->Local_Time->setStyleSheet(" font-size:18pt; font-weight:700;");
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
    timer->start(1000);
}
