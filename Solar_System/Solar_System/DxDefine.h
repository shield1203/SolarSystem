#pragma once

#define DIRECTINPUT_VERSION 0x0800

/////////////
// LINKING //
/////////////
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dcompiler.lib")


//////////////
// INCLUDES //
//////////////
#include <d3d11_1.h>
#include <dinput.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>
using namespace std;
using namespace DirectX;

///////////////////////////
//  warning C4316 처리용  //
///////////////////////////
#include "AlignedAllocationPolicy.h"

enum PLANETS { SUN, MERCURY, VENUS, EARTH, MARS, JUPITER, SATURN, URANUS, NEPTUNE, MOON };