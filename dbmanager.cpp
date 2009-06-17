#include "dbmanager.h"

DBManager::DBManager()
{
    //init member to NULL
    m_pChannel = NULL;
    m_pConnector = NULL;
    m_pItem = NULL;
}
DBManager::~DBManager()
{
    CleanUp();
}
void DBManager::CleanUp()
{
    if (m_pItem){
        delete m_pItem;
        m_pItem = NULL;
    }
    if (m_pChannel){
        delete m_pChannel;
        m_pChannel = NULL;
    }
    if (m_pConnector){
        delete m_pConnector;
        m_pConnector = NULL;
    }
}
/**
  this fn retreives ALL the RSS items from the DB
  */
void DBManager::GetAllData()
{
}
