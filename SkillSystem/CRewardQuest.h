#ifndef CREWARDQUEST_H
#define CREWARDQUEST_H

#include <vector>
#include <string>

struct SQuest
{
	int Index;
	int MonsterIndex;
	int MonsterAmount;
	int KillCounter;
	int RewardAmounts;
	int RewardsCounter;
	bool Finished;
	std::string MonsterName;
};
struct SRewardQuest
{
	int PlayerPID;
	int* Player;
	SQuest m_Quest;
};
struct SRewardRepeat
{
	int PlayerPID;
	int* Player;
	int Quest;
	int Counter;
};
class CRewardQuest
{
	public:
		std::vector<SRewardQuest> vRewardVector;
		std::vector<SRewardRepeat> vRepeatVector;
		int InsertQuest(int* Player,int Quest,int MonsterIndex,int MonsterAmount,int RewardAmounts,std::string MonsterName);
		bool HasQuest(int PID,int Quest);
		bool MaxQuestToday(int PID,int Quest,int MaxCounter);
		void AddKill(int PID,int Index);
		bool QuestComplete(int PID,int Quest);
		int LoadConfig(int PID,int Quest);
		void WriteConfig(int PID,int Quest,int Amount);
};

#endif