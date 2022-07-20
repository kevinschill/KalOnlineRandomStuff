#include "Header.h"
#include "SkillSystem.h"


enum KnightSkills{SPINSPLASH = 38,SWORDDANCE = 43,PerfectDefense =40,PoB=42};
enum MageSkills{FlameInjection = 65,Icicle=66,Thunderbolt = 75,Fireball=73,MagicIntens =64,Bless=69,LightningArrow=67};
enum ArcherSkills{ArrowRain = 47,ComativeSpirit=51,ArrowExplosion=49,VirulentArrow=52};

enum Class{KNIGHT = 0,ARCHER = 2,MAGE = 1,THIEF = 3};

void __fastcall Hooks::Player::hkExcuteSkill(int* PointToPlayerBase, void* _edx, signed int nSkillID, char* PacketPointer, char* PositionPointer) 
{
	UNREFERENCED_PARAMETER(_edx); 
    bool forward = true; 

	int* pPlayer = reinterpret_cast<int*>(*reinterpret_cast<unsigned long*>(PointToPlayerBase)); 
	int* pSkill = *reinterpret_cast<int**>(reinterpret_cast<char*>(PointToPlayerBase)+static_cast<int>(nSkillID)* 4 + 8);

	if(pPlayer[115] == KNIGHT)
	{
		if(nSkillID == KnightSkills::SPINSPLASH)
		{
			forward = false;
			std::unique_ptr<CKnight> KnightSkill;
			KnightSkill->SpinSplash(new CPlayer(pPlayer));
		}
		if(nSkillID == KnightSkills::SWORDDANCE)
		{
			forward = false;
			int nTargetID;
			char bType;
			GameServer::ReadPacket(PacketPointer, PositionPointer, "bd", &bType, &nTargetID);
			int* Target = 0;
			switch(bType)
			{
				case 0:
					Target = (int*)GameServer::Player::FindPlayer(nTargetID);
				break;
				case 1:
					Target = (int*)GameServer::Monster::FindMonster(nTargetID);
				break;
			}
			std::unique_ptr<CKnight> KnightSkill;
			std::thread t = KnightSkill->startSwordDance(new CPlayer(pPlayer),new CPlayer(Target));
			t.detach();                              
		}
		
	}
	if(pPlayer[115] == MAGE)
	{

		if(nSkillID == 67)
		{
			forward = false;
			int nTargetID;
			char bType;
			GameServer::ReadPacket(PacketPointer, PositionPointer, "bd", &bType, &nTargetID);
			int* Target = 0;
			switch(bType)
			{
				case 0:
					Target = (int*)GameServer::Player::FindPlayer(nTargetID);
				break;
				case 1:
					Target = (int*)GameServer::Monster::FindMonster(nTargetID);
				break;
			}
			std::unique_ptr<CMage> MageSkill;
			std::thread t = MageSkill->startLightningArrow(new CPlayer(pPlayer),new CPlayer(Target));
			t.detach();  
		}
		if(nSkillID == MageSkills::FlameInjection)
		{
			forward = false;
			int nTargetID;
			char bType;
			GameServer::ReadPacket(PacketPointer, PositionPointer, "bd", &bType, &nTargetID);
			int* Target = 0;
			switch(bType)
			{
				case 0:
					Target = (int*)GameServer::Player::FindPlayer(nTargetID);
				break;
				case 1:
					Target = (int*)GameServer::Monster::FindMonster(nTargetID);
				break;
			}
			std::unique_ptr<CMage> MageSkill;
			std::thread t = MageSkill->startFlameInjetion(new CPlayer(pPlayer),new CPlayer(Target));
			t.detach(); 
		}
		if(nSkillID == MageSkills::Icicle)
		{
			forward = false;
			std::unique_ptr<CMage> MageSkill;
			
			std::thread t = MageSkill->startIceCircle(new CPlayer(pPlayer));
			t.detach();
		}
		if(nSkillID == MageSkills::Thunderbolt)
		{
			forward = false;

		}
		if(nSkillID == MageSkills::MagicIntens)
		{
			forward = false;
			std::unique_ptr<CMage> MageSkill;
			MageSkill->MagicIntensification(new CPlayer(pPlayer));
		}
	}
	if(pPlayer[115] == ARCHER)
	{
		
		if(nSkillID == ArcherSkills::ArrowRain)
		{
			forward = false;
			int CoordX = 0;
			int CoordY = 0;
			GameServer::ReadPacket(PacketPointer,PositionPointer,"dd",&CoordX,&CoordY);
			
			int c[] = {CoordX,CoordY};
			std::unique_ptr<CArcher> ArcherSkill;
			
			std::thread t = ArcherSkill->startArrowRain(new CPlayer(pPlayer),c);
			t.detach();
		}

	}
	if(pPlayer[115] == THIEF)
	{

	}
	
 if (forward)
	 GameServer::Player::ExecuteSkill(static_cast<void*>(PointToPlayerBase), nSkillID, PacketPointer, PositionPointer);

}