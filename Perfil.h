#pragma once


class Perfil {
public:
    string nombre;
    string dni;
    string fechaRegistro;

    Perfil() : nombre(""), dni(""), fechaRegistro("") {}

    Perfil(string nom, string d, string fecha)
        : nombre(nom), dni(d), fechaRegistro(fecha) {
    }

    // Muestra datos del perfil
    void mostrarPerfil() {
        cout << "  Nombre         : " << nombre << endl;
        cout << "  DNI            : " << dni << endl;
        cout << "  Fecha registro : " << fechaRegistro << endl;
    }

    // Actualiza el nombre
    void actualizarNombre(string nuevoNombre) {
        nombre = nuevoNombre;
        cout << "  [OK] Nombre actualizado a: " << nombre << endl;
    }

    string getNombre() { return nombre; }
    string getDni() { return dni; }
};

