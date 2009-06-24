#ifndef CHANNEL_H
#define CHANNEL_H
#include <QList>
#include "item.h"
class Channel
{
    QString title,link,desc,lang;
    QList<Item> itemsList;
public:
    Channel();
    Channel(const Channel&);
    virtual ~Channel();
    void addItem(Item givenItem);
    void setTitle(QString);
    void setLink(QString);
    void setDesc(QString);
    void setLang(QString);
    QString getTitle();
    QString getLink();
    QString getDesc();
    QString getLang();
    QList<Item> getItems(){return itemsList;}
    int getSize();

};

#endif // CHANNEL_H
