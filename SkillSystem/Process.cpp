#include "Header.h"
#include "CPlayer.h"
#include "Buff.h"
#include "CRewardQuest.h"

CRewardQuest* g_RewardQuest = new CRewardQuest;

bool CustomQuest(int* Player,int Quest)
{
	switch(Quest)
	{
		case 9000: // Accept
			{
				g_RewardQuest->InsertQuest(Player,9001,1,2,4,"Demon Vulgar");
				return true;
			}
		break;
		case 9001: // Turn in
			{
				g_RewardQuest->QuestComplete(Player[113],9001);
				return true;
			}
		break;
		case 9002: // Accept
			{
				g_RewardQuest->InsertQuest(Player,9003,2,2,4,"Demon Scout");
				return true;
			}
		break;
		case 9003: // Turn in
			{
				g_RewardQuest->QuestComplete(Player[113],9003);
				return true;
			}
		break;
	}
	return false;
}
std::map<int*, DWORD64> DropProtect;
void __fastcall Hooks::Player::hkProcess(int *Player, void* _edx, int PacketHeader, char *Packet, char *Pos)
{
	UNREFERENCED_PARAMETER(_edx);
	bool forward = true;

	if(PacketHeader == 0x1a)
	{
		std::map<int*, DWORD64>::iterator it;
		DWORD64 tTime = GetTickCount64();
		it = DropProtect.find(Player);
		if (it != DropProtect.end())
		{
			unsigned long long newTime = GetTickCount64() - it->second;
			if (newTime < 5000)
			{
				GameServer::Player::Write(reinterpret_cast<int*>(Player), 0x3c, "ss", "Drop Protection", "Drop is on Cooldown.");
				forward = false;
			}
			else
				DropProtect[Player] = tTime;
		}
		else
			DropProtect[Player] = tTime;
	}
	if(PacketHeader == 0x2b)
	{
		char bType;
		int iTargetID;
		GameServer::ReadPacket(Packet,Pos,"bd",&bType,&iTargetID);

		if(bType == 47)
		{
			GameServer::Player::WriteInSight(Player, 61, "dbbd",Player[7],5,bType,iTargetID);
			forward = false;
		}
		if(bType == 67)
		{
			GameServer::Player::WriteInSight(Player, 61, "dbbd",Player[7],5,bType,iTargetID);
			forward = false;
		}
	}
	if(PacketHeader == 51)
	{
		int Quest = 0;
		GameServer::ReadPacket(Packet, Pos, "d", &Quest);
	
		if (GameServer::Char::IsGState(Player, 256) && Quest && Quest == 393281539)
			GameServer::Player::Write(Player, 95, "b", 9);
		else
			if(CustomQuest(Player,(Quest >> 16)))
				forward = false;
	}


	if(forward)
		GameServer::Player::Process(Player,PacketHeader,Packet,Pos);
}