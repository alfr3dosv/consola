#include "consola/consola.h"

int main() {
	Consola::Consola c(Consola::anchoYlargo {
		50,
		50,
	});

	auto lista = ConsolaUI("Algo", Consola::lista {
		Consola::lista {

		},
		ConsolaUI("Algo")
	});
	Consola::mostrar(lista);
}