#include <cstring>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <windows.h>

const char BRICK = '#';
const char EMPTY_BOX = '-';
const char ENEMY = 'o';
const char FLYING_ENEMY = 'W';
const char FULL_BOX = '?';
const char MARIO = '@';
const char MONEY = '$';
const char WIN_BRICK = '+';

const int MAP_WIDTH = 200;
const int MAP_HEIGHT = 50;

struct TObject {
    float x, y;
    float width, height;
    float vert_speed;
    float horiz_speed;
    bool is_fly;
    char ctype;
    // Поля для летающих противников
    float origin_x, origin_y;
    float range_x, range_y;
};

// Прототипы функций
void hide_cursor();
void clear_map(char **map, int width, int height);
void show_map(char **map, int width, int height);
void set_cursor_position(int x, int y);
void set_obj_position(TObject* obj, float xpos, float ypos);
void init_object(TObject* obj, float xpos, float ypos, float owidth, float oheight, char inType);
void init_flying_enemy(TObject* obj, float xpos, float ypos, float owidth, float oheight, float rx, float ry, float hspd, float vspd);
void create_current_level(
    int level,
    TObject& mario,
    TObject*& bricks, int& bricks_count,
    TObject*& movings, int& movings_count,
    int& score
);
void dead(
    TObject& mario,
    TObject*& bricks, int& bricks_count,
    TObject*& movings, int& movings_count,
    int& current_level,
    int& score
);
bool is_collision(TObject* obj1, TObject* obj2);
void move_obj_vertically(
    TObject* obj,
    TObject& mario,
    TObject*& bricks, int& bricks_count,
    TObject*& movings, int& movings_count,
    int& current_level,
    int& score
);
void move_flying_enemy(TObject* obj);
void delete_moving(TObject*& movings, int& movings_count, int i);
void mario_collision(
    TObject& mario,
    TObject* bricks, int bricks_count,
    TObject*& movings, int& movings_count,
    int current_level,
    int& score
);
void move_obj_horizontally(
    TObject* obj,
    TObject& mario,
    TObject* bricks, int bricks_count,
    TObject*& movings, int& movings_count,
    int& current_level,
    int& score
);
bool is_pos_in_map(int x, int y);
void put_object_on_map(char** map, TObject obj);
void move_map_horizontally(
    float dx,
    TObject& mario,
    TObject* bricks, int bricks_count,
    TObject* movings, int movings_count
);
void put_score_on_map(char **map, int score);

void hide_cursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void clear_map(char **map, int width, int height) {
    for (int i = 0; i < width; i++) {
        map[0][i] = ' ';
    }
    map[0][width] = '\0';
    for (int j = 1; j < height; j++) {
        strcpy(map[j], map[0]);
    }
}

void show_map(char **map, int width, int height) {
    for (int j = 0; j < height; j++) {
        std::cout << map[j] << std::endl;
    }
}

