#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include "vec2d.hpp"

class Snake
{
public:
    Snake();

private:
    std::vector<stf::Vec2d> m_body;
    stf::Vec2d m_vel = {0,0};
};

#endif // SNAKE_HPP
