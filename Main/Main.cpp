#include "SceneManager/SceneManager.h"
#include <stdio.h>


int main()
{
	SceneManager* sceneMnager = new SceneManager();
	while (!sceneMnager->Run());

	return 0;
}
