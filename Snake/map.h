#ifndef MAP_H
#define MAP_H
#include "maptile.h"
#include "datamap.h"
#include "direction.h"
#include <QWidget>
#include "snaketile.h"
class Snake;
class Map : public QObject
{
    Q_OBJECT
    class Snake {
        QVector<SnakeTile*> snake;
        int snakeId;
        // вектор позиций в которых змея попадает в тупик
        QList<QPoint> badPositions;
    public:
        Snake(const QVector<QPoint> &snakeVector, const Map *map);
        const QVector<SnakeTile*>& getSnake() const;
        void move(const QPoint& newHeadPos);
        void backwardMove(const QPoint& newTailPos);
        int generateSnakeId();
        bool isSnake(const QPoint&);
        QList<QPoint>& getBadPositions();
    };
    QVector<QVector<MapTile*>> map;
    QVector<Snake*> snakes;
    qreal tileWidth;
    qreal tileHeight;
    void initializeMap(const QVector<QVector<MapTileType>> &dataMap);
    void initializeSnakes(const QVector<QVector<QPoint>> &snakesVector);

public:
    explicit Map(const DataMap* dataMap, qreal width, qreal height,QObject* parent = 0);
    const QVector<QVector<MapTile*>>& getMap() const;
    const QVector<Snake*>& getSnakes() const;
    const qreal& getTileWidth() const;
    const qreal& getTileHeight() const;

signals:
    void finish();
public slots:
    void moveSnakes();

};

#endif // MAP_H
