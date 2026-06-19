#pragma once


template <typename T>
class NodoPila {
public: 
    T dato;
    NodoPila<T>* siguiente;
};



template <typename T>
class Pila {
private:
    NodoPila<T>* tope;
    int tamano;

public:
    Pila() {
        tope = nullptr;
        tamano = 0;
    }

    ~Pila() {
        while (!estaVacia()) pop();
    }

    // Push: inserta en el tope
    void push(T dato) {
        NodoPila<T>* nuevo = new NodoPila<T>;
        nuevo->dato = dato;
        nuevo->siguiente = tope;
        tope = nuevo;
        tamano++;
    }

    // Pop: extrae del tope
    T pop() {
        if (estaVacia()) {
            cout << "[Pila] ERROR: la pila esta vacia." << endl;
            return T();
        }
        T dato = tope->dato;
        NodoPila<T>* temp = tope;
        tope = tope->siguiente;
        delete temp;
        tamano--;
        return dato;
    }

    // Peek: ve el tope sin extraer
    T peek() {
        if (estaVacia()) {
            cout << "[Pila] ERROR: la pila esta vacia." << endl;
            return T();
        }
        return tope->dato;
    }

    bool estaVacia() { return tope == nullptr; }
    int getTamano() { return tamano; }

    void mostrar() {
        NodoPila<T>* actual = tope;
        cout << "  [Tope] -> ";
        while (actual != nullptr) {
            cout << actual->dato;
            if (actual->siguiente) cout << " -> ";
            actual = actual->siguiente;
        }
        cout << " [Fondo]" << endl;
    }
};