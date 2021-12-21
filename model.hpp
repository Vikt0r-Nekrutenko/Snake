#ifndef MODEL_HPP
#define MODEL_HPP

#include <cstdint>
#include <ctime>

#include "snake.hpp"
#include "snakemodel.hpp"

enum class Signal : uint8_t
{
    none, start, pause, end,
};

enum class EatType : char
{
    regular = 'o',
    snake   = '~',
    super   = 'O',
};

class Eat
{
public:
    Eat(const stf::Vec2d& pos = {-1,-1}, EatType type = EatType::regular)
        : m_pos(pos), m_type(type)
    {   }

    Eat(const stf::Vec2d& lim1, const stf::Vec2d& lim2, EatType type = EatType::regular)
        : m_pos(stf::Random(time(0)).getNum(lim1.x, lim2.x),
                stf::Random(time(0)).getNum(lim1.y, lim2.y)),
          m_type(type)
    {   }

    inline const stf::Vec2d& pos()  const { return m_pos; }
    inline EatType type()           const { return m_type; }
    inline bool isHidden()          const { return m_pos == stf::Vec2d(-1,-1); }
    inline void hide()                    { m_pos = {-1,-1}; };

private:

    stf::Vec2d m_pos;
    EatType    m_type;
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


    inline const std::vector<Eat>& eats()               const { return m_eats;}
    inline const stf::Vec2d& mapSize()                  const { return m_mapSize;}
    inline const std::vector<SnakeModel>& snakeModels() const { return snakeMods; }
private:
    std::vector<SnakeModel> snakeMods;
    std::vector<Eat> m_eats;

    stf::Vec2d m_mapSize = {0,0};
    bool m_aiIsEnable = false;

    void pasteEat(const SnakeModel& snakeMod);
};

#endif // MODEL_HPP
