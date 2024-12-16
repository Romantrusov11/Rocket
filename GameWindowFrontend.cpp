#include "GameWindow.h"
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include "Ball.h"
#include "Rocket.h"
#include "Rocket2.h"




GameWindow::GameWindow(int w, int h, const char* title): Fl_Double_Window(w, h, title) {
    color(FL_WHITE);
    bgImage = new Fl_JPEG_Image("/Users/pavelatrusev/Downloads/logo_company_968x544_16_almazantey.jpg");

    startButton = new Fl_Button(GAME_WIDTH / 2 - 50, GAME_HEIGHT / 2 - 100, 100, 40, "Start");
    startButton->callback(startButtonCallback, this);

    restartButton = new Fl_Button(GAME_WIDTH / 2 - 50, GAME_HEIGHT / 2 + 50, 100, 40, "Restart");
    restartButton->callback(restartButtonCallback, this);
    restartButton->hide();
}


void GameWindow::draw() {
    Fl_Double_Window::draw();

    if (gameInProgress && !gameOver && !victory) {
        drawBackground();
    }

    if (!gameInProgress) {
        startButton->show();
    } else {
        startButton->hide();
    }

    if (gameOver || victory) {
        drawEndGameMessage();
    }

    if (gameInProgress) {
        drawRocket();
        drawRocket2();
        drawBall();
    }
}

void GameWindow::drawBackground() {
    if (bgImage) {
        bgImage->draw(0, 0, w(), h());
    } else {
        fl_rectf(0, 0, w(), h(), fl_rgb_color(245, 240, 225));
    }
}

void GameWindow::drawRocket() {
    fl_rectf(rocket.x, rocket.y, rocket.width, rocket.height, rocket.color);
}

void GameWindow::drawRocket2() {
    fl_rectf(rocket2.x, rocket2.y, rocket2.width, rocket2.height, rocket2.color);
}

void GameWindow::drawBall() {
    fl_color(ball.color);
    fl_pie(ball.x - ball.radius, ball.y - ball.radius, ball.radius * 2, ball.radius * 2, 0, 360);
}

void GameWindow::drawEndGameMessage() {
    fl_color(FL_BLACK);
    fl_font(FL_HELVETICA, 48);
    fl_draw(winner.c_str(), GAME_WIDTH / 2 - 150, GAME_HEIGHT / 2 - 50);
}

int GameWindow::handle(int event) {
    switch (event) {
        case FL_KEYDOWN: {
            int key = Fl::event_key();
            activeKeys.insert(key);
            handleKeys();
            redraw();
            return 1;
        }
        case FL_KEYUP: {
            int key = Fl::event_key();
            activeKeys.erase(key);
            return 1;
        }
        default:
            return Fl_Double_Window::handle(event);
    }
}

void GameWindow::startButtonCallback(Fl_Widget *, void *data) {
    GameWindow* gw = (GameWindow*)data;
    gw->startGame();
}

void GameWindow::restartButtonCallback(Fl_Widget *, void *data) {
    GameWindow* gw = (GameWindow*)data;
    gw->restartGame();
}