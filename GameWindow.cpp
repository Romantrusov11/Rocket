
#include "GameWindowFrontend.cpp"
#include "GameWindowBackend.cpp"


// void GameWindow::Timer_CB(void* data) {
//     GameWindow* gw = (GameWindow*)data;
//     gw->update();
// }


// GameWindow::GameWindow(int w, int h, const char* title = 0): Fl_Double_Window(w, h, title) {
//     color(FL_WHITE);
//     bgImage = new Fl_JPEG_Image("/Users/pavelatrusev/Downloads/logo_company_968x544_16_almazantey.jpg");

//     startButton = new Fl_Button(GAME_WIDTH / 2 - 50, GAME_HEIGHT / 2 - 100, 100, 40, "Start");
//     startButton->callback(startButtonCallback, this);

//     restartButton = new Fl_Button(GAME_WIDTH / 2 - 50, GAME_HEIGHT / 2 + 50, 100, 40, "Restart");
//     restartButton->callback(restartButtonCallback, this);
//     restartButton->hide();
//     end();

//     winner = "";
//     gameOver = false;
//     gameInProgress = false;
//     victory = false;
    
// }


// //front
// void GameWindow::draw() {
//     Fl_Double_Window::draw();

//     // Показываем фон только во время игры, когда мяч движется
//     if (gameInProgress && !gameOver && !victory) {
//         drawBackground();
//     }

//     if (!gameInProgress) {
//         startButton->show();
//     } else {
//         startButton->hide();
//     }

//     if (gameOver || victory) {
//         drawEndGameMessage();
//         restartButton->show();
//     }

//     if (gameInProgress) {
//         drawRocket();
//         drawRocket2();
//         drawBall();
//     }
// }

// //front
// void GameWindow::drawBackground() {
//     if (bgImage) {
//         bgImage->draw(0, 0, w(), h());  // рисуем фон с подгонкой по размеру окна
//     } else {
//         fl_rectf(0, 0, w(), h(), fl_rgb_color(245, 240, 225));
//     }
// }

// //front
// void GameWindow::drawRocket() {
//     fl_rectf(rocket.x, rocket.y, rocket.width, rocket.height, rocket.color);
// }

// void GameWindow::drawRocket2() {
//     fl_rectf(rocket2.x, rocket2.y, rocket2.width, rocket2.height, rocket2.color);
// }

// void GameWindow::drawBall() {
//     fl_color(ball.color);
//     fl_pie(ball.x - ball.radius, ball.y - ball.radius, ball.radius * 2, ball.radius * 2, 0, 360);
// }

// void GameWindow::drawEndGameMessage() {
//     fl_color(FL_BLACK);
//     fl_font(FL_HELVETICA, 48);
//     fl_draw(winner.c_str(), GAME_WIDTH / 2 - 150, GAME_HEIGHT / 2 - 50);
// }



// //back
// void GameWindow::startGame() {
//     ball.x = 100;
//     ball.y = 80;
//     ball.score = 0;
//     rocket.x = 200;
//     rocket2.x = 200;
//     gameOver = false;
//     victory = false;
//     gameInProgress = true;
//     winner = "";

//     startButton->hide();
//     restartButton->hide();

//     redraw();
//     Fl::add_timeout(1.0 / 90, Timer_CB, this);
// }

// void GameWindow::restartGame() {
//     ball.x = 100;
//     ball.y = 80;
//     ball.radius = 10;
//     ball.xDirection = 2;
//     ball.yDirection = 4;
//     ball.score = 0;

//     rocket.x = 200;
//     rocket.y = 450;
//     rocket2.x = 200;
//     rocket2.y = 30;

//     gameOver = false;
//     victory = false;
//     gameInProgress = true;
//     winner = "";

//     restartButton->hide();
//     startButton->hide();

//     redraw();
//     Fl::add_timeout(1.0 / 60, Timer_CB, this);
// }

// //front
// void GameWindow::startButtonCallback(Fl_Widget *, void *data) {
//     GameWindow* gw = (GameWindow*)data;
//     gw->startGame();
// }

// void GameWindow::restartButtonCallback(Fl_Widget *, void *data) {
//     GameWindow* gw = (GameWindow*)data;
//     gw->restartGame();
// }

// //front
// int GameWindow::handle(int event) {
//     switch (event) {
//         case FL_KEYDOWN: {
//             int key = Fl::event_key();
//             activeKeys.insert(key);
//             handleKeys();
//             redraw();
//             return 1;
//         }
//         case FL_KEYUP: {
//             int key = Fl::event_key();
//             activeKeys.erase(key);
//             return 1;
//         }
//         default:
//             return Fl_Double_Window::handle(event);
//     }
// }

// void GameWindow::handleKeys(){
//         float prognoz_coordinate_x = ball.x + ball.xDirection;
//         float prognoz_coordinate_y = ball.y + ball.yDirection;
        
//         if (activeKeys.count(FL_Left)) {
//             int  prognoz_rocket = rocket.x - rocket.xDirection;
//             if (prognoz_coordinate_x > prognoz_rocket && prognoz_coordinate_x < prognoz_rocket + rocket.width && prognoz_coordinate_y > rocket.y && prognoz_coordinate_y < rocket.y + rocket.height ){
//                 ball.x = prognoz_rocket - ball.radius;
//                 if (ball.x < 0){
//                     ball.y = ball.y - ball.radius;
//                     ball.x = ball.x + ball.radius;
//                 }
                
