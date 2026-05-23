#pragma once
#include <string>
#include <vector>


struct Window {
    int id = 0;                          
    int totalTime = 0;                  
    std::vector<std::string> tickets;    
};


struct Visitor {
    std::string ticketNumber;           
    int duration = 0;                   
};

void electronicQueue();

