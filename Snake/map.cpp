#include "map.h"

Map::Map(const DataMap *dataMap, qreal width, qreal height,QObject * parent) :
    QObject(parent), tileWidth(width), tileHeight(height)
{
    initializeMap(dataMap->getMap());
    initializeSnakes(dataMap->getSnakes());
}

void Map::initializeMap(const QVector<QVector<MapTileType>> &dataMap)
{
    map.resize(dataMap.size());
    for (auto i = 0; i < map.size(); ++i) {
        map[i].resize(dataMap.size());
        for (auto j = 0; j < map.size(); ++j) {
            map[i][j] = new MapTile(dataMap[i][j], QPoint(j, i), tileWidth, tileHeight);
        }
    }
}

void Map::initializeSnakes(const QVector<QVector<QPoint> > &snakesVector)
{
    snakes.reserve(snakesVector.size());
    for (const auto &snake : snakesVector) {
        snakes.push_back(new Snake(snake, this));
    }
}

const QVector<QVector<MapTile*>>& Map::getMap() const
{
    return map;
}

const QVector<Map::Snake*>& Map::getSnakes() const
{
    return snakes;
}

const qreal& Map::getTileWidth() const
{
    return tileWidth;
}

const qreal& Map::getTileHeight() const
{
    return tileHeight;
}

Map::Snake::Snake(const QVector<QPoint> &snakeVector, const Map *map)
{
    static int id = 0;
    snakeId = ++id;
    snake.reserve(snakeVector.size());
    snake.push_back(new SnakeTile(MapTileType::HEAD, QPoint(snakeVector[0].x(),snakeVector[0].y()),
                    map->tileWidth, map->tileHeight, snakeId));
    for(auto i = 1; i < snakeVector.size(); i++) {
        snake.push_back(new SnakeTile(MapTileType::BODY, QPoint(snakeVector[i].x(),snakeVector[i].y()),
                        map->tileWidth, map->tileHeight, snakeId));
    }
}

QList<QPoint>& Map::Snake::getBadPositions()
{
    return badPositions;
}

void Map::moveSnakes()
{

    for (auto &snake : snakes) {
        QPoint headPos = snake->getSnake().first()->getMapPos();
        QList<QPoint> headPossiblePos;

        headPossiblePos.push_back(QPoint(headPos.x()+1, headPos.y()));
        headPossiblePos.push_back(QPoint(headPos.x()-1, headPos.y()));
        headPossiblePos.push_back(QPoint(headPos.x(), headPos.y()+1));
        headPossiblePos.push_back(QPoint(headPos.x(), headPos.y()-1));
        for (auto j = 0; j < headPossiblePos.size(); ++j) {
            if ((headPossiblePos[j].y() < 0) || (headPossiblePos[j].y() > map.size() - 1)
             || (headPossiblePos[j].x() < 0) || (headPossiblePos[j].x() > map.size() - 1)) {
                headPossiblePos.removeAt(j--);
                continue;
            }
            if (map[headPossiblePos[j].y()][headPossiblePos[j].x()]->getType() == MapTileType::WALL) {
                headPossiblePos.removeAt(j--);
                continue;
            }
            if (snake->isSnake(headPossiblePos[j])) {
                headPossiblePos.removeAt(j--);
                continue;
            }
            if (!snake->getBadPositions().empty() && (snake->getBadPositions().contains(headPossiblePos[j]))) {
                headPossiblePos.removeAt(j--);
                continue;
            }
        }
        if (headPossiblePos.size() != 0) {
            auto index = rand() % headPossiblePos.size();
            for (auto &checkSnake : snakes) {
                if (checkSnake == snake)
                    continue;
                if (checkSnake->isSnake(headPossiblePos[index])) {
                    snake->move(headPossiblePos[index]);
                    emit finish();
                    return;
                }
            }
            snake->move(headPossiblePos[index]);
            continue;
        }
        snake->getBadPositions().push_back(snake->getSnake()[0]->getMapPos());
        //Если нет доступных путей для головы, змея двигается назад
        QPoint tailPos = snake->getSnake().last()->getMapPos();
        QList<QPoint> tailPossiblePos;
        tailPossiblePos.push_back(QPoint(tailPos.x()+1, tailPos.y()));
        tailPossiblePos.push_back(QPoint(tailPos.x()-1, tailPos.y()));
        tailPossiblePos.push_back(QPoint(tailPos.x(), tailPos.y()+1));
        tailPossiblePos.push_back(QPoint(tailPos.x(), tailPos.y()-1));
        for (auto j = 0; j < tailPossiblePos.size(); ++j) {
            if ((tailPossiblePos[j].y() < 0) || (tailPossiblePos[j].y() > map.size() - 1)
             || (tailPossiblePos[j].x() < 0) || (tailPossiblePos[j].x() > map.size() - 1)) {
                tailPossiblePos.removeAt(j--);
                continue;
            }
            if (map[tailPossiblePos[j].y()][tailPossiblePos[j].x()]->getType() == MapTileType::WALL) {
                tailPossiblePos.removeAt(j--);
                continue;
            }
            if (snake->isSnake(tailPossiblePos[j])) {
                tailPossiblePos.removeAt(j--);
                continue;
            }

        }
        if (tailPossiblePos.size() != 0) {
            auto index = rand() % tailPossiblePos.size();
            for (auto &checkSnake : snakes) {
                if (checkSnake == snake)
                    continue;
                if (checkSnake->isSnake(tailPossiblePos[index])) {
                    snake->backwardMove(tailPossiblePos[index]);
                    emit finish();
                    return;
                }
            }
            snake->backwardMove(tailPossiblePos[index]);
            continue;
        }
        snake->getBadPositions().clear();
    }
}

void Map::Snake::move(const QPoint &newHeadPos)
{
    qreal width = snake[0]->rect().width();
    qreal height = snake[0]->rect().height();
    QPoint oldPos = newHeadPos;
    QPoint tempPos = snake[0]->getMapPos();
    for (auto i = 0; i < snake.size(); ++i) {
        tempPos = snake[i]->getMapPos();
        snake[i]->setRect(oldPos.x() * width, oldPos.y() * height,
                          width, height);
        snake[i]->setMapPos(oldPos);
        oldPos = tempPos;
    }
}

void Map::Snake::backwardMove(const QPoint &newTailPos)
{
    qreal width = snake[0]->rect().width();
    qreal height = snake[0]->rect().height();
    QPoint oldPos = newTailPos;
    QPoint tempPos = snake.last()->getMapPos();
    for (auto i = snake.size() - 1; i > -1; --i) {
        tempPos = snake[i]->getMapPos();
        snake[i]->setRect(oldPos.x() * width, oldPos.y() * height,
                          width, height);
        snake[i]->setMapPos(oldPos);
        oldPos = tempPos;
    }
}

bool Map::Snake::isSnake(const QPoint & point)
{
    for (auto &tile : snake){
        if ((tile->getMapPos().x() == point.x())
         && (tile->getMapPos().y() == point.y())) {
            return true;
        }
    }
    return false;
}

const QVector<SnakeTile*>& Map::Snake::getSnake() const
{
    return snake;
}
