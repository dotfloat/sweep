#ifndef TILEDELEGATE_H
#define TILEDELEGATE_H

#include <QAbstractItemDelegate>
#include <QSize>

class TileDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    explicit TileDelegate(const QImage *t, QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index ) const;

signals:
    
public slots:

private:
    const QImage *tileset;
};

#endif // TILEDELEGATE_H
