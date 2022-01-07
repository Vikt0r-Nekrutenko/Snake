#include "meatfood.hpp"
#include "random.hpp"

MeatFood::MeatFood(const stf::Vec2d &pos)
    : Food(pos, stf::Random(0).getNum(5, 10))
{}

MeatFood::MeatFood(const stf::Vec2d &lim1, const stf::Vec2d &lim2)
    : Food(lim1, lim2, stf::Random(0).getNum(5, 10))
{}

