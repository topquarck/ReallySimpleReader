#ifndef ITEM_H
#define ITEM_H
#include <QString>
class Item
{
    QString title,link,desc;
public:
    Item();
    Item(QString ,QString,QString);
    virtual ~Item(){}
    void setTitle(QString t);
    void setLink(QString l);
    void setDesc(QString d);
    QString getTitle();
    QString getLink();
    QString getDesc();
};

#endif // ITEM_H
