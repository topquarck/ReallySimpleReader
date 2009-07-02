#include "dbmanager.h"
#include <QStringList>
#include "dbconnector.h"
#include <QSqlQuery>
#include <QVariant>
DBManager::DBManager()
{
    //init member to NULL
    /*m_pChannel = NULL;
    m_pItem = NULL;*/
    m_pConnector = NULL;
}
DBManager::DBManager(QObject* parent):QObject(parent)
{
    //init member to NULL
    /*m_pChannel = NULL;
    m_pItem = NULL;*/
    m_pConnector = NULL;
}
DBManager::~DBManager()
{
    qDebug("in dbmanager's destructor");
    CleanUp();
}
void DBManager::CleanUp()
{
    /*if (m_pItem){
        delete m_pItem;
        m_pItem = NULL;
    }
    if (m_pChannel){
        delete m_pChannel;
        m_pChannel = NULL;
    }*/
    if (m_pConnector){
        delete m_pConnector;
        m_pConnector = NULL;
    }
}
/**
  this fn retreives ALL the RSS items from the DB
  */
/*void DBManager::GetAllData()
{
}*/

QStringList DBManager::GetChannelsURLs()
{ 
    qDebug("in GetChannelsURLs(), dbmanager");
    QStringList channelsList;
    if (! m_pConnector){
        m_pConnector = new DBConnector(this);
    }
    QString channelsURLsQuery = "select channel_link from channel_table";
    QSqlQuery result = m_pConnector->RetreiveData(channelsURLsQuery);
    if ( ! result.isValid() ||
            !result.isActive() || !result.first()){
        //the query result is null , damn it
        qDebug("the query result is null , i am in DBManager");
        //return channelsList; // which is an empty list
    }
    //else, the query result is OK
    while (result.next()){
        channelsList.append(result.value(0).toString());
    }
    qDebug("the size of the list: %d",channelsList.size());
    return channelsList;
}












