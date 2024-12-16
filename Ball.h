//
// Created by Павел Ятрушев on 12/7/24.
//

#pragma once
#include <FL/Enumerations.H>


struct Ball {
    Ball() : x(), y(), radius(10), xDirection(2), yDirection(4), score(0), color(FL_RED) {}
    float x = 100;
    float y = 80;
    int radius = 10;
    float xDirection = 2;
    float yDirection = 4;
    int score = 0;
    Fl_Color color = FL_RED;
} ball;


