#include "Core.hpp"
#include "scenes/Menu.hpp"

int main(void)
{
	Core::SETTINGS.loadFromFile(SETTINGS_FILE);
	Core::WINDOW.create(Core::SETTINGS.videomode, "sfml-template", Core::SETTINGS.getStyle(), Core::SETTINGS.getContextSettings());
	Core::WINDOW.setFramerateLimit(Core::SETTINGS.framerate_limit);
	Core::RESOURCES.setFont("assets/fonts/Roboto.ttf", "Roboto");
	Core::RESOURCES.setSound("assets/audio/select.wav", "select");
	Core::RESOURCES.setTexture("assets/background.jpg", "background");

	OPEN_SCENE(Scenes::Menu);

	return EXIT_SUCCESS;
}