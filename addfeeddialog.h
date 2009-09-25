#ifndef ADDFEEDDIALOG_H
#define ADDFEEDDIALOG_H

#include <QtGui/QDialog>
class HttpDownloader;
class DBManager;

namespace Ui {
    class AddFeedDialog;
}

class AddFeedDialog : public QDialog {
    Q_OBJECT
public:
    AddFeedDialog(QWidget *parent = 0);
    ~AddFeedDialog();

protected:
    void changeEvent(QEvent *e);

private:
    void Init();
    void AddUISignals();
    bool IsValidFeedURL();
    bool IsValidChannel();
    void EnableUIControls();
    void DisableUIControls();
    void AddDBManagerSignals();
    void AddDownloaderSignals();
    void SetFeedURLValidator();

private slots:
    void HandleAddFeed();
    void RetreiveChannel();
    void HandleDownloadError(QString);
    void HandleDBManagerConnectionError(QString);
    void HandleDBManagerQueryError(QString);

private:
    Ui::AddFeedDialog	    *m_ui;
    DBManager		    *m_pDbManager;
    HttpDownloader	    *m_pDownloader;
    QString		    m_feedURL;
};

#endif // ADDFEEDDIALOG_H
