#ifndef Polynomial_h
#define Polynomial_h
#include<iostream>
#include "Monomial.h"

using namespace std;

class Polynomial
{
private:
	Monomial *First;						//pointer to first monomial 'node' in polynomial 
public:
	Polynomial();							// Default Constructor 
	Polynomial(const Monomial &);			//convertion constructor
	Polynomial(const Polynomial &);			//copy constructor
	~Polynomial();							// distructor
	void add(const Monomial&);				//add monomial 'node' to polynomial
	void print() const;						//print polynomial
	friend ostream& operator<<(ostream & out, const Polynomial &);	//operator << for output
	friend istream& operator>>(istream & out, Polynomial &);		//operator >> for input
	Polynomial operator+(const Polynomial &)const;					//operator for adding two polynomials
	Polynomial operator-(const Polynomial &)const;					//operator for subtracting two polynomials
	const Polynomial& operator+=(const Polynomial &);				//operator for adding to polynomials	
	const Polynomial& operator-=(const Polynomial &);				//operator for subtracting from polynomials
	double operator()(const int)const;								//get polynomial value for 'x' value
	double& operator[](const unsigned int)const;					//get coefficiant of monom with certain degree
	const Polynomial& operator=(const Polynomial &);				//copy polynomials
	void delet();													//delete polynomial
	const bool operator!=(const Polynomial &)const;					//check if unequal
	const bool operator==(const Polynomial &)const;					//check if equal
	Polynomial operator-()const;									//switch all signes from + to -, and from - to +
};
#endif
