#include "xmlparser.h"
#include <QDomDocument>
#include <QDomElement>
#include <QByteArray>
#include "channel.h"
#include "item.h"
//
#include "httpdownloader.h"
XmlParser::XmlParser(QString urlName, QObject* parent) : QThread(parent)
{
    //init all pointer vars to NULL;
    m_pDoc = NULL;
    m_pRootElement = NULL;
    m_pData = NULL;
    m_pChannel = NULL;
    m_urlString = urlName;
}
XmlParser::~XmlParser()
{
    qDebug("in xmlParsers destructor");
    CleanUp();
    //qDebug("just leaving xmlParsers destructor");
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
    qDebug("in gethchannle, parser: size of chanels items %d",
           m_pChannel->getItems().size());
    return *m_pChannel;
}

void XmlParser::SetData(const QByteArray& dataArray)
{
    //just for checking, defensive coding,
    if (dataArray.isNull() || dataArray.isEmpty()){
        qDebug("in DetData, parser: the sent data from the downloader is either null or empty");
        emit SignalParseError("the sent data from the downloader is either null or empty");
        return;
    }
    if ( m_pData)
        delete m_pData;

    m_pData = new QByteArray(dataArray);
    qDebug("the size of the buffer in the xmpLaprser's set data is %d",
           m_pData->size());
}
/**
  this fn is the only public method used by the outsiders to DO ALL THE PARSING
  it calls all internal/private parsing methods that do the xML processing
  and returns the xml data in a form of Channel onject containing all parsed data
  */
void XmlParser::ParseXML()
{
    if (OpenBuffer()){
        if (ParseRssHead()){

            if (ParseChannel()){
                //return *m_pChannel;
                {
                    // it hink here we need to delete the dom classes to clean up mem
                    //m_pRootElement->clear();
                    delete m_pRootElement;
                    m_pRootElement = NULL;
                    //m_pDoc->clear();
                    delete m_pDoc;
                    m_pDoc = NULL;
                }
                emit SignalParseDone();
            }//end if ParseChannel
            else{  // channel tag is not valid and can't be parsed
                //report an error
                emit SignalParseError(QString("ERROR: Couldn't Parse Channel tag!"));
                //return NULL;
            }//end else ParseChannel

        }// end if ParseRssHead
        else{
            //the input file IS NOT A VALID RSS FILE
            //report an error
            emit SignalParseError(QString("ERROR: Invalid RssFile! Couldn't FIND <rss> tag!"));
            //return NULL;
        }//end else ParseRssHead

    }//end if buffer was opened
    else{ // failed to open the Buffer for data
        //report error
        emit SignalParseError(QString("ERROR: Couldn't Open Buffer for opening"));
    }//end else

    //return NULL;
}

/**
  this method transforms the Buffer data into DOM format
  if failed, We can't Parse anymore
  */
