#include "channel.h"

Channel::Channel()
{
    itemsList.clear();
}
Channel::Channel(const Channel& givenChannel)
{
    title = givenChannel.title;
    link  = givenChannel.link;
    desc = givenChannel.desc;
    itemsList = givenChannel.itemsList;
}
Channel::~Channel(){
    qDebug("in Channel;s destructor");
    itemsList.clear();
    qDebug("just leaving Channels Dstructor");
}
void Channel::addItem(Item givenItem){
    itemsList.append(givenItem);
}
void Channel::setTitle(QString t){
    this->title = t;
}
void Channel::setLink(QString l ){
    this->link = l;
}
void Channel::setDesc(QString d){
    this->desc = d;
}
void Channel::setLang(QString l){
    this->lang = l;
}
QString Channel::getTitle(){
    return this->title;
}
QString Channel::getLink(){
    return this->link;
}
QString Channel::getDesc(){
    return this->desc;
}
QString Channel::getLang(){
    return this->lang;
}
int Channel::getSize()
{
    return itemsList.size();
}
