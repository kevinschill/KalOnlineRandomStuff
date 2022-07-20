#include "Header.h"
#include "SkillSystem.h"

int CSkill::getGrade(BYTE bIndex)
{
	for(auto PlayerSkills: vPlay)
	{
		if(PlayerSkills.Pointer == this->mPlayer->pObject)
		{
			for(std::map<int,int>::iterator it = PlayerSkills.mSkills.begin(); it != PlayerSkills.mSkills.end(); it++) 
			{
				if(it->first == bIndex)
					return it->second;
			}
		}
	}
	return 0;
}
void CSkill::ConsumeMana(int Amount)
{
	GameServer::Player::UpdateProperty((int)this->mPlayer->pObject,8,0,Amount);
}
bool CSkill::isInArea(int* Object,int Target_X,int Target_Y,int Area)
{
	if(Object && Object[83] < Target_X + Area && Object[83] > Target_X - Area && Object[84] < Target_Y + Area && Object[84] > Target_Y - Area && Object[70] != 1)
		return true;
	else
		return false;
}
bool CSkill::bExecuteSkill(int* Target)
{
	if(GameServer::Player::CanAttack(this->mPlayer->pObject,Target,0) && GameServer::Char::IsNormal(Target) && this->mPlayer->getMap() == Target[79] && this->mPlayer->pObject != Target )
		return true;
	else
		return false;
}
int CSkill::ActionBeforeDamage(int* Target)
{
	int pid = 0;
 
	int v22 = GameServer::Char::GetASpeed(this->mPlayer->pObject);
	int v23_gettick = GetTickCount();
 
	int v25 = 0;
	if (v23_gettick < Target[362])
	v25 -= Target[362] - v23_gettick;
 
	Target[362] = v22 + v23_gettick;
 
	if (Target[115] == 1)
		return pid = 0;
	else
		return pid = v25 * (*(int (__thiscall **)(DWORD *, int))(*this->mPlayer->pObject + 168))((DWORD*)this->mPlayer->pObject, (int)Target) / v22;
	
	return 0;
}

void* CSkill::getTargetList(int Range,int* Target)
{
	void* pReturn = 0;
	DWORD ardx = 0x004935A0;
	//pReturn = (void*)GameServer::sub_4935A0((DWORD*)Target[35],Target[36],Range);
	_asm
	{
		push    Range
		mov     ecx, [Target]
		add     ecx, 144h
		push    ecx
		mov     edx, [Target]
		mov     ecx, [edx+140h]
		call    ardx
		mov		pReturn, eax
	}
	
	return pReturn;
}
std::vector<int> CSkill::getTargets(int Range,int* Target)
{
	void* pReturn = 0;
	DWORD ardx = 0x004935A0;
	//pReturn = (void*)GameServer::sub_4935A0((DWORD*)Target[35],Target[36],Range);
	_asm
	{
		push    Range
		mov     ecx, [Target]
		add     ecx, 144h
		push    ecx
		mov     edx, [Target]
		mov     ecx, [edx+140h]
		call    ardx
		mov		pReturn, eax
	}

	std::vector<int> mobIds;
	while(pReturn)
	{
		int* t = (int*)GameServer::unknown_libname_65(pReturn);
		mobIds.push_back(t[7]);
		pReturn = (void*)GameServer::BaseList::Pop(pReturn);
	}

	return mobIds;
}
std::list<int*> CSkill::getAroundList(int Range,int* Target)
{
	void* pReturn = 0;
	DWORD ardx = 0x004935A0;
	_asm
	{
		push    Range
		mov     ecx, [Target]
		add     ecx, 144h
		push    ecx
		mov     edx, [Target]
		mov     ecx, [edx+140h]
		call    ardx
		mov		pReturn, eax
	}

	std::list<int*> mobIds;
	while(pReturn)
	{
		int* t = (int*)GameServer::unknown_libname_65(pReturn);
		if(t[6] == 1)
			mobIds.push_back((int*)GameServer::Player::FindPlayer(t[7]));
		else
			mobIds.push_back((int*)GameServer::Monster::FindMonster(t[7]));
		pReturn = (void*)GameServer::BaseList::Pop(pReturn);
	}

	return mobIds;
}
int* CSkill::getTarget(char bType,int iTargetID)
{
	switch(bType)
	{
		case 0:
			return (int*)GameServer::Player::FindPlayer(iTargetID);
		break;
			
		case 1:
			return (int*)GameServer::Monster::FindMonster(iTargetID);
		break;
	}
	return 0;
}

int CSkill::DamageMonster(int* Target,int Damage,int Unknown)
{
	int a1,a2 = 0;
	return (*(int(__thiscall **)(int, int, int, int *, int *, int *, int))(*(DWORD *)Target + 72))((int)Target, (int)this->mPlayer->pObject, Damage, &a1, &a2, &Unknown, 0);
}

void CSkill::AddAggro(int* Target)
{
	(*(void (__thiscall **)(void*, int*))(*(DWORD *)Target+0x50))(Target, this->mPlayer->pObject);
}