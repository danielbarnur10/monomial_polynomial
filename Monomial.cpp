#include "Monomial.h"
//#include <iostream> included in the header file
//using namespace std; included in the header file

int Monomial::NumberOfMonomials = 0; 

Monomial::Monomial(double c, unsigned int d) :d(d)							  //constructor default and non default
{ 
	this->c = c;
	NumberOfMonomials++;														//count monomials
}

Monomial::Monomial(const Monomial &mono)	
{
	c = mono.c;
	d = mono.d;
	NumberOfMonomials++;
}

Monomial :: ~Monomial()														//default destructor 
{
	NumberOfMonomials--;													 //update number of monomials
}

 bool Monomial :: add(const Monomial &other)								 //add function to say if adding is possible and add if it is
 {
	 if (this->d == other.d)
	 {
		 this->c += other.c;
		 return true;
	 }
	 return false;
 }

 void Monomial::print() const												//print function 
 {
	 if (this->d == 1)
	 {
		 if (this->c == 1)
			 cout << "x";
		 else
			 cout << this->c << "*x";
	 }
	 else if (this->d == 0)
		 cout << this->c;
	 else if (this->c == 1)
		 cout << "x^" << this->d;
	 else
		 cout << this->c << "*x^" << this->d;
 }

 int Monomial::getNumberOfMonomials()										//returns Number of monomials there are
 {
	 return Monomial::NumberOfMonomials;
 }

 unsigned int Monomial::get_deg() const										//returns the degree of the monomial
 {
	 return this->d;
 }
	
 double Monomial::get_Mekadem() const										// returns the coeofficiant of the monomial
 {
	 return this->c; 
 }

 Monomial* Monomial::GetNext() const										//returns the next node
 {
	 return this->next; 
 }

 void Monomial::SetNext(Monomial *mon)										//sets a new pointer the the next object
 {
	 this->next = mon; 
 }

 void Monomial::SetMekadem(double cc)										// sets new coeofficiant to the object
 {
	 this->c = cc;
 }

 double& Monomial::GetRef()													//returns the referens of the monomial "this"
 {
	 return this->c;
 }

 ostream& operator<<(std::ostream &out, const Monomial &mon)				//operator << to print the monomial
 {
	 if (mon.d == 1)
	 {
		 if (mon.c == 1)
			 out << 'x';
			 else
				 out << mon.c << "*x";
	 }
	 else
		 if (mon.d == 0)
			 out << mon.c;
		 else
			 if (mon.c == 1)
				 out << "x^" << mon.d;
			 else
				 out << mon.c << "*x^" << mon.d;
	 return out;
 }

 istream& operator>>(std::istream &in, Monomial &mono)						//operator >> to input 
 {
	 int i, temp = 1, flag = 0, dd = 0;
	 double cc = 0;
	 char * str = new char[40];
	 i = 0;
	 in.getline(str, 40);
	 while ((flag == 0) && (i < 40))										//if there is 'x' its flags it		
	 {
		 if (str[i] == 'x')
			 flag = 1;
		 else i++;
	 }
	 if (flag == 1)
	 {
		 i = 39;
		 while (str[i] != 'x')												//inputs the number before the 'x'				
		 {
			 if ((str[i] >= '0') && (str[i] <= '9'))
			 {
				 dd += temp * (str[i] - '0');
				 temp *= 10;
			 }
			 i--;
		 }
		 if (dd == 0)														//incase of x^?
			 dd = 1;
		 temp = 1;
		 while (i >= 0)														//takes care of the degree
		 {
			 if ((str[i] >= '0') && (str[i] <= '9'))
			 {
				 cc += temp * (str[i] - '0');
				 temp *= 10;
			 }
			 i--;
		 }
		 if (cc == 0)
			 cc = 1;
		 mono.c = cc;
		 mono.d = dd;
		 return in;
	 }
	 else if (flag == 0)													//when there is no x in the monom
	 {
		 for (i = 39; i >= 0; i--)
		 {
			 if ((str[i] >= '0') && (str[i] <= '9'))
			 {
				 cc += temp * (str[i] - '0');
				 temp *= 10;
			 }
		 }
	 }
	 mono.c = cc;
	 mono.d = 0;
	 return in;
 }

 Monomial Monomial::operator+(const Monomial &mono) const					//operator + 
 {
	 if (this->d == mono.d)													//if degree is equal
		 return Monomial(this->c + mono.c, this->d);						//then create new monomial and return the sum of both
	 else return Monomial(this->c, this->d);								// else create new object and return it
 }		

 Monomial Monomial::operator-(const Monomial &mono) const					//operator -
 {
	 if (this->d == mono.d)													//same as +
		 return Monomial(this->c - mono.c, this->d);
	 else return Monomial(this->c, this->d);
 }

 Monomial Monomial::operator*(const Monomial &mono) const					//operator *
 {
	 return Monomial(this->c * mono.c, this->d + mono.d);		
 }

 const Monomial& Monomial::operator=(const Monomial &mono)					//inputs to to 'this' new coeofficiant and degree
 {
	 this->c = mono.c;
	 this->d = mono.d;
	 return *this;															//returns the address
 }

 const Monomial& Monomial::operator+=(const Monomial &mono)					// += adds to monomial the values 
 {
	 if (this->d == mono.d)													//only if degree is equal
		 this->c += mono.c;	
	 return *this;															//returns the address
 }		

 const Monomial& Monomial::operator-=(const Monomial &mono)					//-=  subtracting same 
 {
	 if (this->d == mono.d)
		 this->c -= mono.c;
	 return *this;
 }

 const Monomial& Monomial::operator*=(const Monomial &mono)					//operator  *= multipling
 {
	 this->c *= mono.c;
	 this->d += mono.d;
	 return *this;
 }
	
 const bool Monomial::operator==(const Monomial &mono)const					// operator == checks if equals
 {
	 if (this->c == mono.c && this->d == mono.d)
		 return true;
	 return false;
 }

 const bool Monomial::operator!=(const Monomial &mono)const					// checks if not equals
 {
	 if (this->c != mono.c || this->d != mono.d)
		 return true;
	 return false;
 }

 Monomial Monomial::operator-() const										//operator - returns the oposite value
 {
	 return Monomial(-1*(this->c), this->d);
 }

 const double Monomial::operator()(unsigned int x) const					//inertion to the monomial an intiger 
 {
	 int sum = 1;
	 for (unsigned int i = 1; i <= this->d; i++)
		 sum *= x;
	 return this->c*sum;													//and returns the value of the monomial with that int
 }

 void Monomial::get_D_And_C(char* str, double &c, int &d)					//converts the string to 'this' monomial 
 {
	 int i;
	 bool checkC = true, minus = false;
	 if (str[0] == '-')														//incase minus
		 minus = true;
	 for (i = 0; str[i] != '\0'; i++)						
	 {
		 if (checkC == true && (str[i] >= '0' && str[i] <= '9'))			//converts to coeofficiant the string
		 { 
			 c = c * 10 + (str[i] - '0');
		 }
		 else if (str[i] == 'x')											//flags the 'x'
		 {
			 checkC = false; 
		 }
		 else if (checkC == false && str[i] != '^' && str[i] != ' ')		//converts the string to degree
		 { 
			 d = d * 10 + (str[i] - '0');
		 }
	 }
	 if (checkC == false && d == 0) d = 1;									//if theres an 'x'
	 if (minus == true) c *= -1;											//if minus is there
 }