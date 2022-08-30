#include "pingwindow.h"
#include "./ui_pingwindow.h"
#include "sub_add_ping_object.h"

#include <iostream>
#include <string>

bool PingWindow::ping_(const QString& ip){
    QStringList parameters;

    #if defined(WIN32)
    parameters << "-n" << "1" << "-l" << "1" << "-w" << "3000";
    #else
    parameters << "-c 1";
    #endif

    parameters << ip;
    QProcess proc;
    proc.start("ping", parameters);
    proc.waitForFinished();
    auto data_byte = proc.readAllStandardOutput();
    if (data_byte.size() > 250) {
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


void PingWindow::on_actionAdd_IP_triggered() //Нажатие на Сабменю Add ip
{
    Sub_Add_Ping_Object add_object;
    add_object.setModal(true);
    add_object.exec();
    base_outer = add_object.base;
    status_timer_outer = add_object.status_timer;
}

struct color_str{
    const QString red = "font-size:18pt; color: rgb(255, 0, 0)";
    const QString green = "font-size:18pt; color: rgb(50, 150, 10)";
    const QString grey = "font-size:18pt; color: rgb(127, 127, 0)";
};

QString PingWindow::answer_color(const QString& ip){
    color_str color;
    if(ping_(ip)) return color.green;
    else return color.red;
}

void PingWindow::worck_to_log(const QString& str, bool del_status = false){
    QLabel *log_label = new QLabel;
    if(log_status.count(str) == 0){
        log_status.push_back(str);
        QString str_log;
        str_log += str + " is missing - " + QTime::currentTime().toString();
        log_label->setStyleSheet("font-size:8pt");
        log_label->setText(str_log);
        ui->log_layout->addWidget(log_label);
    }
    else{
        if(del_status){
            QString str_log;
            str_log += str + " is appeared - " + QTime::currentTime().toString();
            log_label->setStyleSheet("font-size:8pt");
            log_label->setText(str_log);
            ui->log_layout->addWidget(log_label);
            const auto it = std::find(log_status.begin(), log_status.end(), str);
            log_status.erase(it);
        }
    }
}

void PingWindow::reading_update(){ // SLOT для проверки доступности хоста
    for(int i = 0; i < base_outer.size(); ++i){
        QThread *thr = new QThread();
        QString str = answer_color(base_outer[i].second);
        color_str color;
        if(str == color.red){ //Задержка в 3 цикла для смены цвета на красный
            if (status_timer_outer.value(base_outer[i].first) >= 3){
                labels_in_status[i]->setStyleSheet(str);
                worck_to_log(base_outer[i].first);
            }
            else {
                status_timer_outer[base_outer[i].first]++;
                qDebug() << status_timer_outer;
                labels_in_status[i]->setStyleSheet(color.grey);
            }
        }
        else {
            labels_in_status[i]->setStyleSheet(str);
            status_timer_outer[base_outer[i].first] = 0;
            if(log_status.count(base_outer[i].first) != 0){
                worck_to_log(base_outer[i].first, true);
            }
        }
        labels_in_status[i]->setText(base_outer[i].first);
        thr->start();
    }
}

void PingWindow::on_actionBild_triggered() //Нажатие на Сабменю Bild
{
    color_str color;
    for(int i = 0; i < base_outer.size(); ++i){
        QLabel *lab_show_result_ping = new QLabel;
        lab_show_result_ping->setStyleSheet(color.grey);
        lab_show_result_ping->setText(base_outer[i].first);
        ui->status_layout->addWidget(lab_show_result_ping);
        labels_in_status.push_back(lab_show_result_ping);
    }
    QTimer *timer_update = new QTimer;
    connect(timer_update, SIGNAL(timeout()), this, SLOT(reading_update()));
    timer_update->start(10000);

    ui->status_layout->addStretch(); // Смещение результатов пинга вверх в ЛойаутБоксе
}

void PingWindow::Clock(){ //Часы вправом верхнем углу.
    QTimer *timer = new QTimer;
    time = new QTime;
    ui->Local_Time->setText(QTime::currentTime().toString());
    ui->Local_Time->setStyleSheet(" font-size:18pt; font-weight:700;");
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout())); // НУЖНО РАЗОБРАТСЯ!!!!! ЭТО ОСНОВЫ!!!
    timer->start(1000);
}

void PingWindow::on_actionSave_triggered() // Нажатие на сабменю Save
{
    QJsonArray tmp_array;
    for(const auto& [name, ip] : base_outer){
        QJsonArray tmp_array2({name, ip});
        tmp_array.push_back(tmp_array2);
    }
    QJsonDocument doc;
    doc.setArray(tmp_array);
    QFile file("date.txt");
    if (file.open(QIODevice::WriteOnly))
    {
        //qDebug() << "FILE OPEN!!!";
        QString JSON__(doc.toJson());
        QTextStream stream(&file);
        stream << JSON__;
        file.close();
    }
}


void PingWindow::on_actionLoad_triggered() //Нажати на сабменю Load
{
    QFile file("date.txt");
    base_outer.clear();
    status_timer_outer.clear();
    if (file.open(QIODevice::ReadOnly)){
        auto data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        for(const auto& pair_str : doc.array()){
            base_outer.push_back(std::make_pair(pair_str[0].toString(), pair_str[1].toString()));
            status_timer_outer[pair_str[0].toString()] = 0;
        }
    }
}

