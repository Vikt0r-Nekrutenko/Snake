#ifndef EAT_HPP
#define EAT_HPP

#include "random.hpp"
#include "vec2d.hpp"
#include <ctime>

class Eat
{
public:
    Eat(const stf::Vec2d& pos = {-1,-1}) : m_pos(pos) { }
    Eat(const stf::Vec2d& lim1, const stf::Vec2d& lim2)
        : Eat({stf::Random(time(0)).getNum(lim1.x, lim2.x),
               stf::Random(time(0)).getNum(lim1.y, lim2.y)})
    { }
    virtual ~Eat() = default;

    virtual char symbol() const = 0;
    inline const stf::Vec2d& pos()      const { return m_pos; }
    inline uint8_t nutritionalValue()   const { return m_nutritionalValue; }

protected:

    stf::Vec2d m_pos;
    uint8_t    m_nutritionalValue = 0;
};

class RegularEat : public Eat
{
public:
    RegularEat(const stf::Vec2d& pos = {-1,-1}) : Eat(pos)
    {
        m_nutritionalValue = stf::Random(0).getNum(1, 5);
    }

    RegularEat(const stf::Vec2d& lim1, const stf::Vec2d& lim2) : Eat(lim1, lim2)
    {
        m_nutritionalValue = stf::Random(0).getNum(1, 5);
    }

    ~RegularEat() override = default;
    char symbol() const override { return '~'; }
};

class SuperEat : public Eat
{
public:
    SuperEat(const stf::Vec2d& pos = {-1,-1}) : Eat(pos)
    {
        m_nutritionalValue = stf::Random(0).getNum(10, 15);
    }

    SuperEat(const stf::Vec2d& lim1, const stf::Vec2d& lim2) : Eat(lim1, lim2)
    {
        m_nutritionalValue = stf::Random(0).getNum(10, 15);
    }
    ~SuperEat() override = default;
    char symbol() const override { return 'O'; }
};

class MeatEat : public Eat
{
public:

    MeatEat(const stf::Vec2d& pos) : Eat(pos)
    {
        m_nutritionalValue = stf::Random(0).getNum(5, 10);
    }

    MeatEat(const stf::Vec2d& lim1, const stf::Vec2d& lim2) : Eat(lim1, lim2)
    {
        m_nutritionalValue = stf::Random(0).getNum(5, 10);
    }
    ~MeatEat() override = default;
    char symbol() const override { return 'o'; }
};

class EatModel
{
public:
    EatModel(const stf::Vec2d& mapSize, const size_t activeEats = 10) : m_mapSize(mapSize)
    {
        m_eats.resize(mapSize.x * mapSize.y, nullptr);
        size_t i = 0;
        while(i++ < activeEats)
            m_eats[i] = new RegularEat({2,2}, mapSize-2);
    }
    ~EatModel() {
        for(size_t i = 0; i < m_eats.size(); ++i) delete  m_eats[i];
    }
    inline const std::vector<Eat *>& eats() const { return m_eats; }

    const std::vector<Eat *> getPossibleEat() const {
        std::vector<Eat *> possibleEat;
        for(size_t i = 0; i < m_eats.size(); ++i)
            if(m_eats.at(i) != nullptr)
                possibleEat.push_back(m_eats.at(i));
        return possibleEat;
    }

    Eat* nearestFood(const stf::Vec2d& pos) const {
        std::vector<Eat *> possibleFood = getPossibleEat();
        if(possibleFood.size() == 0) return nullptr;

        Eat* nearFood = possibleFood.front();
        for(auto food : possibleFood) {
            if(pos.diff(nearFood->pos()) > pos.diff(food->pos())) {
                nearFood = food;
            }
        }
        return nearFood;
    }
    void remove(Eat *food) {
        for(size_t i = 0; i < m_eats.size(); ++i)
            if(food == m_eats[i]) m_eats[i] = nullptr;
    }
private:
    std::vector<Eat *> m_eats;
    stf::Vec2d m_mapSize;
};

#endif // EAT_HPP
