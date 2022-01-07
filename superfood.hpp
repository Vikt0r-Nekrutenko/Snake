#ifndef SUPERFOOD_HPP
#define SUPERFOOD_HPP

#include "food.hpp"

class SuperFood : public Food
{
public:
    SuperFood(const stf::Vec2d& pos);
    SuperFood(const stf::Vec2d& lim1, const stf::Vec2d& lim2);
    ~SuperFood() override = default;
    inline char symbol() const override { return 'O'; }
};

#endif // SUPERFOOD_HPP
