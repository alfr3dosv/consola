#ifndef CONSOLA_H
#define CONSOLA_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <exception>

using std::vector;
using std::cout;

using namespace std;
namespace Consola {
	static ofstream logFile("consola.log");

	inline void log(string s) {
		if (!logFile.is_open())
			throw "[LOG] El archivo no esta disponible";
		logFile << s + "\n";
	}
	namespace texto {

		inline string Encuadrar(string, int);
		inline string Encuadrar(vector<string>);
		inline string GenerarLinea(int, string = "");
		inline vector<string> ObtenerLineas(string);
		inline int TamanoMayordelinea(string);
		inline int TamanoMayordelinea(vector<string>);
		inline vector<string> Recortar(string, int, int);
		inline vector<string> Recortar(vector<string>, int);
		inline vector<string> Recortarlinea(string, int);

	}
}

namespace Consola {
	namespace Texto {

		inline vector<string> ObtenerLineas(string texto) {
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

		inline vector<string> RecortarLinea(string texto, int ancho) {
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

		inline vector<string> Recortar(string texto, int pos, int ancho) {
			string textoRecortado = texto.substr(pos);
			vector<string> lineas = ObtenerLineas(textoRecortado);
			vector<string> lineasRecortadas;

			for (string l : lineas)
				for (string lr : RecortarLinea(l, ancho - 2))
					lineasRecortadas.push_back(lr);

			return lineasRecortadas;
		}

		inline vector<string> Recortar(vector<string> lineas, int ancho) {
			vector<string> lineasRecortadas;

			for (string l : lineas)
				for (string lr : Texto::RecortarLinea(l, ancho - 2))
					lineasRecortadas.push_back(lr);

			return lineasRecortadas;
		}
		inline int TamanoMayorDeLinea(string texto) {
			
			vector<string> lineas = ObtenerLineas(texto);
			int maximo = 0;
			try {
				for (string s : lineas)
					if (maximo < s.length())
						maximo = s.length();
			} catch(exception& e) {
				maximo = 0;
				Consola::log("[TamanoMayorDeLine] error al iterar");
			}
			return maximo;
		}


		inline string GenerarLinea(int tamano, string str = "") {
			return str + string(tamano, '-');
		}

		inline string Encuadrar(string entrada, int ancho) {
			string salida;
			int tamano = TamanoMayorDeLinea(entrada);
			salida.insert(0, " " + GenerarLinea(ancho) + "\n");

			vector<string> lineas;
			try {
				lineas = Recortar(entrada, 0, ancho);
			} catch(exception& e) {
				lineas = {};
				Consola::log("[RECORTAR] Un error al recortar un ");
			}
			for (string l : lineas)
				salida.append("| " + l + " |\n");

			salida.append(" " + GenerarLinea(ancho));
			return salida;
		}
	}
}

namespace Consola {

	class Tabla;
	class Menu;
	class Lista;

	inline void mostrar(Menu m);
	inline void mostrar(Tabla t);
	inline void mostrar(Lista l);

	class Consola
	{
	public:
		virtual string str() = 0;
	};
	
	//tabla
	class Tabla : Consola
	{
	private:
		int indice;
		int ancho = 20;
		vector<vector<string>> campos;
		vector<vector<string>> recortados;

	public:
		friend inline void ::Consola::mostrar(Tabla t);

		inline Tabla(int a, vector<vector<string>> c) {
			ancho = a;
			campos = c;
		}

		inline string str() {
			organizar();
			int indice = 0;
			int maximo = 0;
			stringstream s;

			for (vector<string> fila : recortados) {
				if (fila.size() > maximo)
					maximo = fila.size();
			}
			for (; indice < maximo; indice++) {
				s << linea(indice) << endl;
			}
			return s.str();
		}

		inline bool finalDeCampos(int indice) {
			for (vector<string> campo : recortados)
				if (indice < campo.size())
					return true;
			return false;
		}

		inline string linea(int indice) {
			string linea;
			for (vector<string> campo : campos) {
				string tmp;
				if (indice < campo.size())
					tmp = campo.at(indice);
				else
					tmp = "";
				while (tmp.length() < ancho)
					tmp.append(" ");
				linea += tmp;
			}
			return linea;
		}

		inline void organizar() {
			recortados = {};
			for (vector<string> campo : campos) {
				string texto = "";
				for (string s : campo)
					texto += s;
				recortados.push_back(Texto::Recortar(texto, 0, 5));
			}
		}
	};

	// menu
	class Menu : public Consola {
	private:
		string texto;
		vector<string> listaOpciones;

	public:
		friend inline void ::Consola::mostrar(Menu m);

		inline Menu(string s, vector<string> opciones) {
			texto = s;
			listaOpciones = opciones;
		}

		inline string str() {
			stringstream s;
			s << texto + "\n";
			int i = 1;
			for (string opcion : listaOpciones)
				s << i++ << " " << opcion << "\n";
			return s.str();
		}

		inline int capturar() {
			int opcion;
			do {
				cout << str();
				cout << " : ";
				if (cin >> opcion) {
					// todo bien
				} else {
					opcion = 0;
					cin.clear();
					cin.ignore();
					cout << "Incorrecto";

				}
			} while (opcion < 1 || opcion > listaOpciones.size());
			return opcion;
		}
	};

	class Lista : public Consola {
	private:
		vector<string> lista;

	public:
		friend inline void ::Consola::mostrar(Lista l);

		inline Lista(vector<string> opciones) {
			lista = opciones;
		}

		inline string str() {
			stringstream s;
			int i = 1;
			for (string opcion : lista)
				s << i++ << " " << opcion << "\n";
			return s.str();
		}

	};

	inline void mostrar(Tabla t) {
		cout << t.str();
	}
	
	inline void mostrar(Menu m) {
		cout << m.str();
	}

	inline void mostrar(Lista l) {
		cout << l.str() << "Hecho :)";
	}
	inline void limpiar() {
		system("cls"); // windows
		cout << "\033[H"; // linux
	}
}






#endif // !CONSOLA_H
