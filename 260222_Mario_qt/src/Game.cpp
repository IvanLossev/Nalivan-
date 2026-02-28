#include "Game.hpp"
#include <cmath>
#include <QString>

// character types inherited from original game
const char BRICK = '#';
const char EMPTY_BOX = '-';
const char ENEMY = 'o';
const char FULL_BOX = '?';
const char MARIO_C = '@';
const char MONEY = '$';
const char WIN_BRICK = '+';

Game::Game()
    : mario(39.0f, 10.0f, 3.0f, 3.0f, MARIO_C), current_level(1), score(0), gameOver(false) {
}

void Game::initializeLevel(int level) {
    current_level = level;
    bricks.clear();
    movings.clear();
    score = 0;
    gameOver = false;
    mario.setPosition(39.0f, 10.0f);

    switch (level) {
    case 1:
        bricks.reserve(13);
        bricks.push_back(Object(20.0f, 20.0f, 40.0f, 5.0f, BRICK));
        bricks.push_back(Object(30.0f, 10.0f, 5.0f, 3.0f, FULL_BOX));
        bricks.push_back(Object(50.0f, 10.0f, 5.0f, 3.0f, FULL_BOX));
        bricks.push_back(Object(60.0f, 15.0f, 40.0f, 10.0f, BRICK));
        bricks.push_back(Object(60.0f, 5.0f, 10.0f, 3.0f, EMPTY_BOX));
        bricks.push_back(Object(70.0f, 5.0f, 5.0f, 3.0f, FULL_BOX));
        bricks.push_back(Object(75.0f, 5.0f, 5.0f, 3.0f, EMPTY_BOX));
        bricks.push_back(Object(80.0f, 5.0f, 5.0f, 3.0f, FULL_BOX));
        bricks.push_back(Object(85.0f, 5.0f, 10.0f, 3.0f, EMPTY_BOX));
        bricks.push_back(Object(100.0f, 20.0f, 20.0f, 5.0f, BRICK));
        bricks.push_back(Object(120.0f, 15.0f, 10.0f, 10.0f, BRICK));
        bricks.push_back(Object(150.0f, 20.0f, 40.0f, 5.0f, BRICK));
        bricks.push_back(Object(210.0f, 15.0f, 10.0f, 10.0f, WIN_BRICK));

        movings.reserve(2);
        movings.push_back(Object(25.0f, 10.0f, 3.0f, 2.0f, ENEMY));
        movings.push_back(Object(80.0f, 10.0f, 3.0f, 2.0f, ENEMY));
        break;

    case 2:
        bricks.reserve(6);
        bricks.push_back(Object(20.0f, 20.0f, 40.0f, 5.0f, BRICK));
        bricks.push_back(Object(60.0f, 15.0f, 10.0f, 10.0f, BRICK));
        bricks.push_back(Object(80.0f, 20.0f, 20.0f, 5.0f, BRICK));
        bricks.push_back(Object(120.0f, 15.0f, 10.0f, 10.0f, BRICK));
        bricks.push_back(Object(150.0f, 20.0f, 40.0f, 5.0f, BRICK));
        bricks.push_back(Object(210.0f, 15.0f, 10.0f, 10.0f, WIN_BRICK));

        movings.reserve(6);
        movings.push_back(Object(25.0f, 10.0f, 3.0f, 2.0f, ENEMY));
        movings.push_back(Object(80.0f, 10.0f, 3.0f, 2.0f, ENEMY));
        movings.push_back(Object(65.0f, 10.0f, 3.0f, 2.0f, ENEMY));
        movings.push_back(Object(120.0f, 10.0f, 3.0f, 2.0f, ENEMY));
        movings.push_back(Object(160.0f, 10.0f, 3.0f, 2.0f, ENEMY));
        movings.push_back(Object(175.0f, 10.0f, 3.0f, 2.0f, ENEMY));
        break;

    case 3:
        bricks.reserve(4);
        bricks.push_back(Object(20.0f, 20.0f, 40.0f, 5.0f, BRICK));
        bricks.push_back(Object(80.0f, 20.0f, 15.0f, 5.0f, BRICK));
        bricks.push_back(Object(120.0f, 15.0f, 15.0f, 10.0f, BRICK));
        bricks.push_back(Object(160.0f, 10.0f, 15.0f, 15.0f, WIN_BRICK));

        movings.reserve(6);
        movings.push_back(Object(25.0f, 10.0f, 3.0f, 2.0f, ENEMY));
        movings.push_back(Object(50.0f, 10.0f, 3.0f, 2.0f, ENEMY));
        movings.push_back(Object(80.0f, 10.0f, 3.0f, 2.0f, ENEMY));
        movings.push_back(Object(90.0f, 10.0f, 3.0f, 2.0f, ENEMY));
        movings.push_back(Object(120.0f, 10.0f, 3.0f, 2.0f, ENEMY));
        movings.push_back(Object(135.0f, 10.0f, 3.0f, 2.0f, ENEMY));
        break;
    }
}

bool Game::isCollision(const Object& a, const Object& b) {
    return (a.x + a.width > b.x && a.x < b.x + b.width &&
            a.y + a.height > b.y && a.y < b.y + b.height);
}

void Game::deleteMoving(int i) {
    if (i < 0 || i >= (int)movings.size()) return;
    movings.erase(movings.begin() + i);
}

