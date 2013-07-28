#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "minesweeper.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Minesweeper *game;
};

#endif // MAINWINDOW_H
