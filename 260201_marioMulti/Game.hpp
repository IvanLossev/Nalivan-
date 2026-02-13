#ifndef GAME_HPP
#define GAME_HPP

#include <windows.h>
#include "Map.hpp"
#include "Object.hpp"

class Game {
private:
    Map map;
    Object mario;
    Object* bricks;
    int bricks_count;
    Object* movings;
    int movings_count;
    int current_level;
    int score;

    // Internal helpers (adapted from centralized version)
    bool isCollision(const Object& a, const Object& b);
    void moveObjectVertically(Object& obj);
    void moveObjectHorizontally(Object& obj);
    void deleteMoving(int i);
    void marioCollision();
    void moveMapHorizontally(float dx);

public:
    Game() : bricks(nullptr), bricks_count(0), movings(nullptr), movings_count(0), current_level(1), score(0) {
        mario = Object(39.0f, 10.0f, 3.0f, 3.0f, '@');
    }

    ~Game() {
        delete[] bricks;
        delete[] movings;
    }

    void initializeLevel(int level);
    void run();
    void handleInput();
    void update();
    void render();
};

#endif