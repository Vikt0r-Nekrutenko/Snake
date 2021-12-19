#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include "vec2d.hpp"
#include "renderer.hpp"

class Snake
{
public:
    Snake(const stf::Vec2d startPos = { 10, 10 });

    inline void feed() { m_body.push_back(m_body.back()); }

    inline const stf::Vec2d& head() const { return m_body.front(); }
    inline const std::vector<stf::Vec2d>& body() const { return m_body; }

    void wrapping(const int top, const int left, const int bottom, const int right);
    void show(stf::Renderer &renderer);
    bool isAteHerself() const;
    void update();

    inline void W() { setVel({0,-1}); }
    inline void A() { setVel({-1,0}); }
    inline void S() { setVel({0,+1}); }
    inline void D() { setVel({+1,0}); }
private:
    std::vector<stf::Vec2d> m_body;
    stf::Vec2d m_vel = {0,+1};

    void moveBody();
    inline void setVel(const stf::Vec2d& vel) { if((head()+vel).diff(m_body.at(1)) > 0.5f) m_vel = vel; }
};

#endif // SNAKE_HPP
