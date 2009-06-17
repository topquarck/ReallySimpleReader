#ifndef RSRMAINWINDOW_H
#define RSRMAINWINDOW_H

#include <QtGui/QMainWindow>

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

private:
    Ui::RSRMainWindow *ui;
};

#endif // RSRMAINWINDOW_H
