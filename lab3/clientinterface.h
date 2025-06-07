#ifndef CLIENTINTERFACE_H
#define CLIENTINTERFACE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QDate>

class MusicAlbum
{
public:
    int id = -1;
    QString name;
    QString author;
    QDate release_date;
    QString genre;
    int songs_quantitty;

    void display() const
    {
        qDebug()
        << "MusicAlbum: \n\tid = " << id
        << ",\n\tname = " << name
        << ",\n\tauthor = " << author
        << ",\n\trelease_date = " << release_date.toString(Qt::ISODate)
        << ",\n\tgenre = " << genre
        << ",\n\tsongs_quantitty = " << songs_quantitty;
    };

    QString albumToString() const
    {
        return QString("Music Album:\n\tid = %1\n\tname = %2\n\tauthor = %3\n\trelease_date = %4\n\tgenre = %5\n\tsongs_quantity =  %6")
            .arg(id).arg(name).arg(author).arg(release_date.toString(Qt::ISODate)).arg(genre).arg(songs_quantitty);
    };

};

class ClientInterface : public QObject
{
    Q_OBJECT

public:
    static ClientInterface *getInstance();
    static ClientInterface *instance;
    ~ClientInterface();

    MusicAlbum getMusicAlbum(const int id) const;
    QList<MusicAlbum> getMusicAlbums() const;
    MusicAlbum createMusicAlbum(const MusicAlbum &album) const;
    MusicAlbum updateMusicAlbum(const int id, const MusicAlbum &album) const;
    bool deleteMusicAlbum(const int id) const;

    static ClientInterface setInstance(ClientInterface *newInstance);
private:
    QNetworkAccessManager * m_client = nullptr;
    explicit ClientInterface(QObject *parent = nullptr);
};

#endif // CLIENTINTERFACE_H
