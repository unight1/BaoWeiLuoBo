#pragma once

#ifndef __PLAYER_INF_H__
#define __PLATER_INF_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class playerInf {
protected:
	int money;                      //玩家金钱
	int startmoney;                 //游戏初始金钱
	int startHP;                    //萝卜初始生命
	int unlockedLevel;              //解锁的关卡
	bool music;                     //音乐是否打开
public:
	
	void consumeMoney(int n);       //花钱
	int getMoney() const;
	void upgradeStartmoney();       //更新初始金币
	void upgradeStartHP();          //更新初始生命
	int getStartmoney() const;
	int getStartHP() const;
	bool getMusic() const;
	void changeMusic();             //改变音乐开关状态
	void clear();                   //清空记录
	void save();                    //保存记录
	void load();                    //加载记录
	int getLevel();
	void changeULevel(int level);   //解锁关卡
	playerInf();
};


extern playerInf player;         //玩家


#endif