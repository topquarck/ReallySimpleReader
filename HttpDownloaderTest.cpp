#include "HttpDownloaderTest.h"
#include "httpdownloader.h"
#include <iostream>
using namespace std;
HttpDownloadTest::HttpDownloadTest()
{
}
void HttpDownloadTest::CreateInstance(){
    QString str="http://www.codeproject.com/webservices/articlerss.aspx?cat=2";
    d = new HttpDownloader(str,this);
    connect(d,SIGNAL(RSSDownloadFinished()),
            this,SLOT(ShowData()));
    //connect(d,SIGNAL(RSSDownloadError(QString)),
      //      this,SLOT(ShowError(QString)));
}
void HttpDownloadTest::testDownload(){
    //d->start();
    //just for testing
    //d->StartIt();
}
void HttpDownloadTest::ShowData(){

        QByteArray m_data = d->GetData();
        if (m_data.size()>0){
            std::cout<<m_data.data()<<endl;
        }else{
            std::cout<<"data byteArray is empty"<<endl;
        }

}
/*void HttpDownloadTest::ShowError(QString err){
    std::cout<<err.toStdString()<<endl;
}*/
