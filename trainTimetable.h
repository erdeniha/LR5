#pragma once

#include <string>
#include <vector>
#include <map>

enum class Type {
    CREATE_TRAIN,
    TRAINS_FOR_TOWN,
    TOWNS_FOR_TRAIN,
    TRAINS,
    UNKNOWN
};

void trainTimetable();