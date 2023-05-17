#include "DataStruct.h"

namespace DataStruct
{
	bool operator<(const DataStruct& a, const DataStruct& b)
	{
		if (a.key1 != b.key1)
		{
			return a.key1 < b.key1;
		}
		else if (abs(a.key2) != abs(b.key2))
		{
			return abs(a.key2) < abs(b.key2);
		}
		else
		{
			return a.key3 < b.key3;
		}
	}

	ScopeGuard::ScopeGuard(std::basic_ios<char>& s) :
		s_(s),
		fill_(s.fill()),
		precision_(s.precision()),
		fmt_(s.flags())
	{}

	ScopeGuard::~ScopeGuard()
	{
		s_.fill(fill_);
		s_.precision(precision_);
		s_.flags(fmt_);
	}

	std::ostream& operator<<(std::ostream& out, const DataStruct& data)
	{
		std::ostream::sentry sentry(out);
		if (!sentry)
		{
			return out;
		}
		ScopeGuard scopeguard(out);
		out << "(:";
		out << "key1 " << data.key1 << "ll" << ":";
		out << "key2 #c" << std::fixed << std::setprecision(1) << "(" << data.key2.real() << " " << data.key2.imag() << ")" << ":";
		out << "key3 \"" << data.key3 << "\":)";
		return out;
	}

	std::istream& operator>>(std::istream& in, DataStruct& dest)
	{
		std::istream::sentry sentry(in);
		if (!sentry)
		{
			return in;
		}
		DataStruct tmp;
		const size_t countKey = 3;
		{
			std::string lbl[countKey] = { "","","" };
			in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' };
			for (int i = 0; i < countKey && in; i++)
			{
				std::string str;
				in >> LabelIO{ str };
				bool isNFound = std::find(std::cbegin(lbl), std::cend(lbl), str) == std::cend(lbl);
				if (!isNFound)
				{
					in.setstate(std::ios::failbit);
					return in;
				}
				lbl[i] = str;
				if (lbl[i] == "key1")
				{
					in >> LongLongIO{ tmp.key1 };
				}
				else if (lbl[i] == "key2")
				{
					in >> ComplexIO{ tmp.key2 };
				}
				else if (lbl[i] == "key3")
				{
					in >> StringIO{ tmp.key3 };
				}
				else
				{
					in.setstate(std::ios::failbit);
					return in;
				}
				in >> DelimiterIO{ ':' };
			}
			in >> DelimiterIO{ ')' };
		}
		if (in)
		{
			dest = tmp;
		}
		return in;
	}

	std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
	{
		std::istream::sentry sentry(in);
		if (!sentry)
		{
			return in;
		}
		char c = '0';
		in >> c;
		if (in && (c != dest.exp))
		{
			in.setstate(std::ios::failbit);
		}
		return in;
	}

	std::istream& operator>>(std::istream& in, StringIO&& dest)
	{
		std::istream::sentry sentry(in);
		if (!sentry)
		{
			return in;
		}
		std::string str;
		in >> DelimiterIO{ '"' };
		std::istream_iterator<char> beg(in);
		while (*beg != '\"' && in.peek() != '\n')
		{
			str += *beg;
			beg++;
		}
		if (*beg == '\"')
		{
			dest.ref = str;
		}
		else
		{
			in.setstate(std::ios::failbit);
		}
		return in;
	}

	std::istream& operator>>(std::istream& in, LongLongIO&& dest)
	{
		std::istream::sentry sentry(in);
		if (!sentry)
		{
			return in;
		}

		int long long tmp;
		in >> tmp;

		if (in.peek() == 'l')
		{
			in >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
		}
		else if (in.peek() == 'L')
		{
			in >> DelimiterIO{ 'L' } >> DelimiterIO{ 'L' };
		}
		else
		{
			in.setstate(std::ios::failbit);
		}

		if (in)
		{
			dest.ref = tmp;
		}
		return in;
	}

	std::istream& operator>>(std::istream& in, ComplexIO&& dest)
	{
		std::istream::sentry sentry(in);
		if (!sentry)
		{
			return in;
		}
		double real;
		double imag;
		in >> DelimiterIO{ '#' } >> DelimiterIO{ 'c' } >> DelimiterIO{ '(' } >> DoubleIO{ real } >> DoubleIO{ imag } >> DelimiterIO{ ')' };
		if (in)
		{
			dest.ref.real(real);
			dest.ref.imag(imag);
		}
		return in;
	}

	std::istream& operator>>(std::istream& in, DoubleIO&& dest)
	{
		std::istream::sentry sentry(in);
		if (!sentry)
		{
			return in;
		}
		in >> dest.ref;
		if (!in)
		{
			in.setstate(std::ios::failbit);
		}
		return in;
	}
}

std::istream& DataStruct::operator>>(std::istream& in, LabelIO&& dest)
{
	std::istream::sentry sentry(in);
	if (!sentry)
	{
		return in;
	}
	in >> dest.ref;
	if (!in)
	{
		in.setstate(std::ios::failbit);
	}
	return in;
}