#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "segmentedentity.hpp"

class Snake : public SegmentedEntity
{
public:
    Snake(const stf::Vec2d startPos = { 10, 10 });

    void update() override;
    void feed() override;
    bool isAteHerself() const;

private:
    void moveBody() override;
};

#endif // SNAKE_HPP
