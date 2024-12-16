//
// Created by Павел Ятрушев on 12/7/24.
//

#pragma once
#include <FL/Enumerations.H>

struct Rocket2 {
    Rocket2() : x(200), y(30), width(100), height(15), xDirection(25), color(FL_GREEN) {}
    int x = 200;
    int y = 30;
    int width = 100;
    int height = 15;
    int xDirection = 35;
    Fl_Color color = FL_GREEN;
} rocket2;
