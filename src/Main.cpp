#include "Game/Game.h"
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    std::string str = argv[0];
    str.erase(str.rfind(
#ifdef _WIN32
        '\\'
#else
        '/'
#endif
        ));

    Game game(str);

    game.Initialize();
    game.Run();
    game.Destroy();

    return 0;
}
