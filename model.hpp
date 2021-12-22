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
    undefine = '.',
    regular = 'o',
    meat   = '~',
    super   = 'O',
};

class Eat
{
public:
    Eat(const stf::Vec2d& pos = {-1,-1}, EatType type = EatType::undefine)
        : m_pos(pos), m_type(type)
    {
        if(type == EatType::undefine)
            initType();
        else
            initNutrional(type);
    }

    Eat(const stf::Vec2d& lim1, const stf::Vec2d& lim2, EatType type = EatType::undefine)
        : Eat({stf::Random(time(0)).getNum(lim1.x, lim2.x),
               stf::Random(time(0)).getNum(lim1.y, lim2.y)}, type)
    { }

    inline const stf::Vec2d& pos()      const { return m_pos; }
    inline EatType type()               const { return m_type; }
    inline uint8_t nutritionalValue()   const { return m_nutritionalValue; }
    inline bool isHidden()              const { return m_pos == stf::Vec2d(-1,-1); }
    inline void hide()                    { m_pos = {-1,-1}; };

private:

    void initType() {
        m_nutritionalValue = stf::Random(0).getNum(0, 15);
             if(m_nutritionalValue <= 5)    m_type = EatType::regular;
        else if(m_nutritionalValue <= 10)   m_type = EatType::meat;
        else                                m_type = EatType::super;
    }
    void initNutrional(EatType type) {
        switch (type) {
        case EatType::regular: m_nutritionalValue = 5; break;
        case EatType::meat:    m_nutritionalValue = 10; break;
        case EatType::super: m_nutritionalValue = 15; break;
        }
    }

    stf::Vec2d m_pos;
    EatType    m_type;
    uint8_t    m_nutritionalValue;
};

class Eat1
{
public:
    Eat1(const stf::Vec2d& pos = {-1,-1}) : m_pos(pos) { }
    Eat1(const stf::Vec2d& lim1, const stf::Vec2d& lim2)
        : Eat1({stf::Random(time(0)).getNum(lim1.x, lim2.x),
                stf::Random(time(0)).getNum(lim1.y, lim2.y)})
    { }
    virtual char symbol() const = 0;

    inline const stf::Vec2d& pos()      const { return m_pos; }
    inline uint8_t nutritionalValue()   const { return m_nutritionalValue; }
    inline bool isHidden()              const { return m_pos == stf::Vec2d(-1,-1); }
    inline void hide()                  { m_pos = {-1,-1}; };
protected:
    stf::Vec2d m_pos;
    uint8_t    m_nutritionalValue = 0;
};

class RegularEat : public Eat1
{
public:
    RegularEat(const stf::Vec2d& pos = {-1,-1}) : Eat1(pos)
    {
        m_nutritionalValue = stf::Random(0).getNum(1, 5);
    }

    RegularEat(const stf::Vec2d& lim1, const stf::Vec2d& lim2) : Eat1(lim1, lim2)
    {
        m_nutritionalValue = stf::Random(0).getNum(1, 5);
    }

    char symbol() const override { return '~'; }
};

class SuperEat : public Eat1
{
public:
    SuperEat(const stf::Vec2d& pos = {-1,-1}) : Eat1(pos)
    {
        m_nutritionalValue = stf::Random(0).getNum(10, 15);
    }

    SuperEat(const stf::Vec2d& lim1, const stf::Vec2d& lim2) : Eat1(lim1, lim2)
    {
        m_nutritionalValue = stf::Random(0).getNum(10, 15);
    }

    char symbol() const override { return 'O'; }
};

class MeatEat : public Eat1
{
public:
    MeatEat(const stf::Vec2d& pos = {-1,-1}) : Eat1(pos)
    {
        m_nutritionalValue = stf::Random(0).getNum(5, 10);
    }

    MeatEat(const stf::Vec2d& lim1, const stf::Vec2d& lim2) : Eat1(lim1, lim2)
    {
        m_nutritionalValue = stf::Random(0).getNum(5, 10);
    }

    char symbol() const override { return 'o'; }
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


    inline const std::vector<Eat1>& eats()              const { return m_eats;}
    inline const stf::Vec2d& mapSize()                  const { return m_mapSize;}
    inline const std::vector<SnakeModel>& snakeModels() const { return snakeMods; }
private:
    std::vector<SnakeModel> snakeMods;
    std::vector<Eat1> m_eats;

    stf::Vec2d m_mapSize = {0,0};
    bool m_aiIsEnable = false;

    void pasteEat(const SnakeModel& snakeMod);
};

#endif // MODEL_HPP
