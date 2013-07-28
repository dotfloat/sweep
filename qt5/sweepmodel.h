#ifndef SWEEPMODEL_H
#define SWEEPMODEL_H

#include <QAbstractTableModel>

#include <sweep.h>

class SweepModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit SweepModel(sweep_board_t board, QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
signals:
    
public slots:

private:
    sweep_board_t board;
};

#endif // SWEEPMODEL_H
