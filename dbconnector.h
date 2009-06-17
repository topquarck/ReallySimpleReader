#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include <QObject>
class QSqlQuery;
class QSqlDatabase;
/**
  this class handles the SQL commands and executes them against the
  DB, used by the DBManager class as a Query executer
  */
class DBConnector : public QObject
{
    Q_OBJECT
public:
    DBConnector();
    virtual         ~DBConnector();
    bool            OpenConnection();
    bool            IsOpen();
    bool            InsertData(QString);
    QSqlQuery&      RetreiveData(QString);

signals:
    void ConnectionErrorSignal(QString);
    void QueryErrorSignal(QString);

private:
    void CleanUp();

private: // variables
    QSqlDatabase*   m_pDatabase;
    QSqlQuery*      m_pQuery;
};

#endif // DBCONNECTOR_H
