#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include "vec2d.hpp"

class Snake
{
public:
    Snake(const stf::Vec2d startPos = { 10, 10 });

private:
    std::vector<stf::Vec2d> m_body;
    stf::Vec2d m_vel = {0,0};

    void moveBody();
};

#endif // SNAKE_HPP
