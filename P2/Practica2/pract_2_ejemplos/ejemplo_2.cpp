#include <stdio.h>
#include <string>

int main()
{
	int num = 5;
	float f = 3.1416;
	char c = 'G';
	std::string s ( "Hola, mundo!" );
	printf ("Ejemplo 2: Imprimir\n");
	printf ("\tNúmeros:\n \t\tEnteros: %d\n", num);
	printf ("\t\tCon punto decimal: %f\n", f);
	printf ("\tCaracteres: %c\n", c);
	printf ("\tStrings: %s\n", s.c_str());
   return 0;
}
