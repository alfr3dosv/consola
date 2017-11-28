#include <iostream>
#include <vector>

namespace Consola {
using namespace std;

struct AnchoYLargo {
	int ancho;
	int largo;
};
// class Lista
// {
// public:
// 	Lista(vector<string>);
// 	~Lista();

// };

// class Menu
// {
// public:
// 	Menu(vector<Lista>);
// 	~Menu();
// };

// void mostrar(T t) {
// 	cout << box(t)
// }
class ConsolaUI
{
public:
	ConsolaUI();
	virtual string str();
	virtual AnchoYLargo propiedades();
};

class Dialogo : public ConsolaUI {
private:
	string _texto;
	vector<string> _opciones;
	AnchoYLargo _propiedades;

public:
	Dialogo(string, vector<string>, AnchoYLargo);
	string str();
	AnchoYLargo propiedades();
};

class Menu : public ConsolaUI
{
private:
	string _texto;
	vector<string> _opciones;
	AnchoYLargo _propiedades;
	boolean horizontal;

public:
	Dialogo(string, vector<string>, AnchoYLargo);
	string str();
	AnchoYLargo propiedades();
};

class Tabla : public ConsolaUI
{
private:
	string _texto;
	vector<string> _opciones;
	AnchoYLargo _propiedades;
	boolean horizontal;

public:
	Dialogo(string, vector<string>, AnchoYLargo);
	string str();
	AnchoYLargo propiedades();;
	
};

namespace Encuadre {

string Encuadrar(string, AnchoYLargo);
string Encuadrar(vector<string>);
string GenerarLinea(int);
}

namespace Texto {

using namespace std;

vector<string> ObtenerLineas(string);
string Recortar(int , Consola::AnchoYLargo);
int TamanoMayorDeLinea(string);
int TamanoMayorDeLinea(vector<string>);
vector<string> Recortar(string, int, AnchoYLargo);
vector<string> RecortarLinea(string, int);

}

}// namespace

using namespace std;
string Consola::Encuadre::Encuadrar(string entrada, AnchoYLargo propiedades) {
	string salida;
	int tamano = Texto::TamanoMayorDeLinea(entrada);
	salida.insert(0, " " + Encuadre::GenerarLinea(propiedades.ancho) + "\n");
	
	vector<string> lineas = Texto::Recortar(entrada, 0, propiedades);

	for (string l : lineas)
		salida.append("| " + l + " |\n");
	
	salida.append(" " + Encuadre::GenerarLinea(propiedades.ancho));
	return salida;
}

string Consola::Encuadre::GenerarLinea(int tamano) {
	return string(tamano, '-');
}

int Consola::Texto::TamanoMayorDeLinea(string texto) {
	vector<string> lineas = Texto::ObtenerLineas(texto);
	int maximo = 0;
	for (string s : lineas)
		if (maximo < s.length())
			maximo = s.length();
	return maximo;
}

vector<string> Consola::Texto::ObtenerLineas(string texto) {
	vector<string> lineas;
	string linea = "";
	for (char c : texto)
		if (c == '\n') {
			lineas.push_back(linea);
			linea = "";

		} else {
			linea += c;
		}

	if (lineas.size() == 0 && texto.length() != 0)
		lineas.push_back(texto);

	return lineas;
}

vector<string> Consola::Texto::Recortar(string texto, int pos, AnchoYLargo propiedades) {
	string textoRecortado = texto.substr(pos);
	vector<string> lineas = Consola::Texto::ObtenerLineas(textoRecortado);
	vector<string> lineasRecortadas;
	
	for (string l : lineas) 
		for (string lr : Texto::RecortarLinea(l, propiedades.ancho-2))
			lineasRecortadas.push_back(lr);
	
	return lineasRecortadas;
}

vector<string> Consola::Texto::RecortarLinea(string texto, int ancho) {
	vector<string> lineas;
	int pos = 0;
	while (pos < texto.length()) {
		string tmp = texto.substr(pos);
		tmp = tmp.substr(0, ancho);
		while (tmp.length() < ancho)
			tmp.append(" ");
		lineas.push_back(tmp);
		pos += ancho;
	}
	return lineas;
}

