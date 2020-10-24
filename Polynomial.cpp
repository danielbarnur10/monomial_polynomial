#include "Polynomial.h"
//#include <iostream> -> it's included in the header file
//using namespace std; -> it's included in the header file

Polynomial::Polynomial()												//default constractor
{
	this->First = NULL;													//points to null
}

Polynomial::Polynomial(const Monomial &mono)							//constractor converting Monomial into a Polynomial
{
	Monomial *temp = new Monomial(mono.get_Mekadem(), mono.get_deg());	//creates new monomial with the same values
	this->First = temp;													//points "this" to temp
}

Polynomial::Polynomial(const Polynomial &poly)							//Copy constractor 
{
	this->First = NULL;							
	Monomial* ptr = poly.First;											// pointer to poly
	while (ptr)															//inputs from poly the monomials to the new polynomial "this"
	{
		this->add(*ptr);
		ptr = ptr->GetNext();
	}
}

Polynomial::~Polynomial()												//distractor
{
	this->delet();
}

void Polynomial::print() const											//printing function		
{
	Monomial *temp = this->First;
	if (temp==NULL)
		cout << "0";
	else
		while (temp) 
		{
			if (temp->get_Mekadem() > 0 && temp != this->First)
				cout << "+";
			temp->print();
			temp = temp->GetNext();
		}
}

void Polynomial::add(const Monomial& other)									//adding to Polynomial function by order 
{	
	Monomial *ptr = this->First;			
	if (this->First == NULL)
		this->First = new Monomial(other.get_Mekadem(), other.get_deg());	//incase polynomial empty
	else
	{
		if (ptr->get_deg() < other.get_deg())								//incase the degree of this is smaller
		{
			this->First = new Monomial(other.get_Mekadem(), other.get_deg());//puts first other in the polynomial
			this->First->SetNext(ptr);
		}
		else
		{
			Monomial *prev = NULL;
			while (ptr != NULL && ptr->get_deg() > other.get_deg())			//incase this is greater degree
			{
				prev = ptr;
				ptr = ptr->GetNext();
			}		
			if (ptr == NULL)												//incase we finished the polynomial we set pointer to new monomial
				prev->SetNext(new Monomial(other.get_Mekadem(), other.get_deg()));
			else if (ptr->get_deg() == other.get_deg())						//incase of same degree we add
			{
				ptr->add(other);
				if (ptr->get_Mekadem() == 0)								
				{
					if (ptr == this->First)
						this->First = this->First->GetNext();
					else
					{
						prev->SetNext(ptr->GetNext());						
					}
					delete ptr;
				}
			}
			else if (ptr->get_deg() < other.get_deg())						//incase this has smaller degree
			{
				prev->SetNext(new Monomial(other.get_Mekadem(), other.get_deg()));
				prev->GetNext()->SetNext(ptr);
			}

		}
	}
}

ostream& operator<<(std::ostream & out, const Polynomial & pn)				//Operator << for output using print funcion
{
	pn.print();
	return out;
}

istream& operator>>(std::istream &in, Polynomial &p)						//Operator >> for input
{																			//uses another function in monomial: get_D_And_C
	int i = 0, j = 0, d = 0, flag = 0;
	double c = 0;
	bool minus, checkinput = false;											
	char *str = new char[100];
	if (p.First)
		p.delet();
	while (!checkinput) 
	{
		cin.getline(str, 100);
		if ((str[0] >= '0' && str[0] <= '9') || (str[0] == '-'))				//incase of minus
		{
			checkinput = true;													//flag for correct input
		}
		else cout << "Incorrect input." << endl;								//else wrong input
	}	
	if (str[0] == '-')															//incase of minus
	{
		flag = 1;																//flag minus
		minus = true;
	}
	else minus = false;															//incase plus
	for (i = 0; str[i] != ',' && str[i] != '\0'; i++) {							//puts minus where needed to monomial
		char *monomialStr = new char[100];
		if (minus == true) 
		{ 
			monomialStr[j] = '-';
			if (flag == 0)
			{
				j++;
			}
			else
			{
				j++;
				i++;
			}
		}
		while (str[i] != '+' && str[i] != '-' && str[i] != ',' && str[i] != '\0') //inputs numbers
		{
			monomialStr[j] = str[i];
			i++;
			j++;
		}			
		monomialStr[j] = '\0';														//monomial finished
		Monomial::get_D_And_C(monomialStr, c, d);									//takes care in Monomial_h						
		delete[]monomialStr;														//deletion of monomoial string
		p.add(Monomial(c, d));
		c = d = j = 0; 
		if (str[i] == '\0')															//incase finished all string
			break; 
		minus = str[i] == '-' ? true : false;
	}
	delete[]str;
	return in;
}

