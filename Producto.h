#pragma once
using namespace System;


class Producto {
public:
    string nombre;
    int stock;
    string categoria;
    double precio;
    bool estado;   // true = disponible, false = no disponible

    // Constructor por defecto
    Producto() : nombre(""), stock(0), categoria(""), precio(0.0), estado(true) {}

    // Constructor con parametros
    Producto(string nom, int st, string cat, double prec, bool est = true)
        : nombre(nom), stock(st), categoria(cat), precio(prec), estado(est) {
    }

   
    void mostrarInfo() {
        cout << "Nombre   : " << nombre<<endl;
        cout << "Stock    : " << stock << " und." << endl;
        cout << "Categoria: " << categoria << endl;
        cout << "Precio   : S/. " << precio << endl;
        cout << "Estado   : " << (estado && stock > 0 ? "Disponible" : "Agotado") << endl;
    }

    // Verifica si el producto se puede vender
    bool estaDisponible() {
        return estado && stock > 0;
    }
};