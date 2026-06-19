#pragma once

#include "GestorInventario.h"
#include "Categoria.h"
#include "Ordenamientos.h"
#include "Cola.h"


class Marketplace {
public:
    string nombre;
    GestorInventario* gestor;     // Puntero al inventario global
    vector<Categoria> categorias;
    Cola<int> colaPedidos;        // Cola de IDs de pedidos por procesar

    Marketplace() : nombre(""), gestor(nullptr) {}
    Marketplace(string nom, GestorInventario* g) : nombre(nom), gestor(g) {}

    // Registra una categoria
    void agregarCategoria(Categoria cat) {
        categorias.push_back(cat);
    }

    // Muestra todos los productos con Fisher-Yates (orden aleatorio)
    void mostrarMercado() {
        cout << "\n  ===== " << nombre << " =====" << endl;
        vector<Producto*> productos = gestor->getProductosDisponibles();
        if (productos.empty()) {
            cout << "  No hay productos disponibles." << endl;
            return;
        }

        // FISHER-YATES: mezcla los productos antes de mostrar
        fisherYates(productos);

        cout << "  Mostrando " << productos.size() << " productos (orden aleatorio):\n" << endl;
        for (int i = 0; i < productos.size(); i++) {
            cout << "  [" << i + 1 << "]" << endl;
            productos[i]->mostrarInfo();
            cout << endl;
        }
    }

    // Muestra productos filtrados por categoria usando LAMBDA
    void mostrarPorCategoria(string& catBuscada) {
        vector<Producto*> todos = gestor->getProductosDisponibles();

        // LAMBDA: filtra productos cuya categoria coincida
        auto esDeLaCategoria = [&catBuscada](Producto* p) {
            return p->categoria == catBuscada;
            };

        cout << " === Productos de categoria: " << endl << catBuscada << " ===" << endl;
        bool encontro = false;
        for (int i = 0; i < todos.size(); i++) {
            if (esDeLaCategoria(todos[i])) {
                todos[i]->mostrarInfo();
                cout << endl;
                encontro = true;
            }
        }
        if (!encontro) cout << "  No hay productos en esa categoria." << endl;
    }

    // Muestra las categorias disponibles
    void mostrarCategorias() {
        cout << "\n  === Categorias ===" << endl;
        for (int i = 0; i < categorias.size(); i++) {
            categorias[i].mostrar();
        }
    }

    // Muestra productos ordenados por precio (usa Insertion Sort + Lambda de comparacion)
    void mostrarOrdenadosPorPrecio() {
        vector<Producto*> productos = gestor->getProductosDisponibles();
        if (productos.empty()) { cout << "  Sin productos." << endl; return; }

        // Insertion Sort sobre punteros usando precio
        int n = productos.size();
        for (int i = 1; i < n; i++) {
            Producto* key = productos[i];
            int j = i - 1;
            while (j >= 0 && productos[j]->precio > key->precio) {
                productos[j + 1] = productos[j];
                j--;
            }
            productos[j + 1] = key;
        }

        cout << "\n  === Productos ordenados por precio (menor a mayor) ===" << endl;
        for (int i = 0; i < productos.size(); i++) {
            cout << "  [" << i + 1 << "] " << productos[i]->nombre
                << " - S/." << productos[i]->precio << endl;
        }
    }
};