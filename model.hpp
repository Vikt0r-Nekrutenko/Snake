#ifndef MODEL_HPP
#define MODEL_HPP

#include <cstdint>
#include <ctime>

#include "smv/imodel.hpp"
#include "snake.hpp"
#include "huntermodel.hpp"
#include "foodmodel.hpp"

enum class Signal : uint8_t
{
    none, start, normal, survival, pause, end,
};

namespace game_model_settings {
constexpr uint8_t NORMAL_SNAKES_COUNT = 0;
constexpr uint8_t NORMAL_MOUSE_COUNT = 5;

constexpr uint8_t SURVIVAL_SNAKES_MIN_COUNT = 3;
constexpr uint8_t SURVIVAL_SNAKES_MAX_COUNT = 7;

constexpr uint8_t SURVIVAL_MOUSES_MIN_COUNT = 5;
constexpr uint8_t SURVIVAL_MOUSES_MAX_COUNT = 10;
}

class GameModel : public stf::smv::BaseModel
{
public:
    GameModel(const stf::Vec2d& mapSize, uint8_t snakes = 0u, uint8_t mouses = 5u);
    ~GameModel() override;

    Signal onUpdate(const float dt);
    Signal keyEvents(const int key);

    stf::smv::ModelBaseState update(const float dt) override;
    stf::smv::ModelBaseState keyEventsHandler(const int key) override;

    void reset(uint8_t snakes = 0u, uint8_t mouses = 5u);
    void killHunterHandler(HunterModel *hunterModel);


    inline const FoodModel& foodModel()                   const { return m_foodModel;}
    inline const stf::Vec2d& mapSize()                    const { return m_mapSize;}
    inline const std::vector<HunterModel *>& hunterModels() const { return m_hunterModels; }
private:
    std::vector<HunterModel *> m_hunterModels;
    FoodModel m_foodModel;

    stf::Vec2d m_mapSize = {0,0};
    bool m_aiIsEnable = false;
};

#endif // MODEL_HPP
