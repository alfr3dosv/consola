#include "consola.h"

int Consola::Texto::tamano(string texto) {
	vector<string> lineas = obtenerLineas(texto);
	int maximo = 0;
	for (string s : lineas)
		if (maximo < s.length())
			maximo = s.length();
	return maximo;
}

vector<string> Consola::Texto::obtenerLineas(string texto) {
	vector<string> lineas;
	string linea = "";
	for (char c : texto)
		if (c != '\n') {
			linea += c;
		} else {
			lineas.push_back(linea);
			linea = "";
		}
	return lineas;
}