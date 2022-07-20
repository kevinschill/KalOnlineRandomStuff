#include "Header.h"
#include "CDatabase.h"
#include "CRewardQuest.h"
#include "ConfigParser.h"


std::vector<SPlay> vPlay;
extern CRewardQuest* g_RewardQuest;



void __fastcall Hooks::Player::hkGameStart(int* Player,void* _edx)
{
	UNREFERENCED_PARAMETER(_edx);
	std::unique_ptr<CDatabase> pDatabase(new CDatabase);

	SPlay sPlay;
	sPlay.Pointer = Player;
	
	pDatabase->Connect();
	std::map<int,int> mPlayerSkills = pDatabase->getSkill(Player[113]);
	pDatabase->Disconnect();

	sPlay.mSkills = mPlayerSkills;

	vPlay.push_back(sPlay);

	for(std::vector<SRewardQuest>::iterator it = g_RewardQuest->vRewardVector.begin(); it != g_RewardQuest->vRewardVector.end(); ++it)
	{
		if(it->PlayerPID == Player[113])
			it->Player = Player;
	}
	for(std::vector<SRewardRepeat>::iterator itRepeat = g_RewardQuest->vRepeatVector.begin(); itRepeat != g_RewardQuest->vRepeatVector.end(); ++itRepeat)
	{
		if(itRepeat->PlayerPID == Player[113])
			itRepeat->Player = Player;
	}

	GameServer::Player::GameStart(Player);
}