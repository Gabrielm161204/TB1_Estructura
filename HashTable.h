#pragma once
#include "vector"
#include "list"
#include "string"

template<typename T>
class HashTable {
private:
    vector<list<pair<string, T>>> tabla;
    int m;  // tamaño de la tabla

    int hashFunction( string& key) {
        unsigned long h = 0;
        for (char c : key) {
            h = h * 31 + (unsigned char)c;
        }
        return h % m;
    }

public:
    HashTable(int tam)
        : tabla(tam), m(tam) {
    }

    // Insertar o actualizar
    void insertar( string key, T value) {
        int idx = hashFunction(key);
        auto& bucket = tabla[idx];

        for (auto& par : bucket) {
            if (par.first == key) {
                par.second = value;   // actualizar
                return;
            }
        }
        bucket.push_back({ key, value }); // nuevo
    }

    bool encontrado( string& key, T& out) {
        int idx = hashFunction(key);
        const auto& bucket = tabla[idx];

        for ( auto& par : bucket) {
            if (par.first == key) {
                out = par.second;
                return true;
            }
        }
        return false;
    }

    bool borrar( string& key) {
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