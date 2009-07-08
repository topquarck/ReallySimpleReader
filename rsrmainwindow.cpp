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
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("ReallySimpleReader 0.1");
    m_pFeedModel = NULL;
    m_pChannelsModel = NULL;
    m_pReader = NULL;
    //
    //get initial data from the DB
    m_pStatusLabel->setText("Loading Feeds List ... ");
    CreateReader();
    this->GetFeeds();
}
void RSRMainWindow::CreateReader()
{
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
    if (!m_pReader)
        CreateReader();
    //
    ui->m_listView->reset();
    ui->m_tableView->reset();
    //
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
    m_pGetFeedsAction->setEnabled(false);
    ui->actionFetchAllFeeds->setEnabled(false);
}
void RSRMainWindow::HandleFetchedCahnnels()
{
    qDebug("in Windows HandleFetchedCahnnels, which invoked after emitting the all channels signal");
    //7-7-09 :will now re-enable the toolbar action and the menu item
    m_pGetFeedsAction->setEnabled(true);
    ui->actionFetchAllFeeds->setEnabled(true);
    //end 7-7
    m_pStatusLabel->clear();

    m_pChannelsModel = new ChannelListModel();
    m_pChannelsModel->SetChannelsList(m_pReader->GetChannelsList());
    ui->m_listView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_listView->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->m_listView,SIGNAL(clicked(QModelIndex)),
            this,SLOT(HandleChannelsViewSelection(QModelIndex) ) );
    ui->m_listView->setModel(m_pChannelsModel);
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
    ui->m_tableView->show();
    //added to handle the double clicks
    connect(ui->m_tableView,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(HandleDoubleClicked(QModelIndex)) );

}

void RSRMainWindow::HandleDoubleClicked(QModelIndex index)
{
    if (!index.isValid() || index.row() >= m_pFeedModel->rowCount())
         return ;
    //else
    QString url = m_pFeedModel->GetLink(index.row());

    /**************8888 NEED REFACTORING
      a very disgusting solution, But it works !!
      the problem: open a window, close it  and then open it again --> will not open
      because the url entry correspondind to it still exists in the hashTable, BUT whent it closed it didnt inform
      the hashtable to delete it : cant find a method to notfiy hashtable with the death of the window

       the disgusstin solution : if the url already exists in the hashtable : close the window - even it was already dead-
       and remove tje entry, then treat it as a new entry (delete it and recreate it )
      **********************/
    if (m_webWindowsHash.contains(url)){
        //just view it
	//m_webWindowsHash.value(url)->raise();
	m_webWindowsHash.value(url)->close();
	m_webWindowsHash.remove(url);
    }
    //else{
        //else , the url is new,
        //create a window and insert it into the hash
        WebPageWindow* window = new WebPageWindow(this);
        //window->setObjectName(url);
	//connect(window,SIGNAL(destroyed(QObject*)),this,SLOT(HandleDestroyedWindow(QObject*)) );
        window->LoadPage(url);
        window->show();
        m_webWindowsHash.insert(url,window);
    //}
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
