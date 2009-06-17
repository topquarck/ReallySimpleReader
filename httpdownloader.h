#ifndef HTTPDOWNLOADER_H
#define HTTPDOWNLOADER_H

//#include <QThread>
#include <QObject>
class QUrl;
class QHttp;
class QBuffer;
class QUrl;
/**
  this class uses the QHttp class to download the XML files from
  remote servers.
  the XML files will be used as a form of QBuffer < not physical
  files> to be handled by the rest of the classes
  */
class HttpDownloader : public QObject //public QThread
{
    Q_OBJECT
protected:
    void run();

public:
    HttpDownloader(QObject*);
    HttpDownloader(QString,QObject *parent);
    virtual ~HttpDownloader();
    const QByteArray GetData();
    void DownloadURL();
    //just for testing
    //void StartIt(){DownloadURL();}
    //end just for testing

public slots:
    void Done(bool);

signals:
    void RSSDownloadFinished();
    void RSSDownloadError(QString);

private:

    bool OpenOutputBuffer();
    void CleanUp();

private: // variables
    QBuffer*    m_pBuffer;  // the file buffer
    QHttp*      m_pHttp;    // the QHttp fetcher
    QString     m_strfileName;   // the string to hold the RSS filename
    QUrl*       m_pUrl;
    static int  m_globalfileCounter ;
};
#endif // HTTPDOWNLOADER_H




