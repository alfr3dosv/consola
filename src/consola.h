#pragma once
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
		
		virtual std::string str();
		virtual Consola::AnchoYLargo propiedades();
	};

	class Dialogo : public ConsolaUI {
	private:
		std::string _texto;
		std::vector<std::string> _opciones;
		Consola::AnchoYLargo _propiedades;

	public:
		Dialogo(std::string, std::vector<std::string>, Consola::AnchoYLargo);
		std::string str();
		Consola::AnchoYLargo propiedades();
	};

	class Menu : public ConsolaUI
	{
	private:
		std::string _texto;
		std::vector<string> _opciones;
		Consola::AnchoYLargo _propiedades;
		bool horizontal;

	public:
		Menu(std::string, std::vector<std::string>, Consola::AnchoYLargo);
		std::string str();
		Consola::AnchoYLargo propiedades();
	};

	class Tabla : public ConsolaUI
	{
	private:
		std::string _texto;
		std::vector<std::string> _opciones;
		Consola::AnchoYLargo _propiedades;
		bool horizontal;

	public:
		Tabla(std::string, std::vector<std::string>, Consola::AnchoYLargo);
		std::string str();
		Consola::AnchoYLargo propiedades();;

	};

	namespace Encuadre {

		std::string Encuadrar(std::string, Consola::AnchoYLargo);
		std::string Encuadrar(std::vector<std::string>);
		std::string GenerarLinea(int);
	}

	namespace Texto {

		using namespace std;

		std::vector<std::string> ObtenerLineas(std::string);
		std::string Recortar(int, Consola::AnchoYLargo);
		int TamanoMayorDeLinea(std::string);
		int TamanoMayorDeLinea(std::vector<string>);
		std::vector<std::string> Recortar(std::string, int, Consola::AnchoYLargo);
		std::vector<std::string> RecortarLinea(std::string, int);

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

		}
		else {
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
		for (string lr : Texto::RecortarLinea(l, propiedades.ancho - 2))
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

Consola::Menu::Menu(string s, vector<string> opciones, AnchoYLargo propiedades)
{
	_texto = s;
	_opciones = opciones;
	_propiedades = propiedades;
}

string Consola::Menu::str() {
	string salida = _texto;
	for (string s : _opciones) {
		salida = Consola::Encuadre::Encuadrar(s, Consola::AnchoYLargo{
			_propiedades.ancho, 1
		});
	}
	return salida;
}

Consola::Menu::Menu(string s, vector<string> opciones, AnchoYLargo propiedades)
{
	_texto = s;
	_opciones = opciones;
	_propiedades = propiedades;
}

Consola::AnchoYLargo Consola::Menu::propiedades() {
	return _propiedades;
}
