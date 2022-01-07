#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "segmentedentity.hpp"

class Mouse : public SegmentedEntity
{
public:
    void update() override;

private:
    void moveBody() override;
};

#endif // MOUSE_HPP
