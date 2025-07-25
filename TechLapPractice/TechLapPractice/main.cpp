

#include <Windows.h>
#include <iostream>
#include "App.h"


int main()
{
	UApp app;
	if (app.Init() == false)
	{
		cout << "App Init Failed" << endl;
		return -1;
	}
	return app.Run();
}