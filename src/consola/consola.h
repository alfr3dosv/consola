#include <iostream>
#include <vector>

namespace Consola {
using namespace std;

struct Lista {
	string texto;
	std::vector<Lista> lista;
};

typedef vector<Lista> lista;
void mostrarLista(vector<Consola::Lista>, int espacios = 0);

void mostrar(Consola::Lista lista) {
	cout << lista.texto;
	mostrarLista(lista.lista);
}

void mostrarLista(vector<Consola::Lista> lista, int espacios) {
	if (!lista.empty())
		for (Lista l : lista) {
			cout << l.texto;
			mostrarLista(l.lista, espacios + 1);
		}
}

Consola::Lista ConsolaUI(std::string texto)
{
	Consola::Lista lista {
		texto,
		std::vector<Consola::Lista> {}
	};
	return lista;
}

Consola::Lista ConsolaUI(std::string texto, std::vector<Consola::Lista> lista)
{
	return Consola::Lista {
		texto,
		lista
	};
}