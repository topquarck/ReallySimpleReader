#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QObject>
#include <QThread>
class QDomDocument;
class QDomElement;
class QByteArray;
class Channel;
class Item;
/**
  the class reponsible for parsing the RSS feeds
  */
class XmlParser : public QThread
{
    Q_OBJECT

protected:
    void run();
public:
    //XmlParser(QObject* parent);
    //
    XmlParser(QString ,QObject* parent);
    virtual ~XmlParser();
    Channel& GetChannel();
    void ParseXML();
    void SetData(const QByteArray&);
    //added on 18-7-09 to verify if the file is valid or not without storing values in internal members, used for verifying newly inserted links
    bool IsValidRSSFile();

signals:
    void SignalParseError(QString);
    void SignalParseDone();

private:  //methods
    void CleanUp();
    bool OpenBuffer();
    Item* ParseItem(QDomElement);
    bool ParseRssHead();
    bool ParseChannel();
    //
    bool IsValidChannel();


private: //variables
    QDomDocument*   m_pDoc;
    QDomElement*    m_pRootElement;
    QByteArray*     m_pData;
    Channel*        m_pChannel;
    QString	    m_urlString;

};

#endif // XMLPARSER_H














