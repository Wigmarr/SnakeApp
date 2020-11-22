#include "snaketile.h"
#include <QPen>
#include <QBrush>
SnakeTile::SnakeTile(const MapTileType& type, const QPoint& mapPos,  const qreal& width,
                     const qreal& height,const int &snakeId) : MapTile(type, mapPos, width, height), snakeId(snakeId)
{
    if (type == MapTileType::HEAD) {
        switch (snakeId % 3) {
        case 0:
            this->setBrush(Qt::darkGreen);
            break;
        case 1:
            this->setBrush(Qt::darkRed);
            break;
        case 2:
            this->setBrush(Qt::darkYellow);
            break;
        }
    } else {
        switch (snakeId % 3) {
        case 0:
            this->setBrush(Qt::green);
            break;
        case 1:
            this->setBrush(Qt::red);
            break;
        case 2:
            this->setBrush(Qt::yellow);
            break;
        }
    }
}
void SnakeTile::redraw()
{
    if (getType() == MapTileType::HEAD) {
        switch (snakeId % 3) {
        case 0:
            this->setBrush(Qt::darkGreen);
            break;
        case 1:
            this->setBrush(Qt::darkRed);
            break;
        case 2:
            this->setBrush(Qt::darkYellow);
            break;
        }
    } else {
        switch (snakeId % 3) {
        case 0:
            this->setBrush(Qt::green);
            break;
        case 1:
            this->setBrush(Qt::red);
            break;
        case 2:
            this->setBrush(Qt::yellow);
            break;
        }
    }
}
