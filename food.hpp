#ifndef EAT_HPP
#define EAT_HPP

#include "random.hpp"
#include "vec2d.hpp"
#include <ctime>

class Food
{
public:
    Food(const stf::Vec2d& pos = {-1,-1});
    Food(const stf::Vec2d& lim1, const stf::Vec2d& lim2);
    virtual ~Food() = default;

    virtual char symbol() const = 0;
    inline const stf::Vec2d& pos()      const { return m_pos; }
    inline uint8_t nutritionalValue()   const { return m_nutritionalValue; }

protected:

    stf::Vec2d m_pos;
    uint8_t    m_nutritionalValue = 0;
};

class RegularFood : public Food
{
public:
    RegularFood(const stf::Vec2d& pos = {-1,-1});
    RegularFood(const stf::Vec2d& lim1, const stf::Vec2d& lim2);
    ~RegularFood() override = default;
    char symbol() const override { return '~'; }
};

class SuperFood : public Food
{
public:
    SuperFood(const stf::Vec2d& pos = {-1,-1});
    SuperFood(const stf::Vec2d& lim1, const stf::Vec2d& lim2);
    ~SuperFood() override = default;
    inline char symbol() const override { return 'O'; }
};

class MeatFood : public Food
{
public:

    MeatFood(const stf::Vec2d& pos);
    MeatFood(const stf::Vec2d& lim1, const stf::Vec2d& lim2);
    ~MeatFood() override = default;
    inline char symbol() const override { return '+'; }
};

class FoodModel
{
public:
    FoodModel(const stf::Vec2d& mapSize, const size_t activeEats = 10);
    ~FoodModel();
    inline const std::vector<Food *>& foods() const { return m_food; }

    const std::vector<Food *> getPossibleFood() const;

    Food* nearestFood(const stf::Vec2d& pos) const;
    void remove(Food *food);
    void pasteFoodFromDeadSnake(const std::vector<stf::Vec2d>& snakeBody);
private:
    std::vector<Food *> m_food;
    stf::Vec2d m_mapSize;
};

#endif // EAT_HPP
