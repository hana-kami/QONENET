#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mqtt/qmqtt.h"
#include <QDebug>
#include <QtNetwork>
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new QMQTT::Client(QHostAddress("183.230.40.39"),6002);
    client->setClientId("1058643508");//设备ID
    client->setUsername("582247");//产品id
    client->setPassword("123456");//鉴权信息
    client->setVersion(QMQTT::MQTTVersion::V3_1_1);
    connect(client,SIGNAL(connected()),this,SLOT(connect_success_slot()));
    connect(client,SIGNAL(received(const QMQTT::Message&)),this,SLOT(received_slot(const QMQTT::Message&)));
    connect(client,SIGNAL(error(const QMQTT::ClientError)),this,SLOT(connect_error_slot(const QMQTT::ClientError)));
    connect(client,SIGNAL(disconnected()),this,SLOT(disconnect_slot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_connect_clicked()
{
   client->connectToHost();
}

void MainWindow::on_btn_send_clicked()
{
    //Message(const quint16 id, const QString &topic,
    //const QByteArray &payload,
    //const quint8 qos = 0, const bool retain = false, const bool dup = false);
    QMQTT::Message msg(110,"app_topic",/*"hello KFB,I am APP"*/ui->le_send->text().toUtf8());
    client->publish(msg);
}

void MainWindow::on_btn_close_clicked()
{
    client->disconnectFromHost();
}

void MainWindow::received_slot(const QMQTT::Message& msg){
    QString strPayload(msg.payload());
    ui->le_receive->setText(strPayload);
}
void MainWindow::connect_success_slot(){
    qDebug() << "connect success";
    client->subscribe("kfb_topic",0);
}

void MainWindow::connect_error_slot(const QMQTT::ClientError error){
    qDebug() << "错误" << error;
}

void MainWindow::disconnect_slot(){
    qDebug() << "disconnect___";
}
