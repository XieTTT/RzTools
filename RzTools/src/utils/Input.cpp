#include <thread>
#include <chrono>
#include <ctime>
#include <iostream>

#include "Input.h"
#include "windows.h"
#include "Vector.h"


using namespace std::chrono;
using namespace std::this_thread;
using namespace std::chrono_literals;


void Input::PressKey(HKey key) {
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = key;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = 0;
	input.ki.dwFlags = KEYEVENTF_SCANCODE;
	Sleep(3);
	SendInput(1, &input, sizeof(INPUT));
	input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	Sleep(7);
	SendInput(1, &input, sizeof(INPUT));
}

void Input::KeyUp(HKey key) {
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = key;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = 0;
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
	// 	Sleep(10);
	// 	SendInput(1, &input, sizeof(INPUT));
}

void Input::KeyDown(HKey key) {
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = key;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = 0;
	input.ki.dwFlags = KEYEVENTF_SCANCODE;
	SendInput(1, &input, sizeof(INPUT));
}

bool Input::WasKeyPressed(HKey key) {

	static high_resolution_clock::time_point nowTime;
	static high_resolution_clock::time_point lastTimePressed[300] = { high_resolution_clock::now() };
	static bool pressed[300] = { 0 };

	static duration<float, std::milli> timeDiff;

	int virtualKey = MapVirtualKeyA(key, MAPVK_VSC_TO_VK);
	if (virtualKey == 0)
		return false;

	nowTime = high_resolution_clock::now();
	timeDiff = nowTime - lastTimePressed[virtualKey];
	if (pressed[virtualKey]) {

		if (timeDiff.count() > 200)
			pressed[virtualKey] = false;
		return false;
	}

	bool keyDown = GetAsyncKeyState(virtualKey) & 0x8000;
	if (keyDown) {
		lastTimePressed[virtualKey] = high_resolution_clock::now();
		pressed[virtualKey] = true;
		return true;
	}

	return false;
}

bool Input::IsKeyDown(HKey key) {
	int virtualKey = MapVirtualKeyA(key, MAPVK_VSC_TO_VK);
	if (virtualKey == 0)
		return false;
	//? return GetAsyncKeyState(virtualKey);
	return GetAsyncKeyState(virtualKey);
}

Vector2 Input::GetCursorPosition()
{
	POINT pos;
	GetCursorPos(&pos);
	return { (float)pos.x, (float)pos.y };
}

void Input::PressLeftClick()
{
	MouseLeftDown();
	Sleep(1);
	MouseLeftUp();
}

void Input::PressRightClick()
{
	MouseRightDown();
	Sleep(5);
	MouseRightUp();
}

void Input::Move(int x, int y)
{
	DWORD nx = x * 65535 / GetSystemMetrics(0);
	DWORD ny = y * 65535 / GetSystemMetrics(1);
	mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE, nx, ny, 0, 0);

	POINT mouse_pos;
	GetCursorPos(&mouse_pos);

	if (mouse_pos.x != nx || mouse_pos.y != ny)
		mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE, nx, ny, 0, 0);
}

void Input::ClipMouse(float x, float y) {
	RECT rect = RECT();
	rect.bottom = y;
	rect.top = y;
	rect.right = x;
	rect.left = x;
	ClipCursor(&rect);
}

void Input::ClickAt(bool leftClick, float x, float y)
{
	BlockInput(true);
	POINT oldPos;
	GetCursorPos(&oldPos);
	ClipMouse(x, y);
	Move(x, y);
	leftClick ? PressLeftClick() : PressRightClick();
	Sleep(3);
	ClipCursor(NULL);

	// 	if (GetAsyncKeyState(VK_RBUTTON) || GetAsyncKeyState(VK_LBUTTON)) {
	// 		Sleep(5);
	// 		Move(oldPos.x, oldPos.y);
	// 	}
	BlockInput(false);
}

void Input::MouseRightDown()
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE;
	SendInput(1, &input, sizeof(INPUT));
	ZeroMemory(&input, sizeof(INPUT));
}

void Input::MouseRightUp()
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_RIGHTUP | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE;
	SendInput(1, &input, sizeof(INPUT));
	ZeroMemory(&input, sizeof(INPUT));
}

void Input::MouseLeftDown()
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &input, sizeof(INPUT));
	ZeroMemory(&input, sizeof(INPUT));
}

void Input::MouseLeftUp()
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &input, sizeof(INPUT));
	ZeroMemory(&input, sizeof(INPUT));
}

void Input::MoveAndPress(HKey key, float x, float y)
{
	BlockInput(true);
	POINT oldPos;
	GetCursorPos(&oldPos);
	ClipMouse(x, y);
	Sleep(1);
	Move(x, y);
	Sleep(1);
	PressLeftClick();//???
	PressKey(key);
	ClipCursor(NULL);
	Sleep(3);
	ClipCursorMove(oldPos.x, oldPos.y);
	BlockInput(false);
}

void Input::MoveAndKeyUp(HKey key, float x, float y)
{
	BlockInput(true);
	POINT oldPos;
	GetCursorPos(&oldPos);
	ClipMouse(x, y);
	Move(x, y);
	//PressLeftClick();
	KeyUp(key);
	Sleep(3);
	ClipCursor(NULL);

	Sleep(17);
	ClipCursorMove(oldPos.x, oldPos.y);
	BlockInput(false);
}

void Input::MoveAndClick(float x, float y) {
	BlockInput(true);
	POINT oldPos;
	GetCursorPos(&oldPos);
	ClipMouse(x, y);
	Move(x, y);
	Sleep(3);
	MouseLeftDown();
	Sleep(7);
	MouseLeftUp();
	Sleep(3);
	ClipCursor(NULL);
	Sleep(7);
	ClipCursorMove(oldPos.x, oldPos.y);
	BlockInput(false);
}

void Input::BlockInputTest(float time)
{
	BlockInput(true);
	std::cout << "BlockInput" << std::endl;

	Sleep(time);

	BlockInput(false);
}

void Input::ClipCursorMove(float x, float y)
{
	ClipMouse(x, y);
	Sleep(1);
	Move(x, y);
	Sleep(1);
	ClipCursor(NULL);
	Sleep(1);
}

void Input::clickMove(Vector2 playerV2) {
	BlockInput(true);
	POINT oldPos;
	GetCursorPos(&oldPos);
	Vector2 mouse = Vector2(oldPos.x, oldPos.y);
	Vector2 direction = playerV2 - mouse;
	Vector2 position = playerV2 + direction.normalize().scale(60.f);

	ClipMouse(position.x, position.y);
	Move(position.x, position.y);
	Sleep(2);
	MouseLeftDown();
	Sleep(3);
	MouseLeftUp();
	Sleep(2);
	ClipCursor(NULL);
	Sleep(3);
	ClipCursorMove(oldPos.x, oldPos.y);
	BlockInput(false);
}

