#pragma once

#include "menu.hpp"

namespace chsng{
    const menu_item* show_variants (const menu_item* current);
    const menu_item* end (const menu_item* current);

    const menu_item* long_east (const menu_item* current);
    const menu_item* altai (const menu_item* current);
    const menu_item* gldn_ring (const menu_item* current);
    const menu_item* back_to_tours (const menu_item* current);
    
    const menu_item* vladik (const menu_item* current);
    const menu_item* Sakhalin (const menu_item* current);
    const menu_item* Khabarovsk (const menu_item* current);
    const menu_item* back_to_regions (const menu_item* current);
    
}