// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: reference additional headers your program requires here
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm> 
#include <bitset>
#include "Console.h"
#include "DList.h"
using namespace std;
using namespace System;

#define PLAYER_SUB 0 // subscript for player in gameObjects array
//Flags for cheats
#define ALIVE_FLAG 1
#define GHOST_FLAG 1 << 1
#define ENEMY_MOVE_FLAG 1 << 2
#define ENEMY_SHOOT_FLAG 1 << 3