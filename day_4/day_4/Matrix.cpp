#include "Matrix.h"

std::istream& operator>>(std::istream& in, Matrix& mat)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			in >> mat.arr[i][j];
		}
	}

	return in;
}

std::ostream& operator<<(std::ostream& out, const Matrix& mat)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; ++j)
		{
			out << mat.arr[i][j] << " ";
		}
		out<< "\n";
	}
	return out;
}

bool Matrix::sameCollumn(const std::vector<int>& collumn) const
{
	bool result = false;
	int counter = 0;
	for (int i = 0; i < 5; i++) {

			for (int j = 0; j < 5; j++)
			{
				for (int k = 0; k < collumn.size(); k++)
				{
					if (arr[i][j] == collumn[k])
					{
						counter++;
					}
				}
			}


			if (counter == 5) {
				return true;
			}

			else{
			counter = 0;
			}
		}
	return result;
}


bool Matrix::sameRow(const std::vector<int>& row) const
{
	bool result = false;
	int counter = 0;
	
	for (int i = 0; i < 5; i++) {

		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < row.size(); k++)
			{
				if (arr[j][i] == row[k])
				{
					counter++;
				}
			}
		}

		if (counter == 5) {
			return true;
		}
		else {
			counter = 0;
		}
	}
	return result;
}

std::vector<int> Matrix::getMatrixAsaVector() const
{
	std::vector<int> converted;
	converted.reserve(25);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
		{
			converted.push_back(arr[i][j]);
		}
	}
	return converted;
}


