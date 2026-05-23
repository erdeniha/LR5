#include "trainTimetable.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

void trainTimetable() {
    std::map<std::string, std::vector<std::string>> train_to_towns;
    std::map<std::string, std::vector<std::string>> town_to_trains;
    std::string command;

    while (true) {
        std::cout << ">>> ";
        if (!(std::cin >> command)) {
            break;
        }

        if (command == "EXIT") {
            break;
        }

        Type cmdType = Type::UNKNOWN;
        if (command == "CREATE_TRAIN") cmdType = Type::CREATE_TRAIN;
        else if (command == "TRAINS_FOR_TOWN") cmdType = Type::TRAINS_FOR_TOWN;
        else if (command == "TOWNS_FOR_TRAIN") cmdType = Type::TOWNS_FOR_TRAIN;
        else if (command == "TRAINS") cmdType = Type::TRAINS;

        if (cmdType == Type::UNKNOWN) {
            std::cout << "Ошибка: Неизвестная команда\n";
            continue;
        }

        if (cmdType == Type::CREATE_TRAIN) {
            std::string train;
            int n = 0;
            std::cin >> train >> n;

            std::vector<std::string> towns(n);
            for (auto& town : towns) {
                std::cin >> town;
            }

            if (train_to_towns.count(train) > 0) {
                std::cout << "Ошибка: Поезд с именем " << train << " уже создан\n";
                continue;
            }

            if (n < 2) {
                std::cout << "Ошибка: Поезд не может быть создан с одной остановкой\n";
                continue;
            }

            bool has_duplicates = false;
            std::vector<std::string> seen;
            for (const auto& town : towns) {
                for (const auto& s : seen) {
                    if (s == town) {
                        has_duplicates = true;
                    }
                }
                seen.push_back(town);
            }

            if (has_duplicates) {
                std::cout << "Ошибка: Поезд не может быть создан с двумя одинаковыми городами\n";
                continue;
            }

            train_to_towns[train] = towns;
            for (const auto& town : towns) {
                town_to_trains[town].push_back(train);
                std::sort(town_to_trains[town].begin(), town_to_trains[town].end());
            }
            std::cout << "Поезд " << train << " создан\n";
        }
        else if (cmdType == Type::TRAINS_FOR_TOWN) {
            std::string town;
            std::cin >> town;

            if (town_to_trains.count(town) == 0) {
                std::cout << "Ошибка: Город " << town << " не найден\n";
            } else {
                std::cout << "Поезда через город " << town << ": ";
                bool first = true;
                for (const auto& t : town_to_trains[town]) {
                    if (!first) {
                        std::cout << ", ";
                    }
                    std::cout << t;
                    first = false;
                }
                std::cout << "\n";
            }
        }
        else if (cmdType == Type::TOWNS_FOR_TRAIN) {
            std::string train;
            std::cin >> train;

            if (train_to_towns.count(train) == 0) {
                std::cout << "Ошибка: Поезд " << train << " не найден\n";
            } else {
                for (const auto& town : train_to_towns[train]) {
                    std::cout << "Город " << town << ": ";
                    bool has_others = false;
                    bool first = true;
                    for (const auto& other_train : town_to_trains[town]) {
                        if (other_train != train) {
                            if (!first) {
                                std::cout << ", ";
                            }
                            std::cout << other_train;
                            first = false;
                            has_others = true;
                        }
                    }
                    if (!has_others) {
                        std::cout << "-";
                    }
                    std::cout << "\n";
                }
            }
        }
        else if (cmdType == Type::TRAINS) {
            if (train_to_towns.empty()) {
                std::cout << "Ошибка: Поезда не найдены\n";
            } else {
                for (const auto& [train, towns] : train_to_towns) {
                    std::cout << "Поезд " << train << ": ";
                    bool first = true;
                    for (const auto& town : towns) {
                        if (!first) {
                            std::cout << ", ";
                        }
                        std::cout << town;
                        first = false;
                    }
                    std::cout << "\n";
                }
            }
        }
    }
}