#include "SceneManager/SceneManager.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

unsigned int timeGetTime()
{
	timeval now;
	gettimeofday(&now,0);
	return now.tv_usec / 1000;
}


int main()
{
	printf("ServerBoot:\n");
	SceneManager* sceneMnager = new SceneManager();

	unsigned int SyncOld = timeGetTime();
	unsigned int SyncNow;

	while (1)
	{
		usleep(1000);
		SyncNow = timeGetTime();
		if(SyncNow - SyncOld >= 1000/60)
		{
			if(sceneMnager->Run())
			{
				break;
			}
			SyncOld = timeGetTime();
		}
	}

	return 0;
}
