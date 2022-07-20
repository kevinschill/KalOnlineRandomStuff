#ifndef SKILLSYSTEM_H
#define SKILLSYSTEM_H

#include "Header.h"
#include "CPlayer.h"
#include <thread>

#define SKILL_FLAMEINJECTION 65

#define SKILL_SPINSPLASH 38

#define SKILL_ICECIRCLE 66

#define SKILL_ARROWRAIN 47

class CSkill
{
	public:
		CPlayer* mPlayer;

		CSkill::CSkill(){}
		CSkill::CSkill(int* Player)
		{
			CPlayer* x = new CPlayer(Player);
			mPlayer = x;
			delete x;
		}
		CSkill::~CSkill(){}

		int ActionBeforeDamage(int* Target);
		void* getTargetList(int Range,int* Target);
		int* getTarget(char bType,int iTargetID);

		int DamageMonster(int* Target,int Damage,int Unknown);

		void AddAggro(int* Target);
		bool isInArea(int* Object,int Target_X,int Target_Y,int Area);
		std::vector<int> getTargets(int Range,int* Target);
		std::list<int*> CSkill::getAroundList(int Range,int* Target);

		bool bExecuteSkill(int* Target);

		void ConsumeMana(int Amount);

		int getGrade(BYTE bIndex);
};

class CKnight : CSkill
{
	public:
		void SpinSplash(CPlayer* p);

		void SwordDanceThrd(CPlayer* p,CPlayer* t);
		std::thread startSwordDance(CPlayer* p,CPlayer* t) 
		{
          return std::thread([=] { SwordDanceThrd(p,t); });
		}
};

class CMage : CSkill
{
	public:
		void Icicle();
		void Thunderbolt();
		void Fireball();
		void Bless();
		void TheraputicTouch();
		void MagicIntensification(CPlayer* p);

		void LightningArrowThrd(CPlayer* p,CPlayer* t);
		std::thread startLightningArrow(CPlayer* p,CPlayer* t) 
		{
          return std::thread([=] { LightningArrowThrd(p,t); });
		}

		void FlameInjetionThrd(CPlayer* p,CPlayer* t);
		std::thread startFlameInjetion(CPlayer* p,CPlayer* t) 
		{
          return std::thread([=] { FlameInjetionThrd(p,t); });
		}
		void IceCircleThrd(CPlayer* p);
		std::thread startIceCircle(CPlayer* p) 
		{
			printf("CMage::start\n");
          return std::thread([=] { IceCircleThrd(p); });
		}
		
};
class CArcher : CSkill
{
	public:
		
		void ArrowRainThrd(CPlayer* p,int* Coordinates);
		 std::thread startArrowRain(CPlayer* p, int* Coordinates) {
          return std::thread([=] { ArrowRainThrd(p, Coordinates); });
		}

		void CombativeSpirit();//gob
		void VirulentArrow();//ig
		void ArrowExplosion();//ig skill 
		void Sharpness();//gob speed skill like ee
		void Shrewdness();//ig eva skill
};


#endif