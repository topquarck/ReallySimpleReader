#include "feedstore.h"
#include <QFile>
#include <QTextStream>


QString FeedStore::m_fileName = "config/feeds";

FeedStore::FeedStore()
{
    m_pFile = NULL;
    m_isFileOpen = false;
    m_pTextStream = NULL;
}
FeedStore::FeedStore(QObject* parent):QObject(parent)
{
    qDebug("in feedStores constructor ****");
    m_pFile = NULL;
    m_isFileOpen = false;
    m_pTextStream = NULL;
    RetreiveFeeds();
}
FeedStore::~FeedStore()
{
    qDebug("in the destructor of the ~feedStore");
    this->CloseFile();
    if (m_pFile){
        delete m_pFile;
        m_pFile = NULL;
    }
    if (m_pTextStream){
        delete m_pTextStream;
        m_pTextStream = NULL;
    }
}
void FeedStore::CloseFile()
{
    if (m_pFile->isOpen())
        m_pFile->close();
}

bool FeedStore::OpenFile()
{
    qDebug("in OpenFile, FeedStore**");
    m_pFile = new QFile(FeedStore::m_fileName);
    if (!m_pFile->open(QIODevice::ReadWrite) ){
        qDebug("Feed file couldn't be opened");
        emit SignalFileNotOpen("Feed file couldn't be opened");
        m_isFileOpen = false;
        return false;
    }
    //else
    m_isFileOpen = true;
    return true;

}

bool FeedStore::RetreiveFeeds()
{
    qDebug("in Retreive Feeds, the store");
    //TODO: inspect it
    if (this->OpenFile()){
        m_pTextStream = new QTextStream(m_pFile);
        qDebug("before the while loop, fs");
        while (!m_pTextStream->atEnd())
            m_feedList<<m_pTextStream->readLine(1000);

        qDebug("size of the list: %d",m_feedList.size());
        return true;
    }
    return false;
}
QStringList FeedStore::GetFeeds()
{
    qDebug("in getFeeds, Store");
    return m_feedList;
}
