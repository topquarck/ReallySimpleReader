#include <QObject>
//#include "httpdownloader.h"
//#include <QString>
class HttpDownloader;

class HttpDownloadTest : public QObject
{
    Q_OBJECT
private:
    HttpDownloader* d;
public:
    HttpDownloadTest();
    void CreateInstance();
    void testDownload();

public slots:
        void ShowData();
        //void ShowError(QString);

};
