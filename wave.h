#pragma once

#ifndef __WAVE_H__
#define __WAVE_H__

class Wave {
protected:
	int wave;
public:
	int getWave() const;
	void nextWave();                //��һ��
	void clear();                   //��������
	Wave();
};

extern Wave game;                   //��Ϸ

#endif