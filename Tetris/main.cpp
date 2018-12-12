/* FILE: main.cpp
 * PROJECT: Tetris				
 * PROGRAMMER: Cavan Biggs
 * FIRST VERSION: December 11th 2018
 * DESCRIPTION: I Made this following a game tutorial showing how to make tetris
 *
 * CITATION: Code-It-Yourself! Tetris - Programming from Scratch (Quick and Simple C++) - https://www.youtube.com/watch?v=8OK8_tHeCIA&t
 *
 *
 *
 *
*/

#include "Common.h"



using namespace std;

int nScreenWidth = 80;
int nScreenHeight = 30;

wstring tetromino[7];
int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char *pField = nullptr;



int main()
{
	// Create Screen Buffer
	wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];
	for (int i = 0; i < nScreenWidth*nScreenHeight; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;
	
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


	pField = new unsigned char[nFieldWidth*nFieldHeight]; // Create play field buffer
	for (int x = 0; x < nFieldWidth; x++) // Board Boundary
		for (int y = 0; y < nFieldHeight; y++)
			pField[y*nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;

	//Game Loop / logic
	// Game Logic
	bool bKey[4];
	int nCurrentPiece = 0;
	int nCurrentRotation = 0;
	int nCurrentX = nFieldWidth / 2;
	int nCurrentY = 0;
	int nSpeed = 20;
	int nSpeedCount = 0;
	bool bForceDown = false;
	bool bRotateHold = true;
	int nPieceCount = 0;
	int nScore = 0;
	vector<int> vLines;
	bool bGameOver = false;

	while (!bGameOver)
	{




		// GAME TIMING ============================================
		this_thread::sleep_for(50ms); //Game Tick
		nSpeedCount++;
		bForceDown = (nSpeedCount == nSpeed);




		// INPUT ==================================================
		for (int k = 0; k < 4; k++)
		{
			bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;
		}
		



		// GAME LOGIC =============================================
		// Handle player movement
		nCurrentX += (bKey[0] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY)) ? 1 : 0;
		nCurrentX -= (bKey[1] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY)) ? 1 : 0;
		nCurrentY += (bKey[2] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1)) ? 1 : 0;

		if (bKey[3])
		{
			nCurrentRotation += (!bRotateHold && DoesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY)) ? 1 : 0;
			bRotateHold = false;
		}
		else
		{
			bRotateHold = true;
		}


		if (bForceDown)
		{
			
				// Update difficulty every 50 pieces
				nSpeedCount = 0;
				nPieceCount++;
				if (nPieceCount % 50 == 0)
					if (nSpeed >= 10) nSpeed--;

				// Test if piece can be moved down
				if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
					nCurrentY++; // It can, so do it!
				else
				{
					// It can't! Lock the piece in place
					for (int px = 0; px < 4; px++)
						for (int py = 0; py < 4; py++)
							if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
								pField[(nCurrentY + py) * nFieldWidth + (nCurrentX + px)] = nCurrentPiece + 1;

					nPieceCount++;
					if (nPieceCount % 10 == 0)
					{
						if (nSpeed >= 10) nSpeed--;
					}


				// Check if we have any lines
					for (int py = 0; py < 4; py++)
					{
						if (nCurrentY + py < nFieldHeight - 1)
						{
							bool bLine = true;
							for (int px = 1; px < nFieldWidth - 1; px++)
							{
								bLine &= (pField[(nCurrentY + py) * nFieldWidth + px]) != 0;
							}

							if (bLine)
							{
								// Remove line, set to = 
								for (int px = 1; px < nFieldWidth - 1; px++)
								{
									pField[(nCurrentY + py) * nFieldWidth + px] = 8;

									vLines.push_back(nCurrentY + py);
								}
							}
						}

					}
					nScore += 25;
					if (!vLines.empty()) nScore += (1 << vLines.size()) * 100;

				//Choose next piece
				nCurrentX = nFieldWidth / 2;
				nCurrentY = 0;
				nCurrentRotation = 0;
				nCurrentPiece = rand() % 7;

				// if piece does not fit
				bGameOver = !DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);

				nSpeedCount = 0;
			}
		}


		// RENDER OUTPUT ==========================================




		// Draw Game Field
		// Draw Field
		for (int x = 0; x < nFieldWidth; x++)
			for (int y = 0; y < nFieldHeight; y++)
				screen[(y + 2)*nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y*nFieldWidth + x]];

		// Draw Current Piece
		for (int px = 0; px < 4; px++)
			for (int py = 0; py < 4; py++)
				if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
					screen[(nCurrentY + py + 2)*nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;
			
		//Draw Score
		swprintf_s(&screen[2 * nScreenWidth + nFieldWidth + 6], 16, L"SCORE: %8d", nScore);
					
		if (!vLines.empty())
		{
			//Display Frame
			WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);
			this_thread::sleep_for(400ms); //Delay

			for (auto &v : vLines)
			{
				for (int px = 1; px < nFieldWidth - 1; px++)
				{
					for (int py = v; py > 0; py--)
					{
						pField[py * nFieldWidth + px] = pField[(py - 1) * nFieldWidth + px];
						pField[px] = 0;
					}
				}
			}
		}

		//Display frame.
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);
	}

	// Game over
	CloseHandle(hConsole);
	cout << "Game Over!! Score:" << nScore << endl;
	system("Pause");
	

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

	// All Field cells >0 are occupied
	for (int px = 0; px < 4; px++)
		for (int py = 0; py < 4; py++)
		{
			// Get index into piece
			int pi = Rotate(px, py, nRotation);

			// Get index into field
			int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

			// Check that test is in bounds. Note out of bounds does
			// not necessarily mean a fail, as the long vertical piece
			// can have cells that lie outside the boundary, so we'll
			// just ignore them
			if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
			{
				if (nPosY + py >= 0 && nPosY + py < nFieldHeight)
				{
					// In Bounds so do collision check
					if (tetromino[nTetromino][pi] != L'.' && pField[fi] != 0)
						return false; // fail on first hit
				}
			}
		}

	return true;
	}
