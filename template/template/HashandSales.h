#pragma once
#include <string>
#include <iostream>
class Sales_data {
	friend std::hash<Sales_data>;
	friend std::ostream &operator<<
		(std::ostream&, const Sales_data&);
	friend std::istream &operator >> (std::istream&, Sales_data&);
	friend bool operator==(const Sales_data &, const Sales_data &);

	friend std::ostream &print(std::ostream&, const Sales_data&);
	friend std::istream &read(std::istream&, Sales_data&);

public:
	// constructors
	Sales_data() = default;
	Sales_data(const std::string &s) : bookNo(s) { }
	Sales_data(const std::string &s, unsigned n, double p) :
		bookNo(s), units_sold(n), revenue(p*n) { }
	Sales_data(std::istream &);

	std::string isbn() const { return bookNo; }
	Sales_data& operator+=(const Sales_data&);
private:
	double avg_price() const;
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

bool operator==(const Sales_data &l, const Sales_data &r)
{
	return l.isbn() == r.isbn() &&
		l.units_sold == r.units_sold &&
		l.revenue == r.revenue;
}

namespace std
{
	template<>
	struct hash<Sales_data>
	{
		typedef size_t result_type;
		typedef Sales_data argument_type;
		size_t operator()(const Sales_data&s) const;
	};

	inline size_t hash<Sales_data>::operator()(const Sales_data & s) const
	{
		return hash<string>()(s.isbn()) ^ hash<unsigned>()(s.units_sold) ^ hash<double>()(s.revenue);
	}
}