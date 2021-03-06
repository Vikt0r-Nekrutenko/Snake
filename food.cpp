#include "food.hpp"
#include "random.hpp"
#include <ctime>


Food::Food(const stf::Vec2d &pos, uint8_t nutritionalValue) : m_pos(pos), m_nutritionalValue(nutritionalValue) { }

Food::Food(const stf::Vec2d &lim1, const stf::Vec2d &lim2, uint8_t nutritionalValue)
    : Food({stf::Random(time(0)).getNum(lim1.x, lim2.x),
           stf::Random(time(0)).getNum(lim1.y, lim2.y)}, nutritionalValue)
{ }

Food::Food(const Food &food)
    : m_pos(food.m_pos),
      m_nutritionalValue(food.m_nutritionalValue)
{}
