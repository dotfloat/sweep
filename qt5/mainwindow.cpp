#include <QtGui>
#include <QVBoxLayout>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    game = new Minesweeper(this);

    QWidget *centralWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(game);

    setCentralWidget(centralWidget);
    setWindowTitle(tr("Sweep Qt5"));
    resize(640, 480);
}

MainWindow::~MainWindow()
{
}
