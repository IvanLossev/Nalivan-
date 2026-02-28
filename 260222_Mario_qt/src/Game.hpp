#ifndef GAME_HPP
#define GAME_HPP

#include "Object.hpp"
#include "Map.hpp"
#include <vector>
#include <QPainter>

// scaling factor in pixels per map unit
static const int CELL_SIZE = 10;

class Game {
private:
    Object mario;
    std::vector<Object> bricks;
    std::vector<Object> movings;
    int current_level;
    int score;
    bool gameOver;

    bool isCollision(const Object& a, const Object& b);
    void moveObjectVertically(Object& obj);
    void moveObjectHorizontally(Object& obj);
    void marioCollision();
    void moveMapHorizontally(float dx);
    void deleteMoving(int i);

public:
    Game();
    void initializeLevel(int level);
    void handleInput(bool left, bool right, bool jump);
    void update();
    void render(QPainter &p);

    bool isGameOver() const { return gameOver; }
};

#endif
