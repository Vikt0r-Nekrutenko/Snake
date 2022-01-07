#ifndef FOODMODEL_HPP
#define FOODMODEL_HPP

#include <vector>

#include "food.hpp"

class FoodModel
{
public:
    FoodModel(const stf::Vec2d& mapSize, const size_t activeFoodCount = food_model_settings::DEF_ACTIVE_FOOD_COUNT);
    ~FoodModel();
    inline const std::vector<Food *>& food() const { return m_food; }
    inline size_t possibleFoodCount() const { return m_possibleFoodCount; }

    const std::vector<Food *> getPossibleFood() const;

    Food* nearestFood(const stf::Vec2d& pos) const;
    void pasteFoodFromDeadSnake(const std::vector<stf::Vec2d>& snakeBody);
    void onUpdate();
    void remove(const Food *food);
    void reset();

private:

    std::vector<Food *> m_food;
    stf::Vec2d m_mapSize;
    size_t m_possibleFoodCount = 0;

    template<class t> void pasteFood(const t food)
    {
        for(size_t i = 0; i < m_food.size() && m_possibleFoodCount < food_model_settings::DEF_ACTIVE_FOOD_COUNT; ++i) {
            if(m_food[i] == nullptr) {
                m_food[i] = new t(food);
                ++m_possibleFoodCount;
            }
        }
    }
};

#endif // FOODMODEL_HPP
