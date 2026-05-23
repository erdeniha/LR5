#include <iostream>
#include <string>
#include "electronicQueue.h"
#include "friendshipAccountingSystem.h"
#include "inventoryAccounting.h"
#include "trainTimetable.h"

int main() {
    int taskChoice;
    
    while (true) {
        std::cout << "Выберите задание:\n";
        std::cout << "1 - Учет товаров на складе\n";
        std::cout << "2 - Электронная очередь\n";
        std::cout << "3 - График движения поездов\n";
        std::cout << "4 - Учет дружеских связей\n";
        std::cout << "0 - Выход из программы\n";
        
        if (!(std::cin >> taskChoice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n'); 
            continue;
        }

        switch (taskChoice) {
            case 0: 
                return 0;
            case 1: 
                inventoryAccounting(); 
                break;
            case 2: 
                electronicQueue(); 
                break;
            case 3: 
                trainTimetable(); 
                break;
            case 4: 
                friendshipAccountingSystem(); 
                break;
            default: 
                std::cout << "Нет такого задания.\n";
        }
    }
    
    return 0;
}