bool XmlParser::OpenBuffer()
{
    qDebug("bool XmlParser::OpenBuffer()");

    m_pDoc = new QDomDocument();
    //if the Buffer contents not loaded to mem
    if (m_pData->isNull()){
        qDebug("the data array is null!!");
    }
    if( !m_pDoc->setContent( *m_pData) ){
        //reportError
        emit SignalParseError(QString("ERROR: Couldn't load the data into DOM"));
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
    qDebug("bool XmlParser::ParseRssHead()");

    m_pRootElement = new QDomElement(m_pDoc->documentElement());
    //get the tag name if the ROOT and make it Uppercase for comparison
    QString tagName = m_pRootElement->tagName().toUpper();
    if (tagName == QString("RSS")){
        return true;
    }
    else
	return false;
}

/**
  this method parses the BODY of the Rss document - the <channel> tag
and the items inisde it. it fills the member variable m_pChannel with data
OR returns false if fails
  */
bool XmlParser::ParseChannel()
{
    qDebug("bool XmlParser::ParseChannel()");

    QDomElement tempElement = (m_pRootElement->firstChild()).toElement();
    if (! tempElement.isNull()){
        if (tempElement.tagName().toUpper() == QString("CHANNEL")){
            // till now, every thing is going OK
            // we found RSS tag as root, ans its first child is channel tag

            //just for checking
            if (m_pChannel)
                delete m_pChannel;

            m_pChannel = new Channel();
	    m_pChannel->setLink(m_urlString);
	    Item* tempItem = NULL;
            QDomNode node = tempElement.firstChild();
            QDomElement e;
            while( !node.isNull() ){
              e = node.toElement();
              if( !e.isNull() ){
                if( e.tagName().toLower() == "title" ){
                    m_pChannel->setTitle(e.text());
                }else if (e.tagName().toLower() == "link"){
		    //commented, expermental
		    //m_pChannel->setLink(e.text());
                }else if (e.tagName().toLower() == "description"){
                    m_pChannel->setDesc(e.text());
                }else if (e.tagName().toLower() == "language"){
                    m_pChannel->setLang(e.text());
                }

                //else if the tag is item, will call getitem
                else if (e.tagName().toLower() == "item"){
		    tempItem = ParseItem(e);
                    m_pChannel->addItem(*tempItem);
                    delete tempItem;
                }

                //else, we will discard the rest of the tags for now

              }//end if e not isNull()
              node = node.nextSibling();
            }//end while

            return true;
        }//end if tag name of first child is channel
        else{   // the first child of RSS root is NOT channel
            //report error
            emit SignalParseError(QString("ERROR: Root's first child is not <channel> tag"));
            return false;
        }
    }//end if first child is not null
    else{ // the first child of the root is NULL,
        //report error
        emit SignalParseError(QString("ERROR: couldn't retreive children of RSS"));
        return false;
    }//end else
}

/**
  this method parses the item element, returns Item* object
  NOTE: if failed to parse an item element, I THINK it is still OK
      WILL NOT interrupt the intire Parsing process because one element is
      faulty, So, if failed to parse the element, will return a NULL Object NOT error
  */
Item* XmlParser::ParseItem(QDomElement givenElement)
{
    qDebug("Item* XmlParser::ParseItem(QDomElement givenElement)");
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
        }
        //commented fro now, this info is no longer needed, replaced by pubDate and auther
        /*else if (e.tagName().toLower() =="description"){
            tempItem->setDesc(e.text());
        }*/
        else if (e.tagName().toLower() == "author"){
            tempItem->setAuther(e.text());
        }
        //else, we will discard the rest of the tags for now
      }else if (e.tagName().toLower() == QString("pubDate").toLower()){
          tempItem->setPubDate(e.text());
      }//end added
      node= node.nextSibling();
    }//end while
    return tempItem;
}

void XmlParser::run()
{
    qDebug("in Run method of the xmparser");
    this->ParseXML();
}

/**
  added on 18-7-09 to verify if the file is valid or not without storing values in internal members,
used for verifying newly inserted link
  */
bool XmlParser::IsValidRSSFile()
{
    if (this->ParseRssHead()){
	if (this->IsValidChannel())
	    return true;
    }
    return false;
}

/**
  this method checks whether the tag name is called channel or not, then fills in the channel object
  WITH : channel name, link and descrition ONLY, no need to parse the items.
  used in adding a new channel to the DB.

  @return true if the given channel is valid, false otherwise
  */
bool XmlParser::IsValidChannel()
{
    QDomElement tempElement = (m_pRootElement->firstChild()).toElement();
    if (! tempElement.isNull()){
	if (tempElement.tagName().toUpper() == QString("CHANNEL")){
	    // till now, every thing is going OK
	    // we found RSS tag as root, ans its first child is channel tag

	    //just for checking
	    if (m_pChannel)
		delete m_pChannel;

	    m_pChannel = new Channel();
	    //added to fix the problem explained in the next block of comment
	    m_pChannel->setLink(m_urlString);
	    QDomNode node = tempElement.firstChild();
	    QDomElement e;
	    while( !node.isNull() ){
	      e = node.toElement();
	      if( !e.isNull() ){
		if( e.tagName().toLower() == "title" ){
		    m_pChannel->setTitle(e.text());
		}
		/*else if (e.tagName().toLower() == "link"){
		    m_pChannel->setLink(e.text());
		     PROBLEM :the channel link item in the XML file is different from the actual desired url
		    example :  in xml  file
		    <channel><title>The Code Project Latest Articles</title>
			<link>http://www.codeproject.com</link>
			but the XML url file we want to store and process is called: http://www.codeproject.com/webservices/articlerss.aspx?cat=2

		    m_pChannel->setLink(m_p
		}*/else if (e.tagName().toLower() == "description"){
		    m_pChannel->setDesc(e.text());
		}else if (e.tagName().toLower() == "language"){
		    m_pChannel->setLang(e.text());
		}
	    }
	  }//end while node not null
	    return true;
	}//end if item tagname is CHANNEL
    }//end if elemnt is not null

    //i think if we are here, that means the channel was not parsed
    return false;
}


