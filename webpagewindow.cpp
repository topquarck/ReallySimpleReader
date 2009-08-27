#include "webpagewindow.h"
#include "ui_webpagewindow.h"
#include <QUrl>
#include <QProgressBar>
#include <QLabel>
#include <QWebSettings>
#include <QCloseEvent>
//trying to disable history
#include <QWebHistory>

WebPageWindow::WebPageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WebPageWindow)
{
    this->Init();
    m_pUrl = NULL;
}

WebPageWindow::WebPageWindow(QString givenUrl,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WebPageWindow)
{
    m_pUrl = new QUrl(givenUrl); 
    this->Init();
    LoadPage();
}
/**
  one common method to add the the UI's common init tasks, to make it easier to modify afterwords
  */
void WebPageWindow::Init()
{
    ui->setupUi(this);

    this->CreateToolBarActions();
    this->SetupStatusBar();
    this->AddWebViewSignals();    

    LoadWebSettings();
}
void WebPageWindow::SetupStatusBar()
{
    m_pStatusLabel = new QLabel(this);
    ui->m_statusbar->addWidget(m_pStatusLabel,4);

    m_pProgressBar = new QProgressBar(this);
    m_pProgressBar->setMinimum(0);
    m_pProgressBar->setMaximum(100);
    ui->m_statusbar->addWidget(m_pProgressBar,1);
    m_pProgressBar->hide();
}
WebPageWindow::~WebPageWindow()
{
    qDebug("in WebPageWindow DEstructor");
    this->DeleteToolBarActions();
    if (m_pProgressBar)
	delete m_pProgressBar;
    if (m_pStatusLabel)
	delete m_pStatusLabel;
    if (m_pUrl)
        delete m_pUrl;

    delete ui;
    qDebug("After finishing the destructor");
}

void WebPageWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void WebPageWindow::CreateToolBarActions()
{
    m_pBackAction = new QAction("Back",this);
    connect(m_pBackAction,SIGNAL(triggered()),
            ui->m_webView,SLOT(back()) );
    ui->m_toolBar->addAction(m_pBackAction);

    m_pForwardAction = new QAction("Forward",this);
    connect(m_pForwardAction,SIGNAL(triggered()),
            ui->m_webView,SLOT(forward()) );
    ui->m_toolBar->addAction(m_pForwardAction);

    m_pRealoadAction = new QAction("Reload",this);
    connect(m_pRealoadAction,SIGNAL(triggered()),
            ui->m_webView,SLOT(reload()) );
    ui->m_toolBar->addAction(m_pRealoadAction);

    m_pStopActoin = new QAction("Stop",this);
    connect(m_pStopActoin,SIGNAL(triggered()),
            ui->m_webView,SLOT(stop()));
    ui->m_toolBar->addAction(m_pStopActoin);
}
void WebPageWindow::DeleteToolBarActions()
{
    qDebug("void WebPageWindow::DeleteToolBarActions()");
    if (m_pBackAction)
        delete m_pBackAction;
    if (m_pForwardAction)
        delete m_pForwardAction;
    if (m_pRealoadAction)
        delete m_pRealoadAction;
    if (m_pStopActoin)
        delete m_pStopActoin;
}

void WebPageWindow::LoadPage()
{
    qDebug("in LoadPAge, WebPageWindow");
    if (m_pUrl && ! m_pUrl->isEmpty() && m_pUrl->isValid()){
        ui->m_webView->load(*m_pUrl);
        setWindowTitle(m_pUrl->toString()+" - ReallySimpleReader.");
    }
}
void WebPageWindow::LoadPage(QString url)
{
    qDebug("in LoadPAge, WebPageWindow");
    SetURL(url);
    if (m_pUrl && ! m_pUrl->isEmpty() && m_pUrl->isValid()){
        ui->m_webView->load(*m_pUrl);
        setWindowTitle(m_pUrl->toString()+" - ReallySimpleReader.");
    }
}
void WebPageWindow::SetURL(QString givenurl)
{
    if (m_pUrl)
        delete m_pUrl;
    m_pUrl = new QUrl(givenurl);
}

void WebPageWindow::AddWebViewSignals()
{
    connect(ui->m_webView,SIGNAL(loadStarted()),
            this,SLOT(HandleWebViewLoadStarted()) );
    connect(ui->m_webView,SIGNAL(loadProgress(int)),
            m_pProgressBar,SLOT(setValue(int)) );
    connect(ui->m_webView,SIGNAL(loadFinished(bool)),
            this,SLOT(HandleWebViewLoadFinished(bool)) );
}

void WebPageWindow::HandleWebViewLoadStarted()
{
    qDebug("Load Started");
    m_pProgressBar->show();
    m_pProgressBar->reset();
    m_pStatusLabel->setText("Loading Page "+ m_pUrl->toString() );
}

void WebPageWindow::HandleWebViewLoadFinished(bool ok)
{
    qDebug("load Finished");
    if (ok){
        m_pProgressBar->hide();
        m_pStatusLabel->clear();
    }else{
        m_pProgressBar->hide();
        m_pStatusLabel->setText("Error Loading "+m_pUrl->toString());
    }
}

//
void WebPageWindow::LoadWebSettings()
{
    m_pSettings = ui->m_webView->settings();
    m_pSettings->setAttribute(QWebSettings::JavaEnabled,false);
    m_pSettings->setAttribute(QWebSettings::JavascriptCanOpenWindows,false);
    m_pSettings->setAttribute(QWebSettings::PluginsEnabled,false);

    m_pSettings->setAttribute(QWebSettings::PrivateBrowsingEnabled,true);

    // try to disable cache
    m_pSettings->setMaximumPagesInCache(0);
    m_pSettings->setObjectCacheCapacities(0, 0, 0);
    //trying to disable history
    ui->m_webView->page()->history()->setMaximumItemCount(0);
}

// trying to send a signal to the main window to tell it that the window has been closed
//so the main window deletes it
void WebPageWindow::closeEvent ( QCloseEvent * event )
{
    emit WebWindowClosing(m_pUrl->toString());
    event->accept();
}


