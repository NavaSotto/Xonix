#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")


#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#else
#error "Unrecognized configuration!"
#endif

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Menu.h"

int main()
{
	Menu m;
	m.openMenu();
	return (EXIT_SUCCESS);
}