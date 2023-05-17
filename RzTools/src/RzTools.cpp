#include <iostream>
#include <Windows.h>

#include "utils/Input.h"
#include "tools/LockScreen.h"

int main()
{
	int time;
	std::cin >> time;
	Sleep(time * 1 * 1000);
	LockScreen::lock();
}