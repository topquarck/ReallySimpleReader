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
    XmlParser(QObject* parent);
    virtual ~XmlParser();
    Channel& GetChannel();
    void ParseXML();
    void SetData(const QByteArray&);

signals:
    void ParseErrorSignal(QString);
    void ParseDone();

private:  //methods
    void CleanUp();
    bool OpenBuffer();
    Item* ParseItem(QDomElement);
    bool ParseRssHead();
    bool ParseChannel();

private: //variables
    QDomDocument*   m_pDoc;
    QDomElement*    m_pRootElement;
    QByteArray*     m_pData;
    Channel*        m_pChannel;

};

#endif // XMLPARSER_H














