#pragma once

#include "Perfil.h"
#include "Carrito.h"
#include "Historial.h"
#include "Pedido.h"
#include "Pila.h"


class Cliente : public Perfil {
private:
    int contadorPedidos = 0;   // Para generar IDs de pedido

public:
    Carrito carrito;
    Historial historial;
    Pila<string> pilaAcciones;   // Pila de acciones realizadas (log/historial)

    Cliente() : Perfil() {

    }

    Cliente(string nom, string d, string fecha) : Perfil(nom, d, fecha), carrito(nom) {
        // ya inicializado por la lista; no hacer asignaciones redundantes
    }

    // Muestra los datos del cliente
    void mostrarDatos() {
        cout << "  ==== = DATOS DEL CLIENTE ==== = \n" << endl;
        mostrarPerfil();
        cout << "  Pedidos realizados: " << historial.cantidadCompras << endl;
        cout << "  Total gastado     : S/." << historial.totalGastado << endl;
    }

    // Agrega un producto al carrito
    void agregarCarrito(Producto* prod, int cantidad) {
        carrito.agregarProducto(prod, cantidad);
    }

    // Genera un pedido a partir del carrito actual
    Pedido generarPedido(string fecha) {
        contadorPedidos++;
        Pedido pedido(contadorPedidos, nombre, fecha);

        vector<ItemCarrito>& items = carrito.getItems();
        for (int i = 0; i < items.size(); i++) {
            pedido.agregarDetalle(items[i].producto, items[i].cantidad);
        }
        pedido.calcularTotal();

        // Descontar stock y vaciar carrito
        carrito.descontarStock();
        carrito.vaciar();

        // Agregar al historial
        historial.agregarPedido(pedido);

        return pedido;
    }
};