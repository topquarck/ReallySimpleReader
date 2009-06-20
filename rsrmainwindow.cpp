#include "rsrmainwindow.h"
#include "ui_rsrmainwindow.h"
#include "reallysimplereader.h"
//t//testing only
//#//#include <QDirModel>
#include "feedmodel.h"
RSRMainWindow::RSRMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::RSRMainWindow)
{
    ui->setupUi(this);
    this->CreateToolBar();
    //this->FillView();
}

RSRMainWindow::~RSRMainWindow()
{
    if (m_pGetFeedsAction)
        delete m_pGetFeedsAction;
    delete ui;
}
void RSRMainWindow::CreateToolBar()
{
    m_pGetFeedsAction = new QAction("Get Feeds",ui->m_mainToolBar);
    connect(m_pGetFeedsAction,SIGNAL(triggered()),
            this,SLOT(GetFeeds()));
    ui->m_mainToolBar->addAction(m_pGetFeedsAction);
}
void RSRMainWindow::GetFeeds()
{
    //if (!m_pReader)
        m_pReader = new ReallySimpleReader(this);
    m_pReader->SetURL("http://feeds.feedburner.com/f055");

    this->AddModelsSignals();
    m_pReader->GetFeeds();
}
void RSRMainWindow::AddModelsSignals()
{
    connect(m_pReader,SIGNAL(Finished()),
            this,SLOT(HandleDownLoadFinished()) );
    connect(m_pReader,SLOT(SignalDownloadProgress(int,int)),
             this,SLOT(HandleDownloadProgress(int,int)) );
    connect(m_pReader,SIGNAL(SignalDownloadError(QString)),
            this,SLOT(HandleDownloadErrors(QString)) );
}
void RSRMainWindow::HandleDownLoadFinished()
{
   qDebug("in Fill view , Window");
    /*QDirModel *model = new QDirModel;
    ui->m_feedListView->setModel(model);
    ui->m_feedListView->setRootIndex(model->index(QDir::currentPath()));
    */
    FeedModel* model = new FeedModel();
    //
    model->setItemsList(m_pReader->GetItemsList());
    ui->m_tableView->setModel(model);
    ui->m_tableView->show();

}
