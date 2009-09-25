#ifndef REALLYSIMPLEREADER_H
#define REALLYSIMPLEREADER_H

#include <QObject>
class DBManager;
class HttpDownloader;
class Qlist;
class Item;
class Channel;
//to add the RSS URL storing functionality
//class FeedStore;
#include <QStringList>
/**
  the Main/Central class of the whole App
  all other classes(UI,db,XML,Http) are children of it
  called by the main() method to run the App
  */
class ReallySimpleReader : public QObject
        //// ****** important, this clsee need polishing
        // add cleanup methos, ... enhance performtanc ...etc
{
    Q_OBJECT
public:
    ReallySimpleReader(QObject *parent);
    virtual ~ReallySimpleReader();
    void GetFeeds();
    QList<Channel> GetChannelsList();

public slots:
    void RetreiveChannels();

private:
    void AddDBManagerSignals();

signals:
    void SignalAllChannelsFetched();
    void SignalChannelFetchStarted();
    void SignalDBConnectionError(QString);
    void SignalDBQueryError(QString) ;


private:
    QList<HttpDownloader*>	m_downloadersList;
    QStringList			m_urlList;
    DBManager			*m_pDbManager;
    QList<Channel>		m_channelsList;
    int				m_channelHitCounter;
};

#endif // REALLYSIMPLEREADER_H
