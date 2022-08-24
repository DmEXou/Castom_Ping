#include "pingwindow.h"
#include "./ui_pingwindow.h"
#include "sub_add_ping_object.h"

bool PingWindow::ping_(const QString& ip){
    QStringList parameters;

    #if defined(WIN32)
    parameters << "-n" << "1" << "-l" << "1" << "-w" << "500";
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

QString PingWindow::answer_color(const QString& ip){
    QString color_lable;
    if(ping_(ip)){
        color_lable = "rgb(50, 150, 10)";
    }
    else{
        color_lable = "rgb(255, 0, 0)";
    }
    color_lable.push_front("font-size:18pt; color: ");
    return color_lable;
}

void PingWindow::reading_update(){ //TEST SLOT
    for(int i = 0; i < base.size(); ++i){
        labels_in_status[i]->setStyleSheet(answer_color(base[i].second));
        labels_in_status[i]->setText(base[i].first);
    }
}

void PingWindow::on_actionBild_triggered() //Нажатие на Сабменю Bild
{
    for(int i = 0; i < base.size(); ++i){
        QLabel *lab_show_result_ping = new QLabel;
        lab_show_result_ping->setStyleSheet("font-size:18pt; color: rgb(127, 127, 0)");
        lab_show_result_ping->setText(base[i].first);
        ui->status_layout->addWidget(lab_show_result_ping);
        labels_in_status.push_back(lab_show_result_ping);
    }
    QTimer *timer_update = new QTimer;
    connect(timer_update, SIGNAL(timeout()), this, SLOT(reading_update()));//
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
    for(const auto& [name, ip] : base){
        QJsonArray tmp_array2({name, ip});
        tmp_array.push_back(tmp_array2);
    }
    QJsonDocument doc;
    doc.setArray(tmp_array);
    QFile file("date.txt");
    if (file.open(QIODevice::WriteOnly))
    {
        qDebug() << "FILE OPEN!!!";
        QString JSON__(doc.toJson());
        QTextStream stream(&file);
        stream << JSON__;
        file.close();
    }
}


void PingWindow::on_actionLoad_triggered() //Нажати на сабменю Load
{
    QFile file("date.txt");
    base.clear();
    if (file.open(QIODevice::ReadOnly)){
        auto data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        for(const auto& pair_str : doc.array()){
            base.push_back(std::make_pair(pair_str[0].toString(), pair_str[1].toString()));
        }
    }
}

