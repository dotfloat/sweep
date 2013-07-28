
#include "minesweeper.h"
#include "tiledelegate.h"

#include <QMessageBox>
#include <QVBoxLayout>
#include <QHeaderView>

Minesweeper::Minesweeper(QWidget *parent) :
    QWidget(parent)
{
    sweep = sweepInitGame();
    sweepNewGame(sweep, SG_EASY);

    model = new SweepModel(sweepGetBoard(sweep), this);
    QImage *tileset = new QImage("tiles.jpg");
    if(tileset->isNull())
    {
        QMessageBox::critical(this, tr("Uh oh"), tr("Couldn't open tiles.jpg"));
    }

    view = new QTableView;
    view->setShowGrid(false);
    view->horizontalHeader()->hide();
    view->horizontalHeader()->setMinimumSectionSize(1);
    view->verticalHeader()->hide();
    view->verticalHeader()->setMinimumSectionSize(1);
    view->setModel(model);

    TileDelegate *delegate = new TileDelegate(tileset ,this);
    view->setItemDelegate(delegate);

    QVBoxLayout *vbox = new QVBoxLayout;

    vbox->addWidget(view);
    setLayout(vbox);
    resize(640, 480);

    updateView();
}

void Minesweeper::updateView()
{
    view->resizeColumnsToContents();
    view->resizeRowsToContents();
}
