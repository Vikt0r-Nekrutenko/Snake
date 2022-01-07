#include "regularfood.hpp"
#include "random.hpp"

RegularFood::RegularFood(const stf::Vec2d &pos)
    : Food(pos, stf::Random(0).getNum(1, 5))
{}

RegularFood::RegularFood(const stf::Vec2d &lim1, const stf::Vec2d &lim2)
    : Food(lim1, lim2, stf::Random(0).getNum(1, 5))
{}
