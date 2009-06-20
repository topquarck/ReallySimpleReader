#include "HttpXMLTest.h"
#include "httpdownloader.h"
#include "xmlparser.h"
#include "channel.h"
#include "item.h"
#include <iostream>
using namespace std;
HttpXMLTest::HttpXMLTest()
{
    downloader = NULL;
    parser = NULL;
}
void HttpXMLTest::Init()
{
    std::cout<<"********** in Init() *******"<<endl;
    QString link = "http://www.codeproject.com/webservices/articlerss.aspx?cat=2";
    downloader = new HttpDownloader(link,this);
    connect(downloader,SIGNAL(RSSDownloadFinished()),
            this,SLOT(DownloadFinished()));
}
void HttpXMLTest::TestDownload()
{
    std::cout<<"**** in testDownload() ******"<<endl;
    downloader->DownloadURL();
}
void HttpXMLTest::DownloadFinished()
{
    std::cout<<"****** DownloadFinished ****"<<endl;
    /*std::cout<<" Showing the data"<<endl;
    QByteArray m_data = downloader->GetData();
        if (m_data.size()>0){
            std::cout<<m_data.data()<<endl;
        }else{
            std::cout<<"data byteArray is empty"<<endl;
        }*/
     TestParse();
}
void HttpXMLTest::TestParse()
{
    std::cout<<"********* in TestPArse() **********"<<endl;
    parser = new XmlParser(this);
    connect(parser,SIGNAL(ParseDone()),
        this,SLOT(doShowData()) );
    connect(parser,SIGNAL(ParseErrorSignal(QString)),
            this,SLOT(ShowParserError(QString)),Qt::DirectConnection);

}
void HttpXMLTest::doShowData()
{
    std::cout<<"***** in doShowData SLOT ***"<<endl;
   parser->SetData(downloader->GetData());
   ShowData(parser->GetChannel());
}
void HttpXMLTest::ShowParserError(QString errorMsg)
{
    std::cout<<"***** in ShowParserError ***"<<endl;
    std::cout<<errorMsg.toStdString()<<endl;
}
void HttpXMLTest::ShowData(Channel& ch)
{
    std::cout<<"********* in ShowData() *********"<<endl;
    Item* tempItem = NULL;
    //priniting the channel
    std::cout<<"channel title: "<<ch.getTitle().toStdString()<<endl;
    std::cout<<"channel link: "<<ch.getLink().toStdString()<<endl;
    std::cout<<"channel Desc: "<<ch.getDesc().toStdString()<<endl;
    std::cout<<"channel lang: "<<ch.getLang().toStdString()<<endl;
    std::cout<<"========================================================"<<endl;
    //now, get the items
    QList<Item*> list = ch.getItems();
    for (int i=0;i<list.size();i++){
        tempItem = list.at(i);
        std::cout<<"***********Item Number: "<<i<<" ***********"<<endl;
        std::cout<<"item name: "<<tempItem->getTitle().toStdString()<<endl;
        std::cout<<"item link: "<<tempItem->getLink().toStdString()<<endl;
        std::cout<<"item desc: "<<tempItem->getDesc().toStdString()<<endl;
        std::cout<<"********************************************************"<<endl;
        std::cout<<"********************************************************"<<endl;
    }
}







