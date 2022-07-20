#include "Header.h"
#include "CPlayer.h"

int CPlayer::Damage(int* Target,int Damage)
{
	int a1,a2,Unknown = 0;
	int Death = (*(int(__thiscall **)(int, int, int, int *, int *, int *, int))(*(DWORD *)Target + 72))((int)Target, (int)this->pObject, Damage, &a1, &a2, &Unknown, 0);
	if(Death)
		this->TargetDeath = true;
	else
		this->TargetDeath = false;

	return Damage;
}
void CPlayer::ConsumeMana(int Amount)
{
	GameServer::Player::UpdateProperty((int)this->pObject,8,0,Amount);
}
std::list<CPlayer*> CPlayer::GetAroundList(int Range,int* Target)
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

	std::list<CPlayer*> mobIds;
	CPlayer* tt = new CPlayer;
	while(pReturn)
	{
		int* t = (int*)GameServer::unknown_libname_65(pReturn);
		if(t[6] == 1)
		{
			tt->pObject = (int*)GameServer::Player::FindPlayer(t[7]);
			mobIds.push_back(new CPlayer(tt->pObject));
		}
		else
		{
			tt->pObject = (int*)GameServer::Monster::FindMonster(t[7]);
			mobIds.push_back(new CPlayer(tt->pObject));
		}
			pReturn = (void*)GameServer::BaseList::Pop(pReturn);
	}
	delete tt;
	return mobIds;
}

bool CPlayer::canAttack(int* Target)
{
	if(GameServer::Player::CanAttack(this->pObject,Target,0) && GameServer::Char::IsNormal(Target) && this->getMap() == Target[79] && this->pObject != Target )
		return true;
	else
		return false;
}
void CPlayer::IncreaseOTP(int Amount)
{
	GameServer::Player::UpdatePrtyPt((int)this->pObject,9,1,Amount,Amount);
}
void CPlayer::IncreaseEvasion(int Amount)
{
	GameServer::Player::UpdatePrtyPt((int)this->pObject,10,1,Amount,Amount);
}
void CPlayer::UpdateProperty(BYTE bID,BYTE bType,int Amount)
{
	GameServer::Player::UpdateProperty((int)this->pObject,bID,bType,Amount);
}
unsigned short CPlayer::getStats(BYTE bType,bool Bonus)
{
	if(Bonus)
	{
		switch(bType)
		{
			case Strength:
				return this->pObject[23];
			break;
			case Health:
				return this->pObject[24];
			break;
			case Intelligence:
				return this->pObject[25];
			break;
			case Agility:
				return this->pObject[27];
			break;
			case Wisdom:
				return this->pObject[26];
			break;
		}
	}
	else
	{
		switch(bType)
		{
			case Strength:
				return this->pObject[16];
			break;
			case Health:
				return this->pObject[17];
			break;
			case Intelligence:
				return this->pObject[18];
			break;
			case Agility:
				return this->pObject[20];
			break;
			case Wisdom:
				return this->pObject[19];
			break;
			case OTP:
				return this->pObject[30];
			break;
			case Evasion:
				return this->pObject[31];
			break;
			case MinPhyDmg:
				return this->pObject[32];
			break;
			case MaxPhyDmg:
				return this->pObject[33];
			break;
			case MinMagicDmg:
				return this->pObject[34];
			break;
			case MaxMagicDmg:
				return this->pObject[35];
			break;
			case MinDef:
				return this->pObject[36];
			break;
			case MaxDef:
				return this->pObject[37];
			break;
			case Absorb:
				return this->pObject[38];
			break;
			case CurrentHP:
				return this->pObject[68];
			break;
			case CurrentMP:
				return this->pObject[69];
			break;
		}
	}
	
	return 0;
}
void CPlayer::SetStats(BYTE bType,unsigned short Amount,bool Bonus)
{
	if(Bonus)
	{
		switch(bType)
		{
			case Strength:
				this->pObject[23] = Amount;
			break;
			case Health:
				this->pObject[24] = Amount;
			break;
			case Intelligence:
				this->pObject[25] = Amount;
			break;
			case Agility:
				this->pObject[27] = Amount;
			break;
			case Wisdom:
				this->pObject[26] = Amount;
			break;
		}
	}
	else
	{
		switch(bType)
		{	
			case Strength:
				this->pObject[16] = Amount;
			break;
			case Health:
				 this->pObject[17] = Amount;
			break;
			case Intelligence:
				 this->pObject[18] = Amount;
			break;
			case Agility:
				 this->pObject[20] = Amount;
			break;
			case Wisdom:
				 this->pObject[19] = Amount;
			break;
			case OTP:
				 this->pObject[30] = Amount;
			break;
			case Evasion:
				 this->pObject[31] = Amount;
			break;
			case MinPhyDmg:
				 this->pObject[32] = Amount;
			break;
			case MaxPhyDmg:
				 this->pObject[33] = Amount;
			break;
			case MinMagicDmg:
				 this->pObject[34] = Amount;
			break;
			case MaxMagicDmg:
				 this->pObject[35] = Amount;
			break;
			case MinDef:
				 this->pObject[36] = Amount;
			break;
			case MaxDef:
				 this->pObject[37] = Amount;
			break;
			case Absorb:
				 this->pObject[38] = Amount;
			break;
			case CurrentHP:
				 this->pObject[68] = Amount;
			break;
			case CurrentMP:
				 this->pObject[69] = Amount;
			break;
		}
	}

}
int CPlayer::getType()
{
	return this->pObject[6];
}
int CPlayer::getAdmin()
{
	return this->pObject[114];
}
int CPlayer::getLevel()
{
	return this->pObject[15];
}
int CPlayer::getID()
{
	return this->pObject[7];
}
int CPlayer::getPID()
{
	return this->pObject[113];
}
int CPlayer::getUID()
{
	return this->pObject[112];
}
BYTE CPlayer::getClass()
{
	return this->pObject[115];
}
int CPlayer::getMap()
{
	return this->pObject[79];
}
int CPlayer::getCoordinate(BYTE bType)
{
	switch(bType)
	{
		case X:
			return this->pObject[83];
		break;
		case Y:
			return this->pObject[84];
		break;
		case Z:
			return this->pObject[85];
		break;
	}
	return 0;
}
int* CPlayer::getCoordinates()
{
	int* pCoords;
	pCoords[0] = this->pObject[83];
	pCoords[1] = this->pObject[84];
	pCoords[2] = this->pObject[85];

	return pCoords;
}
WORD CPlayer::getStatPoints()
{
	return this->pObject[136];
}
WORD CPlayer::getSkillPoints()
{
	return this->pObject[137];
}
char* CPlayer::getName()
{
    return (char *) this->pObject[32];
}