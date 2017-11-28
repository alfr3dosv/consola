#include "consola/consola.h"

int main() {
	using namespace std;
	// Consola::Consola c(Consola::anchoYlargo {
	// 	50,
	// 	50,
	// });

	// auto lista = ConsolaUI("Algo", Consola::lista {
	// 	Consola::lista {

	// 	},
	// 	ConsolaUI("Algo")
	// });
	// Consola::mostrar(lista);
	cout << endl << Consola::Encuadre::Encuadrar("Texto de prueba para probar que funciona", Consola::AnchoYLargo {30,30}) << endl;
}