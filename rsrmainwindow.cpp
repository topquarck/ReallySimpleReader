#include "rsrmainwindow.h"
#include "ui_rsrmainwindow.h"
#include "reallysimplereader.h"
#include "feedmodel.h"
#include "item.h"
//for restoring state of the main window
#include <QByteArray>
#include <QFile>
#include "channellistmodel.h"
#include "channel.h"
//added to view a new window whan bouble-clicking an article
#include "webpagewindow.h"
#include <QProgressBar>
#include <QLabel>
#include "addfeeddialog.h"
#include <QHeaderView>
//trying to disable history
#include <QWebHistory>

RSRMainWindow::RSRMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::RSRMainWindow)
{
    ui->setupUi(this);
    this->CreateToolBar();
    //to add the progressbar to the statusbar
    SetupStatusBar();
    this->RestoreDefaultWindowState();
    this->SetupUIComponents();
    this->AddUISignals();
    Init();
}

RSRMainWindow::~RSRMainWindow()
{
    qDebug("in ~RSRMainWindow destructor");
    if (m_pGetFeedsAction)
        delete m_pGetFeedsAction;
    if (m_pFeedModel)
        delete m_pFeedModel;
    if (m_pChannelsModel)
        delete m_pChannelsModel;
    if (m_pReader)
        delete m_pReader;
    delete ui;
}
void RSRMainWindow::Init()
{
    qDebug("void RSRMainWindow::Init()");
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("ReallySimpleReader 0.1");
    m_pFeedModel = NULL;
    m_pChannelsModel = NULL;
    m_pReader = NULL;
    //
    //get initial data from the DB
    m_pStatusLabel->setText("Loading Feeds List ... ");
    CreateReader();
    //this->GetFeeds();

    //load the settings of the internal web browser
    LoadWebSettings();
}
void RSRMainWindow::CreateReader()
{
    qDebug("void RSRMainWindow::CreateReader()");
    m_pReader = new ReallySimpleReader(this);
    this->AddModelsSignals();
}
void RSRMainWindow::CreateToolBar()
{
    m_pGetFeedsAction = new QAction("Get Feeds",ui->m_mainToolBar);
    connect(m_pGetFeedsAction,SIGNAL(triggered()),
            this,SLOT(GetFeeds()));
    ui->m_mainToolBar->addAction(m_pGetFeedsAction);
}
void RSRMainWindow::SetupUIComponents()
{}
void RSRMainWindow::AddUISignals()
{
    connect(ui->m_webView,SIGNAL(loadStarted()),
            this,SLOT(HandleWebViewLoadStarted()));

    connect(ui->m_webView,SIGNAL(loadProgress(int)),
            m_pProgressBar,SLOT(setValue(int)) );

    connect(ui->m_webView,SIGNAL(loadFinished(bool)),
            this,SLOT(HandleWebViewLoadFinished(bool)));
    // the menu signals:
    connect(ui->actionFetchAllFeeds,SIGNAL(triggered()),
             this,SLOT(GetFeeds()) );
    connect(ui->actionExit,SIGNAL(triggered()),
            this,SLOT(close()) );
    // the add feed
    connect(ui->actionAddFeedSource,SIGNAL(triggered()),
	    this,SLOT(AddNewFeed()) );
}
void RSRMainWindow::HandleWebViewLoadStarted()
{
    if (!m_pProgressBar->isVisible())
        m_pProgressBar->show();
    m_pProgressBar->reset();
    m_pStatusLabel->setText(" Loading page "+
            ui->m_webView->url().toString());
}
void RSRMainWindow::HandleWebViewLoadFinished(bool ok)
{
    if (ok){
        m_pProgressBar->reset();
        m_pProgressBar->hide();
        m_pStatusLabel->clear();
    }else{
        m_pProgressBar->reset();
        m_pProgressBar->hide();
        m_pStatusLabel->setText("ERROR Loading "+ui->m_webView->url().toString());
    }
}
/*********** the following method is commented till we enable saving
              the state of the wain window
void RSRMainWindow::SaveState()
{
    QByteArray stateArray = this->saveState();
    QFile file("config/states");
    if (!file.open(QIODevice::WriteOnly ))
         return;
    file.write(stateArray);
}*/

/**
  this method restores the default Layout/dock state of the main window
  used to fix the POOR look of the window
  */
