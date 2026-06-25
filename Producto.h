
#pragma once
using namespace System;

/**
 * @class Producto
 * @brief Representa un producto disponible en el marketplace.
 *
 * Contiene la información básica de un producto: nombre, stock,
 * categoría, precio y estado de disponibilidad. Provee métodos
 * para consultar su disponibilidad y mostrar su información.
 */
class Producto {
public:
    /// Nombre del producto.
    string nombre;

    /// Cantidad de unidades disponibles en inventario.
    int stock;

    /// Categoría a la que pertenece el producto.
    string categoria;

    /// Precio unitario del producto en soles (S/.).
    double precio;

    /// Estado del producto: true = disponible, false = no disponible.
    bool estado;

    /**
     * @brief Constructor por defecto.
     *
     * Inicializa el producto con valores vacíos/cero y estado disponible.
     */
    Producto() : nombre(""), stock(0), categoria(""), precio(0.0), estado(true) {}

    /**
     * @brief Constructor con parámetros.
     *
     * @param nom   Nombre del producto.
     * @param st    Stock inicial del producto.
     * @param cat   Categoría del producto.
     * @param prec  Precio unitario del producto.
     * @param est   Estado del producto (true por defecto = disponible).
     */
    Producto(string nom, int st, string cat, double prec, bool est = true)
        : nombre(nom), stock(st), categoria(cat), precio(prec), estado(est) {
    }

    /**
     * @brief Muestra en consola la información completa del producto.
     *
     * Imprime nombre, stock, categoría, precio y estado (Disponible/Agotado).
     * El producto se considera agotado si el estado es false o el stock es 0.
     */
    void mostrarInfo() {
        cout << "Nombre   : " << nombre << endl;
        cout << "Stock    : " << stock << " und." << endl;
        cout << "Categoria: " << categoria << endl;
        cout << "Precio   : S/. " << precio << endl;
        cout << "Estado   : " << (estado && stock > 0 ? "Disponible" : "Agotado") << endl;
    }

    /**
     * @brief Verifica si el producto puede ser vendido.
     *
     * Un producto está disponible solo si su estado es true
     * y su stock es mayor a cero.
     *
     * @return true si el producto está disponible para la venta, false en caso contrario.
     */
    bool estaDisponible() {
        return estado && stock > 0;
    }
};
