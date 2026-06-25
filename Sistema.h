#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "Ordenamientos.h"
#include "Producto.h"
#include "NodoProducto.h"
#include "GestorInventario.h"
#include "Categoria.h"

#include "Pedido.h"
#include "Historial.h"
#include "Carrito.h"
#include "MetodoPago.h"
#include "Perfil.h"
#include "Cliente.h"
#include "Marketplace.h"
#include "Pila.h"
#include "Cola.h"
#include "GeneradorData.h"
class Sistema {
private:
	GeneradorData generador;
    GestorInventario inventario;
    Marketplace market;
    Cliente clienteActual;
    // Nota: la Cola de pedidos ahora vive dentro de Marketplace (market.colaPedidos)
    // Nota: la Pila de acciones ahora vive dentro de Cliente (clienteActual.pilaAcciones)
    bool clienteRegistrado = false;
    int contadorPedidosGlobal = 0;

    // ================================================================
    // Funcion para obtener fecha actual simulada
    // ================================================================
    string getFecha() {
        return "2026-05-09";   // Fecha fija para demostracion
    }
    void cuentaRegresiva(int n) {
        if (n == 0) {          // Caso base
            cout << "  Go!" << endl;
            return;
        }
        cout << "  " << n << "..." << endl;
        cuentaRegresiva(n - 1);   // Llamada recursiva
    }
public:
	Sistema() {

	}

	~Sistema() {
	}
	void iniciar() {
		// Inicializar sistema con datos de ejemplo
		market = Marketplace("MercadoTech Peru", &inventario);
		generador.CargarDatosEjemplo(inventario, market);
		clienteActual.pilaAcciones.push("Sistema iniciado");

        int op;
        cout << "================================================" << endl;
        cout << " SISTEMA DE MARKETPLACE - ESTRUCTURA DE DATOS" << endl;
        cout << "================================================\n" << endl;

        do {
            cout << "=============================" << endl;
            cout << "       MENU PRINCIPAL" << endl;
            cout << "=============================" << endl;
            if (clienteRegistrado)
                cout << "Usuario: " << clienteActual.nombre << endl;
            cout << "1. Gestion de Inventario (Admin)" << endl;
            cout << "2. Marketplace (Comprador)" << endl;
            cout << "3. Registrar / Ver mi perfil" << endl;
            cout << "4. Carrito de compras" << endl;
            cout << "5. Gestion de Pedidos" << endl;
            //cout << "6. Demo de Algoritmos" << endl;
            cout << "0. Salir" << endl;
            cout << "Opcion: "; cin >> op;

            switch (op) {
            case 1: menuInventario();    break;
            case 2: menuMarketplace();   break;
            case 3:
                if (!clienteRegistrado) registrarCliente();
                else clienteActual.mostrarDatos();
                break;
            case 4: menuCarrito();       break;
            case 5: menuPedidos();       break;
            case 6: //menuDemostraciones(); 
                break;
            case 0:
                cout << "Hasta luego!\n" << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
            }
        } while (op != 0);
	}

    // ================================================================
// MENU: Gestion de Inventario (Administrador)
// ================================================================
    void menuInventario() {
        int op;
        do {
            cout << "=============================" << endl;
            cout << "  GESTION DE INVENTARIO" << endl;
            cout << "=============================" << endl;
            cout << "1. Registrar producto" << endl;
			cout << "2. Generar n productos" << endl;
            cout << "3. Mostrar productos (recursivo)" << endl;
            cout << "4. Buscar producto (tabla hash)" << endl;
            cout << "5. Actualizar stock" << endl;
            cout << "6. Eliminar producto" << endl;
            cout << "7. Ordenar por precio (Bubble Sort)" << endl;
            cout << "8. Ordenar por precio (Quick Sort)" << endl;
            cout << "0. Volver" << endl;
            cout << "Opcion: "; cin >> op;

            switch (op) {
            case 1:
                
                inventario.registrarProducto();
                clienteActual.pilaAcciones.push("Registro de producto");
                break;
            case 2: {
                int n;
                cout << "  Cantidad de productos a generar: "; cin >> n;
                generador.CargarCantidadProductos(inventario, n);
                clienteActual.pilaAcciones.push("Generacion de " + to_string(n) + " productos");
				cout << "se generaron los " << n << " productos correctamente" << endl;
                break;
			}
            case 3:
                inventario.mostrarProductosRegistrados();
                break;
            case 4:
                inventario.buscarProducto();
                break;
            case 5:
                inventario.actualizarProducto();
                clienteActual.pilaAcciones.push("Actualizacion de stock");
                break;
            case 6:
                inventario.eliminarProducto();
                clienteActual.pilaAcciones.push("Eliminacion de producto");
                break;
            case 7:
                inventario.ordenarPorPrecio();
                break;
            case 8:
                inventario.ordenarQuickSort();
                break;
            case 0: break;
            default: cout << "  Opcion invalida." << endl;
            }
        } while (op != 0);
    }

