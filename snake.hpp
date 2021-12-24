#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include "vec2d.hpp"

class Snake
{
public:
    Snake(const stf::Vec2d startPos = { 10, 10 });

    inline void feed()                                 { m_body.push_back(m_body.back()); }
    inline void setVel(const stf::Vec2d& vel)          { if((head()+vel).diff(m_body.at(1)) > 0.5f) m_vel = vel; }

    inline const std::vector<stf::Vec2d>& body() const { return m_body; }
    inline const stf::Vec2d& head()              const { return m_body.front(); }
    inline size_t length()                       const { return m_body.size(); }
    bool isAteHerself()                          const;
    bool isHeadOverlapped(const stf::Vec2d& pos) const;
    bool isSegmetOverlapped(size_t nOfSeg, const stf::Vec2d& pos) const;

    void wrapping(const int top, const int left, const int right, const int bottom);
    void update();

private:
    std::vector<stf::Vec2d> m_body;
    stf::Vec2d              m_vel = {0,+1};

    void moveBody();
};

#endif // SNAKE_HPP
