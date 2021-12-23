#ifndef MODEL_HPP
#define MODEL_HPP

#include <cstdint>
#include <ctime>

#include "snake.hpp"
#include "snakemodel.hpp"
#include "foodmodel.hpp"

enum class Signal : uint8_t
{
    none, start, pause, end,
};

class GameModel
{
public:
    GameModel(const stf::Vec2d& mapSize);

    Signal onUpdate(const float dt);
    Signal keyEvents(const int key);
    void reset();
    void kill(SnakeModel *snakeMod);


    inline const FoodModel& foodModel()                  const { return m_foodModel;}
    inline const stf::Vec2d& mapSize()                  const { return m_mapSize;}
    inline const std::vector<SnakeModel>& snakeModels() const { return snakeMods; }
private:
    std::vector<SnakeModel> snakeMods;
    FoodModel m_foodModel;

    stf::Vec2d m_mapSize = {0,0};
    bool m_aiIsEnable = false;
};

#endif // MODEL_HPP
