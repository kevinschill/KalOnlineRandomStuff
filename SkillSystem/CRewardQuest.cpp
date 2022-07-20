#include "Header.h"
#include "CRewardQuest.h"
#include "ConfigParser.h"



bool CRewardQuest::QuestComplete(int PID,int Quest)
{
	for(std::vector<SRewardQuest>::iterator it = this->vRewardVector.begin(); it != this->vRewardVector.end(); ++it)
	{
		if(it->PlayerPID == PID)
		{
			if(it->m_Quest.Index == Quest)
			{
				if(it->m_Quest.Finished)
				{
					for(std::vector<SRewardRepeat>::iterator itRepeat = this->vRepeatVector.begin(); itRepeat != this->vRepeatVector.end(); ++itRepeat)
					{
						if(itRepeat->PlayerPID == PID)
						{
							if(itRepeat->Quest == Quest)
							{
								itRepeat->Counter += 1;
								//this->WriteConfig(PID,Quest,itRepeat->Counter);
							}
						}
					}
					GameServer::Player::Write(it->Player,60,"ss","Quest","Quest Completed!");	
					it = this->vRewardVector.erase( it );
					return true;

				}
				else
				{
					GameServer::Player::Write(it->Player,60,"ss","Quest","Quest not Complete!");
					return false;
				}
			}
		}
	}
	return false;
}
void CRewardQuest::AddKill(int PID,int Index)
{
	for(std::vector<SRewardQuest>::iterator it = this->vRewardVector.begin(); it != this->vRewardVector.end(); ++it)
	{
		if(it->PlayerPID == PID)
		{
			if(it->m_Quest.MonsterIndex == Index)
			{
				if(it->m_Quest.Finished == false)
				{
					it->m_Quest.KillCounter += 1;
					int LeftMobs = it->m_Quest.MonsterAmount - it->m_Quest.KillCounter;
					std::stringstream s;
					s << "Kill " << LeftMobs << " more " << it->m_Quest.MonsterName.c_str() << " to finish the Quest.";
					
					GameServer::Player::Write(it->Player,60,"ss","Quest",s.str().c_str());

					if(it->m_Quest.KillCounter >= it->m_Quest.MonsterAmount)
					{
						it->m_Quest.Finished = true;
						
						GameServer::Player::Write(it->Player,60,"ss","Quest","You Finished this Quest, get your Reward!");
					}
				}
			}
		}
	}
}

bool CRewardQuest::HasQuest(int PID,int Quest)
{
	for(std::vector<SRewardQuest>::iterator it = this->vRewardVector.begin(); it != this->vRewardVector.end(); ++it)
	{
		if(it->PlayerPID == PID)
		{
			if(it->m_Quest.Index == Quest)
				return true;
		}
	}
	return false;
}
struct SRewardConfig
{
	int PID;
	int Index;
	int Amount;
};

void CRewardQuest::WriteConfig(int PID,int Quest,int Amount)
{
	printf("write amount %d\n",Amount);
	std::ofstream Cfg;
	std::stringstream sPID;
	sPID << "RewardLog/" << PID << "-" << Quest <<".txt";
	Cfg.open(sPID.str().c_str());

	Cfg << "[Quest (Amount " << Amount << ")]";

	Cfg.close();
}
int CRewardQuest::LoadConfig(int PID,int Quest)
{
	std::ifstream spawnitem;
	std::stringstream sPID;
	sPID << "RewardLog/" << PID << "-" << Quest <<".txt";
	spawnitem.open(sPID.str().c_str());

	std::string line;
	std::vector<SRewardConfig> vRewardConfig;
	SRewardConfig tRewardConfig;
	if(spawnitem.is_open())
	{
		printf("File Open\n");
		while(std::getline(spawnitem,line,']'))
		{
			std::unique_ptr<ConfigParse> Cfg(new ConfigParse(line));
			

			Cfg->Extract("Amount",")",true);
			tRewardConfig.Amount = Cfg->getInt();

			tRewardConfig.PID = PID;
			tRewardConfig.Index = Quest;

			//vRewardConfig.push_back(tRewardConfig);

			//[Quest (Amount 2)]
		}
	}
	spawnitem.close();

	printf("Amount %d\n",tRewardConfig.Amount);
	return tRewardConfig.Amount;
}
int CRewardQuest::InsertQuest(int* Player,int Quest,int MonsterIndex,int MonsterAmount,int RewardAmounts,std::string MonsterName)
{
	bool insert = false;
	int Ret = this->LoadConfig(Player[113],Quest);
	if(Ret > 0)
	{
		printf("Insert Amount: %d\n",Ret);
		insert = true;
		SRewardRepeat tRepeat;
		tRepeat.PlayerPID = Player[113];
		tRepeat.Quest = Quest;
		tRepeat.Counter = Ret;
		tRepeat.Player = Player;
		this->vRepeatVector.push_back(tRepeat);
	}
	if(this->HasQuest(Player[113],Quest))
	{
		GameServer::Player::Write(Player,60,"ss","Quest","You already got this Quest.");
		return 100;
	}
	if(this->MaxQuestToday(Player[113],Quest,RewardAmounts))
		return 101;
		
	SRewardQuest tRewardQuest;
	tRewardQuest.PlayerPID = Player[113];
	tRewardQuest.Player = Player;
	tRewardQuest.m_Quest.Index = Quest;
	tRewardQuest.m_Quest.KillCounter = 0;
	tRewardQuest.m_Quest.RewardsCounter = 0;
	tRewardQuest.m_Quest.Finished = false;
	tRewardQuest.m_Quest.MonsterIndex = MonsterIndex;
	tRewardQuest.m_Quest.MonsterAmount = MonsterAmount;
	tRewardQuest.m_Quest.RewardAmounts = RewardAmounts;
	tRewardQuest.m_Quest.MonsterName = MonsterName;
	this->vRewardVector.push_back(tRewardQuest);

	if(insert == false)
	{
		SRewardRepeat tRepeat;
		tRepeat.PlayerPID = Player[113];
		tRepeat.Quest = Quest;
		tRepeat.Counter = 0;
		tRepeat.Player = Player;
		this->vRepeatVector.push_back(tRepeat);
	}
	
	GameServer::Player::Write(Player,60,"ss","Quest","Quest Accepted!");

	return 1;
}

bool CRewardQuest::MaxQuestToday(int PID,int Quest,int MaxCounter)
{
	for(std::vector<SRewardRepeat>::iterator it = this->vRepeatVector.begin(); it != this->vRepeatVector.end(); ++it)
	{
		if(it->PlayerPID == PID)
		{
			if(it->Quest == Quest)
			{
				if(it->Counter >= MaxCounter)
				{
					GameServer::Player::Write(it->Player,60,"ss","Quest","You reached the Maximum Limit of this Quest for Today. Come back Tomorrow.");
					return true;
				}
				else
					return false;
			}	
		}
	}
	return false;
}