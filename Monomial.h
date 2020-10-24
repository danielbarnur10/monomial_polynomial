#ifndef Monomial_h
#define Monomial_h
#include<iostream>	

using namespace std;

class Monomial
{
private:
	double c;						// coefficiant
	unsigned int d;					// degree 
	Monomial *next = NULL;			//pointer to next 
	static int NumberOfMonomials;	//total monomials existing conter
public:
	Monomial(const Monomial&);						//copy constructor
	~Monomial();									//distructor 
	Monomial(double = 1, unsigned int = 0);			//constructor
	static int getNumberOfMonomials();				//monomial counter
	bool add(const Monomial&);						// check and add monomials if possible
	void print() const;								//print monomial
	Monomial* GetNext() const;						//get next monomial 'node'
	void SetNext(Monomial*);						//set pointer to next monomial 'node'
	unsigned int get_deg() const;					//to get d from private
	double get_Mekadem() const;						//to get c from private
	void SetMekadem(double);						//set mekadem
	double & GetRef();								//get adress of coefficaint
	friend ostream& operator<<(ostream &, const Monomial &);	//operator for output
	friend istream& operator>>(istream &, Monomial &);			//operator for input
	Monomial operator+(const Monomial &) const;					//operator for adding two monomials
	Monomial operator-(const Monomial &) const;					//operator for subtracting two monomials
	Monomial operator*(const Monomial &) const;					//operator for multiplying two monomials
	const Monomial& operator=(const Monomial &);				//operator to copy monomial	
	const Monomial& operator+=(const Monomial &);				//operator to add to monomial
	const Monomial& operator-=(const Monomial &);				//operartor to subtract from monomial
	const Monomial& operator*=(const Monomial &);				//operator to multiply monomial
	const bool operator==(const Monomial &)const;				//operator to check if equal
	const bool operator!=(const Monomial &)const;				//operator to check if unequal
	Monomial operator-() const;									//switch all signes from + to -, and from - to +
	const double operator()(unsigned int) const;				//get monomial value for certain 'x' value
	static void get_D_And_C(char*, double&, int&);				//get the monomials degree and coefficiant
};
#endif