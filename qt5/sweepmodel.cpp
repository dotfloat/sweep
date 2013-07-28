#include <QtGui>

#include "sweepmodel.h"

#include <cstdio>

SweepModel::SweepModel(sweep_board_t b, QObject *parent) :
    QAbstractTableModel(parent),
    board(b)
{
    sweepBoardReveal(board, 0, 0);

    FILE *out = fopen("output.txt", "wb");
    sweepDebugDumpBoard(board, out);
    fclose(out);
}

int SweepModel::rowCount(const QModelIndex &parent) const
{
    return sweepBoardHeight(board);
}

int SweepModel::columnCount(const QModelIndex &parent) const
{
    return sweepBoardWidth(board);
}

QVariant SweepModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    return sweepBoardCellVisible(board, index.row(), index.column());
}

QVariant SweepModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::SizeHintRole)
        return QSize(1, 1);
    return QVariant();
}