void RSRMainWindow::RestoreDefaultWindowState()
{
    QByteArray stateArray ;
    QFile file("config/states");
    if (!file.open(QIODevice::ReadOnly ))
         return;
    stateArray = file.readAll();
    this->restoreState(stateArray);
}

void RSRMainWindow::GetFeeds()
{
    qDebug("void RSRMainWindow::GetFeeds()");
    if (m_pReader)
	delete m_pReader;

    CreateReader();
    ui->m_listView->reset();
    ui->m_tableView->reset();
    m_pReader->GetFeeds();
}
void RSRMainWindow::AddModelsSignals()
{
    /*connect(m_pReader,SIGNAL(Finished()),
            this,SLOT(HandleDownLoadFinished()) );
    connect(m_pReader,SLOT(SignalDownloadProgress(int,int)),
             this,SLOT(HandleDownloadProgress(int,int)) );
    connect(m_pReader,SIGNAL(SignalDownloadError(QString)),
            this,SLOT(HandleDownloadErrors(QString)) );*/

    connect(m_pReader,SIGNAL(SignalAllChannelsFetched()),
            this,SLOT(HandleFetchedCahnnels()) );
    connect(m_pReader,SIGNAL(SignalChannelFetchStarted()),this,SLOT(HandleChannelFetchStarted()));
}
/**
  this SLOT deactivates the toolbar action and the menu item action till channels are fetched
  */
void RSRMainWindow::HandleChannelFetchStarted()
{
    qDebug("void RSRMainWindow::HandleChannelFetchStarted()");
    DisableToolBarActions();
}
void RSRMainWindow::HandleFetchedCahnnels()
{
    qDebug("in Windows HandleFetchedCahnnels, which invoked after emitting the all channels signal");
    //7-7-09 :will now re-enable the toolbar action and the menu item -- UPDATE : made it into a method
    EnableToolBarActions();
    //end 7-7
    m_pStatusLabel->clear();

    //added 04-09-09: if statement to handle if the DB has no records --> no data is sent So, no need to create a model and fill it with nothing
    if (m_pReader->GetChannelsList().size()>0){
        m_pChannelsModel = new ChannelListModel();
        m_pChannelsModel->SetChannelsList(m_pReader->GetChannelsList());
        qDebug("after calling : m_pChannelsModel->SetChannelsList(m_pReader->GetChannelsList());");
        ui->m_listView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->m_listView->setSelectionMode(QAbstractItemView::SingleSelection);
        connect(ui->m_listView,SIGNAL(clicked(QModelIndex)),
                this,SLOT(HandleChannelsViewSelection(QModelIndex) ) );
        ui->m_listView->setModel(m_pChannelsModel);
    }
}
void RSRMainWindow::HandleDownLoadFinished()
{
   qDebug("in Fill view , Window");
    /*QDirModel *model = new QDirModel;
    ui->m_feedListView->setModel(model);
    ui->m_feedListView->setRootIndex(model->index(QDir::currentPath()));
    */
    /*FeedModel* */ /* m_pFeedModel = new FeedModel();
    //
    ui->m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->m_tableView,SIGNAL(clicked(QModelIndex)),
             this,SLOT(HandleItemsViewSelection(QModelIndex) ) );
    m_pFeedModel->setItemsList(m_pReader->GetItemsList());
    ui->m_tableView->setModel(m_pFeedModel);
    //ui->m_tableView->resizeColumnsToContents();
    ui->m_tableView->show();*/

}
void RSRMainWindow::HandleItemsViewSelection(QModelIndex index)
{
    if (!index.isValid() || index.row() >= m_pFeedModel->rowCount())
         return ;
    //else
    QString url = m_pFeedModel->GetLink(index.row());

    ui->m_webView->load(QUrl(url));

}
void RSRMainWindow::HandleChannelsViewSelection(QModelIndex index)
{
    qDebug("in HandleChannelsViewSelection, window");
    if (!index.isValid() || index.row() >= m_pChannelsModel->rowCount())
         return ;
    //will create the feed items model and fill it with items
    if (m_pFeedModel){
        delete m_pFeedModel;
        m_pFeedModel = NULL;
    }

    m_pFeedModel = new FeedModel();
    ui->m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->m_tableView,SIGNAL(clicked(QModelIndex)),
             this,SLOT(HandleItemsViewSelection(QModelIndex) ) );
    m_pFeedModel->setItemsList(m_pChannelsModel->GetChannel(index.row()).getItems() );
    ui->m_tableView->setModel(m_pFeedModel);
    //ui->m_tableView->resizeColumnsToContents();
    ui->m_tableView->horizontalHeader()->resizeSection(0,500);
    ui->m_tableView->show();
    //added to handle the double clicks
    connect(ui->m_tableView,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(HandleDoubleClicked(QModelIndex)) );

}

