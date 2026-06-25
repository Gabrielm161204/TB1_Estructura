#pragma once
#include "vector"
#include "list"
#include "string"

/*
 Clase: HashTable
 Tabla hash generica con manejo de colisiones por encadenamiento (chaining).
 Permite insertar, buscar y eliminar pares clave-valor donde la clave es
 un string y el valor es de tipo T. Usa la funcion hash polinomial de base 31.
*/
template<typename T>
class HashTable {
private:
    vector<list<pair<string, T>>> tabla;  // Vector de listas de pares clave-valor
    int m;                                // Tamanio de la tabla (numero de buckets)

    /*
     Funcion hash polinomial de base 31.
     Convierte una clave string en un indice entero dentro del rango [0, m-1].
    */
    int hashFunction(string& key) {
        unsigned long h = 0;
        for (char c : key) {
            h = h * 31 + (unsigned char)c;
        }
        return h % m;
    }

public:

    /*
     Constructor.
     Inicializa la tabla con el tamanio indicado.
    */
    HashTable(int tam)
        : tabla(tam), m(tam) {
    }

    /*
     Inserta un par clave-valor en la tabla.
     Si la clave ya existe en su bucket, actualiza el valor.
     Si no existe, agrega el nuevo par al bucket correspondiente.
    */
    void insertar(string key, T value) {
        int idx = hashFunction(key);
        auto& bucket = tabla[idx];

        for (auto& par : bucket) {
            if (par.first == key) {
                par.second = value;  // actualizar valor existente
                return;
            }
        }
        bucket.push_back({ key, value });  // insertar nuevo par
    }

    /*
     Busca un valor por clave en la tabla.
     Si lo encuentra, lo asigna al parametro de salida y retorna true.
     Si no lo encuentra, retorna false.
    */
    bool encontrado(string& key, T& out) {
        int idx = hashFunction(key);
        const auto& bucket = tabla[idx];

        for (auto& par : bucket) {
            if (par.first == key) {
                out = par.second;
                return true;
            }
        }
        return false;
    }

    /*
     Elimina un par clave-valor de la tabla.
     Retorna true si la clave fue encontrada y eliminada.
     Retorna false si la clave no existe en la tabla.
    */
    bool borrar(string& key) {
        int idx = hashFunction(key);
        auto& bucket = tabla[idx];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                return true;
            }
        }
        return false;
    }
};
