#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include "vec2d.hpp"

class Snake
{
public:
    Snake(const stf::Vec2d startPos = { 10, 10 });

    inline void feed() { m_body.push_back(m_body.back()); }
    inline void setSnakeState(const bool state) { m_isDead = state; }
    inline bool isDead() const { return m_isDead; }
    inline const stf::Vec2d& head() const { return m_body.front(); }
    inline const std::vector<stf::Vec2d>& body() const { return m_body; }
    inline void setVel(const stf::Vec2d& vel) { if((head()+vel).diff(m_body.at(1)) > 0.5f) m_vel = vel; }

    void wrapping(const int top, const int left, const int right, const int bottom);
    bool isAteHerself() const;
    void update();

private:
    std::vector<stf::Vec2d> m_body;
    stf::Vec2d m_vel = {0,+1};
    bool m_isDead = false;

    void moveBody();
};

#endif // SNAKE_HPP
