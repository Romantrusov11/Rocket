//
// Created by Павел Ятрушев on 12/7/24.
//

#pragma once
#include <FL/Enumerations.H>


struct Ball {
    int x = 100;
    int y = 80;
    int radius = 10;
    float xDirection = 2;
    float yDirection = 4;
    int score = 0;
    Fl_Color color = FL_RED;
} ball;


