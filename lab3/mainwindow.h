#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientinterface.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ClientInterface *clientInt = nullptr;

private slots:
    void on_btnGet_clicked();
    void on_btnList_clicked();
    void on_btnCreate_clicked();
    void on_btnUpdate_clicked();
    void on_btnDelete_clicked();

private:
    Ui::MainWindow *ui;
    // ClientInterface *clientInt;
    QNetworkAccessManager * m_client = nullptr;
};
#endif // MAINWINDOW_H
