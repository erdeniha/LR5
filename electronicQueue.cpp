#include "electronicQueue.h"
#include <iostream>
#include <string>
#include <vector>

void electronicQueue() {
    int numWindows = 0;
    std::cout << "Введите количество окон: ";
    if (!(std::cin >> numWindows) || numWindows <= 0) {
        std::cout << "Ошибка: Неверное количество окон\n";
        return;
    }

    std::vector<Window> windows(numWindows);
    int currentWindowId = 1;
    for (auto& window : windows) {
        window.id = currentWindowId;
        currentWindowId++;
    }

    std::vector<Visitor> queue;
    int ticketCounter = 1; 
    std::string command;

    while (true) {
        std::cout << ">>> ";
        if (!(std::cin >> command)) {
            break;
        }

        if (command == "ENQUEUE") {
            int duration = 0;
            std::cin >> duration;

            if (duration <= 0) {
                std::cout << "Ошибка: Время должно быть больше 0\n";
                continue;
            }

            std::string ticketNumber = "T";
            if (ticketCounter < 10) {
                ticketNumber += "00";
            } else if (ticketCounter < 100) {
                ticketNumber += "0";
            }
            ticketNumber += std::to_string(ticketCounter);
            ticketCounter++;


            queue.push_back(Visitor{ticketNumber, duration});
            std::cout << ticketNumber << "\n";
        } 
        else if (command == "DISTRIBUTE") {
            for (const auto& visitor : queue) {
                Window* bestWindow = &windows[0];

                for (auto& window : windows) {
                    if (window.totalTime < bestWindow->totalTime) {
                        bestWindow = &window;
                    }

                }

                bestWindow->totalTime += visitor.duration;
                bestWindow->tickets.push_back(visitor.ticketNumber);
            }


            for (const auto& window : windows) {
                std::cout << "Окно " << window.id << " (" << window.totalTime << " минут): ";
                bool isFirst = true;
                for (const auto& ticket : window.tickets) {
                    if (!isFirst) {
                        std::cout << ", ";
                    }
                    std::cout << ticket;
                    isFirst = false;
                }
                std::cout << "\n";
            }

            break;
        } 
        else {
            std::cout << "Ошибка: Неизвестная команда\n";
        }
    }
}