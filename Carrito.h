#pragma once

#include "ItemPedido.h"

class Carrito {
private:
    string nombreCliente;
    vector<ItemPedido> items;
    double total;

public:
    Carrito() {
		nombreCliente = "";
		total = 0.0;
    }
    Carrito(string cliente) {
		nombreCliente = cliente;
		total = 0.0;
    }

    // Agrega un producto al carrito
    void agregarProducto(Producto* prod, int cantidad) {
        if (!prod->estaDisponible()) {
            cout << "  [!] El producto '" << prod->nombre << "' no esta disponible." << endl;
            return;
        }
        if (cantidad > prod->stock) {
            cout << "  [!] Stock insuficiente. Disponible: " << prod->stock << endl;
            return;
        }
        // Verificar si ya existe en el carrito
        for (int i = 0; i < (int)items.size(); i++) {
            if (items[i].producto->nombre == prod->nombre) {
                items[i].setCantidad(items[i].cantidad + cantidad);
                cout << "  [OK] Cantidad actualizada para '" << prod->nombre << "'." << endl;
                calcularTotal();
                return;
            }
        }
        ItemPedido item(prod, cantidad);
        items.push_back(item);
        calcularTotal();
        cout << "  [OK] '" << prod->nombre << "' agregado al carrito." << endl;
    }

    // Muestra el contenido del carrito
    void mostrarCarrito() {
        if (items.empty()) {
            cout << "  El carrito esta vacio." << endl;
            return;
        }
        cout << "  ===== CARRITO DE " << nombreCliente << " =====" << endl<<endl;
        for (int i = 0; i < items.size(); i++) {
            cout << "  [" << i + 1 << "] ";
            items[i].mostrar();
        }
        cout << "  --------------------------------" << endl;
        cout << "  TOTAL: S/." << total << endl;
    }

    // Calcula el total usando LAMBDA
    void calcularTotal() {
        // Lambda: funcion anonima que acumula subtotales
        auto sumarSubtotales = [&]() {
            double suma = 0.0;
            for (int i = 0; i < items.size(); i++) { 
                suma += items[i].getSubtotal();
            }
            return suma;
            };
        total = sumarSubtotales();
    }

    // Valida que todos los items tengan stock suficiente
    bool validarStock() {
        // LAMBDA: verifica si algun item supera el stock disponible
        auto tieneStockSuficiente = []( ItemCarrito& item) {
            return item.cantidad <= item.producto->stock;
            };

        for (int i = 0; i < items.size(); i++) {
            if (!tieneStockSuficiente(items[i])) {
                cout << "  [!] Stock insuficiente para: " << items[i].producto->nombre << endl;
                return false;
            }
        }
        return true;
    }

    // Descuenta el stock al confirmar compra
    void descontarStock() {
        for (int i = 0; i < items.size(); i++) {
            items[i].producto->stock -= items[i].cantidad;
            if (items[i].producto->stock == 0)
                items[i].producto->estado = false;
        }
    }

    void vaciar() { items.clear(); total = 0.0; }

    bool estaVacio() { return items.empty(); }
    double getTotal() { return total; }
    vector<ItemCarrito>& getItems() { return items; }
    string getNombreCliente() { return nombreCliente; }
};

