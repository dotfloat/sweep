#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <sweep.h>
#include <QWidget>
#include <QTableView>

#include "sweepmodel.h"

class Minesweeper : public QWidget
{
    Q_OBJECT

public:
    explicit Minesweeper(QWidget *parent = 0);
    
signals:
    
public slots:
    void updateView();

private:
    QTableView *view;
    SweepModel *model;
    sweep_t sweep;
};

#endif // MINESWEEPER_H
