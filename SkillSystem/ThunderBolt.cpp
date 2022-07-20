#include "Header.h"
#include "SkillSystem.h"



struct sThunderBolt
{
	int* pTarget;
	int* pPlayer;
	char* Packet;
	char* Position;
};sThunderBolt g_ThunderBolt;

unsigned long __stdcall Thunderboltx(LPVOID sd)
{
	char* Packet = g_ThunderBolt.Packet;
	char* Posi = g_ThunderBolt.Position;
	int* pPlayer = g_ThunderBolt.pPlayer;
	    int nTargetID;
        char bType;
		GameServer::ReadPacket(Packet, Posi, "bd", &bType, &nTargetID);
 
        int* pTarget = 0;
		
        switch(bType)
        {
            case 0:
                pTarget = (int*)GameServer::Player::FindPlayer(nTargetID);
            break;
            case 1:
                pTarget = (int*)GameServer::Monster::FindMonster(nTargetID);
            break;
        }
		int nDmg = 500;
		if(pTarget)
		{
			//for(int i = 0; i < 5; i++)
			//{				
				GameServer::Player::WriteInSight(pPlayer, 0x3f, "bddbbwwb", 75, pPlayer[7], pTarget[7], 1, 1, nDmg, 0, true); // Send to all Clients Arround Animation                    
                        
				int pid = 0;
				int a1 = 0;
				int a2 = 0;
 
				int v22 = GameServer::Char::GetASpeed(pPlayer); // Get Attack Speed

				int v23 = GetTickCount();

 
				int v25 = 0;
				if(v23 < pTarget[362])
				v25 -= pTarget[362] - v23;
 
				pTarget[362] = v22 + v23;
 
				if(pTarget[115] == 1)
				pid = 0;
				else
				pid = v25 * (*(int (__thiscall **)(DWORD *, int))(*pPlayer + 168))((DWORD*)pPlayer, (int)pTarget) / v22; // dont remember the real func xd

				int Death = (*(int (__thiscall **)(int, int, int, int *, int *, int *, int))(*(DWORD *)pTarget+ 72))((int)pTarget,(int)pPlayer,nDmg,&a1,&a2,&pid,0); // Damage the Monster

				if(!Death)
				(*(void (__thiscall **)(void*, int*))(*(DWORD *)pTarget+0x50))(pTarget, pPlayer); // Add Aggro to Target
						
							   
				Sleep(900);

			//}
			GameServer::Player::WriteInSight(pPlayer, 0x3f, "bddbbwwb", 75, pPlayer[7], pTarget[7], 1, 1, nDmg, 0, false); 
								
			GameServer::ObjectReleases((void *)pTarget, LONG(pTarget) + 0x160);
}
	return TRUE;
}

void CMage::Thunderbolt()
{


}