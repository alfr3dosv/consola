# CONSOLA.H

Es una librería de C++11 para crear interfaces en la consola mas simples.
 * Un Logger basico
 * Creador de Menus
 * Imprimir listas
 * Encuadrar texto
 * Header only (Solo es necesario el .h)

### Requisitos
Un compilador con soporte para C++11, MSVC o GCC funcionaran bien.

## ¿Como instalar?

1. [Descargar](http://a.org) en la sección de releases
2. Agregar al directorio de tu proyecto
3. Incluir ``#include "consola.h"``

## Manual

### Menús
La función capturar muestra la lista de opciones y no retorno hasta que se haya seleccionado un índice valido.

**Ejemplo**
```cpp
auto menu = Consola::Menu("Como te llamas?", vector<string> {
	"Jorge",
	"Alfredo",
	"Otro"
});

int seleccion = menu.capturar();
```
### Lista

Permite enumerar una lista o agregar un modificador propio.

**Ejemplo**
```cpp
auto lista = Consola::Lista(vector<string> lista {
  "Elemento 1",
  "Elemento 2",
  "Elemento 3"
});

cout << lista.letras();
```
### Tablas

Permite mostrar varias filas relacionadas juntas.

**Ejemplo**
```cpp
auto tabla = Consola::Tabla(4, vector<vector<string>> {
		vector<string> {
			"Texto 1",
			"Texto 2",
			"Texto 3"
		},
		vector<string> {
			"Texto 4",
			"Texto 5",
			"Texto 6"

		}
})
```
### Logger
El logger guarda un documento de texto llamado consola.log con información útil para debuggear.

**Ejemplo**
```cpp
Consola::log("[Mensaje Importante] Algo salio mal!");
```
### Limpiar pantalla
Limpia la pantalla.

**Ejemplo**
```cpp
Consola::limpiar();
```
### Encuadrar
Una función útil para hacer sobresalir texto sobre otros

**Ejemplo**
```cpp
Consola::Encuadrar("Texto muy importante");
```
# Licencia 
MIT 

# Autores
 * Alfredo Soto Vargas [alfr3dosv](https://github.com/alfr3dosv)
 * Jorge Eduardo Herrera Solis
