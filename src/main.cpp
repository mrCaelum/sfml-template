#include "Core.hpp"
#include "Settings.hpp"

int main(void)
{
    sf::ContextSettings settings(0, 0, 8);
    Core core(
        sf::VideoMode{1920U, 1080U},
        sf::String{L"sfml-template"},
        144U,
        sf::Style::Fullscreen,
        settings
    );

    return core.run();
}