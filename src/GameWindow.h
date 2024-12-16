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
    
    GameWindow(int width = 500, int height = 500, const char* title = "Rocket");
    //frontend functions:
    void draw() override;
    void drawBackground();
    void drawRocket();
    void drawRocket2();
    void drawBall();
    void drawEndGameMessage();
    
    static void startButtonCallback(Fl_Widget*, void* data);
    static void restartButtonCallback(Fl_Widget*, void* data);
    int handle(int event) override;
    
    
    //backend functions:
    void handleKeys();
    void startGame();
    void restartGame();
    void clampRocketPosition();
    void clampRocket2Position();
    void update();
    void updateBall();
    static void Timer_CB(void * data);
    

    Fl_JPEG_Image* bgImage;
    Fl_Button* startButton;
    Fl_Button* restartButton;
    bool gameInProgress = false;
    bool gameOver = false;
    bool victory= false;
    std::string winner = "";
    std::set<int> activeKeys;
// private:
//     Fl_JPEG_Image* bgImage;
//     Fl_Button* startButton;
//     Fl_Button* restartButton;
//     bool gameInProgress = false;
//     bool gameOver = false;
//     bool victory= false;
//     std::string winner = "";
//     std::set<int> activeKeys;
};
