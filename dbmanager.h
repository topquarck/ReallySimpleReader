#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
class Channel;
class Item;
class DBConnector;
/**
  This Class is the one responsible for reading/Writing to/from
  the DB, execute queries and so on.
  */
class DBManager : public QObject
{
    Q_OBJECT
public:
    DBManager();
    virtual ~DBManager();
    void GetTags();
    void GetAllData();
    void GetUnread();
    void GetRecent();
    void StoreChannel(Channel&);
    void StoreItem(Item&);

private:
    void CleanUp();

private:
    Channel*        m_pChannel;
    Item*           m_pItem;
    DBConnector*    m_pConnector;
};

#endif // DBMANAGER_H