    // ================================================================
    // MENU: Marketplace (Tienda)
    // ================================================================
    void menuMarketplace() {
        int op;
        do {
            cout << "=============================" << endl;
            cout << "    MARKETPLACE: " << market.nombre << endl;
            cout << "=============================" << endl;
            cout << "1. Ver todos los productos (aleatorio Fisher-Yates)" << endl;
            cout << "2. Ver por categoria (lambda)" << endl;
            cout << "3. Ver productos ordenados por precio" << endl;
            cout << "4. Ver categorias disponibles" << endl;
            cout << "0. Volver" << endl;
            cout << "Opcion: "; cin >> op;

            switch (op) {
            case 1:
                market.mostrarMercado();
                break;
            case 2: {
                string cat;
                market.mostrarCategorias();
                cout << "  Ingrese categoria: "; cin.ignore(); getline(cin, cat);
                market.mostrarPorCategoria(cat);
                break;
            }
            case 3:
                market.mostrarOrdenadosPorPrecio();
                break;
            case 4:
                market.mostrarCategorias();
                break;
            case 0: break;
            default: cout << "  Opcion invalida." << endl;
            }
        } while (op != 0);
    }

    // ================================================================
    // Registrar cliente
    // ================================================================
    void registrarCliente() {
        string nom, dni;
        cout << "=== Registro de Cliente ===\n" << endl;
        cout << "Nombre : "; cin >> nom;
        cout << "DNI   : "; cin >> dni;
        clienteActual = Cliente(nom, dni, getFecha());
        clienteRegistrado = true;
        cout << "  [OK] Bienvenido, " << nom << "!" << endl;
    }

    // ================================================================
    // MENU: Carrito de Compras
    // ================================================================
    void menuCarrito() {
        if (!clienteRegistrado) {
            cout << "  [!] Debe registrarse primero.\n" << endl;
            registrarCliente();
        }

        int op;
        do {
            cout << "=============================\n" << endl;
            cout << "  CARRITO DE COMPRAS" << endl;
            cout << "=============================" << endl;
            cout << "1. Ver productos disponibles" << endl;
            cout << "2. Agregar producto al carrito" << endl;
            cout << "3. Ver mi carrito" << endl;
            cout << "4. Confirmar pedido" << endl;
            cout << "0. Volver" << endl;
            cout << "Opcion: "; cin >> op;

            switch (op) {
            case 1:
                market.mostrarMercado();
                break;
            case 2: {
                string nombre;
                int cant;
                cout << "Nombre del producto: "; cin.ignore(); getline(cin, nombre);
                cout << "Cantidad           : "; cin >> cant;
                Producto* p = inventario.buscarPorNombre(nombre);
                if (p) {
                    clienteActual.agregarCarrito(p, cant);
                    clienteActual.pilaAcciones.push("Agregar al carrito: " + nombre);
                }
                else {
                    cout << "[!] Producto no encontrado." << endl;
                }
                break;
            }
            case 3:
                clienteActual.carrito.mostrarCarrito();
                break;
            case 4: {
                if (clienteActual.carrito.estaVacio()) {
                    cout << "[!] El carrito esta vacio." << endl;
                    break;
                }
                if (!clienteActual.carrito.validarStock()) break;

                // Seleccionar metodo de pago
                cout << "Metodo de pago:\n" << endl;
                cout << "1. Efectivo  2. Tarjeta  3. Yape" << endl;
                cout << "Opcion: "; int mOp; cin >> mOp;
                string tipo = (mOp == 1 ? "Efectivo" : mOp == 2 ? "Tarjeta" : "Yape");

                MetodoPago pago(1, tipo, clienteActual.carrito.getTotal(), getFecha());
                if (pago.procesarPago(clienteActual.carrito.getTotal())) {
                    Pedido nuevoPedido = clienteActual.generarPedido(getFecha());
                    nuevoPedido.cambiarEstado("En proceso");
                    contadorPedidosGlobal++;
                    market.colaPedidos.encolar(nuevoPedido.id);  // Encola el pedido
                    clienteActual.pilaAcciones.push("Pedido #" + to_string(nuevoPedido.id) + " generado");
                    cout << "Pedido generado exitosamente!\n" << endl;
                    nuevoPedido.mostrarResumen();
                }
                break;
            }
            case 0: break;
            default: cout << "  Opcion invalida." << endl;
            }
        } while (op != 0);
    }

