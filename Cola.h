#pragma once


template <typename T>
class NodoCola {
public:
    T dato;
	NodoCola<T>* siguiente;
public:
};



template <typename T>
class Cola {
private:
    NodoCola<T>* frente;   // Se extrae por aqui
    NodoCola<T>* fin;      // Se inserta por aqui
    int tamano;

public:
    Cola() {
        frente = nullptr;
        fin = nullptr;
        tamano = 0;
    }

    ~Cola() {
        while (!estaVacia()) desencolar();
    }

    // Encolar: inserta al final
    void encolar(T dato) {
        NodoCola<T>* nuevo = new NodoCola<T>;
        nuevo->dato = dato;
        nuevo->siguiente = nullptr;

        if (fin == nullptr) {
            frente = nuevo;
            fin = nuevo;
        }
        else {
            fin->siguiente = nuevo;
            fin = nuevo;
        }
        tamano++;
    }

    // Desencolar: extrae del frente
    T desencolar() {
        if (estaVacia()) {
            cout << "[Cola] ERROR: la cola esta vacia." << endl;
            return T();
        }
        T dato = frente->dato;
        NodoCola<T>* temp = frente;
        frente = frente->siguiente;
        if (frente == nullptr) fin = nullptr;
        delete temp;
        tamano--;
        return dato;
    }

    // Ver el frente sin extraer
    T verFrente() {
        if (estaVacia()) {
            cout << "[Cola] ERROR: la cola esta vacia." << endl;
            return T();
        }
        return frente->dato;
    }

    bool estaVacia() { return frente == nullptr; }
    int getTamano() { return tamano; }

    void mostrar() {
        NodoCola<T>* actual = frente;
        cout << "  [Frente] -> ";
        while (actual != nullptr) {
            cout << actual->dato;
            if (actual->siguiente) cout << " -> ";
            actual = actual->siguiente;
        }
        cout << " [Fin]" << endl;
    }
};
