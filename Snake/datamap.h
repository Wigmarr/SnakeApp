#ifndef DATAMAP_H
#define DATAMAP_H
#include "maptiletype.h"
#include <QVector>
#include <QPoint>
#include <QSet>
class DataMap
{
    int size;
    int currentId;
    const unsigned int numberOfSnakes = 2;
    QVector<QVector<MapTileType>> map;
    QVector<QVector<QPoint>> snakes;
    void initializeMap();
    void initializeSnakes();
    QVector<QPoint> createPath(QPoint head, QPoint tail);
    void waveExpansion(QVector<QVector<int>> &algMap,
                       const QPoint &head, const QPoint &tail);
    QVector<QPoint> recreatePath(QVector<QVector<int>> &algMap,
                                 const QPoint &head, const QPoint &tail);
    void clearMap();

public:
    DataMap(int size);
    const QVector<QVector<MapTileType>>& getMap() const;
    const QVector<QVector<QPoint>>& getSnakes() const;
    const int& getId();
    const int& getSize();
};

#endif // DATAMAP_H
