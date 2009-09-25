#include "dbmanager.h"
#include "dbconnector.h"
#include "channel.h"
#include <QStringList>
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
        //m_pConnector = NULL;
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
        AddDBConnectorSignals();
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

/**
  this method is used to insert a new feed URL to the db, used by insertFeed Dialog
  it needs to check whether the url already exists before, if found, do nothing, else, write the new entry to the db
  @param feedURL, a QString
  @return true if the file inserted successfully, false otherwise
  */
bool DBManager::InsertNewCahnnel(Channel& givenChannel)
{
    qDebug("bool DBManager::InsertNewCahnnel(Channel& givenChannel)");


    /* Not working, the params need the '' marks before them*/
    //QString query = "insert into channel_table (channel_name,channel_link,channel_desc,channel_lang) values(:name,:link,:desc,:lang)";
    QString query = "insert into channel_table (channel_name,channel_link,channel_desc) values(:name,:link,:desc)";
    query = query.replace(QString(":name"),QString("'"+givenChannel.getTitle()+"'"));
    query = query.replace(":link",QString("'"+givenChannel.getLink()+"'"));
    query = query.replace(":desc",QString("'"+givenChannel.getDesc()+"'"));
    //query = query.replace(":lang",givenChannel.getLang());

    //qDebug("%s",query);

    if (!m_pConnector)
	m_pConnector =  new DBConnector(this);

    return m_pConnector->InsertData(query);
}
bool DBManager::URLExistedBefore(QString givenFeedURL)
{
    if (!m_pConnector)
	m_pConnector = new DBConnector(this);
    qDebug("bool DBManager::URLExistedBefore(QString givenFeedURL)");
    return m_pConnector->ExistedBefore(givenFeedURL);
}

/**
  a method to connect the error signals related to db to the manager
 */
void DBManager::AddDBConnectorSignals()
{
    connect(m_pConnector,SIGNAL(ConnectionErrorSignal(QString)),
            this,SIGNAL(DBMConnectionErrorSignal(QString)) );

    connect(m_pConnector,SIGNAL(QueryErrorSignal(QString)),
            this,SIGNAL(DBMQueryErrorSignal(QString)) );
}








