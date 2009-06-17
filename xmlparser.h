#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QObject>
class QDomDocument;
class QDomElement;
class QByteArray;
class Channel;
class Item;

/**
  the class reponsible for parsing the RSS feeds
  */
class XmlParser : public QObject
{
    Q_OBJECT

public:
    XmlParser(QObject* parent);
    virtual ~XmlParser();
    Channel& GetChannel();
    Channel& ParseXML();
    void SetData(const QByteArray&);

signals:
    void ParseErrorSignal(QString);

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














