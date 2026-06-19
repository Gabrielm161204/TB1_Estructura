#pragma once

#include "Pedido.h"
#include "iostream"

class NodoHistorial {
public:
    Pedido pedido;
    NodoHistorial* siguiente;
    NodoHistorial* anterior;   // <-- puntero al nodo anterior (lista doble)
};

// ============================================================
// Clase Historial: usa LISTA ENLAZADA DOBLE de Pedidos
// Permite recorrer hacia adelante Y hacia atras
// ============================================================
class Historial {
private:
    NodoHistorial* cabeza;   // Primer nodo
    NodoHistorial* cola;     // Ultimo nodo (caso especial de lista doble)

public:
    double totalGastado;
    int cantidadCompras;

    Historial() {
        cabeza = nullptr;
        cola = nullptr;
        totalGastado = 0.0;
        cantidadCompras = 0;
    }

    ~Historial() {
        NodoHistorial* actual = cabeza;
        while (actual != nullptr) {
            NodoHistorial* sig = actual->siguiente;
            delete actual;
            actual = sig;
        }
    }

    // Agrega un pedido al final de la lista doble
    void agregarPedido(Pedido p) {
        NodoHistorial* nuevo = new NodoHistorial;
        nuevo->pedido = p;
        nuevo->siguiente = nullptr;
        nuevo->anterior = nullptr;

        if (cabeza == nullptr) {
            // Caso especial: lista vacia (primer elemento)
            cabeza = nuevo;
            cola = nuevo;
        }
        else {
            // Insercion al final de la lista doble
            nuevo->anterior = cola;
            cola->siguiente = nuevo;
            cola = nuevo;
        }
        totalGastado += p.total;
        cantidadCompras++;
    }

    // Muestra el historial de adelante hacia atras
    void historialCompras() {
        if (cabeza == nullptr) {
            cout << "  No hay compras en el historial." << endl;
            return;
        }
        cout << "\n  ===== HISTORIAL DE COMPRAS (reciente a antiguo) =====" << endl;
        // Recorremos desde la COLA hacia la CABEZA (lista doble)
        NodoHistorial* actual = cola;
        while (actual != nullptr) {
            actual->pedido.mostrarResumen();
            cout << endl;
            actual = actual->anterior;
        }
        cout << "  Total gastado  : S/." << totalGastado << endl;
        cout << "  Total de pedidos: " << cantidadCompras << endl;
    }

    // RECURSIVIDAD: Calcula el total gastado de forma recursiva
    double calcularTotalRecursivo(NodoHistorial* nodo) {
        if (nodo == nullptr) return 0.0;   // Caso base
        return nodo->pedido.total + calcularTotalRecursivo(nodo->siguiente);  // Recursion
    }

    double getTotalRecursivo() {
        return calcularTotalRecursivo(cabeza);
    }

    NodoHistorial* getCabeza() { return cabeza; }
};