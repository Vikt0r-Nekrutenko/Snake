#ifndef EAT_HPP
#define EAT_HPP

#include <cstdint>
#include "vec2d.hpp"

namespace food_model_settings {
constexpr size_t DEF_ACTIVE_FOOD_COUNT = 10;
}

class Food
{
public:
    Food(const stf::Vec2d& pos, uint8_t nutritionalValue);
    Food(const stf::Vec2d& lim1, const stf::Vec2d& lim2, uint8_t nutritionalValue);
    Food(const Food& food);
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
    RegularFood(const stf::Vec2d& pos);
    RegularFood(const stf::Vec2d& lim1, const stf::Vec2d& lim2);
    ~RegularFood() override = default;
    char symbol() const override { return '~'; }
};

class SuperFood : public Food
{
public:
    SuperFood(const stf::Vec2d& pos);
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

#endif // EAT_HPP