/**
  this SLOT is called when the user double-clicks a news item from the items view
  it is supposed to show him a new window that contains the detailed news item's page
  */
void RSRMainWindow::HandleDoubleClicked(QModelIndex index)
{
    if (!index.isValid() || index.row() >= m_pFeedModel->rowCount())
         return ;
    //else
    QString url = m_pFeedModel->GetLink(index.row());

    //if the url already opnen in a window
    if (m_webWindowsHash.contains(url)){
        //just raise it to the user
        m_webWindowsHash.value(url)->raise();
    }
    else{
        //else , the url is new,
        //create a window, view it to the user
        WebPageWindow* window = new WebPageWindow(this);
        connect(window,SIGNAL(WebWindowClosing(QString)),this,SLOT(HandleWebWindowClosed(QString)));
        window->LoadPage(url);
        window->show();
        //and add a refernce to it in the Open windows Hash
        m_webWindowsHash.insert(url,window);
    }
}

/**
  this method adds a label and a progressbar to the statusbar
  */
void RSRMainWindow::SetupStatusBar()
{
    m_pStatusLabel = new QLabel(this);
    ui->m_statusBar->addWidget(m_pStatusLabel,4);

    m_pProgressBar = new QProgressBar(this);
    m_pProgressBar->setMinimum(0);
    m_pProgressBar->setMaximum(100);
    ui->m_statusBar->addWidget(m_pProgressBar,1);
    m_pProgressBar->hide();
}

/**
  this slot method is used to create a new "AddFeedDialog"
  */
void RSRMainWindow::AddNewFeed()
{
    AddFeedDialog* dialog = new AddFeedDialog(this);
    dialog->show();
}

/**
  this SLOT is called when an open child news page is closed, it - the child window - emits a signal called
  WebWindowClosing(QString the_window_url) before it dies.
  this method locates its reference in the open windows Hash table deletes it - removes the table entry AND DELETES
  the child window < calls its destructor>.
  @param url the url of the web , used as the key to locate the window object in the hash table
  */
void RSRMainWindow::HandleWebWindowClosed(QString url)
{
    if (m_webWindowsHash.contains(url)){
        // remove the object : the take() method gets the value from the table AND REMOVES ITS ENTRY
        WebPageWindow* ptr = m_webWindowsHash.take(url);
        //delete the window object
        delete ptr;
    }
}

/**
  a separate method to add some settings to the internal web viewer ui->m_webView,
  the aim of that is to try to minimize the memory usage made by QWebView Component and making the app as lightweight as possible:
  in the internal view : will not load images, will disable both javascript and java, will try to eliminate history and enable private browsing
  */
void RSRMainWindow::LoadWebSettings()
{
    ui->m_webView->settings()->setAttribute(QWebSettings::AutoLoadImages,false); //dont know why it doesnt work
    ui->m_webView->settings()->setAttribute(QWebSettings::JavascriptEnabled,false);
    ui->m_webView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled,false);
    ui->m_webView->settings()->setAttribute(QWebSettings::JavaEnabled,false);
    ui->m_webView->settings()->setAttribute(QWebSettings::PluginsEnabled,false);
    ui->m_webView->settings()->setAttribute(QWebSettings::PrivateBrowsingEnabled,true);

    // try to disable cache
    ui->m_webView->settings()->setMaximumPagesInCache(0);
    ui->m_webView->settings()->setObjectCacheCapacities(0, 0, 0);
    //trying to disable history
    ui->m_webView->page()->history()->setMaximumItemCount(0);

}

void RSRMainWindow::EnableToolBarActions()
{
    m_pGetFeedsAction->setEnabled(true);
    ui->actionFetchAllFeeds->setEnabled(true);
}
void RSRMainWindow::DisableToolBarActions()
{
    m_pGetFeedsAction->setEnabled(false);
    ui->actionFetchAllFeeds->setEnabled(false);
}
