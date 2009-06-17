//#include "dbconnectortest.h"

#include <QObject>
#include <QtTest>
#include <QSqlQuery>
#include "dbconnector.h"
class DBConnectorTest : public QObject
{
    Q_OBJECT

private:
    DBConnector* con;

private slots:
    void testOpenConnection();
    void testInsertData();
    void testRetreiveData();

};

void DBConnectorTest::testOpenConnection()
{
    con = new DBConnector();
    QVERIFY(con->OpenConnection()==1);
}
void DBConnectorTest::testInsertData()
{
    QString str = " insert into channel_table (channel_name,channel_link,channel_desc) values('namee','linky.org','DESSSSC')";
    QCOMPARE(con->InsertData(str),TRUE);
}
void DBConnectorTest::testRetreiveData()
{
    //con->OpenConnection();
    QString q = " select * from channel_table";
    QSqlQuery *sql;
    sql = new QSqlQuery( con->RetreiveData(q));
    QCOMPARE(sql->first(),TRUE);
}

QTEST_MAIN(DBConnectorTest)
#include "dbconnectortest.moc"        
