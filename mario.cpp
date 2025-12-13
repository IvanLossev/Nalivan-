#include <cstring>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>		

const char BRICK = '#';
const char EMPTY_BOX = '-';
const char ENEMY = 'o';
const char FULL_BOX = '?';
const char MARIO = '@';
const char MONEY = '$';
const char WIN_BRICK = '+';

struct TObject {
	float x, y;
	float width, height;
	float vert_speed;
	float horiz_speed;
	bool is_fly;
	char ctype;
};

void clear_map(char **map, const int width, const int height) {
	for (int i = 0; i < width; i++) {
		map[0][i] = ' ';
	}
	map[0][width] = '\0';
	for (int j = 1; j < height; j++) {
		sprintf(map[j], map[0]);
	}
}

void show_map(char **map, const int width, const int height) {
	map[height - 1][width - 1] = '\0';
	for (int j = 0; j < height; j++) {
		std::cout << map[j];
	}
}


void set_obj_position(TObject* obj, const float xpos, const float ypos) {
	obj->x = xpos;
	obj->y = ypos;
}

void init_object(TObject* obj, const float xpos, const float ypos, const float owidth, const float oheight, const char inType) {
    set_obj_position(obj, xpos, ypos);
 	obj->width = owidth;
 	obj->height = oheight;
 	obj->vert_speed = 0;
 	obj->ctype = inType;
 	obj->horiz_speed = 0.2;
}

void CreateLevel(int lvl);
TObject* GetNewMoving();

void Dead() {
    system("color 4F");
    Sleep(500);
    CreateLevel(level);
}

BOOL IsCollision(TObject o1, TObject o2);

void VertMoveObject(TObject* obj) {
    (*obj).IsFly = TRUE;
    (*obj).vertSpeed += 0.05;
    SetObjectPos(obj, (*obj).x, (*obj).y + (*obj).vertSpeed);

    for (int i = 0; i < brickLength; i++) {
        if (IsCollision(*obj, brick[i])) {

            if (obj[0].vertSpeed > 0) {
                obj[0].IsFly = FALSE;
            }

            if ((brick[i].cType == '?') && (obj[0].vertSpeed < 0) && (obj == &mario)) {
                brick[i].cType = '-';
                InitObject(GetNewMoving(), brick[i].x, brick[i].y-3, 3, 2, '$');
                moving[movingLength - 1].vertSpeed = -0.7;
            }

            (*obj).y -= (*obj).vertSpeed;
            (*obj).vertSpeed = 0;
            if (brick[i].cType == '+') {
                level++;
                if (level > maxLvl) level = 1;
                system("color 2F");
                Sleep(500);
                CreateLevel(level);
                
            }
        }
    }
}

//void DeleteMoving(int i) {
//    movingLength--;
//    moving[i] = moving[movingLength];
//    moving = new TObject[movingLength];
//}

void DeleteMoving(int i) {
    if (movingLength <= 0) return;

    movingLength--;

    // заменяем удаляемый элемент последним
    moving[i] = moving[movingLength];

    // уменьшаем массив
    TObject* newArr = new TObject[movingLength];
    for (int j = 0; j < movingLength; j++)
        newArr[j] = moving[j];

    delete[] moving;
    moving = newArr;
}

void MarioCollision() {

    for (int i = 0; i < movingLength; i++) {

        if (IsCollision(mario, moving[i])) {
            if (moving[i].cType == 'o') {
                if ((mario.IsFly = TRUE) && (mario.vertSpeed > 0) && (mario.y + mario.height < moving[i].y + moving[i].height * 0.5)) {
                    score += 50;
                    DeleteMoving(i);
                    i--;
                    continue;
                }
                else {
                    Dead();
                }
            }
            if (moving[i].cType == '$') {
                score += 100;
                DeleteMoving(i);
                i--;
                continue;
            }


        }
    }
}

void HorizonMoveObject(TObject *obj) {
    obj[0].x += obj[0].horizSpeed; //[0] - обращение к адресу указателя (вместо *)

    for (int i = 0; i < brickLength; i++) {
        if (IsCollision(obj[0], brick[i])) {
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = -obj[0].horizSpeed;
            return;
        }
    }~~


    if (obj[0].cType == 'o') {
        TObject tmp = *obj; //копия объекта
        VertMoveObject(&tmp);
        if (tmp.IsFly == TRUE) {
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = -obj[0].horizSpeed;
        }
    }
}

BOOL IsPosInMap(int x, int y) {
    return ((x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight));
}

void PutObjectOnMap(TObject obj) {
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);

    int iWidth = (int)round(obj.width);
    int iHeight = (int)round(obj.height);

    for (int i = ix; i < (ix + iWidth); i++)
        for (int j = iy; j < (iy + iHeight); j++)
            if (IsPosInMap(i, j))
                map[j][i] = obj.cType;

}


