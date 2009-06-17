#include "item.h"

Item::Item()
{
}
Item::Item(QString givenTitle,QString givenLink,QString givenDesc)
{
    this->title  = givenTitle;
    this->link = givenLink;
    this->desc = givenDesc;
}
void Item::setTitle(QString t){
        this->title = t;
}
void Item::setLink(QString l){
        this->link = l;
    }
void Item::setDesc(QString d){
        this->desc = d;
}
QString Item::getTitle(){
    return this->title;
}
QString Item::getLink(){
    return this->link;
}
QString Item::getDesc(){
    return this->desc;
}
