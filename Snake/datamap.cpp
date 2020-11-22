#include "datamap.h"
#include "nopathexception.h"
#include <cstdlib>
#include <ctime>
#include <QDebug>
#include <QQueue>
#include <QStack>
#include <QPair>
#include <random>
#include <QRandomGenerator>

DataMap::DataMap(int size)
{
    srand(time(nullptr));
    static int id = 0;
    currentId = id;
    ++id;
    this->size = size;
    // выделения памяти под карту
    map.resize(size);
    for (auto i = 0; i < this->size; i++) {
        map[i].resize(size);
    }

    snakes.resize(numberOfSnakes);
    initializeMap();
    initializeSnakes();

    clearMap();

}

void DataMap::initializeMap()
{
    for (int i = 0; i < this->size; ++i) {
        for (int j = 0;j < this->size; ++j) {
            int x = QRandomGenerator::global()->generate() % 4;
            if (x == 0) {
                map[i][j] = MapTileType::WALL;
            } else {
                map[i][j] = MapTileType::EMPTY;
            }
        }
    }
}

void DataMap::initializeSnakes()
{
    for (auto& snake : snakes) {
        while (snake.size() == 0) {
            QPoint head(QRandomGenerator::global()->generate() % size, QRandomGenerator::global()->generate() % size);
            QPoint tail(QRandomGenerator::global()->generate() % size, QRandomGenerator::global()->generate() % size);
            while (map[head.y()][head.x()] != MapTileType::EMPTY) {
                head.setX(QRandomGenerator::global()->generate() % size);
                head.setY(QRandomGenerator::global()->generate() % size);
            }
            while (map[tail.y()][tail.x()] != MapTileType::EMPTY) {
                tail.setX(QRandomGenerator::global()->generate() % size);
                tail.setY(QRandomGenerator::global()->generate() % size);
            }
            try {
                snake = createPath(head,tail);
            } catch (NoPathException &ex) {
                qDebug()<<ex.what();
                continue;
            }
        }
    }
}
// Используется волновой алгоритм
QVector<QPoint> DataMap::createPath(QPoint head, QPoint tail)
{
    // структура для хранения расстояния до искомого тайла
    QVector<QVector<int>> algMap(size);

    // инициализация алгоритма

    for (auto& raw : algMap) {
        raw.resize(size);
        raw.fill(-2);
    }
    try {
        waveExpansion(algMap, head, tail);
    } catch (NoPathException &ex) {
        throw ex;
    }
    // восстановление пути
    return recreatePath(algMap,head,tail);
}

// распространение волны
void DataMap::waveExpansion(QVector<QVector<int>> &algMap,
                            const QPoint &head, const QPoint &tail)
{
    QQueue<QPair<QPoint,int>> bypassOrder;
    int length = 0;
    bypassOrder.enqueue(QPair<QPoint,int>(tail,length));

    while (!bypassOrder.empty()) {
        QPair<QPoint,int> pair = bypassOrder.dequeue();
        QPoint currentPoint = pair.first;
        int currentlength = pair.second;
        if (currentPoint == head) {
            algMap[currentPoint.y()][currentPoint.x()] = currentlength;
            return;
        }
        if ((currentPoint.y() < 0) || (currentPoint.y() > size - 1)
         || (currentPoint.x() < 0) || (currentPoint.x() > size - 1)) {
            continue;
        }
        if (algMap[currentPoint.y()][currentPoint.x()] != -2)
            continue;
        if (map[currentPoint.y()][currentPoint.x()] == MapTileType::WALL
         || map[currentPoint.y()][currentPoint.x()] == MapTileType::BODY) {
            continue;
        }
        algMap[currentPoint.y()][currentPoint.x()] = currentlength;
        bypassOrder.enqueue(QPair<QPoint, int>(QPoint(currentPoint.x()+1,currentPoint.y()),currentlength+1));
        bypassOrder.enqueue(QPair<QPoint, int>(QPoint(currentPoint.x()-1,currentPoint.y()),currentlength+1));
        bypassOrder.enqueue(QPair<QPoint, int>(QPoint(currentPoint.x(),currentPoint.y()+1),currentlength+1));
        bypassOrder.enqueue(QPair<QPoint, int>(QPoint(currentPoint.x(),currentPoint.y()-1),currentlength+1));
    }
    throw NoPathException("Impossible to find a path between ("
                          + QString(head.y()) + "," + QString(head.x())
                          + ") and (" + QString(tail.y()) + "," + QString(tail.x()) + ")");
}

QVector<QPoint> DataMap::recreatePath(QVector<QVector<int> > &algMap,
                                      const QPoint &head, const QPoint &tail)
{
    int length = algMap[head.y()][head.x()];
    QVector<QPoint> path;
    path.reserve(length+1);
    QStack<QPoint> neighbours;
    QPoint currentPoint = head;
    map[currentPoint.y()][currentPoint.x()] = MapTileType::BODY;
    path.push_back(currentPoint);
    neighbours.push(QPoint(currentPoint.x()+1,currentPoint.y()));
    neighbours.push(QPoint(currentPoint.x(),currentPoint.y()+1));
    neighbours.push(QPoint(currentPoint.x()-1,currentPoint.y()));
    neighbours.push(QPoint(currentPoint.x(),currentPoint.y()-1));
    while (currentPoint != tail) {
        currentPoint = neighbours.pop();
        if ((currentPoint.y() < 0) || (currentPoint.y() > size - 1)
         || (currentPoint.x() < 0) || (currentPoint.x() > size - 1)) {
            continue;
        }
        if (algMap[currentPoint.y()][currentPoint.x()] == length - 1) {
            --length;
            neighbours.push(QPoint(currentPoint.x()+1,currentPoint.y()));
            neighbours.push(QPoint(currentPoint.x(),currentPoint.y()+1));
            neighbours.push(QPoint(currentPoint.x()-1,currentPoint.y()));
            neighbours.push(QPoint(currentPoint.x(),currentPoint.y()-1));
            path.push_back(currentPoint);
            map[currentPoint.y()][currentPoint.x()] = MapTileType::BODY;
        }
    }
    return path;
}

void DataMap::clearMap() {
    for(auto &row : map) {
        for (auto &tile : row) {
            if (tile == MapTileType::BODY)
                tile = MapTileType::EMPTY;
        }
    }
}

const QVector<QVector<MapTileType>>& DataMap::getMap() const
{
    return map;
}

const QVector<QVector<QPoint>>& DataMap::getSnakes() const
{
    return snakes;
}

const int& DataMap::getSize()
{
    return size;
}

const int& DataMap::getId()
{
    return currentId;
}
