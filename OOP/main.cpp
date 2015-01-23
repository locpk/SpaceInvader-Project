// OOP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"


int _tmain()
{
	// This will check for memory leaks.  They will show up in your
	// output window along with the line number.  Replace the 
	// -1 argument in the second call with the allocation number
	// and then trace back through the call stack to find the leak.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1);
	srand(static_cast<unsigned int>(time(nullptr)));
#if 1
	Game g;
	g.Play();
#endif
#if 0
	typedef DList<char> OurDList;
	OurDList testDList;
	testDList.push_front('#');
	testDList.push_back('@');
	testDList.clear();
	testDList.push_back('i');
	testDList.push_front('r');
	testDList.push_front('h');
	testDList.push_back('s');
	testDList.push_front('t');
	testDList.erase(2);
	testDList.erase(0);
	testDList.erase(2);
	for (size_ i = 0; i < testDList.Size(); i++)
		cout << testDList[i];
	testDList.erase(0);
	testDList.erase(0);
	testDList.push_front('!');
	testDList.push_back('\"');
	testDList.erase(1);
	for (size_ i = 0; i < testDList.Size(); i++)
		cout << testDList[i];
	cout << flush << endl;
	system("pause");
#endif
	return 0;
}

