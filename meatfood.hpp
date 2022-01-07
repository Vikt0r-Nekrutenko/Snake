#ifndef MEATFOOD_HPP
#define MEATFOOD_HPP

#include "food.hpp"

class MeatFood : public Food
{
public:

    MeatFood(const stf::Vec2d& pos);
    MeatFood(const stf::Vec2d& lim1, const stf::Vec2d& lim2);
    ~MeatFood() override = default;
    inline char symbol() const override { return '+'; }
};

#endif // MEATFOOD_HPP
