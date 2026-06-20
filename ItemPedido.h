#pragma once
#include "iostream"
#include "conio.h"
#include "Producto.h"
using namespace std;
class ItemPedido {
public:
	// declaramos los atributos como publicos para poder acceder a ellos desde otras 
	// clases como Carrito y Pedido
	Producto* producto;
	double precioUnitario;
	int cantidad;
public:
	// Constructor por defecto sin parámetros
	ItemPedido() : producto(nullptr), precioUnitario(0), cantidad(0) {}
	// Constructor con parámetros
	// le pasamos un puntero al producto y la cantidad que se desea comprar
	ItemPedido(Producto* prod, int cant) : producto(prod), cantidad(cant),
		precioUnitario(prod->precio) {}

	~ItemPedido() {}

	double getSubtotal() {
		return cantidad * precioUnitario;
	}

	void setCantidad(int n) {
		cantidad = n;
	}

	void mostrar() {
		cout<< "  " << producto->nombre
			<< " | Cant: " << cantidad
			<< " | Precio unit: S/." << precioUnitario
			<< " | Subtotal: S/." << getSubtotal() << endl;
	}


};
