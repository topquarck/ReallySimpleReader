#include "addfeeddialog.h"
#include "ui_addfeeddialog.h"
#include "dbmanager.h"
#include "httpdownloader.h"

AddFeedDialog::AddFeedDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::AddFeedDialog)
{
    m_ui->setupUi(this);
    Init();
}

AddFeedDialog::~AddFeedDialog()
{
    qDebug("~AddFeedDialog()");
    delete m_ui;
    if (m_pDbManager)
	delete m_pDbManager;
    if (m_pDownloader)
	delete m_pDownloader;
}
void AddFeedDialog::Init()
{
    qDebug("void AddFeedDialog::Init()");
    //m_ui->m_btnAddFeed->setEnabled(false);
    //connect(m_ui->m_txtFeedURL,SIGNAL(textChanged(QString)),
	//    m_ui->m_btnAddFeed,SLOT(setEnabled(bool)) );
    m_ui->m_statusLabel->setText("Enter Feed URL to add the feed");
    m_pDbManager = NULL;
    m_pDownloader = NULL;
    AddSignals();
}
void AddFeedDialog::AddSignals()
{
    connect(m_ui->m_btnAddFeed,SIGNAL(clicked()),
	    this,SLOT(HandleAddFeed() ) );
    connect(m_ui->m_btnClose,SIGNAL(clicked()),
	    this,SLOT(accept()) );
}
void AddFeedDialog::HandleAddFeed()
{
    qDebug("void AddFeedDialog::HandleAddFeed()");
    m_feedURL = m_ui->m_txtFeedURL->text();
    if (! IsValidFeedURL()){
	m_ui->m_statusLabel->setText("the Entered URL is Not a Valid Feed URL, Please Supply a valid one");
	m_ui->m_txtFeedURL->setFocus();
	return;
    }
    //else, the URL is valid
    //search for it, if it already exists in the DB
    m_pDbManager = new DBManager(this);
    if (m_pDbManager->URLExistedBefore(m_feedURL) ){
	m_ui->m_statusLabel->setText("Feed URL already Exists");
	return;
    }
    //else, the url is valid and new
    //download the fileand try to parse it
    m_pDownloader = new HttpDownloader(this);
    connect(m_pDownloader,SIGNAL(SignalDownloadDone()),
		    this,SLOT(RetreiveChannel()) );
    m_pDownloader->DownloadURL(m_feedURL);


}
void AddFeedDialog::RetreiveChannel()
{
    /*if (! m_pDownloader->IsValidRSSFile()){
	m_ui->m_statusLabel->setText("ERROR: the given URL doesn't have a valid RSS feed file");
	return;
    }*/
    //else, all good
    //will add the URL to the db
    if (! m_pDbManager->InsertNewCahnnel(m_pDownloader->GetChannel()) ){
	m_ui->m_statusLabel->setText("ERROR: Couldn't Store the URL to the Local DB");
	return;
    }else{
	m_ui->m_statusLabel->setText("the new Feed was added sucessfully to the DB.\n refetch feeds to retreive it");
    }
    // i think we need to delete the downloader object
}
/**
  this method is used to validate the URL inserted in the textBox
  @return true if the URL is gramatically correct, false otherwise
  */
bool AddFeedDialog::IsValidFeedURL()
{
    qDebug("bool AddFeedDialog::IsValidFeedURL()");
    //remove spaces from start/end
    m_feedURL = m_feedURL.trimmed();
    if (m_feedURL.isNull()|| m_feedURL == QString() || m_feedURL.isEmpty()){
	return false;
    }
    //stolen from Akregator source code:
    // HACK: make weird wordpress links ("feed:http://foobar/rss") work
    if (m_feedURL.startsWith(QLatin1String("feed:")))
	m_feedURL = m_feedURL.right( m_feedURL.length() - 5 );
    if (m_feedURL.indexOf(":/") == -1)
	m_feedURL.prepend("http://");
    return true;
}
void AddFeedDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}