Polynomial Polynomial::operator+(const Polynomial &pl)const		//operator for adding two polynomials
{
	Polynomial total=(*this);									//copies the value of "this"
	Monomial *ptr = pl.First;									//pointer of the current node
	while (ptr)
	{
		total.add(*ptr);										//inserts into total values
		ptr = ptr->GetNext();									//points to the next node
	}
	return total;												//returns the new object Polynomial
}

Polynomial Polynomial::operator-(const Polynomial &pl)const		//operator for subtracting two polynomials
{
	Polynomial total = *this;									//copies the value of "this"
	Monomial *ptr = pl.First;									//pointer of the current node
	while (ptr)
	{
		total.add(-*ptr);										//using add function to insert into total values
		ptr = ptr->GetNext();									//points the next node
	}
	return total;												//returns the new object Polynomial
}

const Polynomial& Polynomial::operator+=(const Polynomial &pl)	//operator for adding to polynomials	
{
	Monomial *ptr = pl.First;
	while (ptr)
	{
		this->add(*ptr);										//using add function to add to "this" the value
		ptr = ptr->GetNext();
	}
	return *this;												// returns the addres of "this"
}

const Polynomial& Polynomial::operator-=(const Polynomial &pl)	//operator for subtracting from polynomials
{
	Monomial *ptr = pl.First;
	while (ptr)
	{
		this->add(-*ptr);
		ptr = ptr->GetNext();
	}
	return *this;
}

double Polynomial::operator()(int num)const						//get polynomial value for 'x' value
{
	double sum = 0;
	Monomial *ptr = this->First;
	while (ptr != NULL)							
	{
		sum += (*ptr)(num);										//using sum to add a new value 
		ptr = ptr->GetNext();
	}
	return sum;
}

double& Polynomial::operator[](const unsigned int num)const		//get coefficiant of monom with certain degree
{
	Monomial *ptr = this->First;
	static double temp = 0;
	while (ptr != NULL)
	{
		if (ptr->get_deg() == num)
		{
			return ptr->GetRef();
		}
		ptr = ptr->GetNext();
	}
	return temp;
}

const Polynomial& Polynomial::operator=(const Polynomial& pl)			//opreator = inserts new polynomial into 
{																		//"this" the existing polynomial
	if (this->First != NULL)
		this->delet();

Monomial *ptr = pl.First;
	while (ptr)
	{
		this->add(*ptr);												//using add function to put inside "this"
		ptr = ptr->GetNext();
	}
	return *this;
}

void Polynomial::delet()								
{
	while (this->First != NULL)
	{																	//delete if there are monomials 
		Monomial* temp = this->First;									// put the address to delete in 'temp'
		this->First = First->GetNext();									// skip to the next momomial
		delete temp;													// delete the previous monomial
	}
}

const bool Polynomial::operator!=(const Polynomial &other)const			//operator != 
{
	Monomial *ptr, *otherPtr;
	ptr = this->First;
	otherPtr = other.First;
	while (ptr != NULL && otherPtr != NULL)								//if there is still nodes
	{
		if ((ptr->get_deg() != otherPtr->get_deg()) || (ptr->get_Mekadem() != otherPtr->get_Mekadem()))
			return true;												//if are different returns true
		ptr = ptr->GetNext();
		otherPtr = otherPtr->GetNext();
	}
	if (ptr == NULL && otherPtr == NULL)
		return false;													//else false
	else																//returns boolian true or false 
		return true;
}

const bool Polynomial::operator==(const Polynomial &other)const			//operator ==
{																		//does opposite then !=
	Monomial *ptr, *otherPtr;
	ptr = this->First;
	otherPtr = other.First;
	while (ptr != NULL && otherPtr != NULL)
	{
		if ((ptr->get_deg() != otherPtr->get_deg()) || (ptr->get_Mekadem() != otherPtr->get_Mekadem()))
			return false;
		ptr = ptr->GetNext();
		otherPtr = otherPtr->GetNext();
	}
	if ((ptr == NULL && otherPtr != NULL) || (ptr != NULL && otherPtr == NULL))
		return false;													//if are different return false
	else return true;													//else true
} 

Polynomial Polynomial::operator-()const									//unari minus oprerator 
{
	Polynomial newPl;
	if (!this->First)													//if "this" doesnt exists returns empty polynomial
		return newPl; 
	Monomial* monPtr;
	Monomial* ptr = this->First;				
	if (this->First) {							
		newPl.First = new Monomial(this->First->get_Mekadem(), this->First->get_deg());
		*newPl.First = -(*newPl.First);
		ptr = ptr->GetNext();
	}
	monPtr = newPl.First;
	while (ptr != NULL) {												//inserts minus to each monomial	
		Monomial *m1 = new Monomial(ptr->get_Mekadem(), ptr->get_deg());
		*m1 = -*m1;
		monPtr->SetNext(m1);
		monPtr = monPtr->GetNext();
		ptr = ptr->GetNext();
	}
	return newPl;														//returns new polynomial
}


