#ifndef PINGWINDOW_H
#define PINGWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QElapsedTimer>
#include <QJsonObject>
#include <QFile>
#include <QLabel>
#include <QMap>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class PingWindow; }
QT_END_NAMESPACE

class PingWindow : public QMainWindow
{
    Q_OBJECT

public:
    PingWindow(QWidget *parent = nullptr);
    ~PingWindow();

    bool ping_(const QString& ip);
    QString answer_color(const QString& ip);
    void worck_to_log(const QString&, bool);

private slots:
    void on_actionClose_triggered();

    void on_actionAdd_IP_triggered();

    void on_actionBild_triggered();

    void timerTimeout();

    void Clock();

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

    void reading_update();

private:
    Ui::PingWindow *ui;
    QString text;
    QTime *time;
    QJsonObject JsonObject;
    QVector<QLabel*> labels_in_status;
    QVector<QString> log_status;

protected:
    QVector<QPair<QString, QString>> base_outer = {};
    QMap<QString, int> status_timer_outer;
};
#endif // PINGWINDOW_H
