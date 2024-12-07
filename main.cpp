
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include "GameWindow.h"





int main(int argc, char** argv) {
    GameWindow window(GAME_WIDTH, GAME_HEIGHT, "Rocket");
    window.show(argc, argv);
    Fl::add_timeout(1.0 / 90, window.Timer_CB, &window);
    return Fl::run();
}