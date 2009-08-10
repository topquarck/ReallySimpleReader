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
    void AddSignals();
    bool IsValidFeedURL();
    bool IsValidChannel();

private slots:
    void HandleAddFeed();
    void RetreiveChannel();

private:
    Ui::AddFeedDialog	    *m_ui;
    DBManager		    *m_pDbManager;
    HttpDownloader	    *m_pDownloader;
    QString		    m_feedURL;
};

#endif // ADDFEEDDIALOG_H
