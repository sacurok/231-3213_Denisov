#include "clientinterface.h"

#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

ClientInterface * ClientInterface::instance = nullptr;

ClientInterface::ClientInterface(QObject *parent)
    : QObject{parent}
{
    m_client = new QNetworkAccessManager();
}

ClientInterface *ClientInterface::getInstance()
{
    if(!instance)
    {
        instance = new ClientInterface();
    }
    return instance;
}

ClientInterface::~ClientInterface()
{
    m_client->deleteLater();
}

MusicAlbum ClientInterface::getMusicAlbum(const int id) const
{
    qDebug() << "Get Album...";
    QNetworkReply * repl = m_client->get(QNetworkRequest(QUrl(QString("http://localhost:8000/api/album.get/%1").arg(id))));
    QEventLoop evtLoop;
    QObject::connect(
        m_client, &QNetworkAccessManager::finished,
        &evtLoop, &QEventLoop::quit);
    evtLoop.exec();

    // qDebug() << "***repl = " << repl->readAll();
    QJsonParseError jsonErr;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(
        repl->readAll(), &jsonErr);


    QJsonObject jsonRootObj = jsonDoc.object();

    MusicAlbum album;
    album.id = jsonRootObj["id"].toInt();
    album.name = jsonRootObj["name"].toString();
    album.author = jsonRootObj["author"].toString();
    // album.release_date = jsonRootObj["release_date"].toString();
    album.release_date = QDate::fromString(jsonRootObj["release_date"].toString(), Qt::ISODate);
    album.genre = jsonRootObj["genre"].toString();
    album.songs_quantitty = jsonRootObj["songs_quantitty"].toInt();

    if (album.id == 0){
        qDebug() << "Album not found";
    } else {
        album.display();
    }

    // qDebug() << "Get response:" << repl->readAll();
    return album;    
}

QList<MusicAlbum> ClientInterface::getMusicAlbums() const
{
    qDebug() << "Get Albums...";

    QList<MusicAlbum> musicAlbumsList;

    QNetworkReply* repl = m_client->get(QNetworkRequest(QUrl("http://localhost:8000/api/album.get")));

    QEventLoop evtLoop;
    QObject::connect(
        m_client, &QNetworkAccessManager::finished,
        &evtLoop, &QEventLoop::quit);
    evtLoop.exec();

    QJsonParseError jsonErr;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(
        repl->readAll(), &jsonErr);

    QJsonArray jsonArray = jsonDoc.array();
    for (const QJsonValue& value : jsonArray) {
        QJsonObject obj = value.toObject();
        MusicAlbum album;
        album.id = obj["id"].toInt();
        album.name = obj["name"].toString();
        album.author = obj["author"].toString();
        album.release_date = QDate::fromString(obj["release_date"].toString(), Qt::ISODate);
        album.genre = obj["genre"].toString();
        album.songs_quantitty = obj["songs_quantitty"].toInt();
        album.display();
        musicAlbumsList.append(album);
    }

    return musicAlbumsList;
}

MusicAlbum ClientInterface::createMusicAlbum(const MusicAlbum &album) const
{
    qDebug() << "Create new album...";

    QJsonObject jsonObj;
    jsonObj["name"] = album.name;
    jsonObj["author"] = album.author;
    jsonObj["release_date"] = album.release_date.toString(Qt::ISODate);
    jsonObj["genre"] = album.genre;
    jsonObj["songs_quantitty"] = album.songs_quantitty;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray postData = jsonDoc.toJson();

    QNetworkRequest request(QUrl("http://localhost:8000/api/album.create"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* repl = m_client->post(request, postData);

    QEventLoop evtLoop;
    QObject::connect(
        m_client, &QNetworkAccessManager::finished,
        &evtLoop, &QEventLoop::quit);
    evtLoop.exec();

    QJsonParseError jsonErr;
    QJsonDocument responseDoc = QJsonDocument::fromJson(repl->readAll(), &jsonErr);
    QJsonObject responseObj = responseDoc.object();

    MusicAlbum createdAlbum = album;
    createdAlbum.id = responseObj["id"].toInt(-1);
    createdAlbum.display();

    return createdAlbum;
    // qDebug() << "Create response:" << repl->readAll();
}

MusicAlbum ClientInterface::updateMusicAlbum(const int id, const MusicAlbum &album) const
{
    qDebug() << "Update album with id:" << id;

    QJsonObject jsonObj;
    jsonObj["name"] = album.name;
    jsonObj["author"] = album.author;
    jsonObj["release_date"] = album.release_date.toString(Qt::ISODate);
    jsonObj["genre"] = album.genre;
    jsonObj["songs_quantitty"] = album.songs_quantitty;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray postData = jsonDoc.toJson();

    QNetworkRequest request(QUrl(QString("http://localhost:8000/api/album.update/%1").arg(id)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* repl = m_client->post(request, postData);

    QEventLoop evtLoop;
    QObject::connect(
        m_client, &QNetworkAccessManager::finished,
        &evtLoop, &QEventLoop::quit);
    evtLoop.exec();

    QJsonParseError jsonErr;
    QJsonDocument responseDoc = QJsonDocument::fromJson(
        repl->readAll(), &jsonErr);
    QJsonObject responseObj = responseDoc.object();

    MusicAlbum updatedAlbum;
    updatedAlbum.id = responseObj["id"].toInt();
    updatedAlbum.name = responseObj["name"].toString();
    updatedAlbum.author = responseObj["author"].toString();
    updatedAlbum.release_date = QDate::fromString(responseObj["release_date"].toString(), Qt::ISODate);
    updatedAlbum.genre = responseObj["genre"].toString();
    updatedAlbum.songs_quantitty = responseObj["songs_quantitty"].toInt();

    if (updatedAlbum.id == 0){
        qDebug() << "Album not found";
    } else {
        updatedAlbum.display();
    }

    // qDebug() << "Update response:" << repl->readAll();
    return updatedAlbum;
}

bool ClientInterface::deleteMusicAlbum(const int id) const
{
    qDebug() << "Delete album with id:" << id;

    QNetworkReply* repl = m_client->get(
        QNetworkRequest(QUrl(QString("http://localhost:8000/api/album.delete/%1").arg(id))));

    QEventLoop evtLoop;
    QObject::connect(
        m_client, &QNetworkAccessManager::finished,
        &evtLoop, &QEventLoop::quit);
    evtLoop.exec();

    if (repl->error() == QNetworkReply::NoError) {
        qDebug() << "Album deleted successfully";
        return 1;
    } else {
        qDebug() << "Album not found";
        return 1;
    }

    // qDebug() << "Delete response:" << repl->readAll();
}

// void ClientInterface::responseReceived(QNetworkReply *reply)
// {
//     qDebug() << "Server Response: " <<reply->readAll();
// }
