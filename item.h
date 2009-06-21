#ifndef ITEM_H
#define ITEM_H
#include <QString>
class Item
{
    QString title,link;
    // dont need it it is BIG DATA !!desc;
    //added to give more info to the user
    QString pubDate, auther ;
public:
    Item();
    //Item(QString ,QString,QString);
    Item(QString ,QString,QString,QString);
    virtual ~Item(){}
    void setTitle(QString t);
    void setLink(QString l);
    //void setDesc(QString d);
    void setPubDate(QString );
    void setAuther(QString);
    QString getPubDate();
    QString getAuther();
    QString getTitle();
    QString getLink();
    QString getDesc();
};

#endif // ITEM_H