void set_cursor_position(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void set_obj_position(TObject* obj, float xpos, float ypos) {
    obj->x = xpos;
    obj->y = ypos;
}

void init_object(TObject* obj, float xpos, float ypos, float owidth, float oheight, char inType) {
    set_obj_position(obj, xpos, ypos);
    obj->width = owidth;
    obj->height = oheight;
    obj->vert_speed = 0.0f;
    obj->ctype = inType;
    obj->horiz_speed = 0.2f;
    obj->is_fly = false;
    obj->origin_x = xpos;
    obj->origin_y = ypos;
    obj->range_x = 0.0f;
    obj->range_y = 0.0f;
}

void init_flying_enemy(TObject* obj, float xpos, float ypos, float owidth, float oheight, float rx, float ry, float hspd, float vspd) {
    init_object(obj, xpos, ypos, owidth, oheight, FLYING_ENEMY);
    obj->origin_x = xpos;
    obj->origin_y = ypos;
    obj->range_x = rx;
    obj->range_y = ry;
    obj->horiz_speed = hspd;
    obj->vert_speed = vspd;
}

void create_current_level(
    int level,
    TObject& mario,
    TObject*& bricks, int& bricks_count,
    TObject*& movings, int& movings_count,
    int& score
) {
    system("color 9F");

    // Очистка старых данных
    delete[] bricks;
    bricks = nullptr;
    bricks_count = 0;

    delete[] movings;
    movings = nullptr;
    movings_count = 0;

    score = 0;

    init_object(&mario, 39.0f, 12.0f, 3.0f, 3.0f, MARIO);

    switch (level) {
        case 1:
            bricks_count = 13;
            bricks = new TObject[bricks_count];

            init_object(&bricks[0], 20.0f, 20.0f, 40.0f, 5.0f, BRICK);
            init_object(&bricks[1], 30.0f, 10.0f, 5.0f, 3.0f, FULL_BOX);
            init_object(&bricks[2], 50.0f, 10.0f, 5.0f, 3.0f, FULL_BOX);
            init_object(&bricks[3], 60.0f, 15.0f, 40.0f, 10.0f, BRICK);
            init_object(&bricks[4], 60.0f, 5.0f, 10.0f, 3.0f, EMPTY_BOX);
            init_object(&bricks[5], 70.0f, 5.0f, 5.0f, 3.0f, FULL_BOX);
            init_object(&bricks[6], 75.0f, 5.0f, 5.0f, 3.0f, EMPTY_BOX);
            init_object(&bricks[7], 80.0f, 5.0f, 5.0f, 3.0f, FULL_BOX);
            init_object(&bricks[8], 85.0f, 5.0f, 10.0f, 3.0f, EMPTY_BOX);
            init_object(&bricks[9], 100.0f, 20.0f, 20.0f, 5.0f, BRICK);
            init_object(&bricks[10], 120.0f, 15.0f, 10.0f, 10.0f, BRICK);
            init_object(&bricks[11], 150.0f, 20.0f, 40.0f, 5.0f, BRICK);
            init_object(&bricks[12], 210.0f, 15.0f, 10.0f, 10.0f, WIN_BRICK);

            // 2 обычных врага + 3 летающих
            movings_count = 5;
            movings = new TObject[movings_count];
            init_object(&movings[0], 25.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            init_object(&movings[1], 80.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            init_flying_enemy(&movings[2], 40.0f, 8.0f, 3.0f, 2.0f, 10.0f, 5.0f, 0.15f, 0.1f);
            init_flying_enemy(&movings[3], 110.0f, 12.0f, 3.0f, 2.0f, 8.0f, 4.0f, 0.12f, 0.08f);
            init_flying_enemy(&movings[4], 160.0f, 10.0f, 3.0f, 2.0f, 12.0f, 6.0f, 0.18f, 0.12f);
            break;

        case 2:
            bricks_count = 6;
            bricks = new TObject[bricks_count];

            init_object(&bricks[0], 20.0f, 20.0f, 40.0f, 5.0f, BRICK);
            init_object(&bricks[1], 60.0f, 15.0f, 10.0f, 10.0f, BRICK);
            init_object(&bricks[2], 80.0f, 20.0f, 20.0f, 5.0f, BRICK);
            init_object(&bricks[3], 120.0f, 15.0f, 10.0f, 10.0f, BRICK);
            init_object(&bricks[4], 150.0f, 20.0f, 40.0f, 5.0f, BRICK);
            init_object(&bricks[5], 210.0f, 15.0f, 10.0f, 10.0f, WIN_BRICK);

            // 6 обычных врагов + 3 летающих
            movings_count = 9;
            movings = new TObject[movings_count];
            init_object(&movings[0], 25.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            init_object(&movings[1], 80.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            init_object(&movings[2], 65.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            init_object(&movings[3], 120.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            init_object(&movings[4], 160.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            init_object(&movings[5], 175.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            init_flying_enemy(&movings[6], 45.0f, 10.0f, 3.0f, 2.0f, 10.0f, 5.0f, 0.15f, 0.1f);
            init_flying_enemy(&movings[7], 100.0f, 8.0f, 3.0f, 2.0f, 8.0f, 4.0f, 0.12f, 0.08f);
            init_flying_enemy(&movings[8], 140.0f, 12.0f, 3.0f, 2.0f, 12.0f, 6.0f, 0.18f, 0.12f);
            break;

        case 3:
            bricks_count = 4;
            bricks = new TObject[bricks_count];

            init_object(&bricks[0], 20.0f, 20.0f, 40.0f, 5.0f, BRICK);
            init_object(&bricks[1], 80.0f, 20.0f, 15.0f, 5.0f, BRICK);
            init_object(&bricks[2], 120.0f, 15.0f, 15.0f, 10.0f, BRICK);
            init_object(&bricks[3], 160.0f, 10.0f, 15.0f, 15.0f, WIN_BRICK);

            // 6 обычных врагов + 3 летающих
            movings_count = 9;
            movings = new TObject[movings_count];
            init_object(&movings[0], 25.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            init_object(&movings[1], 50.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            init_object(&movings[2], 80.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            init_object(&movings[3], 90.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            init_object(&movings[4], 120.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            init_object(&movings[5], 135.0f, 10.0f, 3.0f, 2.0f, ENEMY);
            init_flying_enemy(&movings[6], 35.0f, 8.0f, 3.0f, 2.0f, 10.0f, 5.0f, 0.15f, 0.1f);
            init_flying_enemy(&movings[7], 70.0f, 6.0f, 3.0f, 2.0f, 8.0f, 4.0f, 0.12f, 0.08f);
            init_flying_enemy(&movings[8], 145.0f, 5.0f, 3.0f, 2.0f, 12.0f, 6.0f, 0.18f, 0.12f);
            break;
    }
}

void dead(
    TObject& mario,
    TObject*& bricks, int& bricks_count,
    TObject*& movings, int& movings_count,
    int& current_level,
    int& score
) {
    system("color 4F");
    Sleep(500);
    create_current_level(current_level, mario, bricks, bricks_count, movings, movings_count, score);
}

bool is_collision(TObject* obj1, TObject* obj2) {
    return (
        obj1->x + obj1->width > obj2->x &&
        obj1->x < obj2->x + obj2->width &&
        obj1->y + obj1->height > obj2->y &&
        obj1->y < obj2->y + obj2->height
    );
}

void move_obj_vertically(
    TObject* obj,
    TObject& mario,
    TObject*& bricks, int& bricks_count,
    TObject*& movings, int& movings_count,
    int& current_level,
    int& score
) {
    obj->is_fly = true;
    obj->vert_speed += 0.05f;
    set_obj_position(obj, obj->x, obj->y + obj->vert_speed);

    for (int i = 0; i < bricks_count; i++) {
        if (is_collision(obj, &bricks[i])) {
            if (obj->vert_speed > 0) {
                obj->is_fly = false;
            }

            if (bricks[i].ctype == FULL_BOX && obj->vert_speed < 0 && obj == &mario) {
                bricks[i].ctype = EMPTY_BOX;

                // Создаем новую монету
                TObject* temp = new TObject[movings_count + 1];
                for (int j = 0; j < movings_count; j++) {
                    temp[j] = movings[j];
                }
                delete[] movings;
                movings = temp;

                init_object(&movings[movings_count], bricks[i].x, bricks[i].y - 3.0f, 3.0f, 2.0f, MONEY);
                movings[movings_count].vert_speed = -0.7f;
                movings_count++;
            }

            obj->y -= obj->vert_speed;
            obj->vert_speed = 0.0f;

            if (bricks[i].ctype == WIN_BRICK) {
                current_level++;
                if (current_level > 3) {
                    current_level = 1;
                }
                system("color 2F");
                Sleep(500);
                create_current_level(current_level, mario, bricks, bricks_count, movings, movings_count, score);
            }
            break;
        }
    }
}

void move_flying_enemy(TObject* obj) {
    //горизонтальное движение
    obj->x += obj->horiz_speed;
    if (obj->x > obj->origin_x + obj->range_x || obj->x < obj->origin_x - obj->range_x) {
        obj->horiz_speed = -obj->horiz_speed;
        obj->x += obj->horiz_speed;
    }

    //вертикальное движение
    obj->y += obj->vert_speed;
    if (obj->y > obj->origin_y + obj->range_y || obj->y < obj->origin_y - obj->range_y) {
        obj->vert_speed = -obj->vert_speed;
        obj->y += obj->vert_speed;
    }
}

void delete_moving(TObject*& movings, int& movings_count, int i) {
    if (movings_count <= 0 || i < 0 || i >= movings_count) return;
    movings_count--;
    movings[i] = movings[movings_count];
}

void mario_collision(
    TObject& mario,
    TObject* bricks, int bricks_count,
    TObject*& movings, int& movings_count,
    int current_level,
    int& score
) {
    for (int i = 0; i < movings_count; i++) {
        if (is_collision(&mario, &movings[i])) {
            if (movings[i].ctype == ENEMY || movings[i].ctype == FLYING_ENEMY) {
                if (mario.is_fly && mario.vert_speed > 0 &&
                    mario.y + mario.height < movings[i].y + movings[i].height * 0.5f) {
                    score += (movings[i].ctype == FLYING_ENEMY) ? 75 : 50;
                    delete_moving(movings, movings_count, i);
                    i--;
                    continue;
                }
                else {
                    // Перезапуск уровня
                    system("color 4F");
                    Sleep(500);
                    int temp_level = current_level;
                    create_current_level(temp_level, mario, bricks, bricks_count, movings, movings_count, score);
                }
            }

            if (movings[i].ctype == MONEY) {  // ИСПРАВЛЕНО: == вместо =
                score += 100;
                delete_moving(movings, movings_count, i);
                i--;
                continue;
            }
        }
    }
}

void move_obj_horizontally(
    TObject* obj,
    TObject& mario,
    TObject* bricks, int bricks_count,
    TObject*& movings, int& movings_count,
    int& current_level,
    int& score
) {
    obj->x += obj->horiz_speed;

    for (int i = 0; i < bricks_count; i++) {
        if (is_collision(obj, &bricks[i])) {
            obj->x -= obj->horiz_speed;
            obj->horiz_speed = -obj->horiz_speed;
            return;
        }
    }

    if (obj->ctype == ENEMY) {
        TObject tmp = *obj;
        move_obj_vertically(&tmp, mario, bricks, bricks_count, movings, movings_count, current_level, score);
        if (tmp.is_fly) {
            obj->x -= obj->horiz_speed;
            obj->horiz_speed = -obj->horiz_speed;
        }
    }
}

bool is_pos_in_map(int x, int y) {
    return (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT);
}

void put_object_on_map(char** map, TObject obj) {
    int ix = static_cast<int>(round(obj.x));
    int iy = static_cast<int>(round(obj.y));
    int iWidth = static_cast<int>(round(obj.width));
    int iHeight = static_cast<int>(round(obj.height));

    for (int i = ix; i < (ix + iWidth); i++) {
        for (int j = iy; j < (iy + iHeight); j++) {
            if (is_pos_in_map(i, j)) {
                map[j][i] = obj.ctype;
            }
        }
    }
}

void move_map_horizontally(
    float dx,
    TObject& mario,
    TObject* bricks, int bricks_count,
    TObject* movings, int movings_count
) {
    mario.x -= dx;
    for (int i = 0; i < bricks_count; i++) {
        if (is_collision(&mario, &bricks[i])) {
            mario.x += dx;
            return;
        }
    }

    mario.x += dx;

    for (int i = 0; i < bricks_count; i++) {
        bricks[i].x += dx;
    }

    for (int i = 0; i < movings_count; i++) {
        movings[i].x += dx;
        //сдвигаем и центр патрулирования для летающих врагов
        if (movings[i].ctype == FLYING_ENEMY) {
            movings[i].origin_x += dx;
        }
    }
}

void put_score_on_map(char **map, int score) {
    char buffer[30];
    snprintf(buffer, sizeof(buffer), "Score: %d", score);
    int len = strlen(buffer);
    for (int i = 0; i < len; i++) {
        map[1][i + 5] = buffer[i];
    }
}

int main() {
    hide_cursor();
    
    // Инициализация карты
    char **map = new char* [MAP_HEIGHT];
    for (int i = 0; i < MAP_HEIGHT; i++) {
        map[i] = new char[MAP_WIDTH + 1];
        map[i][MAP_WIDTH] = '\0';
    }
    
    // Локальные переменные вместо глобальных
    TObject mario;
    TObject *bricks = nullptr;
    int bricks_count = 0;
    TObject *movings = nullptr;
    int movings_count = 0;
    int current_level = 1;
    int score = 0;
    
    create_current_level(current_level, mario, bricks, bricks_count, movings, movings_count, score);
    
    const int JUMP_KEY = VK_SPACE;
    const int EXIT_KEY = VK_ESCAPE;
    const char LEFT_KEY = 'A';
    const char RIGHT_KEY = 'D';
    
    do {
        clear_map(map, MAP_WIDTH, MAP_HEIGHT);
        
        if (!mario.is_fly && GetKeyState(JUMP_KEY) < 0) {
            mario.vert_speed = -1.0f;
        }
        if (GetKeyState(LEFT_KEY) < 0) {
            move_map_horizontally(1.0f, mario, bricks, bricks_count, movings, movings_count);
        }
        if (GetKeyState(RIGHT_KEY) < 0) {
            move_map_horizontally(-1.0f, mario, bricks, bricks_count, movings, movings_count);
        }
        if (mario.y > MAP_HEIGHT) {
            dead(mario, bricks, bricks_count, movings, movings_count, current_level, score);
        }
        
        move_obj_vertically(&mario, mario, bricks, bricks_count, movings, movings_count, current_level, score);
        mario_collision(mario, bricks, bricks_count, movings, movings_count, current_level, score);
        
        for (int i = 0; i < bricks_count; i++) {
            put_object_on_map(map, bricks[i]);
        }
        
        for (int i = 0; i < movings_count; i++) {
            if (movings[i].ctype == FLYING_ENEMY) {
                move_flying_enemy(&movings[i]);
            } else {
                move_obj_vertically(&movings[i], mario, bricks, bricks_count, movings, movings_count, current_level, score);
                move_obj_horizontally(&movings[i], mario, bricks, bricks_count, movings, movings_count, current_level, score);
            }
            if (movings[i].y > MAP_HEIGHT) {
                delete_moving(movings, movings_count, i);
                i--;
                continue;
            }
            put_object_on_map(map, movings[i]);
        }
        
        put_object_on_map(map, mario);
        put_score_on_map(map, score);
        
        set_cursor_position(0, 0);
        show_map(map, MAP_WIDTH, MAP_HEIGHT);
        
        Sleep(10);
    } while (GetKeyState(EXIT_KEY) >= 0);
    
    // Очистка памяти
    for (int i = 0; i < MAP_HEIGHT; i++) {
        delete[] map[i];
    }
    delete[] map;
    
    delete[] bricks;
    delete[] movings;
    
    return 0;
}