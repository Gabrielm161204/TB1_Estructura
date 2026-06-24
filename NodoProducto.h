#pragma once

#include "Producto.h"

class NodoProducto {
public:
	Producto  producto;
	NodoProducto* siguiente;

public:
	NodoProducto() {}
	~NodoProducto () { }
};
