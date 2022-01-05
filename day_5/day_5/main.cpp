#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<set>
#include<tuple>
#include<algorithm>
#include<functional>

#define PART 2
struct Point
{
	int x{ 0 };
	int y{ 0 };
	unsigned int overlaps{ 1 };

	Point(int x, int y) : x(x), y(y) {};
	Point() = default;

	

	bool operator<(const Point& other) const
	{
		return std::tie(x, y) < std::tie(other.x, other.y);
	}
};

void addPoints(const Point start,const Point end, std::set<Point>& points)
{	
	std::pair<std::set<Point>::iterator, bool> result;

	if (start.x == end.x) 
	{
		int first{ start.y }, last{ end.y };
		if (first > last)
			std::swap(first, last);

		for (int i = first; i <= last; i++)
		{
			
			Point toAdd(start.x, i);
			result = points.emplace(std::move(toAdd));
			

			if (result.second == false)
			{
				Point* p = const_cast<Point*>(&*result.first);
				p->overlaps++;
			}
		}
	}
	else if (start.y == end.y)
	{
		int first{ start.x }, last{ end.x };

		if (first > last)
			std::swap(first, last);

		for (int i = first; i <= last; i++)
		{
			Point toAdd(i, start.y);
			result = points.emplace(std::move(toAdd));

			if (result.second == false)
			{
				Point* p = const_cast<Point*>(&*result.first);
				p->overlaps++;
			}
		}
	}
}

//part 2
void addPointsWithCrossing(const Point start, const Point end, std::set<Point>& points)
{
	std::pair<std::set<Point>::iterator, bool> result;

	if (start.x == end.x)
	{
		int first{ start.y }, last{ end.y };
		if (first > last)
			std::swap(first, last);

		for (int i = first; i <= last; i++)
		{

			Point toAdd(start.x, i);
			result = points.emplace(std::move(toAdd));


			if (result.second == false)
			{
				Point* p = const_cast<Point*>(&*result.first);
				p->overlaps++;
			}
		}
	}
	else if (start.y == end.y)
	{
		int first{ start.x }, last{ end.x };

		if (first > last)
			std::swap(first, last);

		for (int i = first; i <= last; i++)
		{
			Point toAdd(i, start.y);
			result = points.emplace(std::move(toAdd));

			if (result.second == false)
			{
				Point* p = const_cast<Point*>(&*result.first);
				p->overlaps++;
			}
		}
	}
	else if (start.x == start.y && end.x == end.y)
	{
		int first{ start.x }, last{ end.x };

		if (first > last)
			std::swap(first, last);

		for (int i = first; i <= last; i++)
		{
			Point toAdd(i, i);
			result = points.emplace(std::move(toAdd));

			if (result.second == false)
			{
				Point* p = const_cast<Point*>(&*result.first);
				p->overlaps++;
			}
		}
	}
	else if ((start.x == end.y && start.y == end.x) && start.x <= start.y)
	{
		int j = start.y;

		for (int i = start.x; i <= end.x; i++)
		{
			Point toAdd(i, j);
			result = points.emplace(std::move(toAdd));

			if (result.second == false)
			{
				Point* p = const_cast<Point*>(&*result.first);
				p->overlaps++;
			}

			j--;
		}
	}
	else if ((start.x == end.y && start.y == end.x) && start.x > start.y)
	{
		int j = start.x;

		for (int i = start.y; i <= end.y; i++)
		{
			Point toAdd(j, i);
			result = points.emplace(std::move(toAdd));

			if (result.second == false)
			{
				Point* p = const_cast<Point*>(&*result.first);
				p->overlaps++;
			}

			j--;
		}
	}
	
}


void loadDataFromFile(const std::string& filename, std::set<Point>& points, std::function<void(const Point start, const Point end, std::set<Point>& points)> addFun)
{
	std::ifstream in(filename);
	std::string line;
	char separator;
	Point start, end;

	while (!in.eof())
	{
		std::getline(in, line);
		std::stringstream ss(line);
		ss >> start.x >> separator >> start.y >> separator >> separator >> end.x >> separator >> end.y;
		addFun(start, end, points);
	}

}

int countOverlaping(const std::set<Point>& points)
{
	int result = 0;

	std::for_each(points.begin(), points.end(), [&result](const Point& p) {
		if (p.overlaps > 1)
			result++;
		});

	return result;
		
}


int main()
{
	std::function<void(const Point start, const Point end, std::set<Point>& points)> addFun;
	std::string filename("input.txt");
	std::set<Point> points;
#if PART == 1
	addFun = addPoints;
	loadDataFromFile(filename, points, addFun);
	int result = countOverlaping(points);

	std::cout << result << std::endl;
	
#endif

#if PART == 2
	addFun = addPointsWithCrossing;
	loadDataFromFile(filename, points, addFun);
	int result = countOverlaping(points);

	std::cout << result << std::endl;
#endif
	
	
	

	

	std::cin.get();
}

