#ifndef PINGWINDOW_H
#define PINGWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class PingWindow; }
QT_END_NAMESPACE

class PingWindow : public QMainWindow
{
    Q_OBJECT

public:
    PingWindow(QWidget *parent = nullptr);
    ~PingWindow();

private slots:
    void on_actionClose_triggered();

    void on_actionAdd_IP_triggered();

    void on_actionBild_triggered();

    void timerTimeout();

    void Clock();

private:
    Ui::PingWindow *ui;
    QString text;
    QTime *time;

protected:
    QVector<QPair<QString, QString>> base = {};
};
#endif // PINGWINDOW_H
