
#include <QObject>
class HttpDownloader;
class XmlParser;
class Channel;
class HttpXMLTest : public QObject
{
    Q_OBJECT
private:
    HttpDownloader* downloader;
    XmlParser* parser;

public:
    HttpXMLTest();
    void Init();
    void TestDownload();
    void TestParse();
    void ShowData(Channel&);
public slots:
    void DownloadFinished();
    void ShowParserError(QString);
    void doShowData();
};
