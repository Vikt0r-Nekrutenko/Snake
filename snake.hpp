#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include "vec2d.hpp"

class Snake
{
public:
    Snake(const stf::Vec2d startPos = { 10, 10 });

    inline void feed() { m_body.push_back(m_body.back()); }

    inline const stf::Vec2d& head() const { return m_body.front(); }
    inline const std::vector<stf::Vec2d>& body() const { return m_body; }

private:
    std::vector<stf::Vec2d> m_body;
    stf::Vec2d m_vel = {0,0};

    void moveBody();
};

#endif // SNAKE_HPP
