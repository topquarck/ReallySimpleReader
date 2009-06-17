#include "dbconnector.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
//just for testing only
/*#include <QVariant>
#include <iostream>*/
//end testing
DBConnector::DBConnector()
{
    m_pDatabase = NULL;
    m_pQuery    = NULL;
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
    m_pDatabase = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    m_pDatabase->setHostName("localhost");
    m_pDatabase->setDatabaseName("feed_db.sqlite");
    if (! m_pDatabase->isValid()){
        //driver is not valid
        //report the error
        emit ConnectionErrorSignal(
                QString("CONNECTION ERROR: driver is invalid"));
        return false;
    }
    //else, the driver is Valis
    //open the db
    if (! m_pDatabase->open() ){
        //report the failure
        emit ConnectionErrorSignal(
                QString("CONNECTION ERROR: DB couldnt be opened"));
        return false;
    }
    //db is open successfully, i hope!
    return true;
}
QSqlQuery& DBConnector::RetreiveData(QString queryText)
{
    if (m_pQuery){
        delete m_pQuery;
        m_pQuery = NULL;
    }
    m_pQuery = new QSqlQuery(*m_pDatabase);
    if (! m_pQuery->exec(queryText)){
        //report error
        emit QueryErrorSignal(m_pQuery->lastError().text());
        return *m_pQuery; // which is NULL;
    }
    //else: the select query was executed

    // For testing only
    //print out the results
    /*while (m_pQuery->next()){
        std::cout<<m_pQuery->value(2).toString().toStdString()<<"\n";
    }
    */
    return *m_pQuery;
}


/**
  this method executes the query created by the DBManager
  and returns the state of execution
  */
bool DBConnector::InsertData(QString queryText)
{
    if (m_pQuery){
        delete m_pQuery;
        m_pQuery = NULL;
    }
    m_pQuery = new QSqlQuery(*m_pDatabase);
    //m_pQuery->prepare(queryText);
    if (! m_pQuery->exec(queryText)){
        //report error
        emit QueryErrorSignal(m_pQuery->lastError().text());
        return false;
    }
    //i think every thing went OK, and the insert statement executed successfully
    return true;
}











