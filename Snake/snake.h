#ifndef SNAKE_H
#define SNAKE_H
#include <QList>
#include "snaketile.h"
#include "direction.h"
#include "map.h"
class Snake {
    QList<SnakeTile*> snake;
    int snakeId;
public:
    Snake(const QVector<QPoint> &snakeVector, const Map *map);
    const QList<SnakeTile*>& getSnake() const;
    void Move(Direction dir);
    void BackwardMove(Direction dir);
    int generateSnakeId();
};

#endif // SNAKE_H
