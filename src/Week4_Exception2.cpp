//============================================================================
// Name        : Week4_Exception2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <numeric>
#include <cmath>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <exception>
using namespace std;

void EnsureNotZero(const int& denominator){
	if(denominator == 0){
		throw invalid_argument("Invalid argument");
	}
}

class Rational {
public:

	Rational() {
		p = 0;
		q = 1;
	}

	Rational(const int &numerator, const int &denominator) {
		EnsureNotZero(denominator);
		if (numerator > 0 && denominator > 0) {
			p = numerator / gcd(numerator, denominator);
			q = denominator / gcd(numerator, denominator);
		}
		if (numerator == 0) {
			p = 0;
			q = 1;
		}
		if (numerator < 0 && denominator < 0) {
			p = abs(numerator) / gcd(abs(numerator), abs(denominator));
			q = abs(denominator) / gcd(abs(numerator), abs(denominator));
		}
		if ((denominator > 0 && numerator < 0)
				|| (denominator < 0 && numerator > 0)) {
			p = -(abs(numerator) / gcd(abs(numerator), abs(denominator)));
			q = abs(denominator) / gcd(abs(numerator), abs(denominator));
		}
	}

	int Numerator() const {
		return p;
	}

	int Denominator() const {
		return q;
	}

private:
	int p, q;
};


Rational operator+(const Rational &r1, const Rational &r2) {
	return Rational(
			(r1.Numerator() * r2.Denominator()
					+ r2.Numerator() * r1.Denominator()),
			(r1.Denominator() * r2.Denominator()));
}

Rational operator-(const Rational &r1, const Rational &r2) {
	return Rational(
			(r1.Numerator() * r2.Denominator()
					- r2.Numerator() * r1.Denominator()),
			(r1.Denominator() * r2.Denominator()));
}

Rational operator*(const Rational &r1, const Rational &r2) {
	return Rational(r1.Numerator() * r2.Numerator(),
			r1.Denominator() * r2.Denominator());
}

Rational operator/(const Rational &r1, const Rational &r2) {
	if(r2.Numerator() == 0){
		throw domain_error("Division by zero");
	}
	return Rational(r1.Numerator() * r2.Denominator(),
			r1.Denominator() * r2.Numerator());
}

Rational RationalCalculator(const Rational r1, const char& operation, const Rational r2){
	if(operation == '+'){
		return r1 + r2;
	}
	if(operation == '-'){
		return r1 - r2;
	}
	if(operation == '*'){
		return r1*r2;
	}
	if(operation == '/'){
		return r1/r2;
	}
}

bool operator==(const Rational &r1, const Rational &r2) {
	if ((r1.Numerator() == r2.Numerator())
			&& (r1.Denominator() == r2.Denominator())) {
		return true;
	} else {
		return false;
	}
}

bool operator<(const Rational& r1, const Rational& r2){
	if((r1 - r2).Numerator() < 0){
		return true;
	}
	return false;
}

bool operator>(const Rational& r1, const Rational& r2){
	if(!(r1 < r2)){
		return true;
	}
	return false;
}

ostream& operator<<(ostream &stream, const Rational &r) {
	stream << r.Numerator() << '/' << r.Denominator();
	return stream;
}

istream& operator>>(istream &stream, Rational &r) {
	int p, q ;
	char c ;
	if(!stream){
		return stream;
	}
	stream >> p;
	if(!stream){
		return stream;
	}
	stream >> c;
	if( c != '/'){
		return stream;
	}
	stream >> q;
	if(!stream){
		return stream;
	}
	r = Rational(p, q);
	return stream;
}

int main() {
	Rational r1, r2;
	char operation;
	try{
	cin >> r1 >> operation >> r2;
	cout << RationalCalculator(r1, operation, r2) << endl;
	}
	catch(exception& ex){
		cout << ex.what();
	}
	    return 0;
}


