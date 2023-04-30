#include <iostream>
#include "Engine.h"
#include "DEFINITIONS.h"
#include <Windows.h>

int main()
{
	//get console window and hide it
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	Noir2D::Engine engine(SCREEN_WIDTH, SCREEN_HEIGHT, "NOIR2D");
	return EXIT_SUCCESS;
}