#pragma once

class Categoria {
public:
    int id;
    string nombre;
    string descripcion;

    Categoria() {
        id = 0;
        nombre = "";
		descripcion = "";
    }
    Categoria(int i, string nom, string desc) {
        id = i;
        nombre = nom;
        descripcion = desc;
    }

    string getNombre() { return nombre; }

    void mostrar() {
        cout << "  [" << id << "] " << nombre << " - " << descripcion << endl;
    }
};

