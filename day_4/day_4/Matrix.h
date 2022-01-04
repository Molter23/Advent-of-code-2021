#pragma once
#include<iostream>
#include<vector>


struct Winner
{
	int winningBoard;
	std::vector<int> currentNumbers;
};


class Matrix
{
private:
	int arr[5][5];

public:
	Matrix() = default;


	friend std::istream& operator>>(std::istream& in, Matrix& mat);
	friend std::ostream& operator<<(std::ostream& out, const Matrix& mat);



	bool sameCollumn(const std::vector<int>& collumn) const;
	bool sameRow(const std::vector<int>& row) const;

	std::vector<int> getMatrixAsaVector() const;
};