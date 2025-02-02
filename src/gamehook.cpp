#include "gamehook.hpp"

bool GameHook::isCallerCalled = false;

// patches
bool GameHook::takeNoDamage_toggle = false;
void GameHook::TakeNoDamage(bool enabled) {
	if (enabled) 
		GameHook::_nop((char*)(0x9D4329), 6);
	else
		GameHook::_patch((char*)(0x9D4329), (char*)"\x89\x86\x08\x35\x09\x00", 6);
}

bool GameHook::focusPatch_toggle = false;
void GameHook::FocusPatch(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x49E519), (char*)"\xEB\x17", 2); // disable pausing tabbed out
		GameHook::_patch((char*)(0x411DB8), (char*)"\xE9\x82\x00", 3); // enable inputs tabbed out
	}
	else {
		GameHook::_patch((char*)(0x49E519), (char*)"\x75\x17", 2);
		GameHook::_patch((char*)(0x411DB8), (char*)"\x0F\x85\x81", 3);
	}
}

bool GameHook::infJumps_toggle = false;
void GameHook::InfJumps(bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x9E8906), 6); // jumps
		GameHook::_nop((char*)(0x9A120F), 6); // bird jumps
		GameHook::_nop((char*)(0x9E8D8D), 6); // wall jumps
	}
	else {
		GameHook::_patch((char*)(0x9E8906), (char*)"\x01\xAE\x78\x35\x09\x00", 6); // jumps
		GameHook::_patch((char*)(0x9A120F), (char*)"\xFF\x86\x78\x35\x09\x00", 6); // bird jumps
		GameHook::_patch((char*)(0x9E8D8D), (char*)"\x89\xBE\x90\x35\x09\x00", 6); // wall jumps
	}
}

bool GameHook::disableClicking_toggle = false;
void GameHook::DisableClicking(bool enabled) {
	if (enabled)
		GameHook::_nop((char*)(0xC75747), 3);
	else
		GameHook::_patch((char*)(0xC75747), (char*)"\x89\x70\x04", 3);
}

bool GameHook::noClip_toggle= false;
void GameHook::NoClip(bool enabled) {
	if (enabled)
		GameHook::_nop((char*)(0xC13250), 7);
	else
		GameHook::_patch((char*)(0xC13250), (char*)"\xC7\x41\x54\x01\x00\x00\x00", 7);
}

bool GameHook::disableDaze_toggle = false;
void GameHook::DisableDaze(bool enabled) {
	if (enabled)
		GameHook::_patch((char*)(0x430CF4), (char*) "\xEB\x20", 2);
	else
		GameHook::_patch((char*)(0x430CF4), (char*)"\x72\x20", 2);
}

bool GameHook::forceDaze_toggle = false;
void GameHook::ForceDaze(bool enabled) {
	if (enabled)
		GameHook::_patch((char*)(0x65C75C), (char*)"\xF3\x0F\x10\x86\x98\x0C\x00\x00", 8);
	else
		GameHook::_patch((char*)(0x65C75C), (char*)"\xF3\x0F\x10\x86\x9C\x0C\x00\x00", 8);
}

bool GameHook::freezeTimer_toggle = false;
void GameHook::FreezeTimer(bool enabled) {
	if (enabled)
		GameHook::_nop((char*)(0x620C1D), 8);
	else
		GameHook::_patch((char*)(0x620C1D), (char*)"\xF3\x0F\x5C\x05\xF8\xD6\xD9\x00", 8);
}

// uses GameHook::enemyHP_no_damage_toggle
void GameHook::DisableKilling(bool enabled) {
	if (enabled)
		GameHook::_patch((char*)(0x4572D2), (char*) "\xEB\x0C", 2);
	else
		GameHook::_patch((char*)(0x4572D2), (char*)"\x75\x0C", 2);
}

bool GameHook::disableAfterBurnerBounce_toggle = false;
void GameHook::DisableAfterBurnerBounce(bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x959B23), 6); // enemy
		GameHook::_patch((char*)(0x959E2C), (char*)"\xEB\x5E", 2); // wall
	}
	else {
		GameHook::_patch((char*)(0x959B23), (char*)"\x0F\x84\x37\x03\x00\x00", 6); // enemy
		GameHook::_patch((char*)(0x959E2C), (char*)"\x74\x5E", 2); // wall
	}
}

bool GameHook::areaJumpPatch_toggle = false;
void GameHook::AreaJumpPatch(bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x4FC2FB), 6); // enemy
	}
	else {
		GameHook::_patch((char*)(0x4FC2FB), (char*)"\x89\x83\x28\x08\x00\x00", 6); // enemy
	}
}

bool GameHook::easyCutsceneSkip_toggle = false;
void GameHook::EasyCutsceneSkip(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x48FEC4), (char*)"\x90\x90", 2);
		GameHook::_patch((char*)(0x48FEC6), (char*)"\xF7\x05\xCC\x93\xA4\x05\x16\x00\x00\x00", 10); // X Pressed
	}
	else {
		GameHook::_patch((char*)(0x48FEC4), (char*)"\x74\x10", 2); // R2 Held
		GameHook::_patch((char*)(0x48FEC6), (char*)"\xF7\x05\xCC\x93\xA4\x05\x00\x02\x00\x00", 10); // Select Pressed
	}
}

bool GameHook::lessClothes_toggle = false;
void GameHook::LessClothes(bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x8B6BD2), 2);
	}
	else {
		GameHook::_patch((char*)(0x8B6BD2), (char*)"\x74\x0A", 2); // je 
	}
}

bool GameHook::disableLockOnDodge_toggle = false;
void GameHook::DisableLockOnDodge(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x9E87CD), (char*)"\x39\xFF", 2);
	}
	else {
		GameHook::_patch((char*)(0x9E87CD), (char*)"\x39\xDF", 2);
	}
}

bool GameHook::noHoldDodgeOffset_toggle = false;
void GameHook::NoHoldDodgeOffset(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x8EF16B), (char*)"\xEB\x11", 2);
	}
	else {
		GameHook::_patch((char*)(0x8EF16B), (char*)"\x74\x11", 2);
	}
}

bool GameHook::jumpOffset_toggle = false;
void GameHook::JumpOffset(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x9E894F), (char*)"\xEB\x17", 2);
	}
	else {
		GameHook::_patch((char*)(0x9E894F), (char*)"\x74\x0F", 2);
	}
}

bool GameHook::alwaysWalkOnWalls_toggle = false;
void GameHook::AlwaysWalkOnWalls(bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x520496), 10);
		GameHook::_patch((char*)(0x9CB8C4), (char*)"\x81\x0D\x24\xDE\x1A\x05\x00\x00\x10\x00", 10);
	}
	else {
		GameHook::_patch((char*)(0x520496), (char*)"\x81\x25\x24\xDE\x1A\x05\xFF\xFF\xEF\xFF", 10);
		GameHook::_patch((char*)(0x9CB8C4), (char*)"\xF7\x05\x24\xDE\x1A\x05\x00\x00\x10\x00", 10);
	}
}

bool GameHook::getMoreHalos_toggle = false;
void GameHook::GetMoreHalos (bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x49479A), 2);
	}
	else {
		GameHook::_patch((char*)(0x49479A), (char*)"\x76\x0A", 2); // jna
	}
}

bool GameHook::moreEnemyAttacks_toggle = false;
void GameHook::MoreEnemyAttacks (bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x65DEC1), 6);
	}
	else {
		GameHook::_patch((char*)(0x65DEC1), (char*)"\x0F\x84\x51\x06\x00\x00", 6); // je
	}
}

bool GameHook::lessEnemyAttacks_toggle = false;
void GameHook::LessEnemyAttacks (bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x65DEC1), (char*)"\xE9\x52\x06\x00\x00\x90", 6); // jmp
	}
	else {
		GameHook::_patch((char*)(0x65DEC1), (char*)"\x0F\x84\x51\x06\x00\x00", 6); // je
	}
}

bool GameHook::infBirdTime_toggle = false;
void GameHook::InfBirdTime (bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x8BDD17), (char*)"\xEB\x1D", 2); // jmp
	}
	else {
		GameHook::_patch((char*)(0x8BDD17), (char*)"\x75\x1D", 2); // jne
	}
}

bool GameHook::weaponSwapOffset_toggle = false;
void GameHook::WeaponSwapOffset (bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x9EB456), (char*)"\xEB\x1C\x90", 3); // jmp, nop
	}
	else {
		GameHook::_patch((char*)(0x9EB456), (char*)"\x0F\x57\xC0", 3); // xorps xmm0,xmm0
	}
}

bool GameHook::retainPillowTalkCharge_toggle = false;
void GameHook::RetainPillowTalkCharge (bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0xA2B491), 8);
	}
	else {
		GameHook::_patch((char*)(0xA2B491), (char*)"\xF3\x0F\x11\x86\x2C\x33\x00\x00", 8);
	}
}

bool GameHook::swapMashToHold_toggle = false;
void GameHook::SwapMashToHold (bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x9D80DA), 2);
	}
	else {
		GameHook::_patch((char*)(0x9D80DA), (char*)"\x74\x4E", 2);
	}
}

bool GameHook::sixtyFpsCutscenes_toggle = true;
void GameHook::SixtyFpsCutscenes(bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x45B4A7), 2);
		GameHook::_patch((char*)(0x45B4BA), (char*)"\xEB", 1); // jmp
	}
	else {
		GameHook::_patch((char*)(0x45B4A7), (char*)"\x74\x28", 2); // jz
		GameHook::_patch((char*)(0x45B4BA), (char*)"\x74", 1); // jz
	}
}

bool GameHook::jeanneBayoWT_toggle = true;
void GameHook::JeanneBayoWT(bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x8EF3B8), (char*)"\xEB\x0C", 2); // jmp
	}
	else {
		GameHook::_patch((char*)(0x8EF3B8), (char*)"\x75\x0C", 2); // jne
	}
}

