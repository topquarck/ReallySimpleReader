#ifndef WEBPAGEWINDOW_H
#define WEBPAGEWINDOW_H

#include <QtGui/QMainWindow>
class QAction;
class QUrl;
class QProgressBar;
class QLabel;
class QWebSettings;
class QCloseEvent;

namespace Ui {
    class WebPageWindow;
}

class WebPageWindow : public QMainWindow {
    Q_OBJECT
public:
    WebPageWindow(QWidget *parent = 0);
    WebPageWindow(QString givenUrl,QWidget *parent=0);
    ~WebPageWindow();
    void LoadPage();
    void LoadPage(QString);
    void SetURL(QString);

protected:
    void changeEvent(QEvent *e);
    void closeEvent( QCloseEvent * event );

private:    //methods
    void CreateToolBarActions();
    void DeleteToolBarActions();
    void Init();
    void AddWebViewSignals();
    void SetupStatusBar();
    void LoadWebSettings();

private slots:
    void HandleWebViewLoadStarted();
    void HandleWebViewLoadFinished(bool);

signals:
    void WebWindowClosing(QString);

private:
    Ui::WebPageWindow       *ui;
    QAction                 *m_pBackAction;
    QAction                 *m_pForwardAction;
    QAction                 *m_pStopActoin;
    QAction                 *m_pRealoadAction;
    QUrl                    *m_pUrl;
    QProgressBar            *m_pProgressBar;
    QLabel                  *m_pStatusLabel;
    QWebSettings	    *m_pSettings;
};

#endif // WEBPAGEWINDOW_H
