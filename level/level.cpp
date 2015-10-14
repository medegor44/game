#include "level.h"

#include "maze_generator/generators.h"
#include "game_objects/checkpoint.h"
#include "game_objects/character.h"

Level::Level(int w, int h, GameScene *scene)
{
    pixels = scene->getPixels();
    scene->clear();
    loadTextures();

    Generators::MazeGenerator generator(w, h);
    generator.start(true);
    maze = generator.getMaze();

    Generators::createCoins(maze, scene, scene->getPixels());
}

void Level::paint(QPainter *painter, const QRectF &rect)
{
    for(int y = 0; y < maze->getHeight(); y++)
        for(int x = 0; x < maze->getWidth(); x++) {
            QRectF irect = QRectF(x * pixels, y * pixels, pixels, pixels);
            if(rect.intersects(irect)) {
                painter->drawPixmap(irect.toRect(),
                                    textures[maze->getType(QPoint(x, y))]);
            }
        }
}

void Level::initGameObjects(GameScene *s)
{
    // Добавляем стартовый чекпоинт
    s->addItem(new Checkpoint(maze->getStartPos(), s->getPixels(),
                              Checkpoint::CheckpointType::start,
                              maze, CommonThings::down));

    // Конечный
    s->addItem(new Checkpoint(maze->getEndPos(), s->getPixels(),
                              Checkpoint::CheckpointType::start,
                              maze, CommonThings::up));

    // Объект игрка
    Character *player = new Character(maze->getStartPos(), s->getPixels(), maze);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    s->setFocusItem(player);
    s->addItem(player);

    connect(player, &Character::finished, s, &GameScene::finished);
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

void Level::computeResult(bool finished, int remaining, int coins)
{
    if (!finished) // Игрок не дошел до финиша
        emit result(false);

    // Вычисление результата
    int score = (remaining + coins) * 100;
    emit result(true, score);
}

