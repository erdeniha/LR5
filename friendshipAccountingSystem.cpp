#include "friendshipAccountingSystem.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

void friendshipAccountingSystem() {
    int n = 0;
    std::cout << "Введите количество запросов (N): ";
    if (!(std::cin >> n)) {
        return;
    }

    std::map<std::string, std::vector<std::string>> friendship;

    for (int k = 0; k < n; ++k) {
        std::string command;
        std::cout << ">>> ";
        if (!(std::cin >> command)) {
            break;
        }

        if (command == "FRIENDS") {
            std::string i, j;
            std::cin >> i >> j;

            if (i == j) {
                continue;
            }

            bool already_friends = false;
            for (const auto& friend_name : friendship[i]) {
                if (friend_name == j) {
                    already_friends = true;
                    break;
                }
            }

            if (already_friends) {
                std::cout << i << " и " << j << " уже друзья\n";
            } else {
                friendship[i].push_back(j);
                friendship[j].push_back(i);
                std::cout << i << " и " << j << " теперь друзья\n";
            }
        } 
        else if (command == "COUNT") {
            std::string i;
            std::cin >> i;
            std::cout << friendship[i].size() << "\n";
        } 
        else if (command == "QUESTION") {
            std::string i, j;
            std::cin >> i >> j;

            if (i == j) {
                std::cout << "Yes\n";
                continue;
            }

            bool is_friend = false;
            for (const auto& friend_name : friendship[i]) {
                if (friend_name == j) {
                    is_friend = true;
                    break;
                }
            }

            if (is_friend) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        }
    }
}