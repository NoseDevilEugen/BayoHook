#include <pch.h>
#include <base.h>
#include "gamehook.hpp"
#include <windows.h>
#include <XInput.h>

const char* GameHook::previousWeaponName = "Scarborough Fair";
const char* GameHook::previousWeaponName2 = "Scarborough Fair";

int& weaponA1Value = *(int*)GameHook::WeaponA1Address;
int& weaponA2Value = *(int*)GameHook::WeaponA2Address;
int& weaponB1Value = *(int*)GameHook::WeaponB1Address;
int& weaponB2Value = *(int*)GameHook::WeaponB2Address;

bool GameHook::leftPressed = false;
bool GameHook::rightPressed = false;
bool GameHook::upPressed = false;
bool GameHook::downPressed = false;

int GameHook::messageTimer = 200;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Base::Hooks::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(uMsg == WM_KEYDOWN || uMsg == WM_KEYUP)
		Data::WmKeys[wParam] = uMsg;

	if (uMsg == WM_KEYDOWN)
	{
		switch (wParam)
		{
		case VK_DELETE:
			Data::ShowMenu = !Data::ShowMenu;
			if (Data::ShowMenu) {
				ImGui::GetIO().MouseDrawCursor = true;
				GameHook::disableClicking_toggle = true; // bayo
				GameHook::DisableClicking(GameHook::disableClicking_toggle); // bayo
			}
			else {
				ImGui::GetIO().MouseDrawCursor = false;
				GameHook::disableClicking_toggle = false; // bayo
				GameHook::DisableClicking(GameHook::disableClicking_toggle); // bayo
			}
			break;
		case VK_F1:
			GameHook::enemyHP_no_damage_toggle = !GameHook::enemyHP_no_damage_toggle;
			GameHook::DisableKilling(GameHook::enemyHP_no_damage_toggle);
			if (GameHook::enemyHP_no_damage_toggle)
				GameHook::enemyHP_one_hit_kill_toggle = false;
			GameHook::showMessageTimerF1 = GameHook::messageTimer;
			break;
		case VK_F2:
			GameHook::takeNoDamage_toggle = !GameHook::takeNoDamage_toggle;
			GameHook::TakeNoDamage(GameHook::takeNoDamage_toggle);
			GameHook::showMessageTimerF2 = GameHook::messageTimer;
			break;
		case VK_F3:
			GameHook::enemyHP_one_hit_kill_toggle = !GameHook::enemyHP_one_hit_kill_toggle;
			if (GameHook::enemyHP_one_hit_kill_toggle) {
				GameHook::enemyHP_no_damage_toggle = false;
				GameHook::DisableKilling(GameHook::enemyHP_no_damage_toggle);
			}
			GameHook::showMessageTimerF3 = GameHook::messageTimer;
			break;
		case VK_F4:
			GameHook::infJumps_toggle = !GameHook::infJumps_toggle;
			GameHook::InfJumps(GameHook::infJumps_toggle);
			GameHook::showMessageTimerF4 = GameHook::messageTimer;
			break;
		case VK_F5:
			GameHook::noClip_toggle = !GameHook::noClip_toggle;
			GameHook::NoClip(GameHook::noClip_toggle);
			GameHook::showMessageTimerF5 = GameHook::messageTimer;
			break;
		case VK_HOME:
			GameHook::SaveStates_SaveState();
			break;
		case VK_END:
			GameHook::SaveStates_LoadState();
			break;
		}
	}
	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);


	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));




	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) == 0)
		{
			GameHook::leftPressed = false;
		}

		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0
			&& GameHook::leftPressed == false)
		{
			GameHook::leftPressed = true;
			weaponA1Value = weaponA1Value - 1;
			
			if (weaponA1Value < 0)
			{
				weaponA1Value = 17;
			}
			//skip what we dont need on hands
			while (weaponA1Value == 4
				|| weaponA1Value == 5
				|| weaponA1Value == 12)
			{
				weaponA1Value--;
			}
		}

		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) == 0)
		{
			GameHook::rightPressed = false;
		}

		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0
			&& GameHook::rightPressed == false)
		{
			GameHook::rightPressed = true;
			weaponA1Value = weaponA1Value + 1;
			if (weaponA1Value > 17)
			{
				weaponA1Value = 0;
			}
			while (weaponA1Value == 4
				|| weaponA1Value == 5
				|| weaponA1Value == 12)
			{
				weaponA1Value++;
			}
		}


		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) == 0)
		{
			GameHook::upPressed = false;
		}

		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0
			&& GameHook::upPressed == false)
		{
			GameHook::upPressed = true;
			weaponA2Value = weaponA2Value - 1;

			if (weaponA2Value < 0)
			{
				weaponA2Value = 17;
			}
			//skip what we dont need on legs
			while (weaponA2Value == 2
				|| weaponA2Value == 3
				|| weaponA2Value == 9
				|| weaponA2Value == 16)
			{
				weaponA2Value--;
			}
		}

		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) == 0)
		{
			GameHook::downPressed = false;
		}

		if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0
			&& GameHook::downPressed == false)
		{
			GameHook::downPressed = true;
			weaponA2Value = weaponA2Value + 1;
			if (weaponA2Value > 17)
			{
				weaponA2Value = 0;
			}
			while (weaponA2Value == 2
				|| weaponA2Value == 3
				|| weaponA2Value == 9
				|| weaponA2Value == 16)
			{
				weaponA2Value++;
			}
		}


	}


	//INPUT ip;

// Set up a generic keyboard event.
//ip.type = INPUT_KEYBOARD;
//ip.ki.wScan = 0; // hardware scan code for key
//ip.ki.time = 0;
//ip.ki.dwExtraInfo = 0;

// Press the "control" key
//ip.ki.wVk = 0x47; // virtual-key code for the "a" key
//ip.ki.dwFlags = 0; // 0 for key press
//SendInput(1, &ip, sizeof(INPUT));

// Release the "A" key
//ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
//SendInput(1, &ip, sizeof(INPUT));



	if (GameHook::previousWeaponName != GameHook::WeaponNames(weaponA1Value))
	{
		GameHook::WeaponSwapCaller();
		GameHook::previousWeaponName = GameHook::WeaponNames(weaponA1Value);
	}

	if (GameHook::previousWeaponName2 != GameHook::WeaponNames(weaponA2Value))
	{
		GameHook::WeaponSwapCaller();
		GameHook::previousWeaponName2 = GameHook::WeaponNames(weaponA2Value);

	}

	return CallWindowProc(Data::oWndProc, hWnd, uMsg, wParam, lParam);
}
