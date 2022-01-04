#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>


#include"Matrix.h"

void loadDataFromFile(const std::string& filename, std::vector<int>&randomNumbers, std::vector<Matrix>& boards)
{
	std::ifstream in(filename);
	int value{ 0 };
	char separator{ ',' };
	std::string numberToFilter;
	
	std::getline(in, numberToFilter);
	std::stringstream ss(numberToFilter);
	
	while (!ss.eof())
	{
		ss >> value >> separator;
		randomNumbers.push_back(value);
	}
	

	Matrix board;

	while (!in.eof())
	{
		in >> board;
		boards.emplace_back(std::move(board));
	}
}

Winner BingoFirstWin(std::vector<int>& randomNumbers, std::vector<Matrix>& boards)
{
	Winner winer;
	const int numberOfWinningNumbers = 5;
	bool winnerFound = false;
	auto begin= randomNumbers.begin();
	auto end = randomNumbers.begin() + numberOfWinningNumbers;
	int indexOfNextNumber = 5, winningBoard = 0;

	bool winnerC = false , winnerR = false;
	std::vector<int> currentNumbers(begin, end);
	

	
	while (winnerFound != true)
	{
		for (int i = 0; i < boards.size(); ++i)
		{
			winnerC = boards[i].sameCollumn(currentNumbers);
			winnerR = boards[i].sameRow(currentNumbers);

			if (winnerC == true || winnerR == true)
			{
				winnerFound = true;
				winer.winningBoard = i;
				winer.currentNumbers = currentNumbers;
			}
		}

		if (indexOfNextNumber < randomNumbers.size() && winnerFound != true)
		{
			currentNumbers.push_back(randomNumbers[indexOfNextNumber]);
			indexOfNextNumber++;
		}
		else
		{
			break;
		}
	}

	return winer;
}

Winner BingoLastWin(std::vector<int>& randomNumbers, std::vector<Matrix>& boards)
{
	Winner winer;
	const int numberOfWinningNumbers = 5;
	bool winnerFound = false;
	auto begin = randomNumbers.begin();
	auto end = randomNumbers.begin() + numberOfWinningNumbers;
	int indexOfNextNumber = 5;

	bool winnerC = false, winnerR = false;
	std::vector<int> currentNumbers(begin, end);

	std::vector<Matrix>::iterator toErase = boards.begin();


	while (boards.size() != 1)
	{
		while (winnerFound != true)
		{
			for (int i = 0; i < boards.size(); ++i)
			{
				winnerC = boards[i].sameCollumn(currentNumbers);
				winnerR = boards[i].sameRow(currentNumbers);

				if (winnerC == true || winnerR == true)
				{
					std::cout << i << std::endl;
					winnerFound = true;
					winnerC = false;
					winnerR = false;
					winer.winningBoard = i;
					winer.currentNumbers = currentNumbers;
				}
			}

			if (indexOfNextNumber < randomNumbers.size() && winnerFound != true)
			{
				currentNumbers.push_back(randomNumbers[indexOfNextNumber]);
				indexOfNextNumber++;
			}
			else
			{
				break;
			}
		}
		
		*toErase = boards[winer.winningBoard];
		boards.erase(toErase);
	}
	
	return winer;
}
/*{
	Winner winer;
	const int numberOfWinningNumbers = 5;
	bool winnerC = false, winnerR = false;
	auto begin = randomNumbers.begin();
	auto end = randomNumbers.begin() + numberOfWinningNumbers;
	int indexOfNextNumber = 5, winningBoard = 0;

	std::vector<Matrix>::iterator toErase = boards.begin();
	std::vector<int> currentNumbers(begin, end);



	while (boards.size() != 1)
	{	
		for (int i = 0; i < boards.size(); ++i)
		{
			winnerC = boards[i].sameCollumn(currentNumbers);
			winnerR = boards[i].sameRow(currentNumbers);
			*toErase = boards[i];
			
			if (winnerC == true || winnerR == true)
			{
				boards.erase(toErase);
				winnerC = false;
				winnerR = false;
			}
			
		}
		toErase = boards.begin();
	
		winer.currentNumbers = currentNumbers;

		if (indexOfNextNumber < randomNumbers.size())
		{
			currentNumbers.push_back(randomNumbers[indexOfNextNumber]);
			indexOfNextNumber++;
		}
		else
		{
			break;
		}
	}


	winer.winningBoard = 0;

	return winer;
}
*/

bool contains(const std::vector<int>& vect, int value)
{
	for (int i : vect)
	{
		if (i == value)
			return true;
	}
	return false;
}

int finalScore(const Winner win, const std::vector<Matrix>& boards)
{
	int score = 0;
	std::vector<int> winner (boards[win.winningBoard].getMatrixAsaVector());


	for (int i : winner)
	{
		if (!contains(win.currentNumbers, i))
			score += i;
	}

	score *= win.currentNumbers.back();

	return score;
}

int main()
{
	std::vector<int> randomNumbers;
	std::vector<Matrix> boards;
	std::string fileName("input.txt");

	loadDataFromFile(fileName, randomNumbers, boards);
	//Winner winer = BingoFirstWin(randomNumbers, boards);
	
	//int score = finalScore(winer, boards);
	//std::cout << score << std::endl;
	
	Winner lastWiner = BingoLastWin(randomNumbers, boards);



	int secondScore = finalScore(lastWiner, boards);
    std::cout << secondScore << std::endl;

	std::cin.get();
}