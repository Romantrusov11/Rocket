#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Button.H>
#include <string>
#include <iostream>
#include <set>

const int GAME_WIDTH = 500;
const int GAME_HEIGHT = 500;

struct Rocket {
    int x = 200;
    int y = 450;
    int width = 100;
    int height = 15;
    int xDirection = 25;
    Fl_Color color = FL_DARK_BLUE;
} rocket;

struct Rocket2 {
    int x = 200;
    int y = 30;
    int width = 100;
    int height = 15;
    int xDirection = 25;
    Fl_Color color = FL_GREEN;
} rocket2;

struct Ball {
    int x = 100;
    int y = 80;
    int radius = 10;
    float xDirection = 2;
    float yDirection = 4;

    int score = 0;
    Fl_Color color = FL_RED;
} ball;


static void Timer_CB(void* data);

class GameWindow : public Fl_Double_Window {
public:
    GameWindow(int w, int h, const char* title = 0) : Fl_Double_Window(w, h, title) {
        color(FL_WHITE);
        bgImage = new Fl_JPEG_Image("C:/cpp/01c++/logo_company_968x544_16_almazantey.jpg");

        startButton = new Fl_Button(GAME_WIDTH / 2 - 50, GAME_HEIGHT / 2 - 100, 100, 40, "Start");
        startButton->callback(startButtonCallback, this);

        restartButton = new Fl_Button(GAME_WIDTH / 2 - 50, GAME_HEIGHT / 2 + 50, 100, 40, "Restart");
        restartButton->callback(restartButtonCallback, this);
        restartButton->hide(); 

        gameInProgress = false;
        gameOver = false;
        victory = false;
        winner = ""; 

        end();
    }

    void draw() override {
        Fl_Double_Window::draw();
        
        // Показываем фон только во время игры, когда мяч движется
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
            restartButton->show(); 
        }

        if (gameInProgress) {
            drawRocket();
            drawRocket2();
            drawBall();
        }
    }

    void drawBackground() {
        if (bgImage) {
            bgImage->draw(0, 0, w(), h());  // рисуем фон с подгонкой по размеру окна
        } else {
            fl_rectf(0, 0, w(), h(), fl_rgb_color(245, 240, 225));
        }
    }

    void drawRocket() {
        fl_rectf(rocket.x, rocket.y, rocket.width, rocket.height, rocket.color);
    }

    void drawRocket2() {
        fl_rectf(rocket2.x, rocket2.y, rocket2.width, rocket2.height, rocket2.color);
    }

    void drawBall() {
        fl_color(ball.color);
        fl_pie(ball.x - ball.radius, ball.y - ball.radius, ball.radius * 2, ball.radius * 2, 0, 360);
    }

    void drawEndGameMessage() {
        fl_color(FL_BLACK);
        fl_font(FL_HELVETICA, 48);
        fl_draw(winner.c_str(), GAME_WIDTH / 2 - 150, GAME_HEIGHT / 2 - 50); 
    }

    void startGame() {
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

    void restartGame() {
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

    static void startButtonCallback(Fl_Widget*, void* data) {
        GameWindow* gw = (GameWindow*)data;
        gw->startGame();
    }

    static void restartButtonCallback(Fl_Widget*, void* data) {
        GameWindow* gw = (GameWindow*)data;
        gw->restartGame();
    }

    int handle(int event) override {
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

    void handleKeys(){
        if (activeKeys.count(FL_Left)) {
            rocket.x -= rocket.xDirection;  
        }
        if (activeKeys.count(FL_Right)) {
            rocket.x += rocket.xDirection;  
        }
        if (activeKeys.count('a')) {
            rocket2.x -= rocket2.xDirection;  
        }
        if (activeKeys.count('d')) {
            rocket2.x += rocket2.xDirection; 
        }

        clampRocketPosition();
        clampRocket2Position();
    }

    void clampRocketPosition() {
        if (rocket.x < 0) rocket.x = 0;
        if (rocket.x + rocket.width > GAME_WIDTH) rocket.x = GAME_WIDTH - rocket.width;
    }

    void clampRocket2Position() {
        if (rocket2.x < 0) rocket2.x = 0;
        if (rocket2.x + rocket2.width > GAME_WIDTH) rocket2.x = GAME_WIDTH - rocket2.width;
    }

    void update() {
        if (gameInProgress && !gameOver && !victory) {
            updateBall();
            redraw();
            Fl::repeat_timeout(1.0 / 60, Timer_CB, this); 
        }
    }

    void updateBall() {
        ball.x += ball.xDirection;
        ball.y += ball.yDirection;

        if (ball.y + ball.radius > GAME_HEIGHT || ball.y - ball.radius < 0) {
            ball.yDirection = -ball.yDirection;
        }
        if (ball.x + ball.radius > GAME_WIDTH || ball.x - ball.radius < 0) {
            ball.xDirection = -ball.xDirection;
        }

        if (ball.y + ball.radius > rocket.y && ball.y - ball.radius < rocket.y + rocket.height &&
        ball.x + ball.radius > rocket.x && ball.x - ball.radius < rocket.x + rocket.width) {
            if (ball.x < rocket.x || ball.x > rocket.x + rocket.width) {
                ball.xDirection = -ball.xDirection;
            } else {
                ball.yDirection = -ball.yDirection;
                ball.score += 1;
                if (ball.score % 5 == 0) {
                    ball.xDirection *= 1.2;
                    ball.yDirection *= 1.2;
                }
            }
        }

        if (ball.y - ball.radius < rocket2.y + rocket2.height && ball.y + ball.radius > rocket2.y &&
        ball.x + ball.radius > rocket2.x && ball.x - ball.radius < rocket2.x + rocket2.width) {
            if (ball.x < rocket2.x || ball.x > rocket2.x + rocket2.width) {
                ball.xDirection = -ball.xDirection;
            } else {
                ball.yDirection = -ball.yDirection;
                ball.score += 1;
                if (ball.score % 5 == 0) {
                    ball.xDirection *= 1.2;
                    ball.yDirection *= 1.2;
                }
            }
        }

        if (ball.y - ball.radius > rocket.y + rocket.height) {
            victory = true;
            gameOver = true;
            winner = "Player 2 wins!";
        } else if (ball.y + ball.radius < rocket2.y) {
            victory = true;
            gameOver = true;
            winner = "Player 1 wins!";
        }
    }

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

static void Timer_CB(void* data) {
    GameWindow* gw = (GameWindow*)data;
    gw->update();
}

int main(int argc, char** argv) {
    GameWindow window(GAME_WIDTH, GAME_HEIGHT, "Rocket");
    window.show(argc, argv);
    Fl::add_timeout(1.0 / 90, Timer_CB, &window);
    return Fl::run();
}
