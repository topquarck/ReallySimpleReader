#ifndef CHANNEL_H
#define CHANNEL_H
#include <QList>
#include "item.h"
class Channel
{
    QString title,link,desc,lang;
    QList<Item*> itemsList;
public:
    Channel();
    virtual ~Channel();
    void addItem(Item* givenItem);
    void setTitle(QString);
    void setLink(QString);
    void setDesc(QString);
    void setLang(QString);
    QString getTitle();
    QString getLink();
    QString getDesc();
    QString getLang();
    QList<Item*> getItems(){return this->itemsList;}

};

#endif // CHANNEL_H
