#include "Game.h"
#include "windows.h"

sf::Vector2i GetDesktopResolution();
std::string ip;

int main()
{
    sf::Vector2i screenSize = GetDesktopResolution();
    std::cout << "Entrez l'adresse IP de votre copain : ";
    //std::cin >> ip;
    Game game(screenSize);
    game.setAddressIP(ip);
    game.run();

    return 0;
}

sf::Vector2i GetDesktopResolution()
{
   RECT desktop;
   const HWND hDesktop = GetDesktopWindow();
   GetWindowRect(hDesktop, &desktop);
   int horizontal = desktop.right;
   int vertical = desktop.bottom;
   return sf::Vector2i(horizontal, vertical);
}
