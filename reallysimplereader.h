#ifndef REALLYSIMPLEREADER_H
#define REALLYSIMPLEREADER_H

#include <QObject>
//class DBManager;

class HttpDownloader;
class Qlist;
class Item;
class Channel;
//to add the RSS URL storing functionality
class FeedStore;
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
    //void StartUp();
    //void LoadLocalData();
    void GetFeeds();
    void SetURL(QString );
    QList<Channel> GetChannelsList();

public slots:
    //void StartParsing();
    //void StartViewing();
    void RetreiveChannels();

signals:
    //void Finished();
    void SignalAllChannelsFetched();
private:
    QList<HttpDownloader*>   m_downloadersList;
    //HttpDownloader*     m_pHttpDownloader;
    //refactored to be a stringlist instead of one single url
    //QString             m_url;
    QStringList         m_urlList;
    //to add the RSS URL storing functionality
    FeedStore*          m_pStore;
    QList<Channel>      m_channelsList;
    int                 m_channelHitCounter;
};

#endif // REALLYSIMPLEREADER_H
