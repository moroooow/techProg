#include "DataStruct.h"

namespace DataStruct
{

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
		{
			in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' };
			std::string str;
			std::istream_iterator<char> beg(in);
			for (int i = 0; i < 4 && *beg != '\0'; ++i)
			{
				if (i != 3)
				{
					str += *beg;
					beg++;
				}
				else
				{
					str += *beg;
				}
			}
			if (str == "key1" && in)
			{
				in >> LongLongIO{ tmp.key1 } >> DelimiterIO{ ':' };
				std::string str1;
				std::istream_iterator<char> beg(in);
				if (!in)
				{
					in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					return in;
				}
				for (int i = 0; i < 4 && *beg != '\0'; ++i)
				{
					if (i != 3)
					{
						str1 += *beg;
						beg++;
					}
					else
					{
						str1 += *beg;
					}
				}
				if (str1 == "key2" && in)
				{
					in >> ComplexIO{ tmp.key2 } >> DelimiterIO{ ':' };
					std::string str2;
					std::istream_iterator<char> beg(in);
					if (!in)
					{
						in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						return in;
					}
					for (int i = 0; i < 4 && *beg != '\0'; ++i)
					{
						if (i != 3)
						{
							str2 += *beg;
							beg++;
						}
						else
						{
							str2 += *beg;
						}
					}
					if (str2 == "key3" && in)
					{
						in >> StringIO{ tmp.key3 } >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
						if (in)
						{
							dest = tmp;
						}
						return in;
					}
					else
					{
						in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						return in;
					}
				}
				else if (str1 == "key3" && in)
				{
					in >> StringIO{ tmp.key3 } >> DelimiterIO{ ':' };
					std::string str2;
					std::istream_iterator<char> beg(in);
					if (!in)
					{
						in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						return in;
					}
					for (int i = 0; i < 4 && *beg != '\0'; ++i)
					{
						if (i != 3)
						{
							str2 += *beg;
							beg++;
						}
						else
						{
							str2 += *beg;
						}
					}
					if (str2 == "key2" && in)
					{
						in >> ComplexIO{ tmp.key2 } >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
						if (in)
						{
							dest = tmp;
						}
						return in;
					}
					else
					{
						in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						return in;
					}
				}
				else
				{
					in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					return in;
				}
			}
			else if (str == "key2")
			{
				in >> ComplexIO{ tmp.key2 } >> DelimiterIO{ ':' };
				std::string str1;
				std::istream_iterator<char> beg(in);
				if (!in)
				{
					in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					return in;
				}
				for (int i = 0; i < 4 && *beg != '\0'; ++i)
				{
					if (i != 3)
					{
						str1 += *beg;
						beg++;
					}
					else
					{
						str1 += *beg;
					}
				}
				if (str1 == "key1" && in)
				{
					in >> LongLongIO{ tmp.key1 } >> DelimiterIO{ ':' };
					std::string str2;
					std::istream_iterator<char> beg(in);
					if (!in)
					{
						in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						return in;
					}
					for (int i = 0; i < 4 && *beg != '\0'; ++i)
					{
						if (i != 3)
						{
							str2 += *beg;
							beg++;
						}
						else
						{
							str2 += *beg;
						}
					}
					if (str2 == "key3")
					{
						in >> StringIO{ tmp.key3 } >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
						if (in)
						{
							dest = tmp;
						}
						return in;

					}
					else
					{
						in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						return in;
					}
				}
				else if (str1 == "key3" && in)
				{
					in >> StringIO{ tmp.key3 } >> DelimiterIO{ ':' };
					std::string str2;
					std::istream_iterator<char> beg(in);
					if (!in)
					{
						in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						return in;
					}
					for (int i = 0; i < 4 && *beg != '\0'; ++i)
					{
						if (i != 3)
						{
							str2 += *beg;
							beg++;
						}
						else
						{
							str2 += *beg;
						}
					}
					if (str2 == "key1")
					{
						in >> LongLongIO{ tmp.key1 } >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
						if (in)
						{
							dest = tmp;
						}
						return in;
					}
					else
					{
						in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						return in;
					}
				}
				else
				{
					in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					return in;
				}


			}
			else if (str == "key3")
			{
				in >> StringIO{ tmp.key3 } >> DelimiterIO{ ':' };
				std::string str1;
				std::istream_iterator<char> beg(in);
				if (!in)
				{
					in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					return in;
				}
				for (int i = 0; i < 4 && *beg != '\0'; ++i)
				{
					if (i != 3)
					{
						str1 += *beg;
						beg++;
					}
					else
					{
						str1 += *beg;
					}
				}
				if (str1 == "key1")
				{
					in >> LongLongIO{ tmp.key1 } >> DelimiterIO{ ':' };
					std::string str2;
					std::istream_iterator<char> beg(in);
					if (!in)
					{
						in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						return in;
					}
					for (int i = 0; i < 4 && *beg != '\0'; ++i)
					{
						if (i != 3)
						{
							str2 += *beg;
							beg++;
						}
						else
						{
							str2 += *beg;
						}
					}
					if (str2 == "key2")
					{
						in >> ComplexIO{ tmp.key2 } >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
						if (in)
						{
							dest = tmp;
						}
						return in;
					}
					else
					{
						in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						return in;
					}
				}
				else if (str1 == "key2")
				{
					in >> ComplexIO{ tmp.key2 } >> DelimiterIO{ ':' };
					std::string str2;
					std::istream_iterator<char> beg(in);
					if (!in)
					{
						in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						return in;
					}
					for (int i = 0; i < 4 && *beg != '\0'; ++i)
					{
						if (i != 3)
						{
							str2 += *beg;
							beg++;
						}
						else
						{
							str2 += *beg;
						}
					}
					if (str2 == "key1")
					{
						in >> LongLongIO{ tmp.key1 } >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
						if (in)
						{
							dest = tmp;
						}
						return in;
					}
					else
					{
						in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						return in;
					}
				}
				else
				{
					in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					return in;
				}
			}
			else
			{
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return in;
			}
		}
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
		return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
	}

	std::istream& operator>>(std::istream& in, LongLongIO&& dest)
	{
		std::istream::sentry sentry(in);
		if (!sentry)
		{
			return in;
		}
		std::istream_iterator<char> beg(in);
		std::string str1;
		if (*beg == '0')
		{
			in.setstate(std::ios::failbit);
			return in;
		}
		if (*beg == '-')
		{
			str1 += *beg;
			beg++;
		}
		while (*beg > '0' && *beg < '9')
		{
			str1 += *beg;
			beg++;
		}
		dest.ref = std::stoi(str1);
		std::string str;
		str += *beg;
		beg++;
		str += *beg;
		if (str == "LL" || str == "ll")
		{
			return in;
		}
		else
		{
			in.setstate(std::istream::failbit);
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