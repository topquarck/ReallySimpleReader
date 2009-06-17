#include "rsrmainwindow.h"
#include "ui_rsrmainwindow.h"

RSRMainWindow::RSRMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::RSRMainWindow)
{
    ui->setupUi(this);
}

RSRMainWindow::~RSRMainWindow()
{
    delete ui;
}
