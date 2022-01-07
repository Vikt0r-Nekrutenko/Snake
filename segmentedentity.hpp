#ifndef SEGMENTEDENTITY_HPP
#define SEGMENTEDENTITY_HPP

#include "vec2d.hpp"
#include <vector>

class SegmentedEntity
{
public:
    virtual ~SegmentedEntity() = default;
    virtual void update() = 0;
    virtual void feed() = 0;
    inline void setVel(const stf::Vec2d& vel)          { if((head()+vel).diff(m_body.at(1)) > 0.5f) m_vel = vel; }

    inline const std::vector<stf::Vec2d>& body() const { return m_body; }
    inline size_t length()                       const { return m_body.size();  }
    inline const stf::Vec2d& head()              const { return m_body.front(); }
    bool isHeadOverlapped(const stf::Vec2d& pos) const;
    bool isSegmetOverlapped(size_t nOfSeg, const stf::Vec2d& pos) const;
    void wrapping(const int top, const int left, const int right, const int bottom);
protected:
    std::vector<stf::Vec2d> m_body;
    stf::Vec2d              m_vel = {0,+1};

    virtual void moveBody() = 0;
};

#endif // SEGMENTEDENTITY_HPP
