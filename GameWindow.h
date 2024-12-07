//
// Created by Павел Ятрушев on 12/7/24.
//

#pragma once
#include <set>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_JPEG_Image.H>

const int GAME_WIDTH = 500;
const int GAME_HEIGHT = 500;



class GameWindow : public  Fl_Double_Window {
    public:
    GameWindow(int width, int height, const char* title);
    void draw() override;
    void drawBackground();
    void drawRocket();
    void drawRocket2();
    void drawBall();
    void drawEndGameMessage();
    void startGame();
    void restartGame();
    static void startButtonCallback(Fl_Widget*, void* data);
    static void restartButtonCallback(Fl_Widget*, void* data);
    int handle(int event) override;
    void handleKeys();
    void clampRocketPosition();
    void clampRocket2Position();
    void update();
    void updateBall();
    static void Timer_CB(void * data);
private:
    Fl_JPEG_Image* bgImage;
    Fl_Button* startButton;
    Fl_Button* restartButton;
    bool gameInProgress;
    bool gameOver;
    bool victory;
    std::string winner;
    std::set<int> activeKeys;
};
