#include <iostream>
using namespace std;

int main ()
{
	int i = 1000;

	cout << "for: " << endl;
	for(int j = 0; j < i; ++j)
	{
		cout << "j = " << j ;
		if ( j % 2 )
		{ 
			cout << "\t es impar" << endl;
		} else {
			cout << "\t es par" << endl;
		}
	}
  return 0;
}
