#include "consola.h"
#include <iostream>

using namespace std;
int main() {
	auto menu = Consola::Menu("Fruta?", vector<string> {
		"Uvas",
		"Manzanas"
	});

	cout << menu.capturar();
}