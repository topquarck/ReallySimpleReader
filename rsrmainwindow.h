#ifndef RSRMAINWINDOW_H
#define RSRMAINWINDOW_H

#include <QtGui/QMainWindow>

class QAction;
class ReallySimpleReader;
//testing
class FeedModel ;
//class QModelIndex;
#include <QModelIndex>
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
    //testing
    void HandleViewSelection(QModelIndex index);
private:    //methods
    void CreateToolBar();
    void AddModelsSignals();
    void RestoreDefaultWindowState();

private:
    Ui::RSRMainWindow *ui;
    QAction* m_pGetFeedsAction;
    ReallySimpleReader* m_pReader;
    //testing
    FeedModel* m_pFeedModel;

};

#endif // RSRMAINWINDOW_H
