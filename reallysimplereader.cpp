#include "reallysimplereader.h"
#include "dbmanager.h"
#include "httpdownloader.h"
#include "channel.h"
#include <QStringList>
#include <QList>

ReallySimpleReader::ReallySimpleReader(QObject *parent):QObject(parent)
{
    m_channelHitCounter = 0 ;
    m_pDbManager = NULL;
}
ReallySimpleReader::~ReallySimpleReader()
{
    if (m_pDbManager)
	delete m_pDbManager;

    if (!m_downloadersList.isEmpty()){
	HttpDownloader* d;
	while (!m_downloadersList.isEmpty()){
	    d = m_downloadersList.takeFirst();
	    delete d;
	}
    }
    //!!
    if(!m_channelsList.isEmpty())
        m_channelsList.clear();
    if (!m_urlList.isEmpty())
        m_urlList.clear();
}

void ReallySimpleReader::GetFeeds()
{
    qDebug("in Get feeds at RSR.cpp");
    emit SignalChannelFetchStarted();
    if (m_pDbManager)
        delete m_pDbManager;

    m_pDbManager = new DBManager(this);
    AddDBManagerSignals();
    m_urlList = m_pDbManager->GetChannelsURLs();


    if (!m_urlList.isEmpty()){
        //now, create n parsers each one of them downloads and parses a single URL from the urlList
        HttpDownloader* tempDownloader;

        for (int i=0;i<m_urlList.size();i++){
            tempDownloader = new HttpDownloader(m_urlList.at(i),this);
            connect(tempDownloader,SIGNAL(SignalDownloadDone()),
                    this,SLOT(RetreiveChannels()) );
            m_downloadersList.append(tempDownloader);
            tempDownloader->DownloadURL();
        }//end for

        qDebug("im getfeeds, RSR, after the downloader packed in the list, size is %d",
                m_downloadersList.size() );

    }//end if channels list not empty
    else{
        //else; there is no data in the DB : just emit the finished signal with zero channels fetched
        emit SignalAllChannelsFetched();
    }
    delete m_pDbManager;
    m_pDbManager = NULL;

}

/**
  this Slot  is called each time a parser in the list finishes parsing
  it appends its channel to the Common channel list 'n_ChannnelsList'
  this list is sent to the main window's Left tree view to display available channels only
  after all channels have been fetched, i think we need to delete all the parsers
  as they are no longer needed and emit a signal to the UI informibg it that all done
  */
void ReallySimpleReader::RetreiveChannels()
{
    qDebug("in Retreive Channels, RSR");
    m_channelHitCounter++;
    //m_channelsList.append( ((HttpDownloader*)sender())->GetChannel() );
    Channel ch = ((HttpDownloader*)sender())->GetChannel();
    m_channelsList.append(ch);
    qDebug("after appending the parsers channel, size of the channels list is: %d",
            m_channelsList.size());

    //sender()->deleteLater();
    if (m_channelHitCounter >= m_downloadersList.size()){
        qDebug("in hiCounter>= parsersList size, will now delete the downers");
        //it hink, clear the list of parsers and delete them
        // as they are no longer needed
        HttpDownloader* tempDownloader = NULL;
        while (! m_downloadersList.isEmpty()){
            tempDownloader = m_downloadersList.takeFirst();
            qDebug("just before deleting a downloader");
            delete tempDownloader;
	    qDebug("-->After deleting a downloader ");
        }
        //
        qDebug("just before emitting : SignalAllChannelsFetched signal ");
        emit SignalAllChannelsFetched();
    }
}
QList<Channel> ReallySimpleReader::GetChannelsList()
{
    qDebug("in RSRs Getchanlels list, the size of the list is %d",
           m_channelsList.size());
    return m_channelsList;
}


/**
  connect to DBManager's signals
  */
void ReallySimpleReader::AddDBManagerSignals()
{
    /*connect(m_pDbManager,SIGNAL(DBMConnectionErrorSignal(QString)),
            this,SIGNAL(SignalDBConnectionError(QString)) );
    */
    connect (m_pDbManager,SIGNAL(DBMQueryErrorSignal(QString)),
             this,SIGNAL(SignalDBQueryError(QString)) );

}





