#include <iostream>
#include "SaveManager.h"
#include "Engine.h"
#include "DEFINITIONS.h"
#include <Windows.h>

int main()
{
	//get console window and hide it
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	Noir2D::SaveManager::GetInstance().Load(CONFIG_FILE_PATH);
	bool fullscreen = Noir2D::SaveManager::GetInstance().Get<bool>("fullscreen", false);
	Noir2D::Engine engine(SCREEN_WIDTH, SCREEN_HEIGHT, "NOIR2D",fullscreen);
    engine.Run();
	return EXIT_SUCCESS;
}