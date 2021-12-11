#include <iostream>
#include <fstream>

#define PART 1

class stringWrapper
{
public:
	inline static const std::string forward = "forward";
	inline static const std::string down = "down";
	inline static const std::string up = "up";
};


struct position
{
//first part
	int horizontal{ 0 };
	int depth{ 0 };

//second part
	int aim{ 0 };
};


bool compareStrings(const std::string& first, const std::string& second)
{
	if (first.length() != second.length())
		return false;

	for (int i = 0; i < first.length(); i++)
	{
		if (first[i] != second[i])
			return false;
	}

	return true;
}


void proccedComnads(std::ifstream& inputStream, stringWrapper s, position& pos)
{
	std::string command;
	int value;
	while (!inputStream.eof())
	{
		inputStream >> command >> value;
#if PART == 1
		if (compareStrings(command, stringWrapper::forward))
		{
			pos.horizontal += value;
		}
		else if (compareStrings(command, stringWrapper::up))
		{
			pos.depth -= value;
		}
		else if (compareStrings(command, stringWrapper::down))
		{
			pos.depth += value;
		}
#endif

#if PART==2 
		if (compareStrings(command, stringWrapper::forward))
		{
			pos.horizontal += value;
			pos.depth += pos.aim * value;	
		}
		else if (compareStrings(command, stringWrapper::up))
		{
			pos.aim -= value;
		}
		else if (compareStrings(command, stringWrapper::down))
		{
			pos.aim += value;
		}
#endif
	}
}

int main()
{
	std::ifstream input("input.txt");
	stringWrapper s;
	position result;


	proccedComnads(input, s, result);

	std::cout << result.depth * result.horizontal << std::endl;


	std::cin.get();
}