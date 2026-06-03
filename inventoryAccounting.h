#pragma once
#include <string>

const int ZONES = 3;    
const int RACKS = 20;  
const int SECTIONS = 5; 
const int SHELVES = 2; 
const int ALLCELL = ZONES * RACKS * SECTIONS * SHELVES * 10;
struct Cell {
    std::string itemName = "";
    int quantity = 0;
};

void inventoryAccounting();
