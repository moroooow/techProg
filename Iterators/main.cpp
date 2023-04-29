#include "vector"
#include "iostream"
#include "fstream"
#include "DataStruct.h"


int main()
{
	using DataStruct::DataStruct;
	std::vector<DataStruct> data;
	std::ifstream in;

	in.open("test.txt");
	while (!in.eof())
	{
		std::copy(std::istream_iterator<DataStruct>(in),
			std::istream_iterator<DataStruct>(),
			std::back_inserter(data)
		);
		if (in.fail())
		{
			in.clear();
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}


	std::cout << "Data:\n";
	std::copy(
		std::begin(data),
		std::end(data),
		std::ostream_iterator< DataStruct >(std::cout, "\n")
	);
}