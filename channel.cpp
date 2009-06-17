#include "channel.h"

Channel::Channel()
{
    this->itemsList.clear();
}
Channel::~Channel(){
    if (! this->itemsList.empty()){
        //Item* tempItem = NULL;
        while(this->itemsList.empty()){
            delete itemsList.takeLast();
        }
    }
}
void Channel::addItem(Item* givenItem){
    if (givenItem ) // if not null
        this->itemsList.append(givenItem);
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
