#include "maptile.h"
#include <QPen>
#include <QBrush>

MapTile::MapTile(const MapTileType& type, const QPoint& mapPos,
                 const qreal& width, const qreal& height) : QGraphicsRectItem(), type(type), mapPos(mapPos)
{
    setRect(mapPos.x() * width, mapPos.y() * height, width, height);
    switch (type) {
    case MapTileType::EMPTY:
        this->setPen(QPen(Qt::black));
        this->setBrush(Qt::white);
        break;
    case MapTileType::WALL:
        this->setPen(QPen(Qt::black));
        this->setBrush(Qt::black);
        break;
    case MapTileType::BODY:
        this->setPen(QPen(Qt::black));
        this->setBrush(Qt::green);
        break;
    case MapTileType::HEAD:
        this->setPen(QPen(Qt::black));
        this->setBrush(Qt::darkGreen);
        break;
    }
}

const QPoint& MapTile::getMapPos()
{
    return mapPos;
}

const MapTileType& MapTile::getType()
{
    return type;
}

void MapTile::setType(const MapTileType &type)
{
    this->type = type;
}

void MapTile::setMapPos(const QPoint &pos)
{
    mapPos = pos;
}
