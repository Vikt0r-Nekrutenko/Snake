#ifndef MODEL_HPP
#define MODEL_HPP

#include "snake.hpp"
#include <cstdint>
#include "snakemodel.hpp"

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
    void aiControl();
    void reset();
    void kill(SnakeModel *snakeMod);


    inline const std::vector<stf::Vec2d>& eats() const { return m_eats;}
    inline const std::vector<stf::Vec2d>& eats1() const { return m_eats1;}
    inline const stf::Vec2d& mapSize() const { return m_mapSize;}
    inline const std::vector<SnakeModel>& snakeModels() const { return snakeMods; }
private:
    std::vector<SnakeModel> snakeMods;
    std::vector<stf::Vec2d> m_eats;
    std::vector<stf::Vec2d> m_eats1;

    stf::Vec2d m_mapSize = {0,0};
    bool m_aiIsEnable = false;

    void pasteEat(const SnakeModel& snakeMod);
};

#endif // MODEL_HPP