bool GameHook::infDivekick_toggle = true;
void GameHook::InfDivekick(bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x9E93F5), 2);
	}
	else {
		GameHook::_patch((char*)(0x9E93F5), (char*)"\x73\x24", 2); // jae
	}
}

bool GameHook::tauntWithTimeBracelet_toggle = false;
void GameHook::TauntWithTimeBracelet (bool enabled) {
	if (enabled) {
		GameHook::_nop((char*)(0x9E74CF), 2);
	}
	else {
		GameHook::_patch((char*)(0x9E74CF), (char*)"\x75\x69", 2); // jne
	}
}

bool GameHook::parryOffset_toggle = false;
void GameHook::ParryOffset (bool enabled) {
	if (enabled) {
		GameHook::_patch((char*)(0x8F0CA6), (char*)"\x83\xC4\x04\x90\x90", 5); // add esp,4 nop nop // Parry
		GameHook::_patch((char*)(0x8F0D45), (char*)"\x83\xC4\x04\x90\x90", 5); // add esp,4 nop nop // Perfect Parry
	}
	else {
		GameHook::_patch((char*)(0x8F0CA6), (char*)"\xE8\xF5\x1B\xFE\xFF", 5); // call Bayonetta.exe+4D28A0 // Parry
		GameHook::_patch((char*)(0x8F0D45), (char*)"\xE8\x56\x1B\xFE\xFF", 5); // call Bayonetta.exe+4D28A0 // Perfect Parry
	}
}

// detours
std::unique_ptr<FunctionHook> enemyHPHook;
uintptr_t enemyHP_jmp_ret{ NULL };
bool GameHook::enemyHP_no_damage_toggle = false;
bool GameHook::enemyHP_one_hit_kill_toggle = false;
static __declspec(naked) void EnemyHPDetour(void) {
	_asm {
		cmp byte ptr [GameHook::enemyHP_one_hit_kill_toggle], 1
		je one_hit_kill
		jmp check2
		
		check2:
		cmp byte ptr [GameHook::enemyHP_no_damage_toggle], 1
		je no_damage
		jmp originalcode

		no_damage:
		jmp dword ptr [enemyHP_jmp_ret]

		one_hit_kill:
		mov dword ptr [esi+0x000006B4], 0
		jmp dword ptr [enemyHP_jmp_ret]

		originalcode:
		mov [esi+0x000006B4], eax
		jmp dword ptr [enemyHP_jmp_ret]
		// this hides test eax,eax in CE but it is still there
	}
}

