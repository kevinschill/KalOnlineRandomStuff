#ifndef HEADER_H
#define HEADER_H

#include <Windows.h>


#include <sstream>

#include <memory>
#include <vector>
#include <list>
#include <map>

#include <fcntl.h>
#include <io.h>

#include <cstdint>

struct SPlay
{
	int* Pointer;
	std::map<int,int> mSkills;
};
struct SWorldEvent
{
	int TargetIndex;
	int TargetAmount;
	int BossIndex;
	int BossAmount;
	int CoordX;
	int CoordY;
	int Map;
};
struct SWorldEventCounter
{
	int Index;
	int Counter;
};

extern std::vector<SWorldEventCounter> vWorldEventCounter;
extern std::vector<SPlay> vPlay;
extern std::map<int*,unsigned long long> mMute;
extern std::vector <SWorldEvent> vWorldEvent;

namespace GameServer
{
	static char* (__cdecl* ReadPacket)(char *pPacket, char *pPos, const char *sFormat, ...) = (char* (__cdecl*)(char*, char*, const char*, ...))0x4975F0;
	static int (__thiscall* unknown_libname_65)(void *_this) = (int(__thiscall*)(void* _this))0x0042F830;
	static LONG (__thiscall* ObjectReleases)(void* pOject, LONG lpAddend) = (LONG (__thiscall*)(void*, LONG))0x4239C0;
	static void* (__thiscall* sub_4935A0)(DWORD* _this, int a2, int a3) = (void* (__thiscall*)(DWORD* _this, int a2, int a3))0x004935A0;
	static signed int (__cdecl* sub_406E10)(signed int a1, signed int a2) = (signed int (__cdecl*)(signed int a1, signed int a2))0x406E10;

