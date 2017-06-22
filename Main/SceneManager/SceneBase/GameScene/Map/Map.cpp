/*
 * Map.cpp
 *
 *  Created on: 2017/06/19
 *      Author: kei
 */

#include "Map.h"
#include <stdio.h>
#include <stdlib.h>


Map::Map() {
	MapLoad();

}

Map::~Map() {
}

void Map::MapLoad()
{
	FILE* fp;
	fp = fopen("map.csv","r");
	if(fp == NULL)
	{
		printf("fopen error\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("fopen success\n");
	}

	for(int i = 0; i < MAP_HEIGHT; i++)
	{
		for(int j = 0; j < MAP_WIDTH;j++)
		{
			fscanf(fp,"%d,",&m_MapData.Data[i][j]);
		}
	}
	fclose(fp);
}
