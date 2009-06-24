#include "rsrmainwindow.h"
#include "ui_rsrmainwindow.h"
#include "reallysimplereader.h"
#include "feedmodel.h"
//testing
#include "item.h"
//for restoring state of the main window
#include <QByteArray>
#include <QFile>
#include "channellistmodel.h"
#include "channel.h"
RSRMainWindow::RSRMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::RSRMainWindow)
{
    ui->setupUi(this);
    this->CreateToolBar();
    //this->FillView();
    //
    this->RestoreDefaultWindowState();
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
void RSRMainWindow::CreateToolBar()
{
    m_pGetFeedsAction = new QAction("Get Feeds",ui->m_mainToolBar);
    connect(m_pGetFeedsAction,SIGNAL(triggered()),
            this,SLOT(GetFeeds()));
    ui->m_mainToolBar->addAction(m_pGetFeedsAction);
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
    //if (!m_pReader)
        m_pReader = new ReallySimpleReader(this);
    //m_pReader->SetURL("http://feeds.feedburner.com/f055");
    //m_pReader->SetURL("http://www.codeproject.com/webservices/articlerss.aspx?cat=2");

    this->AddModelsSignals();
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
}
void RSRMainWindow::HandleFetchedCahnnels()
{
    qDebug("in Windows HandleFetchedCahnnels, which invoked after emitting the all channels signal");
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
    if (m_pFeedModel)
        delete m_pFeedModel;

    m_pFeedModel = new FeedModel();
    ui->m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->m_tableView,SIGNAL(clicked(QModelIndex)),
             this,SLOT(HandleItemsViewSelection(QModelIndex) ) );
    m_pFeedModel->setItemsList(m_pChannelsModel->GetChannel(index.row()).getItems() );
    ui->m_tableView->setModel(m_pFeedModel);
    //ui->m_tableView->resizeColumnsToContents();
    ui->m_tableView->show();

}


