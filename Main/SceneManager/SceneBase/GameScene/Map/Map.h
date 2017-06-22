/*
 * Map.h
 *
 *  Created on: 2017/06/19
 *      Author: kei
 */

#ifndef MAP_H_
#define MAP_H_

#define MAP_WIDTH 40
#define MAP_HEIGHT 23
#define CHIP_WIDTH 32

class Map
{
public:
	struct MapData
	{
		int Data[MAP_HEIGHT][MAP_WIDTH];
	};

	Map();
	virtual ~Map();

	inline MapData GetMapData()
	{
		return m_MapData;
	}

private:
	void MapLoad();

	MapData m_MapData;

};

#endif /* MAP_H_ */
