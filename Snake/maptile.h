#ifndef MAPTILE_H
#define MAPTILE_H

#include "maptiletype.h"
#include <QObject>
#include <QGraphicsRectItem>

class MapTile : public QGraphicsRectItem
{
    MapTileType type;
    QPoint mapPos;

public:
    explicit MapTile(const MapTileType& type, const QPoint& pos,
                     const qreal& width, const qreal& height);
    const QPoint& getMapPos();
    const MapTileType& getType();
    void setType(const MapTileType &type);
    void setMapPos(const QPoint & newPos);
};

#endif // MAPTILE_H
