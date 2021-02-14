#include "Core.hpp"

int main(void)
{
    Core core(
        sf::VideoMode{1920U, 1080U},
        sf::String{L"platformer"},
        144U,
        sf::Style::Fullscreen
    );

    return core.run();
}