#ifndef CONTROLS_H
#define CONTROLS_H

#include <SDL2/SDL.h>
#include <vector>

enum Keys {
    Forward,
    Back,
    Left,
    Right,
    Ascend,
    Descend,
    Quit
};

class Controls
{
    private:
        std::vector<bool> keyboardState;
        const Uint8 *sdlKeyState;
        void updateKeyboardState();
    public:
        Controls() :
            keyboardState(std::vector<bool>(6)),
            sdlKeyState(SDL_GetKeyboardState(NULL))
        {};
        bool userRequestedExit();
        const std::vector<bool> &getKeyboardState();
        bool getKeyStatus(int keyIndex);
};

#endif
