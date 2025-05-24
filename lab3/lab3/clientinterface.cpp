#include "clientinterface.h"

#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonParseError>

ClientInterface::ClientInterface(QObject *parent)
    : QObject{parent}
{
    m_client = new QNetworkAccessManager();
    QObject::connect(
        m_client, &QNetworkAccessManager::finished,
        this, &ClientInterface::responseReceived);
}

ClientInterface *ClientInterface::getInstance()
{

}

ClientInterface::~ClientInterface()
{
    m_client->deleteLater();
}

void ClientInterface::getMusicAlbum(const int id) const
{
    qDebug() << "before QEventLoop";
    QNetworkReply * repl = m_client->get(QNetworkRequest(QUrl(QString("http://localhost:8000/api/album.get/%1").arg(id))));
    QEventLoop evtLoop;
    QObject::connect(
        m_client, &QNetworkAccessManager::finished,
        &evtLoop, &QEventLoop::quit);
    evtLoop.exec();
    qDebug() << "after QEventLoop";


    qDebug() << "***repl = " << repl->readAll();
    QJsonParseError jsonErr;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(
        repl->readAll(), &jsonErr));
    QJsonObject *jsonRootObj = new QJsonObject(jsonDoc->object());

    MusicAlbum result;
    result.id = jsonRootObj["id"]->toInt();
    result.name = jsonRootObj["name"]->toInt();
    result.author = jsonRootObj["author"]->toInt();
    result.release_date = jsonRootObj["release_date"]->toInt();
    result.songs_quantitty = jsonRootObj["songs_quantitty"]->toInt();
    result.display();

    return result;
}

void ClientInterface::getMusicAlbums() const
{
    m_client->get(QNetworkRequest(QUrl(QString("http://localhost:8000/api/album.get"))));
}

void ClientInterface::createMusicAlbum(MusicAlbum album) const
{
    m_client->get(QNetworkRequest(QUrl(QString("http://localhost:8000/api/album.create"))));
}

void ClientInterface::updateMusicAlbum(const int id, MusicAlbum album) const
{
    m_client->get(QNetworkRequest(QUrl(QString("http://localhost:8000/api/album.update/%1").arg(id))));
}

void ClientInterface::deleteMusicAlbum(const int id) const
{
    m_client->get(QNetworkRequest(QUrl(QString("http://localhost:8000/api/album.create/%1").arg(id))));
}

// void ClientInterface::responseReceived(QNetworkReply *reply)
// {
//     qDebug() << "Server Response: " <<reply->readAll();
// }
