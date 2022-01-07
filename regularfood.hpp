#ifndef REGULARFOOD_H
#define REGULARFOOD_H

#include "food.hpp"

class RegularFood : public Food
{
public:
    RegularFood(const stf::Vec2d& pos);
    RegularFood(const stf::Vec2d& lim1, const stf::Vec2d& lim2);
    ~RegularFood() override = default;
    char symbol() const override { return '~'; }
};

#endif // REGULARFOOD_H
