#include <controls.h>
#include <iostream>

void Controls::updateKeyboardState()
{
    keyboardState[Keys::Forward] = (bool)sdlKeyState[SDL_SCANCODE_UP];
    keyboardState[Keys::Back] = (bool)sdlKeyState[SDL_SCANCODE_DOWN];
    keyboardState[Keys::Left] = (bool)sdlKeyState[SDL_SCANCODE_LEFT];
    keyboardState[Keys::Right] = (bool)sdlKeyState[SDL_SCANCODE_RIGHT];
    keyboardState[Keys::Ascend] = (bool)sdlKeyState[SDL_SCANCODE_SPACE];
    keyboardState[Keys::Descend] = (bool)sdlKeyState[SDL_SCANCODE_LSHIFT];
    keyboardState[Keys::Quit] = (bool)sdlKeyState[SDL_SCANCODE_ESCAPE];
}

bool Controls::userRequestedExit()
{
    updateKeyboardState();
    return keyboardState[Keys::Quit];
}

const std::vector<bool> &Controls::getKeyboardState()
{
    updateKeyboardState();
    return keyboardState;
}

bool Controls::getKeyStatus(int keyIndex)
{
    updateKeyboardState();
    return keyboardState[keyIndex];
}
