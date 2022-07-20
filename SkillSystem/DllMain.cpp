#include "Header.h"
#include "WorldEvent.h"

unsigned long __stdcall InitializeThrd(void* p)
{
	UNREFERENCED_PARAMETER(p);

	Sleep(5000);
	
	int hCrtIn, hCrtOut;
	FILE *conIn, *conOut;
 

	AllocConsole();
	hCrtIn = _open_osfhandle ((intptr_t) GetStdHandle(STD_INPUT_HANDLE), _O_TEXT);
	hCrtOut = _open_osfhandle ((intptr_t) GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	conIn = _fdopen( hCrtIn, "r" );
	conOut = _fdopen( hCrtOut, "w" );
	*stdin = *conIn;
	*stdout = *conOut;


	if(Intercept(INST_CALL, (DWORD)0x004533D4, (DWORD)Hooks::Player::hkExcuteSkill, 5))
		GameServer::MainServer::WriteBlack("Hooks::Player::hkExcuteSkill - Loaded");

	if(Intercept(INST_CALL, (DWORD)0x00452F71, (DWORD)Hooks::Player::hkGameStart,5))
		GameServer::MainServer::WriteBlack("Hooks::Player::hkGameStart - Loaded");

	if(Intercept(INST_CALL, (DWORD)0x0045305B, (DWORD)Hooks::Player::hkGameRestart,5))
		GameServer::MainServer::WriteBlack("Hooks::Player::hkGameRestart - Loaded");

	if(Intercept(INST_CALL, (DWORD)0x0045362F, (DWORD)Hooks::Player::hkProcessMsg, 5))
		GameServer::MainServer::WriteBlack("Hooks::Player::hkProcessMsg - Loaded");

	if(Intercept(INST_CALL, (DWORD)0x00460BE0, (DWORD)Hooks::Player::hkChatCommand, 5))
		GameServer::MainServer::WriteBlack("Hooks::Player::hkChatCommand - Loaded");

	if(Intercept(INST_CALL, (DWORD)0x004956B0, (DWORD)Hooks::Player::hkProcess,5))
		GameServer::MainServer::WriteBlack("Hooks::Player::hkProcess - Loaded");

	if(Intercept(INST_JMP, (DWORD)0x0043F03E, (DWORD)Hooks::CMonsterReal::AllotExp, 5))
		GameServer::MainServer::WriteBlack("Hooks::CMonsterReal::AllotExp - Loaded");

	//std::unique_ptr<CWorldEvent> tWorldEvent;
	//tWorldEvent->LoadConfig();

	return TRUE;
}
void Initialize()
{
	CreateThread(0,0,InitializeThrd,0,0,0);
}
int __stdcall DllMain(HINSTANCE hModule ,unsigned long ulReason, void* pReserved)
{
	UNREFERENCED_PARAMETER(pReserved);
	DisableThreadLibraryCalls(hModule);

	if(ulReason == DLL_PROCESS_ATTACH)
	{
		Initialize();
	}

	return TRUE;
}