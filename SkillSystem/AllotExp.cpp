#include "Header.h"
#include "CPlayer.h"
#include "CRewardQuest.h"


CPlayer* g_Player = new CPlayer;
void KillEvent(int Index,int* Player)
{
	for(std::vector<SWorldEvent>::iterator itKill = vWorldEvent.begin(); itKill != vWorldEvent.end(); itKill++)
	{
			if(itKill->TargetIndex == Index)
			{
					for(std::vector<SWorldEventCounter>::iterator it = vWorldEventCounter.begin(); it != vWorldEventCounter.end(); it++)
					{
						if(it->Index == itKill->TargetIndex)
						{
							it->Counter+=1;
							int left = itKill->TargetAmount - it->Counter;
							std::stringstream s;
							s << "[" << left << "] " << "Monster left for Boss";
							GameServer::Player::Write(Player, 0xF, "s",s.str().c_str());
							if(it->Counter >= itKill->TargetAmount)
							{
								SpawnMonster(itKill->BossIndex,itKill->CoordX,itKill->CoordY,itKill->Map,itKill->BossAmount,1);
								it->Counter = 0;
							}
				
						}
				}
				
			}
		
	}
}
DWORD back = 0x0043F053;
DWORD updatepr = 0x00458800;

int* PlayerPtr = 0;
int Exp = 0;

int* pMonster = 0;

extern CRewardQuest* g_RewardQuest;

int __declspec(naked) Hooks::CMonsterReal::AllotExp()
{
	Exp = 0;
	PlayerPtr = 0;
	
	_asm
	{
			PUSHAD
			PUSHFD

			mov		edx, [ebp - 74h]
			mov		pMonster, edx

			mov		Exp, eax
			mov     edx, [ebp - 2Ch]
			mov		PlayerPtr, edx
	}
	if(pMonster)
		g_RewardQuest->AddKill(PlayerPtr[113],((int*)pMonster[110])[15]);
		//KillEvent(((int*)pMonster[110])[15],PlayerPtr);

	if (PlayerPtr)
	{
		g_Player->pObject = PlayerPtr;

		if(g_Player->getLevel() < 50)
		{
			Exp = (int)Exp * 5.0;
		}
		GameServer::Player::UpdateProperty((int)g_Player->pObject,25,1,Exp);
	}
	__asm{
			POPFD
			POPAD
			mov edx, back
			JMP edx
	}
}