#include "dbconnector.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

DBConnector::DBConnector()
{
    m_pDatabase = NULL;
    m_pQuery    = NULL;
}
DBConnector::DBConnector(QObject* parent): QObject(parent)
{
    m_pDatabase = NULL;
    m_pQuery    = NULL;
    OpenConnection();
}
DBConnector::~DBConnector()
{
    CleanUp();
}
void DBConnector::CleanUp()
{
    if (m_pQuery){
        m_pQuery->clear();
        delete m_pQuery;
        m_pQuery = NULL;
    }
    if (m_pDatabase){
        m_pDatabase->close();
        delete m_pDatabase;
        m_pDatabase = NULL;
    }
}
bool DBConnector::IsOpen()
{
    return m_pDatabase->isOpen();
}
bool  DBConnector::OpenConnection()
{
    if (m_pDatabase){
	m_pDatabase->close();
	delete m_pDatabase;
	m_pDatabase = NULL;
    }

    m_pDatabase = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    m_pDatabase->setHostName("localhost");
    m_pDatabase->setDatabaseName("feed_db.sqlite");
    if (! m_pDatabase->isValid()){
        //driver is not valid
        //report the error
        emit ConnectionErrorSignal(
                QString("DB CONNECTION ERROR: driver is invalid"));
        return false;
    }
    //else, the driver is Valis
    //open the db
    if (! m_pDatabase->open() ){
        //report the failure
        emit ConnectionErrorSignal(
                QString("DB CONNECTION ERROR: DB couldnt be opened"));
        return false;
    }
    //db is open successfully, i hope!
    return true;
}
QSqlQuery& DBConnector::RetreiveData(QString queryText)
{
    qDebug("in REstreiveData methid, dbConnnector class");

    if (m_pQuery){
        delete m_pQuery;
    }

    m_pQuery = new QSqlQuery(*m_pDatabase);

    if (! m_pQuery->exec(queryText)){
        //report error
        emit QueryErrorSignal(m_pQuery->lastError().text());
        //return *m_pQuery; // which is nonactive, nonValid query
    }
    //else: the select query was executed
    qDebug("size po fthe query is : %d",m_pQuery->size() );
    return *m_pQuery;
}

/**
  this method executes the query created by the DBManager
  and returns the state of execution
  */
bool DBConnector::InsertData(QString queryText)
{
    qDebug("in bool DBConnector::InsertData(QString queryText)");
    qDebug()<<queryText;
    if (m_pQuery){
        delete m_pQuery;
        m_pQuery = NULL;
    }

    m_pQuery = new QSqlQuery(*m_pDatabase);
    if (!m_pQuery->exec(queryText) ){
        qDebug()<<m_pQuery->lastError().text();
	emit QueryErrorSignal(m_pQuery->lastError().text());
	return false;
    }
    //i think every thing went OK, and the insert statement executed successfully

    // Commit the Changes to the DB. Dont know why it is needed but if it dont do it it will raise an error
    Commit();
    return true;

}

/**
  this method checks whethter the URL exists before
  @param the url to search for
  @return true if the url exists before, false otherwise
  */
bool DBConnector::ExistedBefore(QString givenUrl)
{
    qDebug("in bool DBConnector::ExistedBefore(QString givenUrl)");

    if (m_pQuery)
	delete m_pQuery;

    m_pQuery = new QSqlQuery(*m_pDatabase);
    m_pQuery->prepare("select channel_id from channel_table where channel_link= :url");
    m_pQuery->bindValue(":url",givenUrl);

    if (! m_pQuery->exec()){
	//report error
	emit QueryErrorSignal(m_pQuery->lastError().text());
	return false;
    }
    else{  // the query executed
        if ( m_pQuery->isActive() && m_pQuery->next() ){

            // I really DONT know WHY need to commit when you execute a SELECT statement !!!!
            /* the BUG is :
                1. insert an existing feed URL ------> App says: feed Already exists
                2. insert a new/nonexisting URL -----> App says: Can't write to DB
               the Solution :
               --> Call Commit() in the method ExistedBefore() !!!! - although it only selects data
               and everything goes well.
            */
            Commit();
            return true;
        }
        else{
            return false;
        }//end else

    }//end ELSE the query executed

}


void DBConnector::Commit()
{
    m_pQuery->clear(); // Clears the result set and releases any resources held by the query. Sets the query state to inactive.
    m_pDatabase->commit(); // Commits a transaction to the database if the driver supports transactions
}






