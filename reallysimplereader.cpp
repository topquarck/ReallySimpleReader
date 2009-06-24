#include "reallysimplereader.h"
//#include "dbmanager.h"
//#include "xmlparser.h"
#include "httpdownloader.h"
//#include "rsrmainwindow.h"
#include "channel.h"
//to add the RSS URL storing functionality
#include "feedstore.h"
#include <QStringList>
#include <QList>
ReallySimpleReader::ReallySimpleReader(QObject *parent):QObject(parent)
{
    //m_pHttpDownloader = NULL;
    //m_pXmlParser = NULL;
    //to add the RSS URL storing functionality
    m_pStore = NULL;
    m_channelHitCounter = 0 ;
}
ReallySimpleReader::~ReallySimpleReader()
{}
void ReallySimpleReader::SetURL(QString u)
{
    //this->m_url = u;
}
void ReallySimpleReader::GetFeeds()
{
    qDebug("in Get feeds at RSR.cpp");
    //will make the reader get the URl from the file instead of sending it as a pram
    m_pStore = new FeedStore(this);

    /*m_url = m_pStore->GetFeeds().at(0);
    m_pHttpDownloader = new HttpDownloader(m_url,this);
    connect (m_pHttpDownloader,SIGNAL(SignalFinished()),
            this,SLOT(StartParsing()) );
    m_pHttpDownloader->DownloadURL();*/

    m_urlList = m_pStore->GetFeeds();
    //i think. need todelete the store
    delete m_pStore;
    m_pStore = NULL;

    //now, create n parsers each one of them downloads and parses a single URL from the urlList
    HttpDownloader* tempDownloader = NULL;
    for (int i=0;i<m_urlList.size();i++){
        tempDownloader = new HttpDownloader(m_urlList.at(i),this);
        connect(tempDownloader,SIGNAL(SignalDownloadDone()),
                this,SLOT(RetreiveChannels()) );
        m_downloadersList.append(tempDownloader);
        tempDownloader->DownloadURL();
    }//end for
    qDebug("im getfeeds, RSR, after the downloader packed in the list, size is %d",
            m_downloadersList.size() );
}

/*void ReallySimpleReader::StartParsing()
{
    qDebug("in StartParsing");
    if (!m_pXmlParser)
        m_pXmlParser = new XmlParser(this);
    connect(m_pXmlParser,SIGNAL(ParseDone()),
            this,SLOT(StartViewing()) );
    m_pXmlParser->SetData(m_pHttpDownloader->GetData());
    m_pXmlParser->start();
}
*/

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
/*void ReallySimpleReader::StartViewing()
{
    emit Finished();
}
*/
/*QList<Item*> ReallySimpleReader::GetItemsList()
{
    return m_pXmlParser->GetChannel().getItems();
}*/









