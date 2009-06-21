#include "item.h"

Item::Item()
{
}
/*Item::Item(QString givenTitle,QString givenLink,QString givenDesc)
{
    this->title  = givenTitle;
    this->link = givenLink;
    this->desc = givenDesc;
}*/
Item::Item(QString givenTitle,QString givenLink,QString pubDate,QString pub)
{
    this->title  = givenTitle;
    this->link = givenLink;
    this->pubDate = pubDate;
    this->auther = pub;
}
void Item::setTitle(QString t){
        this->title = t;
}
void Item::setLink(QString l){
        this->link = l;
    }
/*void Item::setDesc(QString d){
        this->desc = d;
}*/
void Item::setPubDate(QString d)
{
    this->pubDate = d;
}
void Item::setAuther(QString p)
{
    this->auther = p;
}
QString Item::getPubDate()
{
    return this->pubDate;
}
QString Item::getAuther()
{
    return this->auther ;
}
QString Item::getTitle(){
    return this->title;
}
QString Item::getLink(){
    return this->link;
}
/*QString Item::getDesc(){
    return this->desc;
}*/
