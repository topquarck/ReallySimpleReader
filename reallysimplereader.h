#ifndef REALLYSIMPLEREADER_H
#define REALLYSIMPLEREADER_H

#include <QObject>
//class DBManager;
class XmlParser;
class HttpDownloader;
class Qlist;
class Item;
/**
  the Main/Central class of the whole App
  all other classes(UI,db,XML,Http) are children of it
  called by the main() method to run the App
  */
class ReallySimpleReader : public QObject
{
    Q_OBJECT
public:
    ReallySimpleReader(QObject *parent);
    virtual ~ReallySimpleReader();
    //void StartUp();
    //void LoadLocalData();
    void GetFeeds();
    void SetURL(QString );
    QList<Item*> GetItemsList();
public slots:
    void StartParsing();
    void StartViewing();

signals:
    void Finished();
private:
    //DBManager*          m_pDBManger;
    XmlParser*          m_pXmlParser;
    HttpDownloader*     m_pHttpDownloader;
    QString             m_url;
};

#endif // REALLYSIMPLEREADER_H