    // ================================================================
    // MENU: Pedidos (Cola de pedidos)
    // ================================================================
    void menuPedidos() {
        int op;
        do {
            cout << "=============================\n" << endl;
            cout << "  GESTION DE PEDIDOS" << endl;
            cout << "=============================" << endl;
            cout << "Pedidos en cola: " << market.colaPedidos.getTamano() << endl;
            cout << "1. Ver cola de pedidos" << endl;
            cout << "2. Procesar siguiente pedido (desencolar)" << endl;
            cout << "3. Ver historial del cliente" << endl;
            cout << "0. Volver" << endl;
            cout << "Opcion: "; cin >> op;

            switch (op) {
            case 1:
                if (market.colaPedidos.estaVacia()) {
                    cout << "No hay pedidos en cola." << endl;
                }
                else {
                    cout << "Pedido en el frente: #" << market.colaPedidos.verFrente() << endl;
                    cout << "Total en cola: " << market.colaPedidos.getTamano() << endl;
                }
                break;
            case 2:
                if (!market.colaPedidos.estaVacia()) {
                    int id = market.colaPedidos.desencolar();
                    cout << "[OK] Pedido #" << id << " procesado y entregado." << endl;
                    clienteActual.pilaAcciones.push("Pedido #" + to_string(id) + " entregado");
                }
                else {
                    cout << "No hay pedidos en cola." << endl;
                }
                break;
            case 3:
                if (clienteRegistrado) {
                    clienteActual.historial.historialCompras();
                    double totalRec = clienteActual.historial.getTotalRecursivo();
                    cout << "Total calculado recursivamente: S/." << totalRec << endl;
                }
                else {
                    cout << "No hay cliente registrado." << endl;
                }
                break;
            case 0: break;
            default: cout << "Opcion invalida." << endl;
            }
        } while (op != 0);
    }

    // ================================================================
    // MENU: Demostraciones de algoritmos
    // ================================================================
    void menuDemostraciones() {
        int op;
        do {
            cout << "=============================\n" << endl;
            cout << "  DEMO DE ALGORITMOS" << endl;
            cout << "=============================" << endl;
            cout << "1. Demo Recursividad (cuenta regresiva)" << endl;
            cout << "2. Demo Bubble Sort" << endl;
            cout << "3. Demo Selection Sort" << endl;
            cout << "4. Demo Insertion Sort" << endl;
            cout << "5. Demo Quick Sort (recursivo)" << endl;
            cout << "6. Demo Fisher-Yates" << endl;
            cout << "7. Demo Pila (acciones realizadas)" << endl;
            cout << "0. Volver" << endl;
            cout << "Opcion: "; cin >> op;

            vector<double> nums = { 45.0, 12.0, 78.0, 23.0, 56.0, 9.0, 34.0 };

            switch (op) {
            case 1:
                cout << "Cuenta regresiva recursiva:\n" << endl;
                cuentaRegresiva(5);
                break;
            case 2: {
                vector<double> v = nums;
                mostrarVector(v, "Antes");
                bubbleSort(v);
                mostrarVector(v, "Despues (Bubble Sort)");
                break;
            }
            case 3: {
                vector<double> v = nums;
                mostrarVector(v, "Antes");
                selectionSort(v);
                mostrarVector(v, "Despues (Selection Sort)");
                break;
            }
            case 4: {
                vector<double> v = nums;
                mostrarVector(v, "Antes");
                insertionSort(v);
                mostrarVector(v, "Despues (Insertion Sort)");
                break;
            }
            case 5: {
                vector<double> v = nums;
                mostrarVector(v, "Antes");
                quickSort(v, 0, (int)v.size() - 1);
                mostrarVector(v, "Despues (Quick Sort)");
                break;
            }
            case 6: {
                vector<double> v = nums;
                mostrarVector(v, "Antes");
                fisherYates(v);
                mostrarVector(v, "Despues (Fisher-Yates)");
                break;
            }
            case 7:
                cout << "Pila de acciones realizadas:\n" << endl;
                clienteActual.pilaAcciones.mostrar();
                break;
            case 0: break;
            default: cout << "Opcion invalida." << endl;
            }
        } while (op != 0);
    }
	
};
