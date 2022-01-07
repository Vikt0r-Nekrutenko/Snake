#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "segmentedentity.hpp"

namespace snake_settings {
const stf::Vec2d DEF_START_POS { 10, 10 };
constexpr unsigned int DEF_LENGHT = 5;
}

class Snake : public SegmentedEntity
{
public:
    Snake(const stf::Vec2d startPos = snake_settings::DEF_START_POS);

    void update() override;
    void feed() override;
    bool isAteHerself() const;

private:
    void moveBody() override;
};

#endif // SNAKE_HPP
