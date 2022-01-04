#include <iostream>
#include <fstream>
#include<vector>
#include<numeric>
#include<string>

#define PART 2

int bin2Dec(const std::vector<int>& vect) {

    int dec = 0;
    for (int i = 0; i < vect.size(); i++) {
        dec += vect[i] * pow(2, (vect.size() - i - 1));
    }
    return dec;
}

void calculateGammaBin(std::ifstream& input, std::vector<int>& resultsGama)
{
    std::string inputString;
    int recordCounter = 0;

    while (!input.eof())
    {
        std::getline(input, inputString);
        recordCounter++;
        for (int i = 0; i < inputString.size(); i++) {

            if (inputString[i] == '1') {
                resultsGama[i]++;
            }
        }
    }
    input.close();

    for (int i = 0; i < resultsGama.size(); i++)
    {
        if (resultsGama[i] > recordCounter / 2)
        {
            resultsGama[i] = 1;
        }
        else
        {
            resultsGama[i] = 0;
        }
    }
}

void calculateEpsilonBin(const std::vector<int>& resultGamma, std::vector<int>& resultEpsilon)
{

    for (int i = 0; i < resultGamma.size(); i++)
    {
        if (resultGamma[i] == 0)
        {
            resultEpsilon[i] = 1;
        }
        else
        {
            resultEpsilon[i] = 0;
        }
    }
}
//part 2
struct VectorWrapper
{
    std::vector<std::string> data;
    std::vector<int> oneCounter;

    VectorWrapper(std::size_t size)
    {
        oneCounter.reserve(size);
        for (int i = 0; i < size; i++)
        {
            oneCounter.push_back(0);
        }
    }
};

void loadData(std::string filename, VectorWrapper& v)
{
    std::ifstream in(filename);
    std::string inputString;
    int recordCounter = 0;
    while (!in.eof())
    {
        std::getline(in, inputString);
        recordCounter++;
        for (int i = 0; i < inputString.size(); i++) {

            if (inputString[i] == '1') {
                v.oneCounter[i]++;
            }
            v.data.push_back(std::move(inputString));
        }
    }
}

int main()
{
#if PART == 1     
    int gamma = 0, epsilon = 0;

    std::ifstream input("input.txt");
    std::vector<int> resultsGama(12, 0);
    std::vector<int> resultsEpsilon(12, 0);
    
    calculateGammaBin(input, resultsGama);
    calculateEpsilonBin(resultsGama, resultsEpsilon);


    gamma = bin2Dec(resultsGama);
    epsilon = bin2Dec(resultsEpsilon);

    std::cout << gamma * epsilon << std::endl;
#endif 

#if PART == 2
    std::size_t charNumber = 12;
    std::string filename("input.txt");
   
    VectorWrapper data(charNumber);


    loadData(filename,data);
    std::cout << data.data.size();
   
 
    


#endif
}