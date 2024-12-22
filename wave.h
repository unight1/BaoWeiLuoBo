#pragma once

#ifndef __WAVE_H__
#define __WAVE_H__

class Wave {
protected:
	int wave;
public:
	int getWave() const;
	void nextWave();                //下一波
	void clear();                   //波数清零
	Wave();
};

extern Wave game;                   //游戏

#endif