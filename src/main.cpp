#include "Core.hpp"

Settings GLOBAL_SETTINGS;

int main(void)
{
	GLOBAL_SETTINGS.loadFromFile(SETTINGS_FILE);

	Core core{GLOBAL_SETTINGS};

	return core.run();
}