#include "wave.h"

int Wave::getWave() const{
	return wave;
}

void Wave::nextWave() {
	if (wave < 4)
		wave++;
}

void Wave::clear() {
	wave = 1;
}

Wave::Wave(){
	wave = 1;
}

Wave game;