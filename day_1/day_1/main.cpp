#include <iostream>
#include <fstream>
#include <vector>
#include<numeric>

int calulateDepth(std::ifstream& input) //first part
{
    int first{ 0 }, second{ 0 }, counter{ 0 };

    input >> first;


    while (!input.eof())
    {
        input >> second;
        if (second >  first) { counter++; }
        first = second;
    }

    return counter;
}

int calculateTriple(std::ifstream& input)//second part
{
    std::vector<int> vector;
    std::vector<int> sums;

    unsigned int counter = 0;
    int tmp{ 0 }, tmp2{ 0 };

    while (!input.eof())
    {
        input >> tmp;
        vector.push_back(tmp);
    }
    input.close();

    int blockSize = 3;
    std::vector<int>::iterator end = vector.begin();
    auto start = vector.begin();
    std::advance(end, blockSize);

    while (start != vector.end() - blockSize)
    {
        tmp2 = std::accumulate(start, end, 0);
        sums.emplace_back(std::move(tmp2));
        std::advance(start, 1);
        std::advance(end, 1);
    }


    for (int i = 1; i < sums.size(); i++)
    {
        if (sums[i - 1] < sums[i])
            counter++;
    }

    return counter;
}





int main()
{
   std::ifstream input("input.txt");

  //part 1
  // std::cout<< calulateDepth(input) << std::endl;
    
   std::cout <<  calculateTriple(input) << std::endl;

}

