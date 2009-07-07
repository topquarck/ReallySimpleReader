#ifndef RSRMAINWINDOW_H
#define RSRMAINWINDOW_H

#include <QtGui/QMainWindow>

class QAction;
class ReallySimpleReader;
//testing
class FeedModel ;
//class QModelIndex;
#include <QModelIndex>
class ChannelListModel;
namespace Ui
{
    class RSRMainWindow;
}

class RSRMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    RSRMainWindow(QWidget *parent = 0);
    ~RSRMainWindow();

public slots:
    void GetFeeds();

private slots:
    void HandleDownLoadFinished();
    void HandleItemsViewSelection(QModelIndex index);
    //the following slots for the viewing of the channel names in the left listview
    void HandleFetchedCahnnels();
    void HandleChannelsViewSelection(QModelIndex);
    void HandleWebViewLoadStarted();
    void HandleWebViewLoadFinished(bool);
    void HandleChannelFetchStarted();

private:    //methods
    void CreateToolBar();
    void AddModelsSignals();
    void RestoreDefaultWindowState();
    void SetupUIComponents();
    void AddUISignals();
    //
    void Init();
    void CreateReader();
    //

private:
    Ui::RSRMainWindow*      ui;
    QAction*                m_pGetFeedsAction;
    ReallySimpleReader*     m_pReader;

    FeedModel*              m_pFeedModel;
    ChannelListModel*       m_pChannelsModel;

};

#endif // RSRMAINWINDOW_H