	namespace MainServer
	{
		static void (__cdecl* WriteBlack)(char* text,  ...) = (void (__cdecl*)(char* text, ...))0x00432890;
		static void (__cdecl* WriteRed)(char* text,  ...) = (void (__cdecl*)(char* text, ...))0x004328C0;
		static void (__cdecl* WriteBlue)(char* text,  ...) = (void (__cdecl*)(char* text, ...))0x00432860;
	}
	namespace Player
	{
		static int (__thiscall *GameStart)(void *thisp) = (int (__thiscall*)(void*))0x00458270;
		static int (__thiscall *GameRestart)(void* thisp) = (int (__thiscall*)(void *thisp ))0x004585B0;
		static void(__thiscall *Process)(int *Player, int PacketHeader, char *Packet, char *Pos) = (void(__thiscall*)(int*, int, char *, char *))0x00452ED0;
		static int(__thiscall *ChatCommand)(int* pPlayer, const char* szCommand) = (int(__thiscall*)(int* pPlayer, const char* szCommand))0x00461080;
		static int(__thiscall *ExecuteSkill)(void *Player, signed int SkillID, char* Packet, char* Position) = (int(__thiscall*)(void *Player, signed int SkillID, char* Packet, char* Position))0x0047FBB0; 
		static void (__cdecl* WriteInSight) (void* pPlayer, BYTE bType, const char *Format, ...) = ( void (__cdecl*) (void*, BYTE, const char*, ...))0x0040B9E0;
		static void* (__cdecl* FindPlayer) (int nID) = (void* (__cdecl*) (int))0x00450810;
		static signed int (__thiscall* CanAttack)(void* Player, int* Target, int unk) = (signed int(__thiscall*) (void* Player, int* Target, int unk))0x0046AE50;
		static char* (__cdecl *UpdateProperty)(int Player, int ID, int Type, signed __int64 Amount) = (char* (__cdecl*)(int Player, int ID, int Type, signed __int64 Amount))0x00458800; 
		static int(__thiscall *InfoDie)(int* Player, int TargetID, int unknown) = (int(__thiscall*)(int* Player, int TargetID, int unknown))0x00451CF0;
		static int(__thiscall *GetDropItemMask)(int* Player) = (int(__thiscall*)(int* Player))0x0046B310;
		static void* (__cdecl *Write)(int* pPlayer, unsigned char Type, const char* szFormat, ...) = (void* (__cdecl*)(int* pPlayer, unsigned char Type, const char* szFormat, ...))0x00452e60;
		static void* (__cdecl *WriteAll)(unsigned char Type, const char* szFormat, ...) = (void* (__cdecl*)(unsigned char Type, const char* szFormat, ...))0x00450910;
		static int(__thiscall *AddBuff)(int* pPlayer, int Buff) = (int(__thiscall*)(int* pPlayer, int Buff))0x0046B390;
		static void (__cdecl *UpdatePrtyPt)(int, signed int, signed int, __int32, __int32) = (void (__cdecl *)(int, signed int, signed int, __int32, __int32))0x00459840; 
		static void (__thiscall *ProcessMsg)(void *_this, char *a2) = (void (__thiscall*)(void* _this,char* a2))0x00460A50;
	}
	namespace Char
	{
		static __int64 (__thiscall *IsMState)(void* thispointer, __int64 a2) = (__int64 (__thiscall*)(void* thispointer, __int64 a2))0x00406BA0;
		static __int64 (__thiscall *IsBstate)(void* thispointer, __int64 a2) = (__int64 (__thiscall*)(void* thispointer, __int64 a2))0x00409720;
		static int (__thiscall *GetASpeed)(void *Char) = (int (__thiscall*)(void*))0x0043D8E0;
		static bool (__thiscall *IsNormal)(void* thispointer) = (bool (__thiscall*)(void* thispointer))0x0040B280; 
		static int(__thiscall *AddGState)(int* pPlayer, int State) = (int(__thiscall*)(int* pPlayer, int State))0x00409910;
		static void(__thiscall *CancelAllBuff)(int* pPlayer) = (void(__thiscall*)(int* pPlayer))0x0040B750;
		static int(__thiscall *IsGState)(int* pPlayer, int State) = (int(__thiscall*)(int* pPlayer, int State))0x0040B310;
		static int (__thiscall *GetMinAttack)(int)  = (int (__thiscall*)(int))0x0043D9A0;
		static int (__thiscall *GetMaxAttack)(int thispointer) = (int (__thiscall*)(int thispointer))0x0043D9D0; 
		static int (__thiscall *GetStr)(int)  = (int (__thiscall*)(int))0x0043BE20;
		static int (__thiscall *GetHth)(int)  = (int (__thiscall*)(int))0x0043BE60;
		static int (__thiscall *GetInt)(int)  = (int (__thiscall*)(int))0x0043BEA0;
		static int (__thiscall *GetWis)(int)  = (int (__thiscall*)(int))0x0043BEE0;
		static int (__thiscall *GetDex)(int)  = (int (__thiscall*)(int))0x0043BF20;
		static int (__thiscall *GetHit)(void *Char) = (int (__thiscall*)(void*))0x0048E510;
		static int (__thiscall *GetDodge)(void *Char) = (int (__thiscall*)(void*))0x0043DB90;
		static void(__thiscall *CancelBuff)(void*, int a5) = (void(__thiscall*)(void*, int a5))0x0040B6A0;
		static int(__cdecl* CreateBuff)(int BuffIndex, __int32 BuffCooldown, int StatIncrease, int a4) = (int(__cdecl*)(int, __int32, int, int))0x00402610;
		
	}
	namespace Monster
	{
		static void* (__cdecl* FindMonster) (int nID) = (void* (__cdecl*) (int))0x0043A240;
		static void(__thiscall* AllotExp)(int _this, DWORD *a2, DWORD *a3, DWORD *a4) = (void(__thiscall*)(int _this, DWORD *a2, DWORD *a3, DWORD *a4))0x0043ECC0;
		
	}
	namespace MonsterMagic
	{
		static int (__cdecl *Create)(int a1, int a2, int a3, int a4, int a5, int a6, int a7) = (int (__cdecl*)(int a1, int a2, int a3, int a4, int a5, int a6, int a7))0x00441DE0;

	}
	namespace InitMonster
	{
		static int(__thiscall *DropItem)(int _this, int a2, int a3, int a4, int a5, int a6) = (int(__thiscall*)(int _this, int a2, int a3, int a4, int a5, int a6))0x00437D70;
	}
	namespace BaseList
	{
		static int(__thiscall* Pop)(void* unknown) = (int(__thiscall*)(void* unknown))0x00402430;

	}
	namespace IOCriticalSection
	{
		static void(__thiscall *Enter)(void *Section) = (void(__thiscall*)(void*))0x00423640;
		static void(__thiscall *Leave)(void *Section) = (void(__thiscall*)(void*))0x004236d0;
	}
	namespace Link
	{
		static void(__thiscall* MoveTo)(void *Object, int x) = (void(__thiscall*)(void*, int))0x00438C40;
	}
}
namespace Hooks
{
	namespace CMonsterReal
	{
		int AllotExp();
	}
	namespace Player
	{
		void __fastcall hkProcess(int *Player, void* _edx, int PacketHeader, char *Packet, char *Pos);
		void __fastcall hkProcessMsg(int* Player,void* _edx, char* Message);
		void __fastcall hkGameStart(int* Player,void* _edx);
		void __fastcall hkGameRestart(int* Player,void* _edx);
		void __fastcall hkExcuteSkill(int* PointToPlayerBase, void* _edx, signed int nSkillID, char* PacketPointer, char* PositionPointer);
		void __fastcall hkChatCommand(int* Player, void* _edx, const char* command);
	}
}

#define INST_NOP 0x90 
#define INST_CALL 0xe8 
#define INST_JMP 0xe9 
#define INST_BYTE 0x00 
#define SHORT_JZ 0x74

void MemcpyEx(DWORD destination, DWORD source, int length);
DWORD Intercept(BYTE instruction, DWORD lpSource, DWORD lpDest, int len);
void SpawnMonster(int Monsterindex, int x, int y, int map, int amount, int spawntime);

bool IsPointerValid(DWORD p);


#endif