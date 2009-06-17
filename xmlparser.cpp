#include "xmlparser.h"
#include <QDomDocument>
#include <QDomElement>
#include <QByteArray>
#include "channel.h"
#include "item.h"
XmlParser::XmlParser(QObject* parent) : QObject(parent)
{
    //init all pointer vars to NULL;
    m_pDoc = NULL;
    m_pRootElement = NULL;
    m_pData = NULL;
    m_pChannel = NULL;
}
XmlParser::~XmlParser()
{
    CleanUp();
}
void XmlParser::CleanUp()
{
    if (m_pChannel){
        delete m_pChannel;
        m_pChannel = NULL;
    }
    if (m_pRootElement){
        m_pRootElement->clear(); // Converts the node into a null node; if it was not a null node before, its type and contents are deleted.
        //delete m_pRootElement;
        //m_pRootElement = NULL;
    }
    if (m_pDoc){
        m_pDoc->clear();
        //delete m_pRootElement;
        //m_pRootElement = NULL;
    }
    if (m_pData){
        m_pData->clear();
        //delete m_pData;
        //m_pData = NULL;
    }

}
/**
  this method returns the Actual parsed channel data - including itemList inside it-
  NOTE: this fn returns Channel Object NOT pointer to a channel object
  */
Channel& XmlParser::GetChannel()
{
    return *m_pChannel;
}

void XmlParser::SetData(const QByteArray& dataArray)
{
    if (! m_pData) // if m_pData is NULL. not created yet
        m_pData = new QByteArray(dataArray);
    else{ // if buffer already exists, delete it and reallocate it
        delete m_pData ;
        m_pData = new QByteArray(dataArray);
    }

}
/**
  this fn is the only public method used by the outsiders to DO ALL THE PARSING
  it calls all internal/private parsing methods that do the xML processing
  and returns the xml data in a form of Channel onject containing all parsed data
  */
Channel& XmlParser::ParseXML()
{
    if (OpenBuffer()){
        if (ParseRssHead()){

            if (ParseChannel()){
                return *m_pChannel;
            }//end if ParseChannel
            else{  // channel tag is not valid and can't be parsed
                //report an error
                emit ParseErrorSignal(QString("ERROR: Couldn't Parse Channel tag!"));
                //return NULL;
            }//end else ParseChannel

        }// end if ParseRssHead
        else{
            //the input file IS NOT A VALID RSS FILE
            //report an error
            emit ParseErrorSignal(QString("ERROR: Invalid RssFile! Couldn't FIND <rss> tag!"));
            //return NULL;
        }//end else ParseRssHead

    }//end if buffer was opened
    else{ // failed to open the Buffer for data
        //report error
        emit ParseErrorSignal(QString("ERROR: Couldn't Open Buffer for opening"));
    }//end else

    //return NULL;
}

/**
  this method transforms the Buffer data into DOM format
  if failed, We can't Parse anymore
  */
bool XmlParser::OpenBuffer()
{
    //std::cout<<"in the getRSS, RSSReader"<<endl;
    m_pDoc = new QDomDocument();
    //if the Buffer contents not loaded to mem
    if( !m_pDoc->setContent( *m_pData) ){
        //reportError
        emit ParseErrorSignal(QString("ERROR: Couldn't load the data into DOM"));
      return false;
    }
    //else: file contents loaded
    return true;
}

/**
  this method parses the Root element and Makes sure it finds <rss> tag
  OR it will return false as the inout xml document is INVALID
  */
bool XmlParser::ParseRssHead()
{
    m_pRootElement = new QDomElement(m_pDoc->documentElement());
    //get the tag name if the ROOT and make it Uppercase for comparison
    QString tagName = m_pRootElement->tagName().toUpper();
    if (tagName!= QString("RSS")){
        return false;
    }
    else if (tagName == QString("RSS")){
        return true;
    }
    //will not get here, it is either rss or not
    return false;
}

/**
  this method parses the BODY of the Rss document - the <channel> tag
and the items inisde it. it fills the member variable m_pChannel with data
OR returns false if fails
  */
bool XmlParser::ParseChannel()
{
    QDomElement tempElement = (m_pRootElement->firstChild()).toElement();
    if (! tempElement.isNull()){
        if (tempElement.tagName().toUpper() == QString("CHANNEL")){
            // till now, every thing is going OK
            // we found RSS tag as root, ans its first child is channel tag

            //just for checking
            if (m_pChannel){
                delete m_pChannel;
                m_pChannel = NULL;
            }
            m_pChannel = new Channel();
            QDomNode node = tempElement.firstChild();
            QDomElement e;
            while( !node.isNull() ){
              e = node.toElement();
              if( !e.isNull() ){
                if( e.tagName().toLower() == "title" ){
                    m_pChannel->setTitle(e.text());
                }else if (e.tagName().toLower() == "link"){
                    m_pChannel->setLink(e.text());
                }else if (e.tagName().toLower() == "description"){
                    m_pChannel->setDesc(e.text());
                }else if (e.tagName().toLower() == "language"){
                    m_pChannel->setLang(e.text());
                }

                //else if the tag is item, will call getitem
                else if (e.tagName().toLower() == "item"){
                    m_pChannel->addItem(ParseItem(e));
                }

                //else, we will discard the rest of the tags for now

              }//end if e not isNull()
              node = node.nextSibling();
            }//end while

            return true;
        }//end if tag name of first child is channel
        else{   // the first child of RSS root is NOT channel
            //report error
            emit ParseErrorSignal(QString("ERROR: Root's first child is not <channel> tag"));
            return false;
        }
    }//end if first child is not null
    else{ // the first child of the root is NULL,
        //report error
        emit ParseErrorSignal(QString("ERROR: couldn't retreive children of RSS"));
        return false;
    }//end else
}

/**
  this method parses the item element, returns Item* object
  NOTE: if failed to parse an item element, I THINK it is still OK
      WILL NOT interrupt the intire Parsing process because one element is
      faulty, So, if failed to parse the element, will return a NULL Object NOT error
  */
Item* XmlParser::ParseItem(QDomElement givenElement){
    //Item* tempITem = NULL;
    QDomNode node = givenElement.firstChild();
    //if first child id NULL, return immediately
    if (node.isNull()){
        return NULL;
    }
    //else : the first child is NOT NULL
    Item* tempItem = new Item();
    QDomElement e;
    while( !node.isNull() ){
      e = node.toElement();
      if( !e.isNull() )
      {
        if( e.tagName().toLower() == "title" ){
            tempItem->setTitle(e.text());
        }else if (e.tagName().toLower()=="link"){
            tempItem->setLink(e.text());
        }else if (e.tagName().toLower() =="description"){
            tempItem->setDesc(e.text());
        }
        //else, we will discard the rest of the tags for now
      }
      node= node.nextSibling();
    }//end while
    return tempItem;
}







