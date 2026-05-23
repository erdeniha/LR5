#pragma once
#include <string>

struct Cell {
    std::string itemName = "";
    int quantity = 0;
};

void inventoryAccounting();
