#include "superfood.hpp"
#include "random.hpp"

SuperFood::SuperFood(const stf::Vec2d &pos)
    : Food(pos, stf::Random(0).getNum(10, 15))
{}

SuperFood::SuperFood(const stf::Vec2d &lim1, const stf::Vec2d &lim2)
    : Food(lim1, lim2, stf::Random(0).getNum(10, 15))
{}
