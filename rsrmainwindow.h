#ifndef RSRMAINWINDOW_H
#define RSRMAINWINDOW_H

#include <QtGui/QMainWindow>

class QAction;
class ReallySimpleReader;
//testing
class FeedModel ;
#include <QModelIndex>
class ChannelListModel;
class WebPageWindow;
#include <QHash>;
//
#include <QPointer>;
//to add progress bar to the statusbar
class QProgressBar;
class QLabel;

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
    void AddNewFeed();

private slots:
    void HandleDownLoadFinished();
    void HandleItemsViewSelection(QModelIndex index);
    //the following slots for the viewing of the channel names in the left listview
    void HandleFetchedCahnnels();
    void HandleChannelsViewSelection(QModelIndex);
    void HandleWebViewLoadStarted();
    void HandleWebViewLoadFinished(bool);
    void HandleChannelFetchStarted();
    void HandleDoubleClicked(QModelIndex);

private:    //methods
    void CreateToolBar();
    void AddModelsSignals();
    void RestoreDefaultWindowState();
    void SetupUIComponents();
    void AddUISignals();
    void Init();
    void CreateReader();
    //to add the progressbar to the statusBar
    void SetupStatusBar();

private:
    Ui::RSRMainWindow              *ui;
    QAction                        *m_pGetFeedsAction;
    ReallySimpleReader             *m_pReader;

    FeedModel                      *m_pFeedModel;
    ChannelListModel               *m_pChannelsModel;
    //added to view a new window whan bouble-clicking an article
    QHash<QString,WebPageWindow*>   m_webWindowsHash;
    //added to show the status,7 progress INSIDE the statusbar
    QProgressBar                    *m_pProgressBar;
    QLabel                          *m_pStatusLabel;

};

#endif // RSRMAINWINDOW_H
