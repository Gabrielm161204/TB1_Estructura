#pragma once

#include "NodoProducto.h"
#include "Ordenamientos.h"
#include "HashTable.h"
        

class GestorInventario {
private:
    NodoProducto* cabeza;   // Primer nodo de la lista
    int cantidad;
	HashTable<Producto*> indicePorNombre; // Tabla hash para busqueda rapida por nombre

    // RECURSIVIDAD: busca un producto por nombre recorriendo la lista
    NodoProducto* buscarRecursivo(NodoProducto* nodo, string& nombre) {
        // Caso base: llegamos al final sin encontrar
        if (nodo == nullptr) {
            return nullptr;
        }
        // Caso base: encontramos el producto
        if (nodo->producto.nombre == nombre) {
            return nodo;
        }
        // Llamada recursiva al siguiente nodo
        return buscarRecursivo(nodo->siguiente, nombre);
    }

    // RECURSIVIDAD: muestra los productos recursivamente
    void mostrarRecursivo(NodoProducto* nodo, int num) {
        if (nodo == nullptr) return;   // Caso base
        cout << "  [" << num << "] ";
        nodo->producto.mostrarInfo();
        cout << endl;
        mostrarRecursivo(nodo->siguiente, num + 1);  // Llamada recursiva
    }

public:
    GestorInventario() : cabeza(nullptr), cantidad(0), indicePorNombre(211) {}

    ~GestorInventario() {
        NodoProducto* actual = cabeza;
        while (actual != nullptr) {
            NodoProducto* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }

    // Registrar un nuevo producto al inicio de la lista (caso especial: insercion al inicio)
    void registrarProducto() {
        string nom, cat;
        int st;
        double prec;

        cout << "  -- Registrar Producto --\n" << endl;
        cout << "  Nombre   : "; cin.ignore(); getline(cin, nom);
        cout << "  Categoria: "; getline(cin, cat);
        cout << "  Stock    : "; cin >> st;
        cout << "  Precio   : "; cin >> prec;

        Producto p(nom, st, cat, prec);

        NodoProducto* nuevo = new NodoProducto;
        nuevo->producto = p;
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        cantidad++;

        // índice hash: clave = nombre, valor = puntero al producto
        indicePorNombre.insertar(nom, &nuevo->producto);

        cout << "  [OK] Producto '" << nom << "' registrado." << endl;
    }

    // Registrar producto con datos directos (para precarga)
    void registrarProductoDirecto(Producto p) {
        NodoProducto* nuevo = new NodoProducto;
        nuevo->producto = p;
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        cantidad++;

        indicePorNombre.insertar(p.nombre, &nuevo->producto);
    }

    // Muestra todos los productos usando RECURSIVIDAD
    void mostrarProductosRegistrados() {
        if (cabeza == nullptr) {
            cout << "  No hay productos registrados." << endl;
            return;
        }
        cout << "  ===== INVENTARIO =====\n" << endl;
        mostrarRecursivo(cabeza, 1);
    }

    // Busca un producto por nombre (usa funcion recursiva interna)
    void buscarProducto() {
        string nombre;
        cout << "  Nombre a buscar: \n"; cin.ignore(); getline(cin, nombre);

        NodoProducto* resultado = buscarRecursivo(cabeza, nombre);
        if (resultado != nullptr) {
            cout << "  Producto encontrado: \n" << endl;
            resultado->producto.mostrarInfo();
        }
        else {
            cout << "  Producto '" << nombre << "' no encontrado." << endl;
        }
    }

    // Busca y retorna puntero (para uso interno de otras clases)
    Producto* buscarPorNombre(string& nombre) {
        /*NodoProducto* resultado = buscarRecursivo(cabeza, nombre);
        if (resultado) return &resultado->producto;
        return nullptr;*/
        
        Producto* ptr = nullptr;
        if (indicePorNombre.encontrado(nombre, ptr)) {
            return ptr; // encontrado en O(1) promedio
        }
        return nullptr; // no encontrado
        
    }

    // Actualizar stock de un producto
    void actualizarProducto() {
        string nombre;
        cout << "  Nombre del producto a actualizar: \n"; cin.ignore(); getline(cin, nombre);
        NodoProducto* nodo = buscarRecursivo(cabeza, nombre);
        if (nodo == nullptr) {
            cout << "  Producto no encontrado." << endl;
            return;
        }
        cout << "  Stock actual: " << nodo->producto.stock << endl;
        cout << "  Nuevo stock : "; cin >> nodo->producto.stock;
        nodo->producto.estado = (nodo->producto.stock > 0);
        cout << "  [OK] Stock actualizado." << endl;
    }

    // Eliminar producto (caso especial: eliminacion al inicio, medio y final)
    void eliminarProducto() {
        string nombre;
        cout << "\n  Nombre del producto a eliminar: "; cin.ignore(); getline(cin, nombre);

        // Caso especial: lista vacia
        if (cabeza == nullptr) {
            cout << "  No hay productos en el inventario." << endl;
            return;
        }

        // Caso especial: el producto esta al inicio (cabeza)
        if (cabeza->producto.nombre == nombre) {
            indicePorNombre.borrar(nombre);   // quitar del hash

            NodoProducto* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            cantidad--;
            cout << "  [OK] Producto eliminado." << endl;
            return;
        }

        // Buscar en el resto de la lista
        NodoProducto* anterior = cabeza;
        NodoProducto* actual = cabeza->siguiente;
        while (actual != nullptr) {
            if (actual->producto.nombre == nombre) {
                indicePorNombre.borrar(nombre);   // quitar del hash

                anterior->siguiente = actual->siguiente;
                delete actual;
                cantidad--;
                cout << "  [OK] Producto eliminado." << endl;
                return;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        cout << "  Producto no encontrado." << endl;
    }

    // Ordenar productos por precio usando Bubble Sort
    void ordenarPorPrecio() {
        if (cabeza == nullptr) return;
        // Recolectar precios en vector
        vector<double> precios;
        NodoProducto* actual = cabeza;
        while (actual) { precios.push_back(actual->producto.precio); actual = actual->siguiente; }

        bubbleSort(precios);

        // Mostrar resultado ordenado
        cout << "\n  Precios ordenados (Bubble Sort): ";
        for (double p : precios) cout << "S/." << p << " ";
        cout << endl;
    }

    // Ordenar por precio usando QuickSort y mostrar lista completa
    void ordenarQuickSort() {
        if (cabeza == nullptr) return;
        vector<double> precios;
        NodoProducto* actual = cabeza;
        while (actual) { precios.push_back(actual->producto.precio); actual = actual->siguiente; }

        quickSort(precios, 0, precios.size() - 1);

        cout << "\n  Precios ordenados (Quick Sort): ";
        for (double p : precios) cout << "S/." << p << " ";
        cout << endl;
    }

    // Retorna lista de punteros a productos disponibles
    vector<Producto*> getProductosDisponibles() {
        vector<Producto*> lista;
        NodoProducto* actual = cabeza;
        while (actual) {
            if (actual->producto.estaDisponible())
                lista.push_back(&actual->producto);
            actual = actual->siguiente;
        }
        return lista;
    }

    int getCantidad() { return cantidad; }
};