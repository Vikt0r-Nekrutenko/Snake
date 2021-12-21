#ifndef MODEL_HPP
#define MODEL_HPP

#include "snake.hpp"
#include <cstdint>
#include "random.hpp"
#include <ctime>

enum class Signal : uint8_t
{
    none, start, pause, end,
};

class SnakeModel
{
public:
    SnakeModel(const stf::Vec2d& mapSize, const stf::Vec2d& startPos = {10,10})
        : m_snake(startPos),
          m_mapSize(mapSize)
    {

    }

    void onUpdate(const float dt)
    {
        if(m_snake.isDead()) return;

        if(m_time > m_lvlDuration)
        {
            m_snake.update();

//            if(m_snake.isAteHerself())
//                m_snake.killSnake();

            m_snake.wrapping(2,1,m_mapSize.x-1, m_mapSize.y-1);
            m_time = 0.f;
        }
        m_time += dt;
    }

    void keyEvents(const int key)
    {
        switch (key) {
        case 'w': m_snake.W(); break;
        case 'a': m_snake.A(); break;
        case 's': m_snake.S(); break;
        case 'd': m_snake.D(); break;
        }
    }

    void aiControl(const stf::Vec2d& target)
    {
        if(m_snake.head().x > target.x) m_snake.A();
        if(m_snake.head().x < target.x) m_snake.D();
        if(m_snake.head().y > target.y) m_snake.W();
        if(m_snake.head().y < target.y) m_snake.S();
    }

    void reset()
    {
        m_snake = Snake({stf::Random(time(0)).getNum(2, m_mapSize.x-2),
                         stf::Random(time(0)).getNum(2, m_mapSize.y-2)});
        m_snake.rebornSnake();
        m_score = 0u; m_lvl = 1u;
        m_lvlDuration = 0.05f;
    }

    bool isCollideWithEat(const stf::Vec2d& pos) const
    {
        if(m_snake.head().diff(pos) < 1.f) return true;
        return false;
    }

    void collisionWithEatHandler()
    {
        if(m_snake.body().size() < 15) m_snake.feed();
        ++m_score;
//        if(m_score != 1 && m_lvl < 20 && m_score % 5 == 0) {
//            m_lvlDuration -= 0.025f;
//            ++m_lvl;
//        }
    }

    SnakeModel* collisionWithSnakeHandler(SnakeModel* snakeMod)
    {
        if(m_snake.isDead() || snakeMod->snake().isDead()) return nullptr;

        for(size_t s = 0; s < m_snake.body().size(); ++s) {
            for (size_t s1 = 0; s1 < snakeMod->snake().body().size(); ++s1) {
                if(m_snake.body().at(s).diff(snakeMod->snake().body().at(s1)) < 1.f) {
                    if(m_score > snakeMod->score()) {
                        return snakeMod;
                    } else {
                        return this;
                    }
                }
            }
        }
        return nullptr;
    }

    inline uint16_t score() const { return m_score; }
    inline uint16_t lvl() const { return m_lvl; }
    inline const Snake& snake() const { return m_snake; }
    inline const stf::Vec2d& mapSize() const { return m_mapSize;}
    inline bool aiIsEnable() const { return m_aiIsEnable; }
    inline void killSnake() { m_snake.killSnake(); }
    stf::Vec2d *target = nullptr;
private:
    Snake m_snake;
    stf::Vec2d m_mapSize = {0,0};
    float m_time = 0.f;
    float m_lvlDuration = 0.05f;
    bool m_aiIsEnable = true;
    uint16_t m_score = 0u;
    uint16_t m_lvl   = 1u;
};

class GameModel
{
public:
    GameModel(const stf::Vec2d& mapSize);

    Signal onUpdate(const float dt);
    Signal keyEvents(const int key);
    void aiControl();
    void reset();
    void kill(SnakeModel *snakeMod);


    inline const std::vector<stf::Vec2d>& eats() const { return m_eats;}
    inline const std::vector<stf::Vec2d>& eats1() const { return m_eats1;}
    inline const stf::Vec2d& mapSize() const { return m_mapSize;}
    inline const std::vector<SnakeModel>& snakeModels() const { return snakeMods; }
private:
    std::vector<SnakeModel> snakeMods;
    std::vector<stf::Vec2d> m_eats;
    std::vector<stf::Vec2d> m_eats1;

    stf::Vec2d m_mapSize = {0,0};
    bool m_aiIsEnable = false;

    void pasteEat(const SnakeModel& snakeMod);
};

#endif // MODEL_HPP
