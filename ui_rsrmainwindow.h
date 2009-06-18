/********************************************************************************
** Form generated from reading ui file 'rsrmainwindow.ui'
**
** Created: Thu Jun 18 20:01:05 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_RSRMAINWINDOW_H
#define UI_RSRMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_RSRMainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTableView *m_tableView;
    QWebView *m_webView;
    QMenuBar *m_menuBar;
    QToolBar *m_mainToolBar;
    QStatusBar *m_statusBar;

    void setupUi(QMainWindow *RSRMainWindow)
    {
        if (RSRMainWindow->objectName().isEmpty())
            RSRMainWindow->setObjectName(QString::fromUtf8("RSRMainWindow"));
        RSRMainWindow->resize(808, 859);
        centralWidget = new QWidget(RSRMainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setMargin(11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_tableView = new QTableView(centralWidget);
        m_tableView->setObjectName(QString::fromUtf8("m_tableView"));

        gridLayout->addWidget(m_tableView, 0, 0, 1, 1);

        m_webView = new QWebView(centralWidget);
        m_webView->setObjectName(QString::fromUtf8("m_webView"));
        m_webView->setUrl(QUrl("about:blank"));

        gridLayout->addWidget(m_webView, 1, 0, 1, 1);

        RSRMainWindow->setCentralWidget(centralWidget);
        m_menuBar = new QMenuBar(RSRMainWindow);
        m_menuBar->setObjectName(QString::fromUtf8("m_menuBar"));
        m_menuBar->setGeometry(QRect(0, 0, 808, 23));
        RSRMainWindow->setMenuBar(m_menuBar);
        m_mainToolBar = new QToolBar(RSRMainWindow);
        m_mainToolBar->setObjectName(QString::fromUtf8("m_mainToolBar"));
        m_mainToolBar->setToolButtonStyle(Qt::ToolButtonTextOnly);
        RSRMainWindow->addToolBar(Qt::TopToolBarArea, m_mainToolBar);
        m_statusBar = new QStatusBar(RSRMainWindow);
        m_statusBar->setObjectName(QString::fromUtf8("m_statusBar"));
        RSRMainWindow->setStatusBar(m_statusBar);

        retranslateUi(RSRMainWindow);

        QMetaObject::connectSlotsByName(RSRMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *RSRMainWindow)
    {
        RSRMainWindow->setWindowTitle(QApplication::translate("RSRMainWindow", "RSRMainWindow", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(RSRMainWindow);
    } // retranslateUi

};

namespace Ui {
    class RSRMainWindow: public Ui_RSRMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RSRMAINWINDOW_H
