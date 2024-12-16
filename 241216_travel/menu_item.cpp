#include "menu_item.hpp"
#include "menu_func.hpp"

const chsng::menu_item chsng::VLADIK = {
    "1 - Владдивосток", chsng::vladik, &chsng::LONG_EAST
};
const chsng::menu_item chsng::SAKHALIN = {
    "2 - Сахалин", chsng::Sakhalin, &chsng::LONG_EAST
};
const chsng::menu_item chsng::KHABAROVSK = {
    "3 - Хабаровск", chsng::Khabarovsk, &chsng::LONG_EAST
};
const chsng::menu_item chsng::BACK_TO_REGIONS = {
    "0 - К регионам", chsng::back_to_regions, &chsng::LONG_EAST
};

namespace {
    const chsng::menu_item* long_east_children[] = {
        &chsng::BACK_TO_REGIONS,
        &chsng::VLADIK,
        &chsng::SAKHALIN,
        &chsng::KHABAROVSK
    };
    const int size_long_east = sizeof(long_east_children) / sizeof(long_east_children[0]);
}

const chsng::menu_item chsng::LONG_EAST = {
    "1 - Дальний восток", chsng::show_variants, &chsng::SHOW_VARIANTS, long_east_children, size_long_east
};
const chsng::menu_item chsng::ALTAI = {
    "2 - Алтай", chsng::altai, &chsng::SHOW_VARIANTS
};
const chsng::menu_item chsng::GLDN_RING = {
    "3 - Золотое Кольцо России", chsng::gldn_ring, &chsng::SHOW_VARIANTS
};
const chsng::menu_item chsng::BACK_TO_TOURS = {
    "0 - Выйти в главное меню", chsng::back_to_tours, &chsng::SHOW_VARIANTS
};

namespace{
    const chsng::menu_item* regions_children[] = {
        &chsng::BACK_TO_TOURS,
        &chsng::LONG_EAST,
        &chsng::ALTAI,
        &chsng::GLDN_RING
    };
    const int size_regions = sizeof(regions_children) / sizeof(regions_children[0]);
}

const chsng::menu_item chsng::SHOW_VARIANTS = {
    "1 - Путешествовать по Росии", chsng::show_variants, &chsng::MAIN, regions_children, size_regions
};

const chsng::menu_item chsng::END = {
    "0 - Закончить путешествие", chsng::end, &chsng::MAIN
};

namespace {
    const chsng::menu_item* main_children[] = {
        &chsng::END, 
        &chsng::SHOW_VARIANTS
    };
    const int size_main = sizeof(main_children) / sizeof(main_children[0]);
}

const chsng::menu_item chsng::MAIN = {
    nullptr, chsng::show_variants, nullptr, main_children, size_main 
};