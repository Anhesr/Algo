#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


class entero
{
private:
public:
	string _n;
	entero & operator+( entero b);
	entero & operator*( entero const &b);
	entero & operator=( entero const &b);
};



