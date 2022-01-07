#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "segmentedentity.hpp"

class Mouse : public SegmentedEntity
{
public:
    Mouse(const stf::Vec2d startPos)
    {
        for(unsigned int i = 0; i < 3; ++i) {
            m_body.push_back({startPos.x + i, startPos.y});
        }
    }
    void update() override;
    void feed() override;

private:
    void moveBody() override;
};

#endif // MOUSE_HPP
