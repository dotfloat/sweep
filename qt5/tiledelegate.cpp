#include <QtGui>

#include <sweep.h>
#include "tiledelegate.h"

TileDelegate::TileDelegate(const QImage *t, QObject *parent) :
    QAbstractItemDelegate(parent),
    tileset(t)
{
}

void TileDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
           const QModelIndex &index) const
{
    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());

    int size = qMin(option.rect.width(), option.rect.height());
    sweep_linear_t cell = (sweep_linear_t) index.model()->data(index, Qt::DisplayRole).toInt();

    int tileX, tileY;
    switch(cell)
    {
        case SWEEP_EMPTY:
            tileX = 3;
            tileY = 0;
            break;
        case SWEEP_1:
        case SWEEP_2:
        case SWEEP_3:
        case SWEEP_4:
        case SWEEP_5:
        case SWEEP_6:
        case SWEEP_7:
        case SWEEP_8:
            tileX = (cell-SWEEP_1)%4;
            tileY = (cell-SWEEP_1)/4+1;
            break;
        case SWEEP_L_FLAG_TRUE:
        case SWEEP_L_FLAG_FALSE:
        case SWEEP_L_FLAG_NONE:
        case SWEEP_L_EXPLODE:
        case SWEEP_BOMB:
            tileX = 2;
            tileY = 0;
            break;
        case SWEEP_L_FLAG:
            tileX = 1;
            tileY = 0;
            break;
        case SWEEP_L_CLOSED:
        default:
            tileX = 0;
            tileY = 0;
            break;
    }

    painter->save();
    painter->drawImage(index.column()*size, index.row()*size, *tileset, tileX*size, tileY*size, size, size);
    painter->restore();
}

QSize TileDelegate::sizeHint(const QStyleOptionViewItem &option,
               const QModelIndex &index ) const
{
    return QSize(16, 16);
}
