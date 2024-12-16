//
// Created by Павел Ятрушев on 12/7/24.
//

#pragma once
#include <FL/Enumerations.H>

struct Rocket {
    Rocket() : x(200), y(450), width(100), height(15), xDirection(25) {}
    int x = 200;
    int y = 450;
    int width = 100;
    int height = 15;
    int xDirection = 35;
    Fl_Color color = FL_DARK_BLUE;
} rocket;
