#include "Header.h"
#include "CPlayer.h"


int getState(int* pt)
{
	return pt[12];
}
void setState(int* pt,int nr)
{
	pt[12] = nr;
}
static LONG (__thiscall *SendItemInfo)(void *a5,int, char a6) = (LONG (__thiscall*)(void *a5, int,char a6))0x00427430; 
static void* (__thiscall *FindItem)(void* a5, int a2,int a6) = (void* (__thiscall*)(void*,int, int a6))0x0045D190; 

static void (__cdecl *SocketWrite)(void *Socket, unsigned char Type, const char* Format, ...) = (void (__cdecl*)(void*, unsigned char, const char*, ...))0x004948c0;
void __fastcall Hooks::Player::hkChatCommand(int* Player, void* _edx, const char* command)
{
	UNREFERENCED_PARAMETER(_edx);
	bool forward = true;
	if (IsPointerValid((DWORD)Player))
	{
		std::string strCommand = command;
		if(strCommand == "/ta")
		{
			//forward = false;
			//std::unique_ptr<CPlayer> tPlayer(new CPlayer(Player));
			//WORD newOtp = tPlayer->getStats(OTP,false) + 10;
			//524544
			//GameServer::Player::UpdatePrtyPt((int)Player,9,1,newOtp,newOtp);
			//Spawn(567,Player[83]+50,Player[84],0,1,1); AR
			//int* psock = (int*)Player[419];
			//SocketWrite(Player,99,"s","hallo");
			GameServer::Player::Write(Player,99,"s","Daniel is NUUUUUUUUUUUUUUUUUUUUUUB");
			//WSASend(*(DWORD *)(psock + 16), &Buffers, 1u, &NumberOfBytesSent, 0, (LPWSAOVERLAPPED)(psock + 72), 0)

		}
		if(strCommand == "/mute")
		{
			forward = false;
			
			mMute[Player] = GetTickCount64();
		}
		if(strCommand == "/dss")
		{
			forward = false;
			int* itemp = (int*)FindItem(Player,799,1);
			for(int i = 524544; i < 1000000; i++)
			{
				printf("ItemState[%d]\n",getState(itemp));
				setState(itemp,i);
				SendItemInfo(itemp,(int)Player,92);
				Sleep(10);
			}

		}
		if(strCommand == "/tra")
		{
			forward = false;

			int* unk = (int*)Player[277];
			unk[26] = 3;
			Player[278] = 3;
			//*(_DWORD *)(pPlayer + 1112) |= TransformNr;
			GameServer::Char::AddGState(Player, 512);
			GameServer::Player::WriteInSight(Player, 61, "dbb",Player[7],13,Player[278]);

		}
	}
	if (forward)
		GameServer::Player::ChatCommand(Player, command);
}