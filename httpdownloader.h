#ifndef HTTPDOWNLOADER_H
#define HTTPDOWNLOADER_H

//#include <QThread>
#include <QObject>
class QUrl;
class QHttp;
class QBuffer;
class QUrl;
class XmlParser;
#include "channel.h"

/**
  this class uses the QHttp class to download the XML files from
  remote servers.
  the XML files will be used as a form of QBuffer < not physical
  files> to be handled by the rest of the classes
  */
class HttpDownloader : public QObject //public QThread
{
    Q_OBJECT
//protected:
    //void run();

public:
    HttpDownloader(QObject*);
    HttpDownloader(QString,QObject *parent);
    HttpDownloader(QString);
    virtual ~HttpDownloader();
    void DownloadURL();
    void DownloadURL(QString);
    Channel& GetChannel();

public slots:
    void Done(bool);

signals:
    void SignalDownloadProgress(int,int);
    void SignalDownloadError(QString);
    //void SignalFinished();
    void SignalDownloadDone();

private:
    void AddQhttpSignals();
    bool OpenOutputBuffer();
    void CleanUp();
    const QByteArray& GetData();
    //
    void AddParserSignals();

private slots:
    void ViewProgressMessage(int done, int total);
    void ViewErrorMessge(QString error);
    void HandleParseDone();
    void HandleParseError(QString );
private: // variables
    QBuffer*    m_pBuffer;  // the file buffer
    QHttp*      m_pHttp;    // the QHttp fetcher
    QString     m_strfileName;   // the string to hold the RSS filename
    QUrl*       m_pUrl;
    static int  m_globalfileCounter ;
    //
    XmlParser*  m_pParser;
    Channel*    m_pChannel;
};
#endif // HTTPDOWNLOADER_H




