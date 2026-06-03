#include "inventoryAccounting.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

void inventoryAccounting() {
    std::map<std::string, Cell> warehouse;

    for (int z = 0; z < ZONES; ++z) {
        char zoneChar = 'A' + z; 
        for (int r = 1; r <= RACKS; ++r) {
            for (int s = 1; s <= SECTIONS; ++s) {
                for (int sh = 1; sh <= SHELVES; ++sh) {
                    std::string address = zoneChar + std::to_string(r) + std::to_string(s) + std::to_string(sh);
                    warehouse[address] = {"", 0};
                }
            }
        }
    }

    std::string command;
    while (true) {
        std::cout << ">>> ";
        if (!(std::cin >> command)) {
            break;
        }

        if (command == "ADD") {
            std::string itemName;
            int quantity;
            std::string address;
            std::cin >> itemName >> quantity >> address;

            auto it = warehouse.find(address);
            if (it == warehouse.end()) {
                std::cout << "Ошибка: Неверный адрес ячейки\n";
            } else {
                Cell& cell = it->second;
                if (cell.quantity > 0 && cell.itemName != itemName) {
                    std::cout << "Ошибка: Ячейка " << address << " занята товаром " << cell.itemName << "\n";
                } else if (cell.quantity + quantity > 10) {
                    std::cout << "Ошибка: Превышена вместимость ячейки (максимум 10)\n";
                } else {
                    cell.itemName = itemName;
                    cell.quantity += quantity;
                    std::cout << "Добавлено " << quantity << " " << itemName << " в " << address << "\n";
                }
            }
        } 
        else if (command == "REMOVE") {
            std::string itemName;
            int quantity;
            std::string address;
            std::cin >> itemName >> quantity >> address;

            auto it = warehouse.find(address);
            if (it == warehouse.end()) {
                std::cout << "Ошибка: Неверный адрес ячейки\n";
            } else {
                Cell& cell = it->second;
                if (cell.quantity == 0 || cell.itemName != itemName) {
                    std::cout << "Ошибка: Товар " << itemName << " не найден в ячейке " << address << "\n";
                } else if (cell.quantity < quantity) {
                    std::cout << "Ошибка: Недостаточно товаров для удаления\n";
                } else {
                    cell.quantity -= quantity;
                    std::cout << "Удалено " << quantity << " " << itemName << " (остаток: " << cell.quantity << ")\n";
                    if (cell.quantity == 0) {
                        cell.itemName = "";
                    }
                }
            }
        } 
        else if (command == "INFO") {
            int totalUnits = 0;
            int zoneAUnits = 0;
            int zoneBUnits = 0;
            int zoneCUnits = 0;

            for (const auto& [address, cell] : warehouse) {
                totalUnits += cell.quantity;
                if (address[0] == 'A') zoneAUnits += cell.quantity;
                if (address[0] == 'B') zoneBUnits += cell.quantity;
                if (address[0] == 'C') zoneCUnits += cell.quantity;
            }

            double totalOccupancy = (static_cast<double>(totalUnits) / ALLCELL) * 100.0;
            double zoneAOccupancy = (static_cast<double>(zoneAUnits) / (ALLCELL / ZONES)) * 100.0;
            double zoneBOccupancy = (static_cast<double>(zoneBUnits) / (ALLCELL / ZONES)) * 100.0;
            double zoneCOccupancy = (static_cast<double>(zoneCUnits) / (ALLCELL / ZONES)) * 100.0;

            std::cout << std::fixed << std::setprecision(2);
            std::cout << "Загруженность склада: " << totalOccupancy << " %\n";
            std::cout << "Загруженность зоны A: " << zoneAOccupancy << " %\n";
            std::cout << "Загруженность зоны B: " << zoneBOccupancy << " %\n";
            std::cout << "Загруженность зоны C: " << zoneCOccupancy << " %\n";

            std::cout << "Заполненные ячейки:\n";
            for (const auto& [address, cell] : warehouse) {
                if (cell.quantity > 0) {
                    std::cout << address << ": " << cell.itemName << " (" << cell.quantity << ")\n";
                }
            }

            std::cout << "Пустые ячейки:\n";
            bool first = true;
            for (const auto& [address, cell] : warehouse) {
                if (cell.quantity == 0) {
                    if (!first) {
                        std::cout << ", ";
                    }
                    std::cout << address;
                    first = false;
                }
            }
            std::cout << "\n";
        } 
        else if (command == "EXIT") {
            break;
        } 
        else {
            std::cout << "Ошибка: Неизвестная команда\n";
        }
    }
}