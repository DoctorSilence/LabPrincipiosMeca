#include <iostream>
using namespace std;

int main ()
{
	int i;
	string s ("Introduce un numero entero");		
	cout << s << endl;
	cin >> i;

	cout << "Operaciones Aritméticas:" << endl;
	cout << "i + 5 = " << i + 5 << endl;
	cout << "++i = " << ++i << endl;
	cout << "--i = " << --i << endl;
	cout << "i - 10 = " << i - 10 << endl;
	cout << "i * 10 = " << i * 10 << endl;
	cout << "i % 2 = " << i % 2 << endl;

  return 0;
}
