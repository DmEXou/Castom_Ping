#ifndef PINGWINDOW_H
#define PINGWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QElapsedTimer>
//#include <future>
#include <QJsonObject>
//#include <QJSonDocument>
#include <QFile>

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

signals:
    void test();

private slots:
    void on_actionClose_triggered();

    void on_actionAdd_IP_triggered();

    void on_actionBild_triggered();

    void timerTimeout();

    void Clock();

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

private:
    Ui::PingWindow *ui;
    QString text;
    QTime *time;
    QJsonObject JsonObject;

protected:
    QVector<QPair<QString, QString>> base = {};
};
#endif // PINGWINDOW_H
