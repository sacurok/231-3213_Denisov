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
    clientInt = ClientInterface::getInstance();
}

MainWindow::~MainWindow()
{
    clientInt->deleteLater();
    delete ui;
}

void MainWindow::on_btnGet_clicked()
{
    MusicAlbum album = clientInt->getMusicAlbum(ui->spnIdGet->value());
    if (album.id == 0){
        ui->textGet->setPlainText("Album not found");
    } else {
        ui->textGet->setPlainText(album.albumToString());
    }
}

void MainWindow::on_btnList_clicked()
{
    QList<MusicAlbum> albums = clientInt->getMusicAlbums();
    ui->textList->clear();
    for (const MusicAlbum& album : albums) {
        QListWidgetItem* item = new QListWidgetItem(album.albumToString());
        ui->textList->addItem(item);
    }
}

void MainWindow::on_btnCreate_clicked()
{
    MusicAlbum newAlbum;
    newAlbum.name = ui->txtNameCreate->text();
    newAlbum.author = ui->txtAuthorCreate->text();
    newAlbum.genre = ui->txtGenreCreate->text();
    newAlbum.release_date = ui->dateAlbumCreate->date();
    newAlbum.songs_quantitty = ui->spnSongsCreate->value();

    MusicAlbum createdAlbum = clientInt->createMusicAlbum(newAlbum);

    ui->textCreate->setPlainText("Album created successfully!\n" + createdAlbum.albumToString());
}

void MainWindow::on_btnUpdate_clicked()
{
    MusicAlbum editAlbum;
    editAlbum.id = ui->spnIdUpdate->value();
    editAlbum.name = ui->txtNameUpdate->text();
    editAlbum.author = ui->txtAuthorUpdate->text();
    editAlbum.genre = ui->txtGenreUpdate->text();
    editAlbum.release_date = ui->dateAlbumUpdate->date();
    editAlbum.songs_quantitty = ui->spnSongsUpdate->value();

    MusicAlbum updatedAlbum = clientInt->updateMusicAlbum(ui->spnIdUpdate->value(), editAlbum);

    if (updatedAlbum.id == 0){
        ui->textUpdate->setPlainText("Album not found");
    } else {
        ui->textUpdate->setPlainText("Album updated successfully!\n" + updatedAlbum.albumToString());
    }

    // clientInt->updateMusicAlbum(ui->spnIdUpdate->value(), );
}

void MainWindow::on_btnDelete_clicked()
{
    bool check = clientInt->deleteMusicAlbum(ui->spnIdDelete->value());
    if (check == 0){
        ui->textDelete->setPlainText("Album not found");
    } else {
        ui->textDelete->setPlainText("Album deleted successfully!\n");
    }

}

