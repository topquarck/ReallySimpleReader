#include "addfeeddialog.h"
#include "ui_addfeeddialog.h"
#include "dbmanager.h"
#include "httpdownloader.h"
// to validate the url
#include <QRegExpValidator>
#include <QRegExp>
#include <QDebug>

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
    if (m_pDbManager)
	delete m_pDbManager;
    if (m_pDownloader)
	delete m_pDownloader;

    delete m_ui;
}
void AddFeedDialog::Init()
{
    qDebug("void AddFeedDialog::Init()");

    m_ui->m_statusLabel->setText("Enter Feed URL to add the feed");
    m_pDbManager = NULL;
    m_pDownloader = NULL;

    AddUISignals();

    //add avlidator
    SetFeedURLValidator();

}
void AddFeedDialog::AddUISignals()
{
    connect(m_ui->m_btnAddFeed,SIGNAL(clicked()),
	    this,SLOT(HandleAddFeed() ) );
    connect(m_ui->m_btnClose,SIGNAL(clicked()),
	    this,SLOT(accept()) );
    connect(m_ui->m_txtFeedURL,SIGNAL(returnPressed()),
            this,SLOT(HandleAddFeed()));
}
void AddFeedDialog::HandleAddFeed()
{
    qDebug("void AddFeedDialog::HandleAddFeed()");
    m_feedURL = m_ui->m_txtFeedURL->text();
    if (! IsValidFeedURL()){
	m_ui->m_statusLabel->setText("the Entered URL is Not a Valid Feed URL, Please Supply a valid one");
        m_ui->m_txtFeedURL->selectAll();
	m_ui->m_txtFeedURL->setFocus();
	return;
    }
    //else, the URL is valid
    //search for it, if it already exists in the DB
    m_pDbManager = new DBManager(this);
    AddDBManagerSignals();
    if (m_pDbManager->URLExistedBefore(m_feedURL) ){
	m_ui->m_statusLabel->setText("Feed URL already Exists");
        m_ui->m_txtFeedURL->setFocus();
	return;
    }
    //else, the url is valid and new
    //download the fileand try to parse it
    m_pDownloader = new HttpDownloader(this);
    AddDownloaderSignals();

    m_pDownloader->DownloadURL(m_feedURL);
    //dim the add feed button till download is done
    DisableUIControls();
    m_ui->m_statusLabel->setText("Fetching Feed URL ...");


}
void AddFeedDialog::RetreiveChannel()
{
    EnableUIControls();
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

/**
  a method to handle the download/parse errors emitted by the downloader;
  it tells a user the error and reenables the Add feed button again
  */
void AddFeedDialog::HandleDownloadError(QString error)
{
    qDebug()<<error;
    m_ui->m_statusLabel->setText("DOWNLOAD ERROR: Couldn't Download the specified RSS feed file.\n Please Make Sure you've entered a valid one!");
    EnableUIControls();
}

/**
  a method to enable the UI controls to accept user's input
  */
void AddFeedDialog::EnableUIControls()
{
    m_ui->m_btnAddFeed->setEnabled(true);
    m_ui->m_btnClose->setEnabled(true);
    m_ui->m_txtFeedURL->setEnabled(true);
    m_ui->m_txtFeedURL->selectAll();
    m_ui->m_txtFeedURL->setFocus();
}

/**
  a method to enable the UI controls to accept user's input
  */
void AddFeedDialog::DisableUIControls()
{
    m_ui->m_btnAddFeed->setEnabled(false);
    m_ui->m_btnClose->setEnabled(false);
    m_ui->m_txtFeedURL->setEnabled(false);
}

/**
  this method connects to DBManager's error signals
  */
void AddFeedDialog::AddDBManagerSignals()
{
    connect(m_pDbManager,SIGNAL(ConnectionErrorSignal(QString)),
            this,SLOT(HandleDBManagerConnectionError(QString)) );

    connect(m_pDbManager,SIGNAL(QueryErrorSignal(QString)),
            this,SLOT(HandleDBManagerQueryError(QString)) );
}

/**
  this method connects to HttpDownloader's error signals
  */
void AddFeedDialog::AddDownloaderSignals()
{
    connect(m_pDownloader,SIGNAL(SignalDownloadDone()),
                    this,SLOT(RetreiveChannel()) );
    connect (m_pDownloader,SIGNAL(SignalDownloadError(QString)),
             this,SLOT(HandleDownloadError(QString)) );
}

void AddFeedDialog::SetFeedURLValidator()
{
    QRegExp rx("(([a-zA-Z][0-9a-zA-Z+\\-\\.]*:)?/{0,2}[0-9a-zA-Z;/?:@&=+$\\.\\-_!~*'()%]+)?(#[0-9a-zA-Z;/?:@&=+$\\.\\-_!~*'()%]+)?");

    QRegExpValidator *urlValidator = new QRegExpValidator(rx, this);
    m_ui->m_txtFeedURL->setValidator(urlValidator);
}

/**
  prints the error string to the status label
  */
void AddFeedDialog::HandleDBManagerConnectionError(QString error)
{
    m_ui->m_statusLabel->setText(error);
}

void AddFeedDialog::HandleDBManagerQueryError(QString error)
{
    m_ui->m_statusLabel->setText(error);
}





