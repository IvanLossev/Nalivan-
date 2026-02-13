#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <cstring>
#include <windows.h>
#include "Object.hpp"

const int MAP_WIDTH = 200;
const int MAP_HEIGHT = 50;

class Map {
private:
    char** map;

public:
    Map() {
        map = new char*[MAP_HEIGHT];
        for (int i = 0; i < MAP_HEIGHT; i++) {
            map[i] = new char[MAP_WIDTH + 1];
            map[i][MAP_WIDTH] = '\0';
        }
    }

    ~Map() {
        for (int i = 0; i < MAP_HEIGHT; i++) {
            delete[] map[i];
        }
        delete[] map;
    }

    void clear() {
        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < MAP_WIDTH; j++) {
                map[i][j] = ' '; // Ensure the map is cleared properly
            }
            map[i][MAP_WIDTH] = '\0';
        }
    }

    void display() {
        // Reset cursor position to the top-left corner
        COORD coord = {0, 0};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        for (int j = 0; j < MAP_HEIGHT; j++) {
            std::cout << map[j] << std::endl;
        }
    }

    void putObject(const Object& obj) {
        int ix = static_cast<int>(round(obj.x));
        int iy = static_cast<int>(round(obj.y));
        int iWidth = static_cast<int>(round(obj.width));
        int iHeight = static_cast<int>(round(obj.height));

        for (int i = ix; i < (ix + iWidth); i++) {
            for (int j = iy; j < (iy + iHeight); j++) {
                if (isPositionInMap(i, j)) {
                    map[j][i] = obj.ctype; // Ensure object type is correctly placed
                }
            }
        }
    }

    bool isPositionInMap(int x, int y) {
        return (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT);
    }

    void putScore(int score) {
        char buffer[30];
        snprintf(buffer, sizeof(buffer), "Score: %d", score);
        int len = strlen(buffer);
        for (int i = 0; i < len; i++) {
            map[1][i + 5] = buffer[i];
        }
    }
};

#endif