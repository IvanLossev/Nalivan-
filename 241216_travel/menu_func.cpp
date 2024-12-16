#include "menu_func.hpp"

#include <iostream>

const chsng::menu_item* chsng::show_variants (const menu_item* current){
    for(int i = 0; i < current->children_count; i++){
        std::cout << current->child[i]->title << std::endl;
    }
    std::cout << current->child[0]->title << std::endl;
    std::cout << "Выбор >";

    int input;
    std::cin >> input;
    std::cout << std::endl;

    return current->child[input];
}

const chsng::menu_item* chsng::end (const menu_item* current){
    std::exit(0);
}

const chsng::menu_item* chsng::long_east (const menu_item* current) {
    std::cout << current->title << std::endl << std::endl;
    return current->par;
}

const chsng::menu_item* chsng::altai (const menu_item* current) {
    std::cout << current->title << std::endl << std::endl;
    return current->par;
}

const chsng::menu_item* chsng::gldn_ring (const menu_item* current) {
    std::cout << current->title << std::endl << std::endl;
    return current->par;
}

const chsng::menu_item* chsng::back_to_tours (const menu_item* current) {
    std::cout << current->title << std::endl << std::endl;
    return current->par->par;
}

const chsng::menu_item* chsng::vladik (const menu_item* current) {
    std::cout << current->title << std::endl << std::endl;
    return current->par->par;
}

const chsng::menu_item* chsng::Sakhalin (const menu_item* current) {
    std::cout << current->title << std::endl << std::endl;
    return current->par->par;
}

const chsng::menu_item* chsng::Khabarovsk (const menu_item* current) {
    std::cout << current->title << std::endl << std::endl;
    return current->par->par;
}

const chsng::menu_item* chsng::back_to_regions (const menu_item* current) {
    std::cout << current->title << std::endl << std::endl;
    return current->par->par;
}