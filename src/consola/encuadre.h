#include <iostream>
#include <vector>
#

namespace Encuadre {
	using namespace std;

	string encuadrar(string);
	vector<string> encuadrar(vector<string>);
	int tamano(vector<string>);
	string generarLinea(int); 

	string encuadrar(string entrada) {
		string salida(entrada);
		salida.insert(0, " " + Encuadre::generarLinea(entrada.length()) + "\n|");
		salida.append("|\n");
		salida.append(" " + Encuadre::generarLinea(entrada.length()));
		return salida;
	}

	string generarLinea(int tamano) {
		return string(tamano, '-');
	}
}