#ifndef MODEL_HPP
#define MODEL_HPP

#include <cstdint>
#include <ctime>

#include "snake.hpp"
#include "huntermodel.hpp"
#include "foodmodel.hpp"

enum class Signal : uint8_t
{
    none, start, pause, end,
};

class GameModel
{
public:
    GameModel(const stf::Vec2d& mapSize, uint8_t snakes = 0u, uint8_t mouses = 5u);
    ~GameModel();

    Signal onUpdate(const float dt);
    Signal keyEvents(const int key);
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
