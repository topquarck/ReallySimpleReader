#ifndef FEEDSTORE_H
#define FEEDSTORE_H

#include <QObject>
#include <QStringList>

class QTextStream;
class QFile;
/**
  this file is the store that holds the URLs of the Registered
  feeds, to be retreived and used with app
  */
class FeedStore : public QObject
{
    Q_OBJECT
public:
    FeedStore();
    FeedStore(QObject* parent);
    virtual ~FeedStore();
    //bool StoreFeed(QString);
    QStringList GetFeeds();

private:
    bool RetreiveFeeds();
    bool OpenFile();
    void CloseFile();

signals:
    void SignalFileNotOpen(QString);

private:
    QStringList     m_feedList;
    QFile*          m_pFile;
    QTextStream*    m_pTextStream;
    bool            m_isFileOpen;
    static QString  m_fileName;
};

#endif // FEEDSTORE_H
