/* FILE: main.cpp
 * PROJECT: Tetris				
 * PROGRAMMER: Cavan Biggs
 * FIRST VERSION: December 11th 2018
 * DESCRIPTION: I Made this following a game tutorial 
 *
 * CITATION: Code-It-Yourself! Tetris - Programming from Scratch (Quick and Simple C++) - https://www.youtube.com/watch?v=8OK8_tHeCIA&t
 *
 *
 *
 *
*/

#include <iostream>
#include <Windows.h>

using namespace std;


wstring tetromino[7];
int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char *pField = nullptr;

int nScreenWidth = 80;
int nScreenHeight = 30;

int main()
{
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");

	tetromino[1].append(L"..X.");
	tetromino[1].append(L".XX.");
	tetromino[1].append(L".X..");
	tetromino[1].append(L"....");

	tetromino[2].append(L".X..");
	tetromino[2].append(L".XX.");
	tetromino[2].append(L"..X.");
	tetromino[2].append(L"....");

	tetromino[3].append(L"....");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L"....");

	tetromino[4].append(L"..X.");
	tetromino[4].append(L".XX.");
	tetromino[4].append(L"..X.");
	tetromino[4].append(L"....");

	tetromino[5].append(L"....");
	tetromino[5].append(L".XX.");
	tetromino[5].append(L"..X.");
	tetromino[5].append(L"..X.");

	tetromino[6].append(L"....");
	tetromino[6].append(L".XX.");
	tetromino[6].append(L".X..");
	tetromino[6].append(L".X..");



	pField = new unsigned char[nFieldWidth*nFieldHeight]; //Create play field buffer
	for (int x = 0; x < nFieldWidth; x++) //Board Boundary
	{
		for (int y = 0; y < nFieldHeight; y++)
			pField[y*nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;
	}

	wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	//Game Loop
	bool bGameOver = false;

	while (!bGameOver)
	{
		
		
		// GAME TIMING ============================================





		// INPUT ==================================================





		// GAME LOGIC =============================================





		// RENDER OUTPUT ==========================================




		// Draw Game Field
		for (int x = 0; x < nFieldWidth; x++)
		{
			for (int y = 0; y < nFieldHeight; y++)
				screen[(y + 2)*nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y*nFieldWidth + x]];
		}

		//Display Frame
		WriteConsoleOutputCharacter(hConsole, (LPCSTR)screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);
	}


	

	return 0;
}



/*
*	METHOD			  :
*
*
*
*	DESCRIPTION		  :
*
*
*	PARAMETERS		  :
*
*
*	RETURNS			  :
*
*/
int Rotate(int px, int py, int r)
{
	switch (r % 4)
	{
	case 0: return py * 4 + px;			// 0 degrees
	case 1: return 12 + py - (px * 4);	// 90 degrees
	case 2: return 15 - (py * 4) - px;  // 180 degrees
	case 3: return 3 - py + (px * 4);   // 270 degrees
	}
	return 0;
}

bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
{

	//Left at 16:40


	return true;
}