#pragma once
#ifndef DATA_STRUCT
#define DATA_STRUCT
#include "complex"
#include "iomanip"
#include "iostream"
#include "string"
#include "iterator"
#include "algorithm"


namespace DataStruct
{
	struct DataStruct
	{
		int long long key1;
		std::complex<double> key2;
		std::string key3;
	};
	
	struct ComplexIO
	{
		std::complex<double>& ref;
	};
	struct LongLongIO
	{
		int long long& ref;
	};
	
	struct LabelIO
	{
		std::string& ref;
	};

	struct DelimiterIO
	{
		char exp;
	};
	

	struct DoubleIO
	{
		double& ref;
	};

	struct StringIO
	{
		std::string& ref;
	};

	std::istream& operator>>(std::istream& in, DataStruct& dest);
	std::ostream& operator<<(std::ostream& out,const DataStruct& data);
	std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
	std::istream& operator>>(std::istream& in, StringIO&& dest);
	std::istream& operator>>(std::istream& in, LongLongIO&& dest);
	std::istream& operator>>(std::istream& in, ComplexIO&& dest);
	std::istream& operator>>(std::istream& in, DoubleIO&& dest);
	std::istream& operator>>(std::istream& in, LabelIO&& dest);

	bool operator<(const DataStruct& a, const DataStruct& b);


	class ScopeGuard
	{
	public:
		ScopeGuard(std::basic_ios<char>& s);
		~ScopeGuard();
	private:
		std::basic_ios<char>& s_;
		char fill_;
		std::streamsize precision_;
		std::basic_ios<char>::fmtflags fmt_;
	};
}
#endif // !DATA_STRUCT