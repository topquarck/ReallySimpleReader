#ifndef RSRMAINWINDOW_H
#define RSRMAINWINDOW_H

#include <QtGui/QMainWindow>

class QAction;
class ReallySimpleReader;
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
private:    //methods
    void CreateToolBar();
    void AddModelsSignals();

private:
    Ui::RSRMainWindow *ui;
    QAction* m_pGetFeedsAction;
    ReallySimpleReader* m_pReader;

};

#endif // RSRMAINWINDOW_H
