#ifndef REALLYSIMPLEREADER_H
#define REALLYSIMPLEREADER_H

#include <QObject>
class DBManager;
class XmlParser;
class HttpDownloader;
class RSRMainWindow;
/**
  the Main/Central class of the whole App
  all other classes(UI,db,XML,Http) are children of it
  called by the main() method to run the App
  */
class ReallySimpleReader : public QObject
{
    Q_OBJECT
public:
    ReallySimpleReader();
    /*virtual ~ReallySimpleReader();
    void StartUp();
    void LoadLocalData();*/
private:/*
    DBManager*          m_pDBManger;
    XmlParser*          m_pXmlParser;
    HttpDownloader*     m_pHttpDownloader;
    RSRMainWindow*      m_pMainWindow;
    */
};

#endif // REALLYSIMPLEREADER_H
