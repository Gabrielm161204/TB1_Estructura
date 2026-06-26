#pragma once

#include "NodoProducto.h"
#include "Ordenamientos.h"
#include "HashTable.h"

/*
 Clase: GestorInventario
 Administra el inventario de productos usando una lista enlazada simple.
 Permite registrar, buscar, actualizar y eliminar productos.
 Usa recursividad para buscar y mostrar, y una tabla hash para
 busquedas rapidas por nombre en tiempo O(1) promedio.
*/
class GestorInventario {
private:
    NodoProducto* cabeza;                       // Primer nodo de la lista enlazada
    int cantidad;                               // Total de productos registrados
    HashTable<Producto*> indicePorNombre;        // Indice hash para busqueda rapida por nombre
    Ordenamientos ordenamientos;                 // Instancia de la clase de algoritmos de ordenamiento
    /*
     Busca un producto por nombre recorriendo la lista de forma recursiva.
     Caso base: llega al final (nullptr) o encuentra el producto.
     Retorna el nodo encontrado o nullptr si no existe.
    */
    NodoProducto* buscarRecursivo(NodoProducto* nodo, string& nombre) {
        if (nodo == nullptr) return nullptr;
        if (nodo->producto.nombre == nombre) return nodo;
        return buscarRecursivo(nodo->siguiente, nombre);
    }

    /*
     Muestra todos los productos de forma recursiva a partir de un nodo.
     Caso base: nodo es nullptr (fin de la lista).
     Cada llamada imprime el producto actual y avanza al siguiente.
    */
    void mostrarRecursivo(NodoProducto* nodo, int num) {
        if (nodo == nullptr) return;
        cout << "[" << num << "]";
        nodo->producto.mostrarInfo();
        mostrarRecursivo(nodo->siguiente, num + 1);
    }

public:
    GestorInventario() : cabeza(nullptr), cantidad(0), indicePorNombre(211) {}

