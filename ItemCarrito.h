#pragma once

#include "Producto.h"


class ItemCarrito {
public:
    Producto* producto;
    int cantidad;
    double precioUnitario;
	// constructor en caso no se proporcionen parametros
    ItemCarrito() : producto(nullptr), cantidad(0), precioUnitario(0.0) {}
    // constructor con parametros
    // se le pasa un punterio al prodcuto y la canidad que se desa comprar
    ItemCarrito(Producto* prod, int cant)
        : producto(prod), cantidad(cant), precioUnitario(prod->precio) {
    }

    double getSubtotal() {
        return cantidad * precioUnitario;
    }

    void setCantidad(int n) {
        cantidad = n;
    }

    void mostrar() {
        cout << "  " << producto->nombre
            << " | Cant: " << cantidad
            << " | Precio unit: S/." << precioUnitario
            << " | Subtotal: S/." << getSubtotal() << endl;
    }
};

