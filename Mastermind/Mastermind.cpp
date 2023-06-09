#include <iostream>
#include <conio.h>
#include <string> 
#include <sstream>

#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13
#define BACKSPACE 8

using namespace std;

void moveCarriageHome()
{
	cout << "\033[H\0";
}

void moveCarriageToXY(int x, int y)
{
	cout << "\033[" + to_string(y) + ';' + to_string(x) + "H\0";
}

void moveCarriageLeft(int n)
{
	cout << "\033[" + to_string(n) + "D\0";
}

void moveCarriageRight(int n)
{
	cout << "\033[" + to_string(n) + "C\0";
}

void clearScreenFromCursorDown()
{
	cout << "\033[J\0";
}

int main()
{
    srand(time(NULL));

	const char leftTopCorner = 201, rightTopCorner = 187, leftBottomCorner = 200, rightBottomCorner = 188, horizontalWall = 205, verticalWall = 186, tWall = 203, upsideDownTWall = 202;

	const int roundsNumber = 10;

	int numbersRange = 6; // 6 for a code containing numbers 1-6, max 9

	while (true)
	{
		cout << "  " << leftTopCorner << string(10, horizontalWall) << rightTopCorner << "\n";
		cout << "  " << verticalWall << "MASTERMIND" << verticalWall << "\n";
		cout << "  " << leftBottomCorner << string(10, horizontalWall) << rightBottomCorner << "\n";

		cout << leftTopCorner << string(9, horizontalWall) << tWall << string(4, horizontalWall) << rightTopCorner << "\n";

		for (int i = 0; i < roundsNumber; i++) cout << verticalWall << string(9, ' ') << verticalWall << string(4, ' ') << verticalWall << "\n";

		cout << leftBottomCorner << string(9, horizontalWall) << upsideDownTWall << string(4, horizontalWall) << rightBottomCorner << "\n";

		int currentRound = 1;
		int codeToGuess = 0;

		for (int i = 0; i < 4; i++) codeToGuess = codeToGuess * 10 + rand() % numbersRange + 1;

		while (currentRound <= roundsNumber)
		{
			MoveCarriageToXY(3, 4 + currentRound);

			int carriagePos = 0;

			string currentGuessString = "0000";

			while (true)
			{
				MoveCarriageToXY(3, 4 + currentRound);

				for (int i = 0; i < 4; i++)
				{
					if (currentGuessString[i] > '0') cout << currentGuessString[i] << ' ';
					else cout << "  ";
				}

				MoveCarriageToXY(3 + carriagePos * 2, 4 + currentRound);

				int key = _getch();

				if (key == ENTER && currentGuessString.find("0") == std::string::npos) break;

				if (key == KEY_RIGHT && carriagePos < 3)
				{
					carriagePos++;
					MoveCarriageRight(2);
				}

				if (key == KEY_LEFT && carriagePos > 0)
				{
					carriagePos--;
					MoveCarriageLeft(2);
				}

				if (key == BACKSPACE)
				{
					if (currentGuessString[carriagePos] == '0' && carriagePos > 0)
					{
						MoveCarriageLeft(2);

						currentGuessString[--carriagePos] = '0';

						cout << ' ';

						MoveCarriageLeft(1);
					}
					else
					{
						currentGuessString[carriagePos] = '0';

						cout << ' ';

						MoveCarriageLeft(1);
					}
				}

				if (key > '0' && key <= '0' + numbersRange)
				{
					currentGuessString[carriagePos] = key;

					if (carriagePos < 3) if (currentGuessString[carriagePos + 1] == '0') carriagePos++;
				}
			}

			int correctDigitAndPos = 0;
			int correctDigitWrongPos = 0;

			string codeToGuessString = to_string(codeToGuess);

			for (int i = 0; i < 4; i++)
				if (codeToGuessString[i] == currentGuessString[i]) correctDigitAndPos++;

			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					if (codeToGuessString[i] == currentGuessString[j])
					{
						correctDigitWrongPos++;
						codeToGuessString[i] = 'X';
						currentGuessString[j] = 'Y';
					}

			correctDigitWrongPos -= correctDigitAndPos;

			MoveCarriageToXY(12, 4 + currentRound);

			for (int i = 0; i < correctDigitAndPos; i++) cout << (char)178;

			for (int i = 0; i < correctDigitWrongPos; i++) cout << (char)177;

			currentRound++;

			if (correctDigitAndPos == 4)
			{
				codeToGuess = -1;
				break;
			}
		}

		MoveCarriageToXY(0, 6 + roundsNumber);

		cout << "     " << leftTopCorner << string(4, horizontalWall) << rightTopCorner << "\n";
		cout << "     " << verticalWall << (codeToGuess == -1 ? "WIN!" : "LOSE") << verticalWall << "\n";
		cout << "     " << leftBottomCorner << string(4, horizontalWall) << rightBottomCorner << "\n";

		if (codeToGuess != -1)
		{
			cout << "     " << leftTopCorner << string(4, horizontalWall) << rightTopCorner << "\n";
			cout << "     " << verticalWall << codeToGuess << verticalWall << "\n";
			cout << "     " << leftBottomCorner << string(4, horizontalWall) << rightBottomCorner << "\n";
		}

		MoveCarriageToXY(9, 3 + currentRound);

		_getch();

		MoveCarriageHome();
		ClearScreenFromCursorDown();
	}
}
