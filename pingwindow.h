#ifndef PINGWINDOW_H
#define PINGWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>

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

private:
    Ui::PingWindow *ui;
    QTime time;
    QString text;
    QTimer *timer;//

protected:
    QVector<QPair<QString, QString>> base = {};
};
#endif // PINGWINDOW_H
