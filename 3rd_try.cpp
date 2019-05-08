#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class a
{
	private:
		int b;
	public:
		a();
		~a();
};

a:: a()
{
}

a:: ~a()
{
	std:: cout << "Hui sosi guboy tryasi\n"; 
}


int main ()
{
	a mn;

	return 0;
}