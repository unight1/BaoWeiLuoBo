#pragma once

#ifndef __PLAYER_INF_H__
#define __PLATER_INF_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class playerInf {
protected:
	int money;                      //��ҽ�Ǯ
	int startmoney;                 //��Ϸ��ʼ��Ǯ
	int startHP;                    //�ܲ���ʼ����
	int unlockedLevel;              //�����Ĺؿ�
	bool music;                     //�����Ƿ��
	int difficulty;                 //��Ϸ�Ѷ�
public:
	
	void consumeMoney(int n);       //��Ǯ
	int getMoney() const;
	void upgradeStartmoney();       //���³�ʼ���
	void upgradeStartHP();          //���³�ʼ����
	int getStartmoney() const;
	int getStartHP() const;
	bool getMusic() const;
	void changeMusic();             //�ı����ֿ���״̬
	void clear();                   //��ռ�¼
	void save();                    //�����¼
	void load();                    //���ؼ�¼
	int getLevel() const;
	void changeULevel(int level);   //�����ؿ�
	int getDifficulty() const;
	void changeDifficulty(int dif); //�ı��Ѷ�
	playerInf();
};


extern playerInf player;         //���


#endif