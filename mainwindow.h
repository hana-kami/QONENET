#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "mqtt/qmqtt.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_connect_clicked();

    void on_btn_send_clicked();

    void on_btn_close_clicked();

    void connect_success_slot();

    void connect_error_slot(const QMQTT::ClientError error);

    void disconnect_slot();

    void received_slot(const QMQTT::Message& msg);

private:
    Ui::MainWindow *ui;
    QMQTT::Client *client;
};

#endif // MAINWINDOW_H
