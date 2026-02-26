#include "Game.hpp"
#include "GameOver.hpp"
#include <windows.h>
#include <cmath>
#include <cstring>
#include <cstdio>

//постоянные для объектов и карты
const char BRICK = '#';
const char EMPTY_BOX = '-';
const char ENEMY = 'o';
const char FULL_BOX = '?';
const char MARIO_C = '@';
const char MONEY = '$';
const char WIN_BRICK = '+';

void Game::initializeLevel(int level) {
    system("color 9F"); //цвет для каждого уровня

    map.initialize();  //инициализация карты

    delete[] bricks;
    bricks = nullptr;
    bricks_count = 0;

    delete[] movings;
    movings = nullptr;
    movings_count = 0;

    score = 0;

    mario.setPosition(39.0f, 10.0f);

    switch (level) {
        case 1:
            bricks_count = 13;
            bricks = new Object[bricks_count];

            bricks[0] = Object(20.0f, 20.0f, 40.0f, 5.0f, BRICK);
            bricks[1] = Object(30.0f, 10.0f, 5.0f, 3.0f, FULL_BOX);
            bricks[2] = Object(50.0f, 10.0f, 5.0f, 3.0f, FULL_BOX);
            bricks[3] = Object(60.0f, 15.0f, 40.0f, 10.0f, BRICK);
            bricks[4] = Object(60.0f, 5.0f, 10.0f, 3.0f, EMPTY_BOX);
            bricks[5] = Object(70.0f, 5.0f, 5.0f, 3.0f, FULL_BOX);
            bricks[6] = Object(75.0f, 5.0f, 5.0f, 3.0f, EMPTY_BOX);
            bricks[7] = Object(80.0f, 5.0f, 5.0f, 3.0f, FULL_BOX);
            bricks[8] = Object(85.0f, 5.0f, 10.0f, 3.0f, EMPTY_BOX);
            bricks[9] = Object(100.0f, 20.0f, 20.0f, 5.0f, BRICK);
            bricks[10] = Object(120.0f, 15.0f, 10.0f, 10.0f, BRICK);
            bricks[11] = Object(150.0f, 20.0f, 40.0f, 5.0f, BRICK);
            bricks[12] = Object(210.0f, 15.0f, 10.0f, 10.0f, WIN_BRICK);

            movings_count = 2;
            movings = new Object[movings_count];
            movings[0] = Object(25.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            movings[1] = Object(80.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            break;

        case 2:
            bricks_count = 6;
            bricks = new Object[bricks_count];

            bricks[0] = Object(20.0f, 20.0f, 40.0f, 5.0f, BRICK);
            bricks[1] = Object(60.0f, 15.0f, 10.0f, 10.0f, BRICK);
            bricks[2] = Object(80.0f, 20.0f, 20.0f, 5.0f, BRICK);
            bricks[3] = Object(120.0f, 15.0f, 10.0f, 10.0f, BRICK);
            bricks[4] = Object(150.0f, 20.0f, 40.0f, 5.0f, BRICK);
            bricks[5] = Object(210.0f, 15.0f, 10.0f, 10.0f, WIN_BRICK);

            movings_count = 6;
            movings = new Object[movings_count];
            movings[0] = Object(25.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            movings[1] = Object(80.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            movings[2] = Object(65.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            movings[3] = Object(120.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            movings[4] = Object(160.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            movings[5] = Object(175.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            break;

        case 3:
            bricks_count = 4;
            bricks = new Object[bricks_count];

            bricks[0] = Object(20.0f, 20.0f, 40.0f, 5.0f, BRICK);
            bricks[1] = Object(80.0f, 20.0f, 15.0f, 5.0f, BRICK);
            bricks[2] = Object(120.0f, 15.0f, 15.0f, 10.0f, BRICK);
            bricks[3] = Object(160.0f, 10.0f, 15.0f, 15.0f, WIN_BRICK);

            movings_count = 6;
            movings = new Object[movings_count];
            movings[0] = Object(25.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            movings[1] = Object(50.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            movings[2] = Object(80.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            movings[3] = Object(90.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            movings[4] = Object(120.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            movings[5] = Object(135.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            break;
    }
}

void Game::run() {
    //спрятать курсор для более чистого отображения
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    initializeLevel(current_level);

    const int JUMP_KEY = VK_SPACE;
    const int EXIT_KEY = VK_ESCAPE;
    const char LEFT_KEY = 'A';
    const char RIGHT_KEY = 'D';

    do {
        handleInput();
        update();
        render();
        Sleep(15);
    } while (GetKeyState(EXIT_KEY) >= 0);
}

void Game::handleInput() {
    if (!mario.is_fly && GetKeyState(VK_SPACE) < 0) {
        mario.vert_speed = -1.0f;
    }
    if (GetKeyState('A') < 0) {
        moveMapHorizontally(1.0f);
    }
    if (GetKeyState('D') < 0) {
        moveMapHorizontally(-1.0f);
    }
}

void Game::update() {
    //обновить вертикальное положение Марио (гравитация и прыжки)
    moveObjectVertically(mario);

    //если упал, перезапустить уровень
    if (mario.y > MAP_HEIGHT) {
        system("color 4F");
        Sleep(500);
        initializeLevel(current_level);
        return;
    }

    //перезапуск уровня при столкновении с врагом и начисление очков при сборе монет
    for (int i = 0; i < movings_count; i++) {
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

void Game::render() {
    map.clear();
    map.putObject(mario);
    for (int i = 0; i < bricks_count; i++) {
        map.putObject(bricks[i]);
    }
    for (int i = 0; i < movings_count; i++) {
        map.putObject(movings[i]);
    }
    map.putScore(score);
    map.display();
}

bool Game::isCollision(const Object& a, const Object& b) {
    return (a.x + a.width > b.x && a.x < b.x + b.width &&
            a.y + a.height > b.y && a.y < b.y + b.height);
}

void Game::deleteMoving(int i) {
    if (movings_count <= 0 || i < 0 || i >= movings_count) return;
    movings_count--;
    movings[i] = movings[movings_count];
}

void Game::moveObjectVertically(Object& obj) {
    obj.is_fly = true;
    obj.vert_speed += 0.05f;
    obj.y += obj.vert_speed;

    for (int i = 0; i < bricks_count; i++) {
        if (isCollision(obj, bricks[i])) {
            float prevSpeed = obj.vert_speed;

            if (prevSpeed > 0) {
                obj.is_fly = false;
                //задать позицию Марио прямо над кирпичом
                obj.y = bricks[i].y - obj.height;
            }

            //спавн монетки
            if (bricks[i].ctype == FULL_BOX && prevSpeed < 0 && &obj == &mario) {
                bricks[i].ctype = EMPTY_BOX;

                // expand movings array by 1
                Object* temp = new Object[movings_count + 1];
                for (int j = 0; j < movings_count; j++) temp[j] = movings[j];
                delete[] movings;
                movings = temp;

                movings[movings_count] = Object(bricks[i].x, bricks[i].y - 3.0f, 3.0f, 2.0f, MONEY);
                movings[movings_count].vert_speed = -0.7f;
                movings_count++;
            }

            //удар головой о кирпич
            if (prevSpeed < 0) {
                obj.y = bricks[i].y + bricks[i].height;
            }

            obj.vert_speed = 0.0f;

            if (bricks[i].ctype == WIN_BRICK) {
                current_level++;
                if (current_level > 3) {
                    GameOver::show();
                } else {
                    system("color 2F");
                    Sleep(500);
                    initializeLevel(current_level);
                }
            }
            break;
        }
    }
}

void Game::moveObjectHorizontally(Object& obj) {
    obj.x += obj.horiz_speed;

    for (int i = 0; i < bricks_count; i++) {
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
    for (int i = 0; i < movings_count; i++) {
        if (isCollision(mario, movings[i])) {
            if (movings[i].ctype == ENEMY) {
                if (mario.is_fly && mario.vert_speed > 0 &&
                    mario.y + mario.height < movings[i].y + movings[i].height * 0.5f) {
                    score += 50;
                    deleteMoving(i);
                    i--;
                    continue;
                } else {
                    system("color 4F");
                    Sleep(500);
                    int temp_level = current_level;
                    initializeLevel(temp_level);
                    return; //перезапуск уровня
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
    //обновить позицию Марио и всех объектов на карте
    for (int i = 0; i < bricks_count; i++) bricks[i].x += dx;
    for (int i = 0; i < movings_count; i++) movings[i].x += dx;

    //столкновение с кирпичем
    for (int i = 0; i < bricks_count; i++) {
        if (isCollision(mario, bricks[i])) {
            for (int j = 0; j < bricks_count; j++) bricks[j].x -= dx;
            for (int j = 0; j < movings_count; j++) movings[j].x -= dx;
            return;
        }
    }
}
