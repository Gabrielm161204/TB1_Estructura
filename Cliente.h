#pragma once

#include "Perfil.h"
#include "Carrito.h"
#include "Historial.h"
#include "Pedido.h"
#include "Pila.h"

/*
 Clase: Cliente
 Representa a un cliente registrado en el marketplace.
 Hereda de Perfil y agrega funcionalidad de carrito de compras,
 historial de pedidos y una pila de acciones realizadas.
*/
class Cliente : public Perfil {
private:
    int contadorPedidos = 0;   // Contador interno para generar IDs de pedido unicos

public:
    Carrito carrito;                 // Carrito de compras del cliente
    Historial historial;             // Historial de pedidos realizados
    Pila<string> pilaAcciones;       // Pila de acciones realizadas (log de actividad)

    /*
     Constructor por defecto.
     Inicializa el cliente con los valores por defecto de Perfil.
    */
    Cliente() : Perfil() {
    }

    /*
     Constructor con parametros.
     Recibe nombre, DNI y fecha de registro del cliente.
     Inicializa el carrito con el nombre del cliente.
    */
    Cliente(string nom, string d, string fecha) : Perfil(nom, d, fecha), carrito(nom) {
    }

    /*
     Muestra en consola los datos completos del cliente.
     Incluye datos del perfil, cantidad de pedidos y total gastado.
    */
    void mostrarDatos() {
        cout << "  ===== DATOS DEL CLIENTE =====\n" << endl;
        mostrarPerfil();
        cout << "  Pedidos realizados: " << historial.cantidadCompras << endl;
        cout << "  Total gastado     : S/." << historial.totalGastado << endl;
    }

    /*
     Agrega un producto al carrito del cliente con la cantidad indicada.
     Delega la operacion al metodo agregarProducto del carrito.
    */
    void agregarCarrito(Producto* prod, int cantidad) {
        carrito.agregarProducto(prod, cantidad);
    }

    /*
     Genera un pedido a partir del contenido actual del carrito.
     Crea un nuevo Pedido, le agrega los items del carrito,
     calcula el total, descuenta el stock, vacia el carrito
     y registra el pedido en el historial.
     Retorna el pedido generado.
    */
    Pedido generarPedido(string fecha) {
        contadorPedidos++;
        Pedido pedido(contadorPedidos, nombre, fecha);

        vector<ItemPedido>& items = carrito.getItems();
        for (int i = 0; i < items.size(); i++) {
            pedido.agregarDetalle(items[i].producto, items[i].cantidad);
        }
        pedido.calcularTotal();

        carrito.descontarStock();
        carrito.vaciar();

        historial.agregarPedido(pedido);

        return pedido;
    }
};
