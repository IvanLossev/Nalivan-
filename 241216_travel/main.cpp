#include <iostream>

#include "menu.hpp"
#include "menu_func.hpp"
#include "menu_item.hpp"    

int main(){
    std::cout << "Здравстввуйте! Выберите, где вы хотели бы провести выходные." << std::endl;

    const chsng::menu_item* current = &chsng::MAIN;
    do {
        current = current->func(current);
    } while (true);

    return 0;
}