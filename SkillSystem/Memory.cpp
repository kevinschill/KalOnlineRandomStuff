#include "Header.h"

bool IsPointerValid(DWORD p)
{
	__try
	{
		DWORD x = *(DWORD*)(p);
 
		return true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		printf("Invalid Pointer\n");
		return false;
	}
}
void MemcpyEx(DWORD destination, DWORD source, int length)
{
	DWORD oldSource = 0;
	DWORD oldDestination = 0;
	VirtualProtect((LPVOID)source, length, PAGE_EXECUTE_READWRITE, &oldSource);
	VirtualProtect((LPVOID)destination, length, PAGE_EXECUTE_READWRITE, &oldDestination);
	memcpy((void*)destination, (void*)source, length);
	VirtualProtect((LPVOID)destination, length, oldDestination, &oldDestination);
	VirtualProtect((LPVOID)source, length, oldSource, &oldSource);
}
DWORD Intercept(BYTE instruction, DWORD lpSource, DWORD lpDest, int len)
{
	DWORD realtarget = 0;
	LPBYTE buffer = new BYTE[len];
	memset(buffer, 0x90, len); //Fill out with nops 
	if (instruction != INST_NOP && len >= 5){
		buffer[(len - 5)] = instruction;
		DWORD dwJMP = (DWORD)lpDest - (lpSource + 5 + (len - 5));
		memcpy(&realtarget, (void*)(lpSource + 1), 4);
		realtarget = realtarget + lpSource + 5;
		memcpy(buffer + 1 + (len - 5), &dwJMP, 4);
	}
	if (instruction == SHORT_JZ){
		buffer[0] = instruction;
		buffer[1] = (BYTE)lpDest;
	}
	if (instruction == INST_BYTE){
		buffer[0] = (BYTE)lpDest;
	}
	MemcpyEx(lpSource, (DWORD)buffer, len);
	delete[] buffer;
	return realtarget;
}
void Dereference(DWORD destination, DWORD source, int length)
{
    DWORD oldSource      = 0;
    DWORD oldDestination = 0;
    VirtualProtect((LPVOID)source,length,PAGE_EXECUTE_READWRITE,&oldSource);
    VirtualProtect((LPVOID)destination,length,PAGE_EXECUTE_READWRITE,&oldDestination);
    *((DWORD *)destination) = source;
    VirtualProtect((LPVOID)destination,length,oldDestination,&oldDestination);
    VirtualProtect((LPVOID)source,length,oldSource,&oldSource);
}

void SpawnMonster(int Monsterindex, int x, int y, int map, int amount, int spawntime)
{
    Dereference((DWORD)0x0044402B,(DWORD)Monsterindex,4);
	Dereference((DWORD)0x004440A6,(DWORD)x,4);
    Dereference((DWORD)0x004440AD,(DWORD)y,4);
    Dereference((DWORD)0x004440BA,(DWORD)map,4);
    Dereference((DWORD)0x00444129,(DWORD)spawntime,4);

    for (int i = 0; i < amount; i++)
    {
        __asm push 0
        __asm mov edx, 0x00443FD0
        __asm call edx
        __asm add esp, 4
    }
}