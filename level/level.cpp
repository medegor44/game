#include "level.h"

#include "maze_generator/generators.h"
#include "game_objects/checkpoint.h"
#include "game_objects/character.h"

Level::Level(int w, int h)
{
    loadTextures(); // Загрузка текстур

    Generators::MazeGenerator generator(w, h); // Инициализация генератора лабиринта
    generator.start(true); // Генерация уровня
    maze = generator.getMaze();
}

void Level::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    for(int y = 0; y < maze->getHeight(); y++)
        for(int x = 0; x < maze->getWidth(); x++) {
                painter->drawPixmap(QRect(x * pixels, y * pixels, pixels, pixels),
                                    textures[maze->getType(QPoint(x, y))]);
        }
}

QRectF Level::boundingRect() const
{
    return QRectF(0, 0, maze->getWidth() * pixels, maze->getHeight() * pixels);
}

void Level::initGameObjects()
{
    Generators::createCoins(maze, pixels, this); // Генерация монеток на поле

    // Добавляем стартовый чекпоинт
    new Checkpoint(maze->getStartPos(), pixels,Checkpoint::CheckpointType::start,
                                  maze, CommonThings::down, this);

    // Конечный
    new Checkpoint(maze->getEndPos(), pixels, Checkpoint::CheckpointType::end,
                                  maze, CommonThings::up, this);

    // Объект игрка
    Character *player = new Character(maze->getStartPos(), pixels, maze, this);

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    scene()->setFocusItem(player);

    connect(player, &Character::finished, this, &Level::computeResult);
}

void Level::loadTextures()
{
    textures.resize(Graph::maxTypes);

    textures[Terrain_t::wall] = QPixmap(":/textures/bricks.png");
    textures[Terrain_t::field] = QPixmap(":/textures/grass.png");
    textures[Terrain_t::hill] = QPixmap(":/textures/hill.png");
    textures[Terrain_t::sand] = QPixmap(":/textures/sand.png");
    textures[Terrain_t::swamp] = QPixmap(":/textures/swamp.png");
}

void Level::computeResult(bool success, int remaining, int coins)
// Вычисление результата игры
{
    emit stop(); // Сообщить об окончании игры
    if (!success) { // Игрок не дошел до финиша
        emit result(false);
        return;
    }

    // Вычисление результата
    int score = (remaining + coins) * 100;
    emit result(true, score);
}

Level::~Level()
{
    delete maze;
}