    /*
     Destructor.
     Libera la memoria de todos los nodos de la lista enlazada.
    */
    ~GestorInventario() {
        NodoProducto* actual = cabeza;
        while (actual != nullptr) {
            NodoProducto* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }

    /*
     Registra un nuevo producto solicitando datos por consola.
     El producto se inserta al inicio de la lista (caso especial).
     Tambien lo agrega al indice hash para busquedas rapidas.
    */
    void registrarProducto() {
        string nom, cat;
        int st;
        double prec;

        cout << " -- Registrar Producto --\n" << endl;
        cout << " Nombre : "; cin.ignore(); getline(cin, nom);
        cout << " Categoria: "; getline(cin, cat);
        cout << " Stock : "; cin >> st;
        cout << " Precio : "; cin >> prec;

        Producto p(nom, st, cat, prec);

        NodoProducto* nuevo = new NodoProducto;
        nuevo->producto = p;
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        cantidad++;

        indicePorNombre.insertar(nom, &nuevo->producto);

        cout << " [OK] Producto '" << nom << "' registrado." << endl;
    }

    /*
     Registra un producto directamente con datos ya construidos.
     Utilizado para precarga de datos sin interaccion del usuario.
     Inserta al inicio de la lista y lo agrega al indice hash.
    */
    void registrarProductoDirecto(Producto p) {
        NodoProducto* nuevo = new NodoProducto;
        nuevo->producto = p;
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        cantidad++;
        indicePorNombre.insertar(p.nombre, &nuevo->producto);
    }

    /*
     Muestra todos los productos del inventario usando recursividad.
     Si no hay productos, muestra un mensaje informativo.
    */
    void mostrarProductosRegistrados() {
        if (cabeza == nullptr) {
            cout << " No hay productos registrados." << endl;
            return;
        }
        cout << " ===== INVENTARIO =====" << endl;
        mostrarRecursivo(cabeza, 1);
    }

    /*
     Solicita un nombre por consola y busca el producto en la lista.
     Usa la funcion recursiva interna para recorrer la lista.
     Muestra la informacion del producto si es encontrado.
    */
    void buscarProducto() {
        string nombre;
        cout << " Nombre a buscar: \n"; cin.ignore(); getline(cin, nombre);

        NodoProducto* resultado = buscarRecursivo(cabeza, nombre);
        if (resultado != nullptr) {
            cout << " Producto encontrado: \n" << endl;
            resultado->producto.mostrarInfo();
        }
        else {
            cout << " Producto '" << nombre << "' no encontrado." << endl;
        }
    }

    /*
     Busca un producto por nombre usando la tabla hash.
     Retorna un puntero al producto si es encontrado en O(1) promedio.
     Retorna nullptr si el producto no existe.
    */
    Producto* buscarPorNombre(string& nombre) {
        Producto* ptr = nullptr;
        if (indicePorNombre.encontrado(nombre, ptr)) {
            return ptr;
        }
        return nullptr;
    }

    /*
     Permite actualizar el stock de un producto existente.
     Busca el producto por nombre y solicita el nuevo valor de stock.
     Actualiza el estado del producto segun si el nuevo stock es mayor a cero.
    */
    void actualizarProducto() {
        string nombre;
        cout << " Nombre del producto a actualizar: \n"; cin.ignore(); getline(cin, nombre);
        NodoProducto* nodo = buscarRecursivo(cabeza, nombre);
        if (nodo == nullptr) {
            cout << " Producto no encontrado." << endl;
            return;
        }
        cout << " Stock actual: " << nodo->producto.stock << endl;
        cout << " Nuevo stock : "; cin >> nodo->producto.stock;
        nodo->producto.estado = (nodo->producto.stock > 0);
        cout << " [OK] Stock actualizado." << endl;
    }

    /*
     Elimina un producto del inventario por nombre.
     Maneja tres casos especiales: lista vacia, eliminacion al inicio (cabeza)
     y eliminacion en el medio o al final de la lista.
     Tambien elimina la entrada correspondiente del indice hash.
    */
    void eliminarProducto() {
        string nombre;
        cout << "\n Nombre del producto a eliminar: "; cin.ignore(); getline(cin, nombre);

        if (cabeza == nullptr) {
            cout << " No hay productos en el inventario." << endl;
            return;
        }

        // Caso especial: el producto esta al inicio (cabeza)
        if (cabeza->producto.nombre == nombre) {
            indicePorNombre.borrar(nombre);
            NodoProducto* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            cantidad--;
            cout << " [OK] Producto eliminado." << endl;
            return;
        }

        // Buscar en el resto de la lista
        NodoProducto* anterior = cabeza;
        NodoProducto* actual = cabeza->siguiente;
        while (actual != nullptr) {
            if (actual->producto.nombre == nombre) {
                indicePorNombre.borrar(nombre);
                anterior->siguiente = actual->siguiente;
                delete actual;
                cantidad--;
                cout << " [OK] Producto eliminado." << endl;
                return;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        cout << " Producto no encontrado." << endl;
    }

    /*
     Ordena los precios del inventario usando Bubble Sort y los muestra.
     Extrae los precios en un vector, aplica el algoritmo y los imprime en consola.
    */
    void ordenarPorPrecio() {
        if (cabeza == nullptr) return;
        vector<double> precios;
        NodoProducto* actual = cabeza;
        while (actual) { precios.push_back(actual->producto.precio); actual = actual->siguiente; }
        ordenamientos.bubbleSort(precios);
        cout << "\n Precios ordenados (Bubble Sort): ";
        for (double p : precios) cout << "S/." << p << " ";
        cout << endl;
    }

    /*
     Ordena los precios del inventario usando Quick Sort y los muestra.
     Extrae los precios en un vector, aplica el algoritmo recursivo y los imprime.
    */
    void ordenarQuickSort() {
        if (cabeza == nullptr) return;
        vector<double> precios;
        NodoProducto* actual = cabeza;
        while (actual) { precios.push_back(actual->producto.precio); actual = actual->siguiente; }
        ordenamientos.quickSort(precios, 0, precios.size() - 1);
        cout << "\n Precios ordenados (Quick Sort): ";
        for (double p : precios) cout << "S/." << p << " ";
        cout << endl;
    }

    /*
     Retorna un vector con punteros a todos los productos disponibles.
     Un producto esta disponible si su estado es true y su stock es mayor a cero.
    */
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

    // Retorna la cantidad total de productos registrados en el inventario
    int getCantidad() { return cantidad; }
};