//             };
//             rocket.x -= rocket.xDirection;  // Перемещение ракетки 1 влево
//         }
//         if (activeKeys.count(FL_Right)) {
//             int prognoz_rocket = rocket.x + rocket.xDirection;
//             if (prognoz_coordinate_x > prognoz_rocket && prognoz_coordinate_x < prognoz_rocket + rocket.width && prognoz_coordinate_y > rocket.y && prognoz_coordinate_y < rocket.y + rocket.height ){
//                 if (ball.x > GAME_WIDTH){
//                     ball.y = ball.y - ball.radius;
//                     ball.x = ball.x - ball.radius;
//                 }
//                 ball.x = prognoz_rocket + rocket.width + ball.radius;
//             };
//             rocket.x += rocket.xDirection;  // Перемещение ракетки 1 вправо
//         }
//         if (activeKeys.count('a')) {
//             int prognoz_rocket2 = rocket2.x - rocket2.xDirection;
//             if (prognoz_coordinate_x > prognoz_rocket2 && prognoz_coordinate_x < prognoz_rocket2 + rocket.width && prognoz_coordinate_y > rocket.y && prognoz_coordinate_y < rocket.y + rocket.height ){
//                 ball.x = prognoz_rocket2 - ball.radius;
//                 if (ball.x < 0){
//                     ball.y = ball.y + ball.radius;
//                     ball.x = ball.x + ball.radius;
//                 }
//             };
//             rocket2.x -= rocket2.xDirection;  // Перемещение ракетки 2 влево
//         }
//         if (activeKeys.count('d')) {
//             int prognoz_rocket2 = rocket2.x + rocket2.xDirection;
//             if (prognoz_coordinate_x > prognoz_rocket2 && prognoz_coordinate_x < prognoz_rocket2 + rocket.width && prognoz_coordinate_y > rocket.y && prognoz_coordinate_y < rocket.y + rocket.height ){
//                 if (ball.x > GAME_WIDTH){
//                     ball.y = ball.y + ball.radius;
//                     ball.x = ball.x - ball.radius;
//                 }
//                 ball.x = prognoz_rocket2 + rocket2.width + ball.radius;
//             };
//             rocket2.x += rocket2.xDirection;  // Перемещение ракетки 2 вправо
//         }

//         clampRocketPosition();
//         clampRocket2Position();
//     }



// //back
// void GameWindow::clampRocketPosition() {
//     if (rocket.x < 0) rocket.x = 0;
//     if (rocket.x + rocket.width > GAME_WIDTH) rocket.x = GAME_WIDTH - rocket.width;
// }

// void GameWindow::clampRocket2Position() {
//     if (rocket2.x < 0) rocket2.x = 0;
//     if (rocket2.x + rocket2.width > GAME_WIDTH) rocket2.x = GAME_WIDTH - rocket2.width;
// }

// void GameWindow::update() {
//     if (gameInProgress && !gameOver && !victory) {
//         updateBall();
//         redraw();
//         Fl::repeat_timeout(1.0 / 60, Timer_CB, this);
//     }
// }


// //back
// void GameWindow::updateBall() {
//         ball.x += ball.xDirection;
//         ball.y += ball.yDirection;

//         if (ball.y + ball.radius > GAME_HEIGHT || ball.y - ball.radius < 0) {
//             ball.yDirection = -ball.yDirection;
//         }
//         if (ball.x + ball.radius > GAME_WIDTH || ball.x - ball.radius < 0) {
//             ball.xDirection = -ball.xDirection;
//         }
//         // Столкновение с нижней ракеткой (rocket)
//     if (ball.y + ball.radius > rocket.y && ball.y - ball.radius < rocket.y + rocket.height &&
//         ball.x + ball.radius > rocket.x && ball.x - ball.radius < rocket.x + rocket.width) {
//         if (ball.x < rocket.x || ball.x > rocket.x + rocket.width) {
//             if (ball.x < rocket.x){
//                 ball.x = rocket.x - ball.radius;
//             }
//             else{
//                 ball.x = rocket.x + rocket.width + ball.radius;
//             }

//             // Отскок от боковых сторон ракетки
//             ball.xDirection = -ball.xDirection;
//         } else {
//             // Отскок от верхней стороны ракетки
//             ball.yDirection = -ball.yDirection;
//             ball.y = rocket.y - ball.radius;
//             ball.score += 1;
//             if (ball.score % 5 == 0){
//                 //ball.y =  ball.y - 1;
//                 ball.xDirection = ball.xDirection * 1.2;
//                 ball.yDirection = ball.yDirection * 1.2;
//         }
//     }
//         }
//     // Столкновение с верхней ракеткой (rocket2)
//     if (ball.y - ball.radius < rocket2.y + rocket2.height && ball.y + ball.radius > rocket2.y &&
//         ball.x + ball.radius > rocket2.x && ball.x - ball.radius < rocket2.x + rocket2.width) {
//         if (ball.x < rocket2.x || ball.x > rocket2.x + rocket2.width) {
//             if (ball.x < rocket2.x){
//                 ball.x = rocket2.x - ball.radius;
//             }
//             else{
//                 ball.x = rocket2.x + rocket2.width + ball.radius;
//             }
//             // Отскок от боковых сторон ракетки
//             ball.xDirection = -ball.xDirection;
//         } else {
//             // Отскок от нижней стороны ракетки
//             ball.yDirection = -ball.yDirection;
//             ball.y = rocket2.y + rocket2.height + ball.radius;
//             ball.score += 1;
//             if (ball.score % 5 == 0){
//                 ball.xDirection = ball.xDirection * 1.2;
//                 ball.yDirection = ball.yDirection * 1.2;
//             }
//         }
//     }
//         if (ball.y - ball.radius > rocket.y + rocket.height) {
//             victory = true;
//             gameOver = true;
//         }

//         if (ball.y + ball.radius < rocket2.y) {
//             victory = false;
//             gameOver = true;
//         }
//     }

