#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_client = new QNetworkAccessManager();
    QObject::connect(
        m_client, &QNetworkAccessManager::finished,
        this, &MainWindow::responseReceived);
    m_client->get(QNetworkRequest(QUrl("http://localhost:8000/api/album.get/1011")));
}

void MainWindow::responseReceived(QNetworkReply *reply)
{
    qDebug() << reply->readAll();
}

MainWindow::~MainWindow()
{
    delete ui;
    m_client->deleteLater();
}

