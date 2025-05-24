#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void responseReceived(QNetworkReply *reply);
private:
    Ui::MainWindow *ui;
    QNetworkAccessManager * m_client = nullptr;
};
#endif // MAINWINDOW_H