void setCur(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void HorizonMoveMap(float dx) {
    mario.x -= dx;
    for (int i = 0; i < brickLength; i++) {
        if (IsCollision(mario, brick[i])) {
            mario.x += dx;
            return;
        }
    }

    mario.x += dx;

    for (int i = 0; i < brickLength; i++)
        brick[i].x += dx;

    for (int i = 0; i < movingLength; i++)
        moving[i].x += dx;
}

BOOL IsCollision(TObject o1, TObject o2) {
    return ((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) && ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height));
}

TObject* GetNewBrick() {
    brickLength++;

    // новый массив большего размера
    TObject* newArr = new TObject[brickLength];

    // копируем старые элементы
    for (int i = 0; i < brickLength - 1; i++)
        newArr[i] = brick[i];

    // освобождаем старую память
    delete[] brick;

    // обновляем указатель
    brick = newArr;

    // возвращаем указатель на новый (последний) элемент
    return &brick[brickLength - 1];
}

TObject* GetNewMoving() {
    movingLength++;

    // создаем новый массив большего размера
    TObject* newArr = new TObject[movingLength];

    // копируем старые элементы
    for (int i = 0; i < movingLength - 1; i++)
        newArr[i] = moving[i];

    // освобождаем старую память
    delete[] moving;

    // обновляем указатель
    moving = newArr;

    // возвращаем указатель на новый (последний) элемент
    return &moving[movingLength - 1];
}

void ScoreOnMap() {

    char c[30];
    sprintf(c, "Score: %d", score);
    int len = strlen(c);
    for (int i = 0; i < len; i++) {
        map[1][i + 5] = c[i];
    }


}

void CreateLevel(int lvl) {
    score = 0;
    system("color 9F");

    brickLength = 0;
    movingLength = 0;

    InitObject(&mario, 39, 10, 3, 3, '0');

    if (lvl == 1) {
        InitObject(GetNewBrick(), 20, 20, 40, 5, '#');
        InitObject(GetNewBrick(), 60, 15, 40, 10, '#');
        InitObject(GetNewBrick(), 100, 20, 20, 5, '#');
        InitObject(GetNewBrick(), 120, 15, 10, 10, '#');
        InitObject(GetNewBrick(), 150, 20, 40, 5, '#');
            InitObject(GetNewBrick(), 30, 10, 5, 3, '?');
            InitObject(GetNewBrick(), 50, 10, 5, 3, '?');
            InitObject(GetNewBrick(), 60, 5, 10, 3, '-');
            InitObject(GetNewBrick(), 70, 5, 5, 3, '?');
            InitObject(GetNewBrick(), 75, 5, 5, 3, '-');
            InitObject(GetNewBrick(), 80, 5, 5, 3, '?');
            InitObject(GetNewBrick(), 85, 5, 10, 3, '-');
        InitObject(GetNewBrick(), 210, 15, 10, 10, '+');

        InitObject(GetNewMoving(), 25, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 80, 10, 3, 2, 'o');
    }

    if (lvl == 2 ){
        InitObject(GetNewBrick(), 20, 20, 40, 5, '#');
        InitObject(GetNewBrick(), 60, 15, 10, 10, '#');
        InitObject(GetNewBrick(), 80, 20, 20, 5, '#');
        InitObject(GetNewBrick(), 120, 15, 10, 10, '#');
        InitObject(GetNewBrick(), 150, 20, 40, 5, '#');
        InitObject(GetNewBrick(), 210, 15, 10, 10, '+');

        moving = new TObject[movingLength];
        InitObject(GetNewMoving(), 25, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 80, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 65, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 120, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 160, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 175, 10, 3, 2, 'o');
    }

    if (lvl == 3) {
        brick = new TObject[brickLength];
        InitObject(GetNewBrick(), 20, 20, 40, 5, '#');
        InitObject(GetNewBrick(), 80, 20, 15, 5, '#');
        InitObject(GetNewBrick(), 120, 15, 15, 10, '#');
        InitObject(GetNewBrick(), 160, 10, 15, 15, '+');

        moving = new TObject[movingLength];
        InitObject(GetNewMoving(), 25, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 50, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 80, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 90, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 120, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 130, 10, 3, 2, 'o');
    }

    maxLvl = 3;
}

int main()
{
    CreateLevel(level);
    

    do {
        ClearMap();

        if ((mario.IsFly == FALSE) && (GetKeyState(VK_SPACE) < 0)) mario.vertSpeed = -1;
        if (GetKeyState('A') < 0) HorizonMoveMap(1);
        if (GetKeyState('D') < 0) HorizonMoveMap(-1);

        if (mario.y >= mapHeight) Dead();

        VertMoveObject(&mario);
        MarioCollision();
        for (int i = 0; i < brickLength; i++) {
            PutObjectOnMap(brick[i]);
        }
        for (int i = 0; i < movingLength; i++) {
            VertMoveObject(moving+i);
            HorizonMoveObject(moving+i);
            if (moving[i].y > mapHeight) {
                DeleteMoving(i);
                i--;
                continue;
            }
            PutObjectOnMap(moving[i]);
        }

        PutObjectOnMap(mario);
        ScoreOnMap();
        setCur(0, 0);
        ShowMap();

        Sleep(10);
    } while (GetKeyState(VK_ESCAPE) >= 0);
    return 0;
}