#include "reallysimplereader.h"
//#include "dbmanager.h"
#include "xmlparser.h"
#include "httpdownloader.h"
//#include "rsrmainwindow.h"
#include "channel.h"
ReallySimpleReader::ReallySimpleReader(QObject *parent):QObject(parent)
{
}
ReallySimpleReader::~ReallySimpleReader()
{}
void ReallySimpleReader::SetURL(QString u)
{
    this->m_url = u;
}
void ReallySimpleReader::GetFeeds()
{
    qDebug("in Get feeds at RSR.cpp");
    m_pHttpDownloader = new HttpDownloader(m_url,this);
    connect (m_pHttpDownloader,SIGNAL(SignalFinished()),
            this,SLOT(StartParsing()) );
    m_pHttpDownloader->DownloadURL();
}
void ReallySimpleReader::StartParsing()
{
    qDebug("in StartParsing");
    if (!m_pXmlParser)
        m_pXmlParser = new XmlParser(this);
    connect(m_pXmlParser,SIGNAL(ParseDone()),
            this,SLOT(StartViewing()) );
    m_pXmlParser->SetData(m_pHttpDownloader->GetData());
    m_pXmlParser->start();
}
void ReallySimpleReader::StartViewing()
{
    emit Finished();
}
QList<Item*> ReallySimpleReader::GetItemsList()
{
    return m_pXmlParser->GetChannel().getItems();
}









