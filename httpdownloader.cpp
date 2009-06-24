#include "httpdownloader.h"
#include <QUrl>
#include <QBuffer>
#include <QHttp>
#include <QFileInfo>
#include <iostream>
#include "xmlparser.h"
//

using namespace std;
int HttpDownloader::m_globalfileCounter = 0;
HttpDownloader::HttpDownloader(QObject *parent):QObject(parent)//QThread(parent)
{
    m_pBuffer = NULL;
    m_pHttp = NULL;
    m_pUrl = NULL;
    //
    m_pParser = NULL;
    m_pChannel = NULL;
}
HttpDownloader::HttpDownloader(QString givenFilename,QObject *parent):QObject(parent) //QThread(parent)
{
    m_pBuffer = NULL;
    m_pHttp = NULL;
    m_pUrl = NULL;
    m_strfileName = givenFilename;
    //
    m_pParser = NULL;
    m_pChannel = NULL;
}

HttpDownloader::~HttpDownloader()
{
    qDebug("in the HttpDowner's destructor");
    CleanUp();
    qDebug("leaving HttpDowner's destructor");
}
/**
  clean out all the pointers
  NOTE: the Buffer contents MUST be COPIED by the consumer before deleting the buffer
      OR it will throw a NULL pointer exception and the application will crash
  */
void HttpDownloader::CleanUp()
{
    if (m_pHttp){
        delete m_pHttp;
        m_pHttp = NULL;
    }
    if (m_pUrl){
        delete m_pUrl;
        m_pUrl = NULL;
    }
    if (m_pBuffer){
        m_pBuffer->close();
        delete m_pBuffer;
        m_pBuffer = NULL;
    }
    if (m_pParser){
        delete m_pParser;
        m_pParser = NULL;
    }
    /*if (m_pChannel){
        delete m_pChannel;
        m_pChannel = NULL;
    }*/
}

/**
  this fn is the one that actually fetch the RSS file from the internet
  */
void HttpDownloader::DownloadURL()
{
    if (OpenOutputBuffer()){
        //lazily-loading/initializing the QHttp
        m_pHttp = new QHttp(this);
        //the following statement is VERY IMPORTANT
        this->AddQhttpSignals();
        m_pHttp->setHost(m_pUrl->host(), m_pUrl->port(80));
        m_pHttp->get(m_pUrl->path(), m_pBuffer);
        m_pHttp->close();
    }
    else{
        //TODO: handle the error
    }
}
void HttpDownloader::DownloadURL(QString ur)
{
    m_strfileName = ur;
    this->DownloadURL();
}
void HttpDownloader::AddQhttpSignals()
{
    connect(m_pHttp, SIGNAL(done(bool)),
                this, SLOT(Done(bool)));
        //connect for progress and state change
        connect(m_pHttp,SIGNAL(dataReadProgress(int,int)),
                this,SLOT(ViewProgressMessage(int,int)) );
        connect(this,SIGNAL(SignalDownloadError(QString)),
                this,SLOT(ViewErrorMessge(QString) ) );
}
/**
  opens and makes the buffer ready for writing
  */
bool HttpDownloader::OpenOutputBuffer()
{
    m_pUrl = new QUrl(m_strfileName);
    QFileInfo fileInfo(m_pUrl->path());
    QString fileName = fileInfo.fileName();
    if (fileName.isEmpty()) {
        //make a default name index[number].html to avoid
        //overwriting the same file name with another feed file
        //hope it works
        m_globalfileCounter++;
        fileName = "index";
        fileName.append(QString("%1").arg(m_globalfileCounter));
        fileName.append(".html");
    }
    m_pBuffer = new QBuffer(this);
    if (!m_pBuffer->open(QIODevice::ReadWrite)) {
        std::cout<< "Unable to save the file" << endl;
        //CleanUp();
        return false;
    }
    return true;
}
/**
  the slot that is called when downloading the RSS file is DONE
  */
void HttpDownloader::Done(bool error) {
    qDebug("in Done slot, HttpDownloader");

    if (error) {
        std::cout << "Error: "<<m_pHttp->errorString().toStdString()<<endl;
        //handle Error Messages
        emit SignalDownloadError(m_pHttp->errorString());
        return;
    }
    else {
        //view a Success message
        std::cout << "File downloaded as " <<m_pUrl->toString().toStdString()<< endl;
        // the code to parse the XML file
        if (m_pParser)
            delete m_pParser;
        m_pParser = new XmlParser(this);
        this->AddParserSignals();
        m_pParser->SetData(this->GetData());
        //delete m_pBuffer;
        m_pParser->start();
    }
    //emit SignalFinished();
}
void HttpDownloader::AddParserSignals()
{
    connect(m_pParser,SIGNAL(SignalParseDone()),
            this,SLOT(HandleParseDone()) );
    connect(m_pParser,SIGNAL(SignalParseError(QString) ),
            this,SLOT(HandleParseError(QString)) );
}

void HttpDownloader::HandleParseDone()
{
    qDebug("inside handleParsDone, Donwloader");
    if (m_pChannel){
        delete m_pChannel;
    }
    m_pChannel = &m_pParser->GetChannel();
    qDebug("***");
    if (!m_pChannel){
        emit SignalDownloadError("damn it");
        return;
        }

    emit SignalDownloadDone();
}
void HttpDownloader::HandleParseError(QString error)
{
    std::cout<<error.toStdString()<<endl;
    emit SignalDownloadError(error);
}
Channel& HttpDownloader::GetChannel()
{
    return *m_pChannel;
}
/**
  this fn returns the CONTENTS of the Buffer to the consumer
  NOTE: IT DOESN;T RETURN A POINTER TO THE RSS BUFFER
      IT RETURNS THE ACTUAL BUFFER ITSELF, So it is copied and handled
      by the consumer in order to avoid Dangling pointer problem
      in case the buffer was destroyed anywhere in the application,
      it shouldn't affect other parties that use it.
  */
const QByteArray& HttpDownloader::GetData()
{
    //seek the buffer to the beginning
    m_pBuffer->seek(0);
    //return the contents of the buffer NOT a pointer to it.
    //
    return m_pBuffer->data();
}
void HttpDownloader::ViewProgressMessage(int done, int total)
{
    /*if (! m_pMainWindow)
        m_pMainWindow = new  IStatusBarViewer();
    int result = (done/total)*100;
    m_pMainWindow->ShowStatusBarMessage(result);*/
    qDebug("%d out of %d downloaded",done,total);

}
void HttpDownloader::ViewErrorMessge(QString error)
{
    /*if (! m_pMainWindow)
        m_pMainWindow = new  IStatusBarViewer();
    m_pMainWindow->ShowStatusBarMessage(error);*/
    std::cout<<"Download ERROR: "<<error.toStdString()<<endl;
}