std::unique_ptr<FunctionHook> witchTimeHook;
uintptr_t witchTimeMultiplier_jmp_ret{ NULL };
bool GameHook::witchTimeMultiplier_toggle = false;
float GameHook::witchTimeMultiplier = 1.0;
static __declspec(naked) void WitchTimeMultiplierDetour(void) {
	_asm {
		cmp byte ptr [GameHook::witchTimeMultiplier_toggle], 0
		je originalcode

		fmul dword ptr [esi+0x00095D68] // might be game speed or something? 1 by default
		fdiv dword ptr [GameHook::witchTimeMultiplier]
		jmp dword ptr [witchTimeMultiplier_jmp_ret]

		originalcode:
		fmul dword ptr [esi+0x00095D68]
		jmp dword ptr [witchTimeMultiplier_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> infMagicHook;
uintptr_t infMagic_jmp_ret{ NULL };
bool GameHook::inf_magic_toggle = false;
float GameHook::inf_magic_value = 1200.0f;
static __declspec(naked) void InfMagicDetour(void) {
	_asm {
		push eax
		mov eax, [GameHook::playerMagicAddress]
		cmp byte ptr [GameHook::inf_magic_toggle], 0
		je originalcode

		movss xmm0, [GameHook::inf_magic_value]
		movss [eax], xmm0

		originalcode:
		movss xmm0, [eax]
		pop eax
		jmp dword ptr [infMagic_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> damageDealtMultiplierHook;
uintptr_t damageDealtMultiplier_jmp_ret{ NULL };
bool GameHook::damageDealtMultiplier_toggle = false;
float damageDealtMultiplierXmm0Backup = 0.0f;
float GameHook::damageDealtMultiplierMult = 1.0f;
static __declspec(naked) void DamageDealtMultiplierDetour(void) {
	_asm {
		mov [esi+0x000006B8], eax // originalcode, early bytes to avoid EnemyHPDetour
		cmp byte ptr [GameHook::damageDealtMultiplier_toggle], 0
		je originalcode

		movss [damageDealtMultiplierXmm0Backup], xmm0 // xmm0 backup
		cvtsi2ss xmm0, edi // convert to float
		mulss xmm0, [GameHook::damageDealtMultiplierMult] // multiply
		cvttss2si edi, xmm0 // convert from float
		movss xmm0,[damageDealtMultiplierXmm0Backup] // restore xmm0

		originalcode:
		sub eax,edi
		mov [GameHook::haloDisplayValue], eax // after damage subtraction
		jmp dword ptr [damageDealtMultiplier_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> customCameraDistanceHook;
uintptr_t customCameraDistance_jmp_ret{ NULL };
bool GameHook::customCameraDistance_toggle = false;
float GameHook::customCameraDistance = 10.0f;
static __declspec(naked) void CustomCameraDistanceDetour(void) {
	_asm {
		cmp byte ptr [GameHook::customCameraDistance_toggle], 0
		je originalcode

		fld dword ptr [GameHook::customCameraDistance]
		jmp dword ptr [customCameraDistance_jmp_ret]

		originalcode:
		fld dword ptr [edi+0x00000B50]
		jmp dword ptr [customCameraDistance_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> haloDisplayHook;
uintptr_t haloDisplay_jmp_ret{ NULL };
bool GameHook::haloDisplay_toggle = false;
int GameHook::haloDisplayValue = 0;
uintptr_t haloDisplayAddress = 0x5BB57B0;
static __declspec(naked) void HaloDisplayDetour(void) {
	_asm {
		cmp byte ptr [GameHook::haloDisplay_toggle], 0
		je originalcode

		cmp dword ptr [GameHook::haloDisplayValue], 1
		jle originalcode
		mov eax, [GameHook::haloDisplayValue]	

		originalcode:
		push esi
		mov esi,[haloDisplayAddress] // i still hate this
		mov [esi],eax
		pop esi
		jmp dword ptr [haloDisplay_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> moveIDSwapHook;
uintptr_t moveIDSwap_jmp_ret{ NULL };
bool GameHook::moveIDSwap_toggle = false;

int GameHook::moveIDSwapSourceMove1 = -1;
int GameHook::moveIDSwapSourceMove2 = -1;
int GameHook::moveIDSwapDesiredMove1 = 0;
int GameHook::moveIDSwapDesiredMove2 = 0;

static __declspec(naked) void MoveIDSwapDetour(void) {
	_asm {
		cmp byte ptr [GameHook::moveIDSwap_toggle], 0
		je originalcode

		push eax
		mov eax, [GameHook::playerPointerAddress] // only edit player anim
		cmp [eax], ecx
		pop eax
		jne originalcode

		cmp edx, [GameHook::moveIDSwapSourceMove1]
		je newMove1
		cmp edx, [GameHook::moveIDSwapSourceMove2]
		je newMove2
		jmp originalcode

		newMove1:
		mov edx, [GameHook::moveIDSwapDesiredMove1]
		jmp originalcode

		newMove2:
		mov edx, [GameHook::moveIDSwapDesiredMove2]
		jmp originalcode

		originalcode:
		mov [ecx+0x0000034C], edx
		jmp dword ptr [moveIDSwap_jmp_ret]
	}
}

bool GameHook::stringIDSwap_toggle = false;

int GameHook::stringIDSwapSourceString1 = -1;
int GameHook::stringIDSwapSourceString2 = -1;

int GameHook::stringIDSwapDesiredString1 = 0;
int GameHook::stringIDSwapDesiredString2 = 0;

std::unique_ptr<FunctionHook> punchStringIDSwapHook;
uintptr_t punchStringIDSwap_jmp_ret{ NULL };
static __declspec(naked) void PunchStringIDSwapDetour(void) {
	_asm {
		cmp byte ptr [GameHook::stringIDSwap_toggle], 0
		je originalcode

		push eax
		mov eax, [GameHook::playerPointerAddress] // only edit player anim
		cmp [eax], esi
		pop eax
		jne originalcode

		cmp edx, [GameHook::stringIDSwapSourceString1]
		je newString1
		cmp edx, [GameHook::stringIDSwapSourceString2]
		je newString2
		jmp originalcode

		newString1:
		mov edx, [GameHook::stringIDSwapDesiredString1]
		jmp originalcode

		newString2:
		mov edx, [GameHook::stringIDSwapDesiredString2]
		jmp originalcode

		originalcode:
		mov [esi+0x00095C64], edx
		jmp dword ptr [punchStringIDSwap_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> latePunchStringIDSwapHook;
uintptr_t latePunchStringIDSwap_jmp_ret{ NULL };
static __declspec(naked) void LatePunchStringIDSwapDetour(void) {
	_asm {
		cmp byte ptr [GameHook::stringIDSwap_toggle], 0
		je originalcode

		push eax
		mov eax, [GameHook::playerPointerAddress] // only edit player anim
		cmp [eax], esi
		pop eax
		jne originalcode

		cmp eax, [GameHook::stringIDSwapSourceString1]
		je newString1
		cmp eax, [GameHook::stringIDSwapSourceString2]
		je newString2
		jmp originalcode

		newString1:
		mov eax, [GameHook::stringIDSwapDesiredString1]
		jmp originalcode

		newString2:
		mov eax, [GameHook::stringIDSwapDesiredString2]
		jmp originalcode

		originalcode:
		mov [esi+0x00095C64], eax
		jmp dword ptr [latePunchStringIDSwap_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> kickStringIDSwapHook;
uintptr_t kickStringIDSwap_jmp_ret{ NULL };
static __declspec(naked) void KickStringIDSwapDetour(void) {
	_asm {
		cmp byte ptr [GameHook::stringIDSwap_toggle], 0
		je originalcode

		push eax
		mov eax, [GameHook::playerPointerAddress] // only edit player anim
		cmp [eax], esi
		pop eax
		jne originalcode

		cmp edx, [GameHook::stringIDSwapSourceString1]
		je newString1
		cmp edx, [GameHook::stringIDSwapSourceString2]
		je newString2

		jmp originalcode

		newString1:
		mov edx, [GameHook::stringIDSwapDesiredString1]
		jmp originalcode

		newString2:
		mov edx, [GameHook::stringIDSwapDesiredString2]
		jmp originalcode

		originalcode:
		mov [esi+0x00095C64], edx
		jmp dword ptr [kickStringIDSwap_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> lateKickStringIDSwapHook;
uintptr_t lateKickStringIDSwap_jmp_ret{ NULL };
static __declspec(naked) void LateKickStringIDSwapDetour(void) {
	_asm {
		cmp byte ptr [GameHook::stringIDSwap_toggle], 0
		je originalcode

		push eax
		mov eax, [GameHook::playerPointerAddress] // only edit player anim
		cmp [eax], esi
		pop eax
		jne originalcode

		cmp ecx, [GameHook::stringIDSwapSourceString1]
		je newString1
		cmp ecx, [GameHook::stringIDSwapSourceString2]
		je newString2

		jmp originalcode

		newString1:
		mov ecx, [GameHook::stringIDSwapDesiredString1]
		jmp originalcode

		newString2:
		mov ecx, [GameHook::stringIDSwapDesiredString2]
		jmp originalcode

		originalcode:
		mov [esi+0x00095C64], ecx
		jmp dword ptr [lateKickStringIDSwap_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> inputIconsHook;
uintptr_t inputIcons_jmp_ret{ NULL };
bool GameHook::inputIcons_toggle = false;
int GameHook::inputIconsValue = 0; // 0 keyboard, 1 gamepad
static __declspec(naked) void InputIconsDetour(void) {
	_asm {
		cmp byte ptr [GameHook::inputIcons_toggle], 0
		je originalcode

		mov eax, [GameHook::inputIconsValue]

		originalcode:
		cmp dword ptr [ebx+0x000003E8], 00
		mov [ebx+0x00000CA8], eax
		jmp dword ptr [inputIcons_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> easierMashHook;
uintptr_t easierMash_jmp_ret{ NULL };
bool GameHook::easierMash_toggle = false;
static __declspec(naked) void EasierMashDetour(void) {
	_asm {
		cmp byte ptr [GameHook::easierMash_toggle], 0
		je originalcode

		mov dword ptr [esi+0x30], 0x3fc00000 // 1.5f

		originalcode:
		divss xmm0, [esi+0x30]
		jmp dword ptr [easierMash_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> initialAngelSlayerFloorHook;
uintptr_t initialAngelSlayerFloor_jmp_ret{ NULL };
int GameHook::initialAngelSlayerFloor = 0;
static __declspec(naked) void InitialAngelSlayerFloorDetour(void) {
	_asm {
		push eax
		push esi
		mov eax, [GameHook::angelSlayerFloorAddress]
		mov esi, [GameHook::initialAngelSlayerFloor]
		mov [eax], esi
		pop esi
		pop eax
		jmp dword ptr [initialAngelSlayerFloor_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> cancellableAfterBurnerHook;
uintptr_t cancellableAfterBurner_jmp_ret{ NULL };
bool GameHook::cancellableAfterBurner_toggle = false;
uintptr_t cancellableMovesCall = 0x9E85E0;
static __declspec(naked) void CancellableAfterBurnerDetour(void) {
	_asm {
		cmp byte ptr [GameHook::cancellableAfterBurner_toggle], 0
		je originalcode

		push ecx
		mov ecx, esi // put player pointer in ecx before call
		call dword ptr [cancellableMovesCall] // "is cancellable" call
		pop ecx // restore ecx

		originalcode:
		cmp [esi+0x00000350], ebx
		jmp dword ptr [cancellableAfterBurner_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> cancellableFallingKickHook;
uintptr_t cancellableFallingKick_jmp_ret{ NULL };
bool GameHook::cancellableFallingKick_toggle = false;
uintptr_t CancellableFallingKickDefaultCall = 0x433220;
static __declspec(naked) void CancellableFallingKickDetour(void) {
	_asm {
		cmp byte ptr [GameHook::cancellableFallingKick_toggle], 0
		je originalcode

		push ecx
		mov ecx, esi // put player pointer in ecx before call
		call dword ptr [cancellableMovesCall] // "is cancellable" call
		pop ecx // restore ecx

		originalcode:
		call dword ptr [CancellableFallingKickDefaultCall]
		jmp dword ptr [cancellableFallingKick_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> turboHook;
uintptr_t turbo_jmp_ret{ NULL };
bool GameHook::openMenuPause_toggle = false;
bool GameHook::turbo_toggle = false;
float GameHook::turboValue = 1.0f;
float GameHook::turboZero = 0.0f;
static __declspec(naked) void TurboHookDetour(void) {
	_asm {
		cmp byte ptr [GameHook::openMenuPause_toggle], 1
		je zerospeed
		jmp turbocheck

		zerospeed:
		cmp byte ptr [Base::Data::ShowMenu], 0
		je turbocheck
		movss xmm0, [GameHook::turboZero]
		jmp originalcode

		turbocheck:
		cmp byte ptr [GameHook::turbo_toggle], 0
		je originalcode
		movss xmm0, [GameHook::turboValue]
		jmp originalcode

		originalcode:
		movss [edi+0x44], xmm0
		jmp dword ptr [turbo_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> altTeleInputHook;
uintptr_t altTeleInput_jmp_ret{ NULL };
uintptr_t altTeleInput_jmp_jle = 0x8BE5AC;
uintptr_t altTeleInput_jmp_je = 0x8BE5B6;
bool GameHook::altTeleInput_toggle = false;
static int altTeleInput = 0x400; // dpad down = 0x4, taunt = 0x400
static __declspec(naked) void AltTeleInputDetour(void) {
	_asm {
		cmp byte ptr [GameHook::altTeleInput_toggle], 0
		je originalcode

		push eax
		mov eax, [altTeleInput]
		test [ebx+0x00094B48], eax
		pop eax
		jnz teleport
		jmp jmp_je

		teleport:
		mov dword ptr [ebx+0x0009399C],0x00000001
		jmp dword ptr [altTeleInput_jmp_ret]

		originalcode:
		test [ebx+0x00094B48], eax
		je jmp_je
		cmp [ebx+0x000939A0], esi
		jle jmp_jle
		mov dword ptr [ebx+0x0009399C],0x0000000A // frames mashed
		jmp dword ptr [altTeleInput_jmp_ret] // Bayonetta.exe+4BE5A2, accept teleport

		jmp_jle:
		jmp dword ptr [altTeleInput_jmp_jle]

		jmp_je:
		jmp dword ptr [altTeleInput_jmp_je] // Bayonetta.exe+4BE5B6, deny teleport
	}
}
/* // unused since adding TauntWithTimeBracelet
std::unique_ptr<FunctionHook> altTauntInputHook;
uintptr_t altTauntInput_jmp_ret{ NULL };
static int altTauntInputTauntRemap = 4;
static __declspec(naked) void AltTauntInputDetour(void) {
	_asm {
		cmp byte ptr [GameHook::altTeleInput_toggle], 0
		je originalcode

		mov eax,[ecx+eax*4+0x2C]
		test eax, 0x400
		jz retcode
		mov eax, [altTauntInputTauntRemap]
		jmp retcode

		originalcode:
		mov eax,[ecx+eax*4+0x2C]

		retcode:
		ret 0004
	}
}
*/
std::unique_ptr<FunctionHook> tauntWithTimeBracelet2Hook; // tap taunt
uintptr_t tauntWithTimeBracelet2_jmp_ret{ NULL };
static __declspec(naked) void TauntWithTimeBracelet2Detour(void) {
	_asm {
		cmp byte ptr [GameHook::tauntWithTimeBracelet_toggle], 1
		je cheatcode
		cmp byte ptr [GameHook::altTeleInput_toggle], 1
		je cheatcode
		jmp originalcode

		cheatcode:
		mov eax,4

		originalcode:
		test [esi+0x00094B4C],eax
		jmp [tauntWithTimeBracelet2_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> tauntWithTimeBracelet3Hook; // hold taunt
uintptr_t tauntWithTimeBracelet3_jmp_ret{ NULL };
static __declspec(naked) void TauntWithTimeBracelet3Detour(void) {
	_asm {
		cmp byte ptr [GameHook::tauntWithTimeBracelet_toggle], 1
		je cheatcode
		cmp byte ptr [GameHook::altTeleInput_toggle], 1
		je cheatcode
		jmp originalcode

		cheatcode:
		mov eax,4

		originalcode:
		test [ebx+0x00094B44],eax
		jmp [tauntWithTimeBracelet3_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> disableSlowmoHook;
uintptr_t disableSlowmo_jmp_ret{ NULL };
static float disableSlowmoDefaultSpeed = 1.0f;
bool GameHook::disableSlowmo_toggle = false;
static __declspec(naked) void DisableSlowmoDetour(void) {
	_asm {
		cmp byte ptr [GameHook::disableSlowmo_toggle], 0
		je originalcode

		movss xmm0, [disableSlowmoDefaultSpeed]
		jmp dword ptr [disableSlowmo_jmp_ret]

		originalcode:
		movss xmm0, [ecx+0x38]
		jmp dword ptr [disableSlowmo_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> lowerDivekickHook;
uintptr_t lowerDivekick_jmp_ret{ NULL };
static float lowerDivekickTime = 7.0f;
bool GameHook::lowerDivekick_toggle = false;
static __declspec(naked) void LowerDivekickDetour(void) {
	_asm {
		cmp byte ptr [GameHook::lowerDivekick_toggle], 0
		je originalcode

		movss xmm0, [lowerDivekickTime]
		comiss xmm0,[esi+0x00093594]
		xorps xmm0,xmm0 // restore xmm0
		jmp dword ptr [lowerDivekick_jmp_ret]

		originalcode:
		comiss xmm0, [esi+0x00093594]
		jmp dword ptr [lowerDivekick_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> dualAfterBurnerHook;
uintptr_t dualAfterBurner_jmp_ret{ NULL };
bool GameHook::dualAfterBurner_toggle = false;
uintptr_t dualAfterBurnerCall = 0x9E33D0;
static __declspec(naked) void DualAfterBurnerDetour(void) {
	_asm {
		call dword ptr [dualAfterBurnerCall]
		cmp byte ptr [GameHook::dualAfterBurner_toggle], 0
		je jmpcode

		// reuse stack
		// movss xmm0,[Bayonetta.exe+9A0DD4]
		sub esp, 0x14
		// movss [esp+10],xmm0
		// movss xmm0,[Bayonetta.exe+A280B0]
		// movss [esp+0C],xmm0
		// movss xmm0,[Bayonetta.exe+A2718C]
		// movss [esp+08],xmm0
		// xorps xmm0,xmm0
		// movss [esp+04],xmm0
		// movss xmm0,[Bayonetta.exe+99D79C]
		// movss [esp],xmm0
		push 0x03
		mov ecx,esi
		call dword ptr [dualAfterBurnerCall]

		jmpcode:
		jmp dword ptr [dualAfterBurner_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> loadReplaceHook;
uintptr_t loadReplace_jmp_ret{ NULL };
bool GameHook::loadReplace_toggle = false;
static __declspec(naked) void LoadReplaceDetour(void) {
	_asm {
		push ecx
		cmp byte ptr [GameHook::loadReplace_toggle], 0
		je originalcode

		cmp edx, 0x622180 // AA
		je angelattack
		jmp originalcode

		angelattack:
		mov edx, 0x00619DD0 // stage select
		jmp originalcode

		originalcode:
		mov ecx, [eax+0x08]
		call edx
		jmp dword ptr [loadReplace_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> longerPillowTalkChargeHook;
uintptr_t longerPillowTalkCharge_jmp_ret{ NULL };
bool GameHook::longerPillowTalkCharge_toggle = false;
float longerPillowTalkChargeMult = 2.0f;
static __declspec(naked) void LongerPillowTalkChargeDetour(void) {
	_asm {
		cmp byte ptr [GameHook::longerPillowTalkCharge_toggle], 0
		je originalcode

		movss xmm0, [esp+0x04]
		mulss xmm0, [longerPillowTalkChargeMult]
		jmp dword ptr [longerPillowTalkCharge_jmp_ret]

		originalcode:
		movss xmm0, [esp+0x04] // from [00DA0DE8]
		jmp dword ptr [longerPillowTalkCharge_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> alwaysWitchTimeHook;
uintptr_t alwaysWitchTime_jmp_ret{ NULL };
bool GameHook::alwaysWitchTime_toggle = false;
float alwaysWitchTimeTimer = 120.0f;
static __declspec(naked) void AlwaysWitchTimeDetour(void) {
	_asm {
		cmp byte ptr [GameHook::alwaysWitchTime_toggle], 0
		je originalcode

		movss xmm1, [alwaysWitchTimeTimer]
		jmp dword ptr [alwaysWitchTime_jmp_ret]

		originalcode:
		movss xmm1, [esi+0x00000704]
		jmp dword ptr [alwaysWitchTime_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> getMotNameHook;
uintptr_t getMotName_jmp_ret{ NULL };
bool GameHook::getMotName_toggle = false;
uintptr_t getMotName_playerTestAddress = NULL;
uintptr_t getMotName_weaponTestAddress = NULL;
char GameHook::getMotName_playerMotString[0x128]{};
char GameHook::getMotName_weaponMotString[0x128]{};
static __declspec(naked) void GetMotNameDetour(void) {
	_asm {
		cmp byte ptr [GameHook::getMotName_toggle], 0
		je originalcode

		push eax
		cmp word ptr [edi], 0x6C70 // 'pl'
		je writeplayermotname
		cmp word ptr [edi], 0x7077 // 'wp'
		je writeweaponmotname
		jmp originalcodepop

		writeplayermotname:
		cmp [getMotName_playerTestAddress], edi
		mov [getMotName_playerTestAddress], edi
		je originalcodepop
		mov eax, [edi]
		mov dword ptr [GameHook::getMotName_playerMotString], eax
		mov eax, [edi+0x04]
		mov dword ptr [GameHook::getMotName_playerMotString+0x04], eax
		mov eax, [edi+0x08]
		mov dword ptr [GameHook::getMotName_playerMotString+0x08], eax
		mov eax, [edi+0x0C]
		mov dword ptr [GameHook::getMotName_playerMotString+0x0C], eax
		mov eax, [edi+0x10]
		mov dword ptr [GameHook::getMotName_playerMotString+0x10], eax
		mov eax, [edi+0x14]
		mov dword ptr [GameHook::getMotName_playerMotString+0x14], eax
		mov eax, [edi+0x18]
		mov dword ptr [GameHook::getMotName_playerMotString+0x18], eax
		mov eax, [edi+0x1C]
		mov dword ptr [GameHook::getMotName_playerMotString+0x1C], eax
		jmp originalcodepop

		writeweaponmotname:
		cmp [getMotName_weaponTestAddress], edi
		mov [getMotName_weaponTestAddress], edi
		je originalcodepop
		mov eax, [edi]
		mov dword ptr [GameHook::getMotName_weaponMotString], eax
		mov eax, [edi+0x04]
		mov dword ptr [GameHook::getMotName_weaponMotString+0x04], eax
		mov eax, [edi+0x08]
		mov dword ptr [GameHook::getMotName_weaponMotString+0x08], eax
		mov eax, [edi+0x0C]
		mov dword ptr [GameHook::getMotName_weaponMotString+0x0C], eax
		mov eax, [edi+0x10]
		mov dword ptr [GameHook::getMotName_weaponMotString+0x10], eax
		mov eax, [edi+0x14]
		mov dword ptr [GameHook::getMotName_weaponMotString+0x14], eax
		mov eax, [edi+0x18]
		mov dword ptr [GameHook::getMotName_weaponMotString+0x18], eax
		mov eax, [edi+0x1C]
		mov dword ptr [GameHook::getMotName_weaponMotString+0x1C], eax
		jmp originalcodepop

		originalcodepop:
		pop eax

		originalcode:
		mov al, [edi]
		xor esi, esi
		mov ebp, ecx
		jmp dword ptr [getMotName_jmp_ret]
	}
}

std::unique_ptr<FunctionHook> pl0012Hook;
const char* pl0012att = "pl0012.dat\\pl0012.att";
const char* pl0012flg = "pl0012.dat\\pl0012.flg";
static __declspec(naked) void pl0012Detour(void) {
	_asm {
		push    ebp
		push    edi
		push    esi
		mov     esi, 12973536
		push    ebx
		mov     ebx, ecx
		sub     esp, 24
		push    15139064
		call    esi
		mov     edi, eax
		mov     DWORD PTR[esp], 15139040
		call    esi
		pop     ecx
		mov     ecx, ebx
		pop     ebp
		push    edi
		push    eax
		mov     eax, 5106176
		call    eax
		pop     edx
		pop     ecx
		test    eax, eax
		je		L1
		sub     esp, 12
		push    [pl0012att]
		call    esi
		mov     esi, eax
		add     esp, 16
		test    eax, eax
		je		L3
		mov     edi, DWORD PTR[eax]
		test    edi, edi
		jle		L3
		sub     esp, 8
		mov     ecx, ebx
		mov     eax, 4528928
		add     esi, 4
		push    94730872
		push    edi
		call    eax
		lea     eax, [edi + edi * 2]
		mov     edi, 4541472
		lea     ebp, [esi + eax * 4]
		pop     eax
		pop     edx

		L4:
		sub     esp, 4
		mov     ecx, ebx
		push    DWORD PTR[esi + 8]
		add     esi, 12
		push    DWORD PTR[esi - 8]
		push    DWORD PTR[esi - 12]
		call    edi
		pop     eax
		cmp     ebp, esi
		jne		L4

		L5:
		sub     esp, 12
		mov     esi, 12973536
		mov     edi, 12958688
		push    15139396
		call    esi
		lea     ecx, [ebx + 3056]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15139368
		call    esi
		lea     ecx, [ebx + 3072]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15139340
		call    esi
		lea     ecx, [ebx + 3088]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15139312
		call    esi
		lea     ecx, [ebx + 3104]
		mov     DWORD PTR[esp], eax
		call    edi
		mov     ecx, ebx
		mov     eax, 4867920
		push    19
		call    eax
		push    [pl0012flg]
		call    esi
		mov     esi, eax
		add     esp, 16
		test    eax, eax
		je		L19
		mov     ecx, DWORD PTR[eax + 4]
		test    ecx, ecx
		je		L7
		mov     edi, DWORD PTR[eax + 8]
		test    edi, edi
		je		L7
		add     edi, eax
		xor		ebp, ebp

		L9:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[edi]
		mov     eax, 4862688
		call    eax
		add     esp, 12
		test    eax, eax
		je		L8
		mov     ecx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[ecx + 16]
		and		eax, DWORD PTR[edi + 4]
		or		eax, DWORD PTR[edi + 8]
		mov     DWORD PTR[ecx + 16], eax

		L8:
		add     ebp, 1
		add     edi, 12
		cmp     ebp, DWORD PTR[esi + 4]
		jb		L9

		L7:
		mov     edx, DWORD PTR[esi + 12]
		test    edx, edx
		je		L10
		mov     eax, DWORD PTR[esi + 16]
		test    eax, eax
		je		L10
		xor		edi, edi
		lea     ebp, [esi + eax]

		L12:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[ebp + 0 + edi * 8]
		mov     eax, 4862688
		call    eax
		add     esp, 12
		test    eax, eax
		je		L11
		mov     ecx, DWORD PTR[ebp + 4 + edi * 8]
		mov     DWORD PTR[eax + 84], ecx

		L11:
		add     edi, 1
		cmp     edi, DWORD PTR[esi + 12]
		jb		L12

		L10:
		mov     eax, DWORD PTR[esi + 20]
		test    eax, eax
		je		L13
		mov     eax, DWORD PTR[esi + 24]
		test    eax, eax
		je		L13
		xor		ebp, ebp
		lea     edi, [esi + eax]

		L15:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[edi + ebp * 8]
		mov     eax, 4862688
		call    eax
		mov     ecx, eax
		add     esp, 12
		test    eax, eax
		je		L14
		sub     esp, 12
		mov     eax, 4849216
		push    DWORD PTR[edi + 4 + ebp * 8]
		call    eax
		add     esp, 12

		L14:
		add     ebp, 1
		cmp     ebp, DWORD PTR[esi + 20]
		jb		L15

		L13:
		mov     eax, DWORD PTR[ebx]
		sub     esp, 12
		mov     ecx, ebx
		push    0
		mov     eax, DWORD PTR[eax + 8]
		call	eax
		mov     eax, 1
		mov     DWORD PTR[ebx + 26912], 0
		add     esp, 12

		L1:
		add     esp, 12
		pop     ebx
		pop     esi
		pop     edi
		pop     ebp
		ret

		L3:
		sub     esp, 8
		mov     ecx, ebx
		mov     eax, 4528928
		mov     esi, 4541472
		push    94730872
		push    3
		call    eax
		mov     ecx, ebx
		sub     esp, 12
		push    0
		push    9
		push    0
		call    esi
		mov     ecx, ebx
		push    0
		push    15
		push    41
		call    esi
		mov     ecx, ebx
		push    0
		push    6
		push    82
		call    esi
		add     esp, 20
		jmp		L5

		L19:
		xor		edi, edi
		mov     esi, 4862688

		L6:
		sub     esp, 12
		mov     ecx, ebx
		push    edi
		call    esi
		add     esp, 12
		test    eax, eax
		je		L16
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L16:
		add     edi, 1
		cmp     edi, 4
		jne		L6
		mov     edi, 8
		mov     esi, 4862688

		L18:
		sub     esp, 12
		mov     ecx, ebx
		push    edi
		call    esi
		add     esp, 12
		test    eax, eax
		je		L17
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L17:
		add     edi, 1
		cmp     edi, 12
		jne		L18
		jmp		L13
	}
}

std::unique_ptr<FunctionHook> pl0031Hook;
const char* pl0031att = "pl0031.dat\\pl0031.att";
const char* pl0031flg = "pl0031.dat\\pl0031.flg";
static __declspec(naked) void pl0031Detour(void) {
	_asm {
		push    ebp
		push    edi
		push    esi
		mov     esi, 12973536
		push    ebx
		mov     ebx, ecx
		sub     esp, 24
		push    15147736
		call    esi
		mov     edi, eax
		mov     DWORD PTR[esp], 15147712
		call    esi
		pop     ecx
		mov     ecx, ebx
		pop     ebp
		push    edi
		push    eax
		mov     eax, 5106176
		call    eax
		pop     edx
		pop     ecx
		test    eax, eax
		je		L1
		sub     esp, 12
		mov     edi, 12958688
		push    15147684
		call    esi
		lea     ecx, [ebx + 3088]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15147656
		call    esi
		lea     ecx, [ebx + 3072]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15147628
		call    esi
		lea     ecx, [ebx + 3056]
		mov     DWORD PTR[esp], eax
		call    edi
		push    [pl0031att]
		call    esi
		mov     esi, eax
		add     esp, 16
		test    eax, eax
		je		L3
		mov     edi, DWORD PTR[eax]
		test    edi, edi
		jle		L3
		sub     esp, 8
		mov     ecx, ebx
		mov     eax, 4528928
		add     esi, 4
		push    94730872
		push    edi
		call    eax
		lea     eax, [edi + edi * 2]
		mov     edi, 4541472
		lea     ebp, [esi + eax * 4]
		pop     eax
		pop     edx

		L4:
		sub     esp, 4
		mov     ecx, ebx
		push    DWORD PTR[esi + 8]
		add     esi, 12
		push    DWORD PTR[esi - 8]
		push    DWORD PTR[esi - 12]
		call    edi
		pop     eax
		cmp     ebp, esi
		jne		L4

		L5:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4867920
		push    19
		call    eax
		mov     eax, 12973536
		push    [pl0031flg]
		call    eax
		mov     esi, eax
		add     esp, 16
		test    eax, eax
		je		L85
		mov     ecx, DWORD PTR[eax + 4]
		test    ecx, ecx
		je		L9
		mov     edi, DWORD PTR[eax + 8]
		test    edi, edi
		je		L9
		add     edi, eax
		xor		ebp, ebp

		L11:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[edi]
		mov     eax, 4862688
		call    eax
		add     esp, 12
		test    eax, eax
		je		L10
		mov     ecx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[ecx + 16]
		and		eax, DWORD PTR[edi + 4]
		or		eax, DWORD PTR[edi + 8]
		mov     DWORD PTR[ecx + 16], eax

		L10:
		add     ebp, 1
		add     edi, 12
		cmp     ebp, DWORD PTR[esi + 4]
		jb		L11

		L9:
		mov     edx, DWORD PTR[esi + 12]
		test    edx, edx
		je		L12
		mov     eax, DWORD PTR[esi + 16]
		test    eax, eax
		je		L12
		xor		edi, edi
		lea     ebp, [esi + eax]

		L14:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[ebp + 0 + edi * 8]
		mov     eax, 4862688
		call    eax
		add     esp, 12
		test    eax, eax
		je		L13
		mov     ecx, DWORD PTR[ebp + 4 + edi * 8]
		mov     DWORD PTR[eax + 84], ecx

		L13:
		add     edi, 1
		cmp     edi, DWORD PTR[esi + 12]
		jb		L14

		L12:
		mov     eax, DWORD PTR[esi + 20]
		test    eax, eax
		je		L16
		mov     eax, DWORD PTR[esi + 24]
		test    eax, eax
		je		L16
		xor		ebp, ebp
		lea     edi, [esi + eax]

		L19:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[edi + ebp * 8]
		mov     eax, 4862688
		call    eax
		mov     ecx, eax
		add     esp, 12
		test    eax, eax
		je		L18
		sub     esp, 12
		mov     eax, 4849216
		push    DWORD PTR[edi + 4 + ebp * 8]
		call    eax
		add     esp, 12

		L18:
		add     ebp, 1
		cmp     ebp, DWORD PTR[esi + 20]
		jb		L19

		L16:
		mov     eax, DWORD PTR[ebx]
		sub     esp, 12
		mov     ecx, ebx
		push    0
		mov     eax, DWORD PTR[eax + 8]
		call	eax
		mov     eax, 1
		mov     DWORD PTR[ebx + 26912], 2
		add     esp, 12

		L1:
		add     esp, 12
		pop     ebx
		pop     esi
		pop     edi
		pop     ebp
		ret

		L3:
		sub     esp, 8
		mov     ecx, ebx
		mov     eax, 4528928
		mov     esi, 4541472
		push    94730872
		push    10
		call    eax
		mov     ecx, ebx
		sub     esp, 12
		push    0
		push    3
		push    91
		call    esi
		mov     ecx, ebx
		push    0
		push    4
		push    92
		call    esi
		mov     ecx, ebx
		push    0
		push    5
		push    93
		call    esi
		mov     ecx, ebx
		push    0
		push    6
		push    94
		call    esi
		mov     ecx, ebx
		push    0
		push    7
		push    95
		call    esi
		mov     ecx, ebx
		push    0
		push    8
		push    96
		call    esi
		mov     ecx, ebx
		push    0
		push    9
		push    97
		call    esi
		mov     ecx, ebx
		push    0
		push    13
		push    98
		call    esi
		mov     ecx, ebx
		push    0
		push    14
		push    99
		call    esi
		mov     ecx, ebx
		push    0
		push    15
		push    100
		call    esi
		add     esp, 20
		jmp		L5

		L85:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    0
		call    eax
		add     esp, 12
		test    eax, eax
		je		L8
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L8:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    1
		call    eax
		add     esp, 12
		test    eax, eax
		je		L20
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L20:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    2
		call    eax
		add     esp, 12
		test    eax, eax
		je		L21
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L21:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    3
		call    eax
		add     esp, 12
		test    eax, eax
		je		L22
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L22:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    4
		call    eax
		add     esp, 12
		test    eax, eax
		je		L23
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L23:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    5
		call    eax
		add     esp, 12
		test    eax, eax
		je		L24
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L24:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    6
		call    eax
		add     esp, 12
		test    eax, eax
		je		L25
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L25:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    15
		call    eax
		add     esp, 12
		test    eax, eax
		je		L26
		mov     eax, DWORD PTR[eax + 112]
		and		DWORD PTR[eax + 16], -2

		L26:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    16
		call    eax
		add     esp, 12
		test    eax, eax
		je		L27
		mov     eax, DWORD PTR[eax + 112]
		and		DWORD PTR[eax + 16], -2

		L27:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    17
		call    eax
		mov     ecx, eax
		add     esp, 12
		test    eax, eax
		je		L16
		mov     edx, DWORD PTR[eax + 112]
		sub     esp, 12
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -69
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax
		mov     eax, 4849216
		mov     DWORD PTR[ecx + 84], 18
		push    1
		call    eax
		add     esp, 12
		jmp		L16
	}
}

std::unique_ptr<FunctionHook> pl004cHook;
const char* pl004catt = "pl004c.dat\\pl004c.att";
const char* pl004cflg = "pl004c.dat\\pl004c.flg";
static __declspec(naked) void pl004cDetour(void) {
	_asm {
		push    ebp
		push    edi
		push    esi
		mov     esi, 12973536
		push    ebx
		mov     ebx, ecx
		sub     esp, 24
		push    15156328
		call    esi
		mov     edi, eax
		mov     DWORD PTR[esp], 15156304
		call    esi
		pop     ecx
		mov     ecx, ebx
		pop     ebp
		push    edi
		push    eax
		mov     eax, 5106176
		call    eax
		pop     edx
		pop     ecx
		test    eax, eax
		je		L1
		sub     esp, 12
		mov     edi, 12958688
		push    15156276
		call    esi
		lea     ecx, [ebx + 3056]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15156248
		call    esi
		lea     ecx, [ebx + 3072]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15156220
		call    esi
		lea     ecx, [ebx + 3088]
		mov     DWORD PTR[esp], eax
		call    edi
		push    15156192
		call    esi
		lea     ecx, [ebx + 3104]
		mov     DWORD PTR[esp], eax
		call    edi
		push    [pl004catt]
		call    esi
		mov     esi, eax
		add     esp, 16
		test    eax, eax
		je		L3
		mov     edi, DWORD PTR[eax]
		test    edi, edi
		jle		L3
		sub     esp, 8
		mov     ecx, ebx
		mov     eax, 4528928
		add     esi, 4
		push    94730872
		push    edi
		call    eax
		lea     eax, [edi + edi * 2]
		mov     edi, 4541472
		lea     ebp, [esi + eax * 4]
		pop     eax
		pop     edx

		L4:
		sub     esp, 4
		mov     ecx, ebx
		push    DWORD PTR[esi + 8]
		add     esi, 12
		push    DWORD PTR[esi - 8]
		push    DWORD PTR[esi - 12]
		call    edi
		pop     eax
		cmp     ebp, esi
		jne		L4

		L5:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4867920
		push    19
		call    eax
		mov     eax, 12973536
		push    [pl004cflg]
		call    eax
		mov     esi, eax
		add     esp, 16
		test    eax, eax
		je		L77
		mov     ecx, DWORD PTR[eax + 4]
		test    ecx, ecx
		je		L9
		mov     edi, DWORD PTR[eax + 8]
		test    edi, edi
		je		L9
		add     edi, eax
		xor		ebp, ebp

		L11:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[edi]
		mov     eax, 4862688
		call    eax
		add     esp, 12
		test    eax, eax
		je		L10
		mov     ecx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[ecx + 16]
		and		eax, DWORD PTR[edi + 4]
		or		eax, DWORD PTR[edi + 8]
		mov     DWORD PTR[ecx + 16], eax

		L10:
		add     ebp, 1
		add     edi, 12
		cmp     ebp, DWORD PTR[esi + 4]
		jb		L11

		L9:
		mov     edx, DWORD PTR[esi + 12]
		test    edx, edx
		je		L12
		mov     eax, DWORD PTR[esi + 16]
		test    eax, eax
		je		L12
		xor		edi, edi
		lea     ebp, [esi + eax]

		L14:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[ebp + 0 + edi * 8]
		mov     eax, 4862688
		call    eax
		add     esp, 12
		test    eax, eax
		je		L13
		mov     ecx, DWORD PTR[ebp + 4 + edi * 8]
		mov     DWORD PTR[eax + 84], ecx

		L13:
		add     edi, 1
		cmp     edi, DWORD PTR[esi + 12]
		jb		L14

		L12:
		mov     eax, DWORD PTR[esi + 20]
		test    eax, eax
		je		L16
		mov     eax, DWORD PTR[esi + 24]
		test    eax, eax
		je		L16
		xor		ebp, ebp
		lea     edi, [esi + eax]

		L19:
		sub     esp, 12
		mov     ecx, ebx
		push    DWORD PTR[edi + ebp * 8]
		mov     eax, 4862688
		call    eax
		mov     ecx, eax
		add     esp, 12
		test    eax, eax
		je		L18
		sub     esp, 12
		mov     eax, 4849216
		push    DWORD PTR[edi + 4 + ebp * 8]
		call    eax
		add     esp, 12

		L18:
		add     ebp, 1
		cmp     ebp, DWORD PTR[esi + 20]
		jb		L19

		L16:
		mov     eax, DWORD PTR[ebx]
		sub     esp, 12
		mov     ecx, ebx
		push    0
		mov     eax, DWORD PTR[eax + 8]
		call	eax
		mov     eax, 1
		mov     DWORD PTR[ebx + 26912], 0
		add     esp, 12

		L1:
		add     esp, 12
		pop     ebx
		pop     esi
		pop     edi
		pop     ebp
		ret

		L3:
		sub     esp, 8
		mov     ecx, ebx
		mov     eax, 4528928
		mov     esi, 4541472
		push    94730872
		push    3
		call    eax
		mov     ecx, ebx
		sub     esp, 12
		push    0
		push    9
		push    0
		call    esi
		mov     ecx, ebx
		push    0
		push    15
		push    41
		call    esi
		mov     ecx, ebx
		push    0
		push    6
		push    82
		call    esi
		add     esp, 20
		jmp L5

		L77:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    0
		call    eax
		add     esp, 12
		test    eax, eax
		je		L8
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L8:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    1
		call    eax
		add     esp, 12
		test    eax, eax
		je		L20
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L20:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    2
		call    eax
		add     esp, 12
		test    eax, eax
		je		L21
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L21:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    3
		call    eax
		add     esp, 12
		test    eax, eax
		je		L22
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L22:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    8
		call    eax
		add     esp, 12
		test    eax, eax
		je		L23
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L23:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    9
		call    eax
		add     esp, 12
		test    eax, eax
		je		L24
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L24:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    10
		call    eax
		add     esp, 12
		test    eax, eax
		je		L25
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax

		L25:
		sub     esp, 12
		mov     ecx, ebx
		mov     eax, 4862688
		push    11
		call    eax
		add     esp, 12
		test    eax, eax
		je		L16
		mov     edx, DWORD PTR[eax + 112]
		mov     eax, DWORD PTR[edx + 16]
		and		eax, -65
		or		ah, 32
		mov     DWORD PTR[edx + 16], eax
		jmp		L16
	}
}

// int GameHook::saveStates_SavedEnemyMovePart = 0;
// float GameHook::saveStates_SavedEnemyAnimFrame = 0.0f;
bool GameHook::saveStatesHotkeys_toggle = false;
int GameHook::saveStates_SavedEnemyMoveID = 0;
float GameHook::saveStates_SavedEnemyXYZPos[3]{0, 0, 0};
int GameHook::saveStates_SavedPlayerMoveID = 0;
float GameHook::saveStates_SavedPlayerXYZPos[3];
void GameHook::SaveStates_SaveState() {
	if (GameHook::saveStatesHotkeys_toggle) {
		uintptr_t* enemy_ptr = (uintptr_t*)GameHook::enemyLockedOnAddress;
		uintptr_t enemy_base = *enemy_ptr;
		if (enemy_base) {
			// GameHook::saveStates_SavedEnemyAnimFrame = *(float*)(enemy_base + 0x3E4);
			GameHook::saveStates_SavedEnemyMoveID = *(int*)(enemy_base + 0x34C);
			// GameHook::saveStates_SavedEnemyMovePart = *(int*)(enemy_base + 0x350);
			GameHook::saveStates_SavedEnemyXYZPos[0] = *(float*)(enemy_base + 0xD0);
			GameHook::saveStates_SavedEnemyXYZPos[1] = *(float*)(enemy_base + 0xD4);
			GameHook::saveStates_SavedEnemyXYZPos[2] = *(float*)(enemy_base + 0xD8);
		}
	}
}
void GameHook::SaveStates_LoadState() {
	if (GameHook::saveStatesHotkeys_toggle) {
		uintptr_t* enemy_ptr = (uintptr_t*)GameHook::enemyLockedOnAddress;
		uintptr_t enemy_base = *enemy_ptr;
		if (enemy_base) {
			// *(float*)(enemy_base + 0x3E4) = GameHook::saveStates_SavedEnemyAnimFrame;
			*(int*)(enemy_base + 0x34C) = GameHook::saveStates_SavedEnemyMoveID;
			*(int*)(enemy_base + 0x350) = 0; // cancel current anim
			*(float*)(enemy_base + 0xD0) = GameHook::saveStates_SavedEnemyXYZPos[0];
			*(float*)(enemy_base + 0xD4) = GameHook::saveStates_SavedEnemyXYZPos[1];
			*(float*)(enemy_base + 0xD8) = GameHook::saveStates_SavedEnemyXYZPos[2];
		}
	}
}

void GameHook::WeaponSwapCaller(void) {
	//GameHook::isCallerCalled=true;
	uintptr_t weaponSwapCallAddress = 0xC43ED0;
	//
	uintptr_t addressOf = 0x05BB8B60;
	__asm {
		pushad
		pushfd
		call weaponSwapCallAddress
		popfd
		popad
	}
	//GameHook::isCallerCalled = false;
	//GameHook::switchLimit = 90;
}


// dev functions
void GameHook::_patch(char* dst, char* src, int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void GameHook::_nop(char* dst, unsigned int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

bool install_hook_absolute(uintptr_t location, std::unique_ptr<FunctionHook>& hook, void* detour, uintptr_t* ret, ptrdiff_t next_instruction_offset = 0) {
	//assert(!hook);
	hook = std::make_unique<FunctionHook>(location, detour);
	if (!hook->create()) {
		return false;
	}

	if (next_instruction_offset) {
		if (ret) {
			*ret = location + next_instruction_offset;
		}
	}
	else {
		if (ret) {
			*ret = hook->get_original();
		}
	}
	return true;
}

void GameHook::InitializeDetours(void) {
	install_hook_absolute(0x4572BA, enemyHPHook, &EnemyHPDetour, &enemyHP_jmp_ret, 6);
	install_hook_absolute(0x9E1808, witchTimeHook, &WitchTimeMultiplierDetour, &witchTimeMultiplier_jmp_ret, 6);
	install_hook_absolute(0x8BCE4C, infMagicHook, &InfMagicDetour, &infMagic_jmp_ret, 8);
	install_hook_absolute(0x4572B2, damageDealtMultiplierHook, &DamageDealtMultiplierDetour, &damageDealtMultiplier_jmp_ret, 8);
	install_hook_absolute(0xA941FA, customCameraDistanceHook, &CustomCameraDistanceDetour, &customCameraDistance_jmp_ret, 6);
	install_hook_absolute(0x4250F7, haloDisplayHook, &HaloDisplayDetour, &haloDisplay_jmp_ret, 5);
	install_hook_absolute(0x4BD053, moveIDSwapHook, &MoveIDSwapDetour, &moveIDSwap_jmp_ret, 6);
	install_hook_absolute(0x8D2A82, punchStringIDSwapHook, &PunchStringIDSwapDetour, &punchStringIDSwap_jmp_ret, 6); //
	install_hook_absolute(0x8D2AC4, latePunchStringIDSwapHook, &LatePunchStringIDSwapDetour, &latePunchStringIDSwap_jmp_ret, 6);
	install_hook_absolute(0x8D2AE5, kickStringIDSwapHook, &KickStringIDSwapDetour, &kickStringIDSwap_jmp_ret, 6);
	install_hook_absolute(0x8D2AA3, lateKickStringIDSwapHook, &LateKickStringIDSwapDetour, &lateKickStringIDSwap_jmp_ret, 6); //
	install_hook_absolute(0x411CD4, inputIconsHook, &InputIconsDetour, &inputIcons_jmp_ret, 13);
	install_hook_absolute(0x4A8EFF, easierMashHook, &EasierMashDetour, &easierMash_jmp_ret, 5);
	install_hook_absolute(0x41C8B5, initialAngelSlayerFloorHook, &InitialAngelSlayerFloorDetour, &initialAngelSlayerFloor_jmp_ret, 10);
	install_hook_absolute(0x95ABD3, cancellableAfterBurnerHook, &CancellableAfterBurnerDetour, &cancellableAfterBurner_jmp_ret, 6);
	install_hook_absolute(0x952142, cancellableFallingKickHook, &CancellableFallingKickDetour, &cancellableFallingKick_jmp_ret, 5);
	install_hook_absolute(0x513FC7, turboHook, &TurboHookDetour, &turbo_jmp_ret, 5);
	install_hook_absolute(0x8BE592, altTeleInputHook, &AltTeleInputDetour, &altTeleInput_jmp_ret, 26);
	//install_hook_absolute(0x50137D, altTauntInputHook, &AltTauntInputDetour, &altTauntInput_jmp_ret, 7);
	install_hook_absolute(0x9E751A, tauntWithTimeBracelet2Hook, &TauntWithTimeBracelet2Detour, &tauntWithTimeBracelet2_jmp_ret, 6);
	install_hook_absolute(0x8BE5C2, tauntWithTimeBracelet3Hook, &TauntWithTimeBracelet3Detour, &tauntWithTimeBracelet3_jmp_ret, 6);
	install_hook_absolute(0x513C1E, disableSlowmoHook, &DisableSlowmoDetour, &disableSlowmo_jmp_ret, 5);
	install_hook_absolute(0x9E93B9, lowerDivekickHook, &LowerDivekickDetour, &lowerDivekick_jmp_ret, 7);
	install_hook_absolute(0x94CAAF, dualAfterBurnerHook, &DualAfterBurnerDetour, &dualAfterBurner_jmp_ret, 5);
	//install_hook_absolute(0xC798A7, getMotNameHook, &GetMotNameDetour, &getMotName_jmp_ret, 6);
	install_hook_absolute(0x6222D0, loadReplaceHook, &LoadReplaceDetour, &loadReplace_jmp_ret, 6);
	install_hook_absolute(0x4CCCA0, longerPillowTalkChargeHook, &LongerPillowTalkChargeDetour, &longerPillowTalkCharge_jmp_ret, 6);
	install_hook_absolute(0x8EF527, alwaysWitchTimeHook, &AlwaysWitchTimeDetour, &alwaysWitchTime_jmp_ret, 8);
	install_hook_absolute(0x9F5AF0, pl0012Hook, &pl0012Detour, NULL, 0);
	install_hook_absolute(0x9FC890, pl0031Hook, &pl0031Detour, NULL, 0);
	install_hook_absolute(0xA17420, pl004cHook, &pl004cDetour, NULL, 0);
}

void GameHook::onConfigLoad(const utils::Config& cfg) {
	// patches
	takeNoDamage_toggle = cfg.get<bool>("TakeNoDamageToggle").value_or(false);
	TakeNoDamage(takeNoDamage_toggle);
	focusPatch_toggle = cfg.get<bool>("FocusPatchToggle").value_or(false);
	FocusPatch(focusPatch_toggle);
	infJumps_toggle = cfg.get<bool>("InfJumpsToggle").value_or(false);
	InfJumps(infJumps_toggle);
	disableDaze_toggle = cfg.get<bool>("DisableDazeToggle").value_or(false);
	DisableDaze(disableDaze_toggle);
	forceDaze_toggle = cfg.get<bool>("ForceDazeToggle").value_or(false);
	ForceDaze(forceDaze_toggle);
	freezeTimer_toggle = cfg.get<bool>("FreezeTimerToggle").value_or(false);
	FreezeTimer(freezeTimer_toggle);
	showMessages_toggle = cfg.get<bool>("ShowMessagesToggle").value_or(true);
	disableAfterBurnerBounce_toggle = cfg.get<bool>("DisableAfterBurnerBounceToggle").value_or(false);
	DisableAfterBurnerBounce(disableAfterBurnerBounce_toggle);
	easyCutsceneSkip_toggle = cfg.get<bool>("EasyCutsceneSkipToggle").value_or(false);
	EasyCutsceneSkip(easyCutsceneSkip_toggle);
	disableLockOnDodge_toggle = cfg.get<bool>("DisableLockOnDodgeToggle").value_or(false);
	DisableLockOnDodge(disableLockOnDodge_toggle);
	noHoldDodgeOffset_toggle = cfg.get<bool>("NoHoldDodgeOffsetToggle").value_or(false);
	NoHoldDodgeOffset(noHoldDodgeOffset_toggle);
	jumpOffset_toggle = cfg.get<bool>("JumpOffsetToggle").value_or(false);
	JumpOffset(jumpOffset_toggle);
	alwaysWalkOnWalls_toggle = cfg.get<bool>("AlwaysWalkOnWallsToggle").value_or(false);
	AlwaysWalkOnWalls(alwaysWalkOnWalls_toggle);
	getMoreHalos_toggle = cfg.get<bool>("GetMoreHalosToggle").value_or(false);
	GetMoreHalos(getMoreHalos_toggle);
	moreEnemyAttacks_toggle = cfg.get<bool>("MoreEnemyAttacksToggle").value_or(false);
	MoreEnemyAttacks(moreEnemyAttacks_toggle);
	lessEnemyAttacks_toggle = cfg.get<bool>("LessEnemyAttacksToggle").value_or(false);
	LessEnemyAttacks(lessEnemyAttacks_toggle);
	infBirdTime_toggle = cfg.get<bool>("InfBirdTimeToggle").value_or(false);
	InfBirdTime(infBirdTime_toggle);
	weaponSwapOffset_toggle = cfg.get<bool>("WeaponSwapOffsetToggle").value_or(false);
	WeaponSwapOffset(weaponSwapOffset_toggle);
	retainPillowTalkCharge_toggle = cfg.get<bool>("RetainPillowTalkChargeToggle").value_or(false);
	RetainPillowTalkCharge(retainPillowTalkCharge_toggle);
	swapMashToHold_toggle = cfg.get<bool>("SwapMashToHoldToggle").value_or(false);
	SwapMashToHold(swapMashToHold_toggle);
	sixtyFpsCutscenes_toggle = cfg.get<bool>("60FpsCutscenes").value_or(false);
	SixtyFpsCutscenes(sixtyFpsCutscenes_toggle);
	jeanneBayoWT_toggle = cfg.get<bool>("JeanneBayoWTToggle").value_or(false);
	JeanneBayoWT(jeanneBayoWT_toggle);
	infDivekick_toggle = cfg.get<bool>("InfDivekickToggle").value_or(false);
	InfDivekick(infDivekick_toggle);
	//areaJumpPatch_toggle = cfg.get<bool>("AreaJumpPatchToggle").value_or(false);
	//AreaJumpPatch(areaJumpPatch_toggle);
	parryOffset_toggle = cfg.get<bool>("ParryOffsetToggle").value_or(false);
	ParryOffset(parryOffset_toggle);

	// detours
	enemyHP_no_damage_toggle = cfg.get<bool>("DealNoDamageToggle").value_or(false);
	DisableKilling(enemyHP_no_damage_toggle);
	enemyHP_one_hit_kill_toggle = cfg.get<bool>("OneHitKillToggle").value_or(false);
	witchTimeMultiplier_toggle = cfg.get<bool>("WitchTimeMultiplierToggle").value_or(false);
	witchTimeMultiplier = cfg.get<float>("WitchTimeMultiplier").value_or(1.0f);
	inf_magic_toggle = cfg.get<bool>("InfMagicToggle").value_or(false);
	inf_magic_value = cfg.get<float>("InfMagicValue").value_or(1200.0f);
	damageDealtMultiplier_toggle = cfg.get<bool>("DamageDealtMultiplierToggle").value_or(false);
	damageDealtMultiplierMult = cfg.get<float>("DamageDealtMultiplierMult").value_or(1.0f);
	customCameraDistance_toggle = cfg.get<bool>("CustomCameraDistanceToggle").value_or(false);
	customCameraDistance = cfg.get<float>("CustomCameraDistance").value_or(10.0f);
	lessClothes_toggle = cfg.get<bool>("LessClothesToggle").value_or(false);
	haloDisplay_toggle = cfg.get<bool>("HaloDisplayToggle").value_or(false);
	inputIcons_toggle = cfg.get<bool>("InputIconsToggle").value_or(false);
	inputIconsValue = cfg.get<int>("InputIconsValue").value_or(0);
	easierMash_toggle = cfg.get<bool>("EasierMashToggle").value_or(false);
	showComboUI_toggle = cfg.get<bool>("ShowComboUIToggle").value_or(false);
	comboUI_X = cfg.get<float>("ComboUI_X").value_or(0.875f);
	comboUI_Y = cfg.get<float>("ComboUI_Y").value_or(0.215f);
	initialAngelSlayerFloor = cfg.get<int>("InitialAngelSlayerFloor").value_or(0);
	cancellableAfterBurner_toggle = cfg.get<bool>("CancellableAfterBurnerToggle").value_or(false);
	cancellableFallingKick_toggle = cfg.get<bool>("CancellableFallingKickToggle").value_or(false);
	openMenuPause_toggle = cfg.get<bool>("OpenMenuPauseToggle").value_or(false);
	turbo_toggle = cfg.get<bool>("TurboToggle").value_or(false);
	turboValue = cfg.get<float>("TurboValue").value_or(1.0f);
	altTeleInput_toggle = cfg.get<bool>("AltTeleInputToggle").value_or(false);
	disableSlowmo_toggle = cfg.get<bool>("DisableSlowmoToggle").value_or(false);
	lowerDivekick_toggle = cfg.get<bool>("LowerDivekickToggle").value_or(false);
	dualAfterBurner_toggle = cfg.get<bool>("DualAfterBurnerToggle").value_or(false);
	loadReplace_toggle = cfg.get<bool>("LoadReplaceToggle").value_or(false);
	longerPillowTalkCharge_toggle = cfg.get<bool>("LongerPillowTalkChargeToggle").value_or(false);
	alwaysWitchTime_toggle = cfg.get<bool>("AlwaysWitchTimeToggle").value_or(false);
	saveStatesHotkeys_toggle = cfg.get<bool>("SaveStatesHotkeysToggle").value_or(false);
	tauntWithTimeBracelet_toggle = cfg.get<bool>("TauntWithTimeBraceletToggle").value_or(false);

	//tick
	/*comboMakerTest1 = cfg.get<bool>("ComboMakerTest1Toggle").value_or(false);
	comboMakerMoveID1 = cfg.get<int>("ComboMakerMoveID1").value_or(-1);
	comboMakerMovePart1 = cfg.get<int>("ComboMakerMovePart1").value_or(-1);
	comboMakerStringID1 = cfg.get<int>("ComboMakerStringID1").value_or(-1);
	comboMakerTest2 = cfg.get<bool>("ComboMakerTest2Toggle").value_or(false);
	comboMakerMoveID2 = cfg.get<int>("ComboMakerMoveID2").value_or(-1);
	comboMakerMovePart2 = cfg.get<int>("ComboMakerMovePart2").value_or(-1);
	comboMakerStringID2 = cfg.get<int>("ComboMakerStringID2").value_or(-1);*/
	GameHook::forceThirdAccessory_toggle = cfg.get<bool>("ForceThirdAccessoryToggle").value_or(false);
	GameHook::desiredThirdAccessory = cfg.get<int>("DesiredThirdAccessoryValue").value_or(0);
}

void GameHook::onConfigSave(utils::Config& cfg) {
	// patches
	cfg.set<bool>("TakeNoDamageToggle", takeNoDamage_toggle);
	cfg.set<bool>("FocusPatchToggle", focusPatch_toggle);
	cfg.set<bool>("InfJumpsToggle", infJumps_toggle);
	cfg.set<bool>("DisableDazeToggle", disableDaze_toggle);
	cfg.set<bool>("ForceDazeToggle", forceDaze_toggle);
	cfg.set<bool>("FreezeTimerToggle", freezeTimer_toggle);
	cfg.set<bool>("ShowMessagesToggle", showMessages_toggle);
	cfg.set<bool>("DisableAfterBurnerBounceToggle", disableAfterBurnerBounce_toggle);
	cfg.set<bool>("EasyCutsceneSkipToggle", easyCutsceneSkip_toggle);
	cfg.set<bool>("DisableLockOnDodgeToggle", disableLockOnDodge_toggle);
	cfg.set<bool>("NoHoldDodgeOffsetToggle", noHoldDodgeOffset_toggle);
	cfg.set<bool>("JumpOffsetToggle", jumpOffset_toggle);
	cfg.set<bool>("AlwaysWalkOnWallsToggle", alwaysWalkOnWalls_toggle);
	cfg.set<bool>("GetMoreHalosToggle", getMoreHalos_toggle);
	cfg.set<bool>("MoreEnemyAttacksToggle", moreEnemyAttacks_toggle);
	cfg.set<bool>("LessEnemyAttacksToggle", lessEnemyAttacks_toggle);
	cfg.set<bool>("InfBirdTimeToggle", infBirdTime_toggle);
	cfg.set<bool>("WeaponSwapOffsetToggle", weaponSwapOffset_toggle);
	cfg.set<bool>("RetainPillowTalkChargeToggle", retainPillowTalkCharge_toggle);
	cfg.set<bool>("SwapMashToHoldToggle", swapMashToHold_toggle);
	cfg.set<bool>("60FpsCutscenes", sixtyFpsCutscenes_toggle);
	cfg.set<bool>("JeanneBayoWTToggle", jeanneBayoWT_toggle);
	cfg.set<bool>("InfDivekickToggle", infDivekick_toggle);
	cfg.set<bool>("ParryOffsetToggle", parryOffset_toggle);

	//cfg.set<bool>("AreaJumpPatchToggle", areaJumpPatch_toggle);
	// detours
	cfg.set<bool>("DealNoDamageToggle", enemyHP_no_damage_toggle);
	cfg.set<bool>("OneHitKillToggle", enemyHP_one_hit_kill_toggle);
	cfg.set<bool>("WitchTimeMultiplierToggle", witchTimeMultiplier_toggle);
	cfg.set<float>("WitchTimeMultiplier", witchTimeMultiplier);
	cfg.set<bool>("InfMagicToggle", inf_magic_toggle);
	cfg.set<float>("InfMagicValue", inf_magic_value);
	cfg.set<bool>("DamageDealtMultiplierToggle", damageDealtMultiplier_toggle);
	cfg.set<float>("DamageDealtMultiplierMult", damageDealtMultiplierMult);
	cfg.set<bool>("CustomCameraDistanceToggle", customCameraDistance_toggle);
	cfg.set<float>("CustomCameraDistance", customCameraDistance);
	cfg.set<bool>("LessClothesToggle", lessClothes_toggle);
	cfg.set<bool>("HaloDisplayToggle", haloDisplay_toggle);
	cfg.set<bool>("InputIconsToggle", inputIcons_toggle);
	cfg.set<int>("InputIconsValue", inputIconsValue);
	cfg.set<bool>("EasierMashToggle", easierMash_toggle);
	cfg.set<bool>("ShowComboUIToggle", showComboUI_toggle);
	cfg.set<float>("ComboUI_X", comboUI_X);
	cfg.set<float>("ComboUI_Y", comboUI_Y);
	cfg.set<int>("InitialAngelSlayerFloor", initialAngelSlayerFloor);
	cfg.set<bool>("CancellableAfterBurnerToggle", cancellableAfterBurner_toggle);
	cfg.set<bool>("CancellableFallingKickToggle", cancellableFallingKick_toggle);
	cfg.set<bool>("OpenMenuPauseToggle", openMenuPause_toggle);
	cfg.set<bool>("TurboToggle", turbo_toggle);
	cfg.set<float>("TurboValue", turboValue);
	cfg.set<bool>("AltTeleInputToggle", altTeleInput_toggle);
	cfg.set<bool>("DisableSlowmoToggle", disableSlowmo_toggle);
	cfg.set<bool>("LowerDivekickToggle", lowerDivekick_toggle);
	cfg.set<bool>("DualAfterBurnerToggle", dualAfterBurner_toggle);
	cfg.set<bool>("LoadReplaceToggle", loadReplace_toggle);
	cfg.set<bool>("LongerPillowTalkChargeToggle", longerPillowTalkCharge_toggle);
	cfg.set<bool>("AlwaysWitchTimeToggle", alwaysWitchTime_toggle);
	cfg.set<bool>("SaveStatesHotkeysToggle", saveStatesHotkeys_toggle);
	cfg.set<bool>("TauntWithTimeBraceletToggle", tauntWithTimeBracelet_toggle);

	//tick
	/*cfg.set<bool>("ComboMakerTest1Toggle", comboMakerTest1);
	cfg.set<int>("ComboMakerMoveID1", comboMakerMoveID1);
	cfg.set<int>("ComboMakerMovePart1", comboMakerMovePart1);
	cfg.set<int>("ComboMakerStringID1", comboMakerStringID1);
	cfg.set<bool>("ComboMakerTest2Toggle", comboMakerTest2);
	cfg.set<int>("ComboMakerMoveID2", comboMakerMoveID2);
	cfg.set<int>("ComboMakerMovePart2", comboMakerMovePart2);
	cfg.set<int>("ComboMakerStringID2", comboMakerStringID2);*/

	cfg.set<bool>("ForceThirdAccessoryToggle", forceThirdAccessory_toggle);
	cfg.set<int>("DesiredThirdAccessoryValue", desiredThirdAccessory);
	cfg.save(GameHook::cfgString);
}
