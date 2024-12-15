#include "Ball.h"
#include "GameWindow.h"
#include "Rocket.h"
#include "Rocket2.h"
#include <FL/Fl.H>

void GameWindow::Timer_CB(void* data) {
    GameWindow* gw = (GameWindow*)data;
    gw->update();
}


void GameWindow::startGame() {
    ball.x = 100;
    ball.y = 80;
    ball.score = 0;
    rocket.x = 200;
    rocket2.x = 200;
    gameOver = false;
    victory = false;
    gameInProgress = true;
    winner = "";

    startButton->hide();
    restartButton->hide();

    redraw();
    Fl::add_timeout(1.0 / 90, Timer_CB, this);
}

void GameWindow::restartGame() {
    ball.x = 100;
    ball.y = 80;
    ball.radius = 10;
    ball.xDirection = 2;
    ball.yDirection = 4;
    ball.score = 0;

    rocket.x = 200;
    rocket.y = 450;
    rocket2.x = 200;
    rocket2.y = 30;

    gameOver = false;
    victory = false;
    gameInProgress = true;
    winner = "";

    restartButton->hide();
    startButton->hide();

    redraw();
    Fl::add_timeout(1.0 / 60, Timer_CB, this);
}

void GameWindow::handleKeys(){
        float prognoz_coordinate_x = ball.x + ball.xDirection;
        float prognoz_coordinate_y = ball.y + ball.yDirection;
        
        if (activeKeys.count(FL_Left)) {
            int  prognoz_rocket = rocket.x - rocket.xDirection;
            if (prognoz_coordinate_x > prognoz_rocket && prognoz_coordinate_x < prognoz_rocket + rocket.width && prognoz_coordinate_y > rocket.y && prognoz_coordinate_y < rocket.y + rocket.height ){
                ball.x = prognoz_rocket - ball.radius;
                if (ball.x < 0){
                    ball.y = rocket.y - ball.radius;
                    ball.x = rocket.x;
                }
                
            };
            rocket.x -= rocket.xDirection;  // Перемещение ракетки 1 влево
        }
        if (activeKeys.count(FL_Right)) {
            int prognoz_rocket = rocket.x + rocket.xDirection;
            if (prognoz_coordinate_x > prognoz_rocket && prognoz_coordinate_x < prognoz_rocket + rocket.width && prognoz_coordinate_y > rocket.y && prognoz_coordinate_y < rocket.y + rocket.height ){
                ball.x = prognoz_rocket + rocket.width + ball.radius;
                if (ball.x > GAME_WIDTH){
                    ball.y = rocket.y - ball.radius;
                    ball.x = rocket.x + rocket.width;
                }
            };
            rocket.x += rocket.xDirection;  // Перемещение ракетки 1 вправо
        }
        if (activeKeys.count('a')) {
            int prognoz_rocket2 = rocket2.x - rocket2.xDirection;
            if (prognoz_coordinate_x > prognoz_rocket2 && prognoz_coordinate_x < prognoz_rocket2 + rocket.width && prognoz_coordinate_y > rocket.y && prognoz_coordinate_y < rocket.y + rocket.height ){
                ball.x = prognoz_rocket2 - ball.radius;
                if (ball.x < 0){
                    ball.y = rocket2.y + rocket.height + ball.radius;
                    ball.x = rocket2.x;
                }
            };
            rocket2.x -= rocket2.xDirection;  // Перемещение ракетки 2 влево
        }
        if (activeKeys.count('d')) {
            int prognoz_rocket2 = rocket2.x + rocket2.xDirection;
            if (prognoz_coordinate_x > prognoz_rocket2 && prognoz_coordinate_x < prognoz_rocket2 + rocket.width && prognoz_coordinate_y > rocket.y && prognoz_coordinate_y < rocket.y + rocket.height ){
                 ball.x = prognoz_rocket2 + rocket2.width + ball.radius;
                if (ball.x > GAME_WIDTH){
                    ball.y = rocket2.y + rocket2.height + ball.radius;
                    ball.x = rocket2.x + rocket.width;
                }
            };
            rocket2.x += rocket2.xDirection;  // Перемещение ракетки 2 вправо
        }

        clampRocketPosition();
        clampRocket2Position();
    }


void GameWindow::clampRocketPosition() {
    if (rocket.x < 0) rocket.x = 0;
    if (rocket.x + rocket.width > GAME_WIDTH) rocket.x = GAME_WIDTH - rocket.width;
}

void GameWindow::clampRocket2Position() {
    if (rocket2.x < 0) rocket2.x = 0;
    if (rocket2.x + rocket2.width > GAME_WIDTH) rocket2.x = GAME_WIDTH - rocket2.width;
}

void GameWindow::updateBall() {
        ball.x += ball.xDirection;
        ball.y += ball.yDirection;

        if (ball.y + ball.radius > GAME_HEIGHT || ball.y - ball.radius < 0) {
            ball.yDirection = -ball.yDirection;
        }
        if (ball.x + ball.radius > GAME_WIDTH || ball.x - ball.radius < 0) {
            ball.xDirection = -ball.xDirection;
        }
        // Столкновение с нижней ракеткой (rocket)
    if (ball.y + ball.radius > rocket.y && ball.y - ball.radius < rocket.y + rocket.height &&
        ball.x + ball.radius > rocket.x && ball.x - ball.radius < rocket.x + rocket.width) {
        if (ball.x < rocket.x || ball.x > rocket.x + rocket.width) {
            if (ball.x < rocket.x){
                ball.x = rocket.x - ball.radius;
            }
            else{
                ball.x = rocket.x + rocket.width + ball.radius;
            }

            // Отскок от боковых сторон ракетки
            ball.xDirection = -ball.xDirection;
        } else {
            // Отскок от верхней стороны ракетки
            ball.yDirection = -ball.yDirection;
            ball.y = rocket.y - ball.radius;
            ball.score += 1;
            if (ball.score % 5 == 0){
                //ball.y =  ball.y - 1;
                ball.xDirection = ball.xDirection * 1.2;
                ball.yDirection = ball.yDirection * 1.2;
        }
    }
        }
    // Столкновение с верхней ракеткой (rocket2)
    if (ball.y - ball.radius < rocket2.y + rocket2.height && ball.y + ball.radius > rocket2.y &&
        ball.x + ball.radius > rocket2.x && ball.x - ball.radius < rocket2.x + rocket2.width) {
        if (ball.x < rocket2.x || ball.x > rocket2.x + rocket2.width) {
            if (ball.x < rocket2.x){
                ball.x = rocket2.x - ball.radius;
            }
            else{
                ball.x = rocket2.x + rocket2.width + ball.radius;
            }
            // Отскок от боковых сторон ракетки
            ball.xDirection = -ball.xDirection;
        } else {
            // Отскок от нижней стороны ракетки
            ball.yDirection = -ball.yDirection;
            ball.y = rocket2.y + rocket2.height + ball.radius;
            ball.score += 1;
            if (ball.score % 5 == 0){
                ball.xDirection = ball.xDirection * 1.2;
                ball.yDirection = ball.yDirection * 1.2;
            }
        }
    }
        if (ball.y - ball.radius > rocket.y + rocket.height) {
            victory = true;
            gameOver = true;
            winner = "Player 1 wins!";
        }

        if (ball.y + ball.radius < rocket2.y) {
            victory = false;
            gameOver = true;
            winner = "Player 2 wins!";
        }
    }

void GameWindow::update() {
    if (gameInProgress && !gameOver && !victory) {
        updateBall();
        redraw();
        Fl::repeat_timeout(1.0 / 60, Timer_CB, this);
    }
}