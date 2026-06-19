#pragma once

#include "Producto.h"


class DetallePedido {
public:
    Producto* producto;
    int cantidad;
    double precioUnitario;

    DetallePedido() : producto(nullptr), cantidad(0), precioUnitario(0.0) {}

    DetallePedido(Producto* prod, int cant)
        : producto(prod), cantidad(cant), precioUnitario(prod->precio) {
    }

    double getSubtotal() {
        return cantidad * precioUnitario;
    }

    void mostrar() {
        cout << "    - " << producto->nombre
            << " x" << cantidad
            << " @ S/." << precioUnitario
            << " => S/." << getSubtotal() << endl;
    }
};

