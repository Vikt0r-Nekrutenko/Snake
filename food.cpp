#include "food.hpp"


Food::Food(const stf::Vec2d &pos) : m_pos(pos) { }

Food::Food(const stf::Vec2d &lim1, const stf::Vec2d &lim2)
    : Food({stf::Random(time(0)).getNum(lim1.x, lim2.x),
           stf::Random(time(0)).getNum(lim1.y, lim2.y)})
{ }

Food::Food(const Food &food)
    : m_pos(food.m_pos),
      m_nutritionalValue(food.m_nutritionalValue)
{}

RegularFood::RegularFood(const stf::Vec2d &pos) : Food(pos)
{
    m_nutritionalValue = stf::Random(0).getNum(1, 5);
}

RegularFood::RegularFood(const stf::Vec2d &lim1, const stf::Vec2d &lim2) : Food(lim1, lim2)
{
    m_nutritionalValue = stf::Random(0).getNum(1, 5);
}

SuperFood::SuperFood(const stf::Vec2d &pos) : Food(pos)
{
    m_nutritionalValue = stf::Random(0).getNum(10, 15);
}

SuperFood::SuperFood(const stf::Vec2d &lim1, const stf::Vec2d &lim2) : Food(lim1, lim2)
{
    m_nutritionalValue = stf::Random(0).getNum(10, 15);
}

MeatFood::MeatFood(const stf::Vec2d &pos) : Food(pos)
{
    m_nutritionalValue = stf::Random(0).getNum(5, 10);
}

MeatFood::MeatFood(const stf::Vec2d &lim1, const stf::Vec2d &lim2) : Food(lim1, lim2)
{
    m_nutritionalValue = stf::Random(0).getNum(5, 10);
}

FoodModel::FoodModel(const stf::Vec2d &mapSize, const size_t activeFoodCount)
    : m_mapSize(mapSize),
      m_possibleFoodCount(activeFoodCount)
{
    m_food.resize(mapSize.x * mapSize.y, nullptr);
    size_t i = 0;
    while(i++ < activeFoodCount)
        m_food[i] = new RegularFood({2,2}, mapSize-2);
}

FoodModel::~FoodModel() {
    for(size_t i = 0; i < m_food.size(); ++i) delete  m_food[i];
}

const std::vector<Food *> FoodModel::getPossibleFood() const {
    std::vector<Food *> possibleFood;
    for(size_t i = 0; i < m_food.size(); ++i)
        if(m_food.at(i) != nullptr)
            possibleFood.push_back(m_food.at(i));
    return possibleFood;
}

Food *FoodModel::nearestFood(const stf::Vec2d &pos) const {
    std::vector<Food *> possibleFood = getPossibleFood();
    if(possibleFood.size() == 0) return nullptr;

    Food* nearFood = possibleFood.front();
    for(auto food : possibleFood) {
        if(pos.diff(nearFood->pos()) > pos.diff(food->pos())) {
            nearFood = food;
        }
    }
    return nearFood;
}

void FoodModel::onUpdate(const float dt)
{
    pasteFood<RegularFood>({ {2,2},m_mapSize-2 });
}

void FoodModel::remove(Food *food) {
    for(size_t i = 0; i < m_food.size(); ++i)
        if(food == m_food[i] && food != nullptr) {
            delete m_food[i];
            m_food[i] = nullptr;
            food = nullptr;
            --m_possibleFoodCount;
        }
}

void FoodModel::pasteFoodFromDeadSnake(const std::vector<stf::Vec2d> &snakeBody) {
    m_possibleFoodCount += snakeBody.size();
    for(auto s : snakeBody)
        for(size_t i = 0; i < m_food.size(); ++i)
            if(m_food[i] == nullptr) {
                m_food[i] = new MeatFood(s);
                break;
            }
}
