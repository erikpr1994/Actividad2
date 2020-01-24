#include "Map.h"
#include "Engine.h"
#include "FAriasSimpleGraphics.h"

#include <iostream>
#include <cstdlib>

extern Game game;

int const mapHeight = 1000, mapWidth = 150;
int const MAX_STONE_PART_LENGTH = 30;
bool map[mapHeight][mapWidth];
int lastLeftXPosition = 3;
int lastXPosition = mapWidth;

int IncreaseOrDecrease();
int PaintLeftPart(int mapHeigthPosition);
int PaintRightPart(int mapHeigthPosition);
void setFalseParts(int mapHeigthPosition, int startEmptyMapPoint, int endEmptyMapPoint);

void PaintMap() {
	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			if (map[i][j] == true)
				//Pintar mapa
				FASG::WritePixelBuffer(j, i, FASG::EBackColor::Green);
		}
	}
}

void InitMap() {
	for (int i = 0; i < mapHeight; i++) {
		int startEmptyMapPoint = PaintLeftPart(i);
		int endEmptyMapPoint = PaintRightPart(i);
		setFalseParts(i, startEmptyMapPoint, endEmptyMapPoint);
	}
}

int PaintLeftPart(int mapHeigthPosition) {
	int increaseOrDecrease = IncreaseOrDecrease();
	lastLeftXPosition += increaseOrDecrease;
	int startLine = 0;
	if (startLine < 2) {
		for (int j = 0; j < 2; j++) {
			map[mapHeigthPosition][j] = true;
			startLine++;
		}
	}
	if (lastLeftXPosition > MAX_STONE_PART_LENGTH) {
		lastLeftXPosition = MAX_STONE_PART_LENGTH;
	}

	for (startLine; startLine < lastLeftXPosition; startLine++) {

		if (map[mapHeigthPosition][startLine +1] == false) {
			map[mapHeigthPosition][startLine + increaseOrDecrease] = true;
			lastLeftXPosition = startLine+increaseOrDecrease;
			break;
		}
	}

	for (int i = lastLeftXPosition; i > 1; i--) {
		map[mapHeigthPosition][i] = true;
	}

	return lastLeftXPosition +1;
}

int PaintRightPart(int mapHeigthPosition){
	int increaseOrDecrease = IncreaseOrDecrease();
	int maxRightStones = mapWidth - MAX_STONE_PART_LENGTH;
	for (lastXPosition; lastXPosition > maxRightStones; lastXPosition--) {
		if (lastXPosition > 148) {
			for (int j = 149; j > 147; j--) {
				map[mapHeigthPosition][j] = true;
				continue;
			}
		}

		if (map[mapHeigthPosition][lastXPosition + -1] == false) {
			map[mapHeigthPosition][lastXPosition + increaseOrDecrease] = true;
			lastXPosition += increaseOrDecrease;
			break;
		}
	}

	return lastXPosition - 1;
}

void setFalseParts(int mapHeigthPosition, int startEmptyMapPoint, int endEmptyMapPoint) {
	for (int j = startEmptyMapPoint; j < endEmptyMapPoint; j++) {
		map[mapHeigthPosition][j] = false;
	}
}

int IncreaseOrDecrease() {
	int randomNumber = rand()%5-1;
	return randomNumber;
}