#include "PlayerInf.h"

playerInf::playerInf() {
	money = UserDefault::getInstance()->getIntegerForKey("Money", 0);
	unlockedLevel = UserDefault::getInstance()->getIntegerForKey("UnlockedLevel", 1);
	startmoney = UserDefault::getInstance()->getIntegerForKey("Startmoney", 600);
	startHP = UserDefault::getInstance()->getIntegerForKey("StartHP", 10);
	music = UserDefault::getInstance()->getBoolForKey("VolumeCheckBoxState", true);
	difficulty= UserDefault::getInstance()->getIntegerForKey("Difficulty", 1);
}

//��Ǯ
void playerInf::consumeMoney(int n) {
	if (money >= n) {
		money = money - n;
		save();
	}
}

int playerInf::getMoney() const {
	return money;
}

//���³�ʼ���
void playerInf::upgradeStartmoney() {
	startmoney += 100;
	save();
}

//���³�ʼ����
void playerInf::upgradeStartHP() {
	startHP += 5;
	save();
}

int playerInf::getStartmoney() const {
	return startmoney;
}

int playerInf::getStartHP() const {
	return startHP;
}

void playerInf::clear() {
	// ��ձ��������
	UserDefault::getInstance()->setIntegerForKey("Money", 0);
	UserDefault::getInstance()->setIntegerForKey("UnlockedLevel", 1); // ����ΪĬ�Ͻ�����һ��
	UserDefault::getInstance()->setIntegerForKey("Startmoney", 600);
	UserDefault::getInstance()->setIntegerForKey("StartHP", 10);
	UserDefault::getInstance()->setBoolForKey("Music", true);
	UserDefault::getInstance()->setIntegerForKey("Difficulty", 1);
	UserDefault::getInstance()->flush();

	money = 0;
	startmoney = 600;
	startHP = 10;
	unlockedLevel = 1;
	save();
}

void playerInf::save() {
	// ��������
	UserDefault::getInstance()->setIntegerForKey("Money", money);
	UserDefault::getInstance()->setIntegerForKey("UnlockedLevel", unlockedLevel);
	UserDefault::getInstance()->setIntegerForKey("Startmoney", startmoney);
	UserDefault::getInstance()->setIntegerForKey("StartHP", startHP);
	UserDefault::getInstance()->setBoolForKey("VolumeCheckBoxState", music);
	UserDefault::getInstance()->setIntegerForKey("Difficulty", difficulty);
	UserDefault::getInstance()->flush(); // ȷ�����ݱ�д��
}

void playerInf::load() {
	money = UserDefault::getInstance()->getIntegerForKey("Money", 0);
	unlockedLevel = UserDefault::getInstance()->getIntegerForKey("UnlockedLevel", 1);
	startmoney = UserDefault::getInstance()->getIntegerForKey("Startmoney", 600);
	startHP = UserDefault::getInstance()->getIntegerForKey("StartHP", 10);
	music = UserDefault::getInstance()->getBoolForKey("VolumeCheckBoxState", true);
	difficulty = UserDefault::getInstance()->getIntegerForKey("Difficulty", 1);
}

bool playerInf::getMusic() const {
	return music;
}

void playerInf::changeMusic() {
	music = !music;
}

int playerInf::getLevel() const{
	return unlockedLevel;
}

void playerInf::changeULevel(int level) {
	if (unlockedLevel < level)
		unlockedLevel = level;
	player.save();
}

int playerInf::getDifficulty() const {
	return difficulty;
}

void playerInf::changeDifficulty(int dif) {
	difficulty = dif;
	player.save();
}

playerInf player;         //���