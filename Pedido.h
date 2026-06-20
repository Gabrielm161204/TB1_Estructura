#pragma once

#include "ItemPedido.h"

// Forward declaration para evitar inclusion circular
//class Cliente;


class Pedido {
public:
    int id;
    string nombreCliente;       // Guardamos nombre en lugar de puntero para simplificar
    vector<ItemPedido> detalles;
    double total;
    string estado;              // "Pendiente", "En proceso", "Entregado", "Cancelado"
    string fechaHora;

    Pedido() : id(0), nombreCliente(""), total(0.0), estado("Pendiente"), fechaHora("") {}

    Pedido(int i, string cliente, string fecha)
        : id(i), nombreCliente(cliente), total(0.0), estado("Pendiente"), fechaHora(fecha) {
    }

    // Agrega un detalle al pedido
    void agregarDetalle(Producto* prod, int cant) {
        ItemPedido det(prod, cant);
        detalles.push_back(det);
    }

    // Calcula el total sumando todos los subtotales
    double calcularTotal() {
        total = 0.0;
        for (int i = 0; i < detalles.size(); i++) {
            total += detalles[i].getSubtotal();
        }
        return total;
    }

    // Muestra el resumen del pedido
    void mostrarResumen() {
        cout << "  ===== PEDIDO #" << id << " =====" << endl;
        cout << "  Cliente  : " << nombreCliente << endl;
        cout << "  Fecha    : " << fechaHora << endl;
        cout << "  Estado   : " << estado << endl;
        cout << "  Detalles :" << endl;
        for (int i = 0; i < detalles.size(); i++) {
            detalles[i].mostrar();
        }
        cout << "  Total    : S/." << total << endl;
    }

    // Cambia el estado del pedido
    void cambiarEstado(string nuevoEstado) {
        estado = nuevoEstado;
        cout << "  [OK] Pedido #" << id << " -> Estado: " << estado << endl;
    }

    string getEstado() { return estado; }

    // Para poder imprimir con cola (operator<<)
    void mostrar() { mostrarResumen(); }
};