void Game::moveObjectVertically(Object& obj) {
    obj.is_fly = true;
    obj.vert_speed += 0.05f;
    obj.y += obj.vert_speed;

    for (size_t i = 0; i < bricks.size(); ++i) {
        if (isCollision(obj, bricks[i])) {
            float prevSpeed = obj.vert_speed;

            if (prevSpeed > 0) {
                obj.is_fly = false;
                obj.y = bricks[i].y - obj.height;
            }

            if (bricks[i].ctype == FULL_BOX && prevSpeed < 0 && &obj == &mario) {
                bricks[i].ctype = EMPTY_BOX;
                Object coin(bricks[i].x, bricks[i].y - 3.0f, 3.0f, 2.0f, MONEY);
                coin.vert_speed = -0.7f;
                movings.push_back(coin);
            }

            if (prevSpeed < 0) {
                obj.y = bricks[i].y + bricks[i].height;
            }

            obj.vert_speed = 0.0f;

            if (bricks[i].ctype == WIN_BRICK) {
                current_level++;
                if (current_level > 3) {
                    gameOver = true;
                } else {
                    initializeLevel(current_level);
                }
            }
            break;
        }
    }
}

void Game::moveObjectHorizontally(Object& obj) {
    obj.x += obj.horiz_speed;

    for (size_t i = 0; i < bricks.size(); ++i) {
        if (isCollision(obj, bricks[i])) {
            obj.x -= obj.horiz_speed;
            obj.horiz_speed = -obj.horiz_speed;
            return;
        }
    }

    if (obj.ctype == ENEMY) {
        Object tmp = obj;
        moveObjectVertically(tmp);
        if (tmp.is_fly) {
            obj.x -= obj.horiz_speed;
            obj.horiz_speed = -obj.horiz_speed;
        }
    }
}

void Game::marioCollision() {
    for (size_t i = 0; i < movings.size(); ++i) {
        if (isCollision(mario, movings[i])) {
            if (movings[i].ctype == ENEMY) {
                if (mario.is_fly && mario.vert_speed > 0 &&
                    mario.y + mario.height < movings[i].y + movings[i].height * 0.5f) {
                    score += 50;
                    deleteMoving(i);
                    i--;
                    continue;
                } else {
                    initializeLevel(current_level);
                    return;
                }
            }

            if (movings[i].ctype == MONEY) {
                score += 100;
                deleteMoving(i);
                i--;
                continue;
            }
        }
    }
}

void Game::moveMapHorizontally(float dx) {
    for (auto &b : bricks) b.x += dx;
    for (auto &m : movings) m.x += dx;

    for (auto &b : bricks) {
        if (isCollision(mario, b)) {
            for (auto &bb : bricks) bb.x -= dx;
            for (auto &mm : movings) mm.x -= dx;
            return;
        }
    }
}

void Game::handleInput(bool left, bool right, bool jump) {
    if (jump && !mario.is_fly) {
        mario.vert_speed = -1.0f;
    }
    if (left) moveMapHorizontally(1.0f);
    if (right) moveMapHorizontally(-1.0f);
}

void Game::update() {
    moveObjectVertically(mario);

    if (mario.y > MAP_HEIGHT) {
        initializeLevel(current_level);
        return;
    }

    for (size_t i = 0; i < movings.size(); ++i) {
        moveObjectVertically(movings[i]);
        moveObjectHorizontally(movings[i]);
        if (movings[i].y > MAP_HEIGHT) {
            deleteMoving(i);
            i--;
            continue;
        }
    }

    marioCollision();
}

void Game::render(QPainter &p) {
    // paint background
    p.fillRect(0, 0, MAP_WIDTH * CELL_SIZE, MAP_HEIGHT * CELL_SIZE, Qt::black);

    // draw bricks
    for (const auto &b : bricks) {
        QRect rect(int(b.x * CELL_SIZE), int(b.y * CELL_SIZE),
                   int(b.width * CELL_SIZE), int(b.height * CELL_SIZE));
        QColor color;
        switch (b.ctype) {
        case BRICK: color = Qt::gray; break;
        case FULL_BOX: color = QColor(139,69,19); break; // brown
        case EMPTY_BOX: color = Qt::lightGray; break;
        case WIN_BRICK: color = Qt::green; break;
        default: color = Qt::gray; break;
        }
        p.fillRect(rect, color);
    }

    // draw movings (enemies, coins)
    for (const auto &m : movings) {
        QRect rect(int(m.x * CELL_SIZE), int(m.y * CELL_SIZE),
                   int(m.width * CELL_SIZE), int(m.height * CELL_SIZE));
        QColor color;
        switch (m.ctype) {
        case ENEMY: color = Qt::red; break;
        case MONEY: color = Qt::yellow; break;
        default: color = Qt::white; break;
        }
        p.fillRect(rect, color);
    }

    // draw mario
    QRect mrect(int(mario.x * CELL_SIZE), int(mario.y * CELL_SIZE),
                int(mario.width * CELL_SIZE), int(mario.height * CELL_SIZE));
    p.fillRect(mrect, Qt::blue);

    // draw score
    p.setPen(Qt::white);
    p.drawText(5, 15, QString("Score: %1").arg(score));
}
