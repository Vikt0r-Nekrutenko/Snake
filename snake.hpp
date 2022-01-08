#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "segmentedentity.hpp"

namespace snake_settings {
const stf::Vec2d DEF_START_POS { 10, 10 };
constexpr int DEF_LENGHT = 5;
}

class Snake : public SegmentedEntity
{
public:
    Snake(const stf::Vec2d startPos = snake_settings::DEF_START_POS);

    void update() override;
    void feed() override;
    bool isAteHerself() const;

    void show(stf::Renderer &renderer, const stf::Vec2d &camera) override;

private:
    void moveBody() override;
};

#endif // SNAKE_HPP
