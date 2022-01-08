#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "segmentedentity.hpp"

class Mouse : public SegmentedEntity
{
public:
    Mouse(const stf::Vec2d startPos);
    void update() override;
    void feed() override;
    void show(stf::Renderer &renderer, const stf::Vec2d &camera) override;

private:
    void moveBody() override;
};

#endif // MOUSE_HPP
