#ifndef SNAKETILE_H
#define SNAKETILE_H
#include "maptile.h"

class SnakeTile : public MapTile
{
    int snakeId;
public:
    SnakeTile(const MapTileType& type, const QPoint& mapPos,  const qreal& width,
              const qreal& height,const int &snakeId);
    void redraw();
};

#endif // SNAKETILE_H
