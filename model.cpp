#include "model.hpp"
#include "random.hpp"
#include <ctime>

GameModel::GameModel(const stf::Vec2d &mapSize)
    : m_mapSize(mapSize)
{
    for(int i = 0; i < 2; ++i)
        snakeMods.push_back(SnakeModel(mapSize, {i*10, 0}));

    m_eats.resize(mapSize.x * mapSize.y);
    int i = 0;
    while(i++ < 10)
        m_eats[i] = RegularEat({2,2}, mapSize-2);
}

Signal GameModel::onUpdate(const float dt)
{
    for(size_t s = 0; s < snakeModels().size() - 1; ++s) {
        for (size_t s1 = s+1; s1 < snakeModels().size(); ++s1) {
            SnakeModel* deadSnake = snakeMods.at(s).collisionWithSnakeHandler(&snakeMods.at(s1));
            if(deadSnake != nullptr)
                kill(deadSnake);
        }
    }
    for(auto &snakeMod : snakeMods) {
        if(snakeMod.isAteHerself()) kill(&snakeMod);
        if(snakeMod.aiIsEnable()) {
//            Eat *target = &m_eats.front();
            std::vector<const stf::Vec2d *> possibleEat;
            for(auto &e : m_eats)
                if(!e.isHidden()) possibleEat.push_back(&e.pos());

            snakeMod.targ = *possibleEat.front();
            for(auto eat : possibleEat) {
                if(snakeMod.snake().head().diff(*eat) < snakeMod.snake().head().diff(snakeMod.targ))
                    snakeMod.targ = *eat;
            }
            snakeMod.aiControl(snakeMod.targ);
        }
        for(auto &eat : m_eats)
            if(snakeMod.isCollideWithEat(eat.pos())) {
                snakeMod.collisionWithEatHandler(eat.nutritionalValue());
//                switch (eat.type()) {
//                case EatType::super:
//                case EatType::regular:  eat = Eat({2,2}, m_mapSize-2);  break;
//                case EatType::meat:     eat.hide();                     break;
//                }
            }
        snakeMod.onUpdate(dt);
    }
    return Signal::none;
}

Signal GameModel::keyEvents(const int key)
{
    for(auto &snakeMod : snakeMods)
        snakeMod.keyEvents(key);
    if(key == ' ') return Signal::pause;
    return Signal::none;
}

void GameModel::aiControl()
{

}

void GameModel::reset()
{
    for(auto &snakeMod : snakeMods)
        snakeMod.reset();
//    m_eat = stf::Vec2d(stf::Random(time(0)).getNum(2, m_mapSize.x-1),
    //                       stf::Random(time(0)).getNum(2, m_mapSize.y-1));
}

void GameModel::kill(SnakeModel* snakeMod)
{
    snakeMod->killSnake();
    pasteEat(*snakeMod);
    snakeMod->reset();
}

void GameModel::pasteEat(const SnakeModel &snakeMod)
{
    for(auto &segment : snakeMod.snake().body()) {
        for(auto &emptyCell : m_eats) {
            if(emptyCell.isHidden()) {
                emptyCell = MeatEat(segment);
                break;
            }
        }
    }
}
