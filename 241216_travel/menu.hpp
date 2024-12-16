#pragma once

namespace chsng{
    struct menu_item
    {
        const char* const title;
        const menu_item* (*func)(const menu_item* current);
        const menu_item* par;
        const menu_item* const* child;
        const int children_count;
    };
    
}