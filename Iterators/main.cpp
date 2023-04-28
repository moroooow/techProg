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
	std::string line;
	std::getline(in, line);
	do
	{
		if (!line.empty())
		{
			std::istringstream iss(line);
			std::copy(
				std::istream_iterator< DataStruct >(iss),
				std::istream_iterator< DataStruct >(),
				std::back_inserter(data)
			);
		}
	} while (std::getline(in, line));

	std::cout << "Data:\n";
	std::copy(
		std::begin(data),
		std::end(data),
		std::ostream_iterator< DataStruct >(std::cout, "\n")
	);
}