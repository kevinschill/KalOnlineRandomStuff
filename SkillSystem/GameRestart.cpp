#include "Header.h"
#include "CDatabase.h"

void __fastcall Hooks::Player::hkGameRestart(int* Player,void* _edx)
{
	UNREFERENCED_PARAMETER(_edx);
	std::unique_ptr<CDatabase> pDatabase(new CDatabase);
	
	for (std::vector<SPlay>::iterator b = vPlay.begin(); b != vPlay.end();) 
	{ 
		if (b->Pointer == Player) 
		{
			b = vPlay.erase( b );
		}
		else
			++b;
	}

	GameServer::Player::GameRestart(Player);
}