#pragma once

class MetodoPago {
public:
    int id;
    string tipo;        // "Efectivo", "Tarjeta", "Yape", etc.
    string estado;      // "Pendiente", "Aprobado", "Rechazado", "Cancelado"
    double monto;
    string fechaPago;

    MetodoPago() : id(0), tipo(""), estado("Pendiente"), monto(0.0), fechaPago("") {}

    MetodoPago(int i, string t, double m, string fecha)
        : id(i), tipo(t), estado("Pendiente"), monto(m), fechaPago(fecha) {
    }

    // Procesa el pago si el monto es valido
    bool procesarPago(double montoPagar) {
        if (!validarMonto(montoPagar)) return false;
        estado = "Aprobado";
        monto = montoPagar;
        cout << "  [OK] Pago de S/." << montoPagar << " procesado con " << tipo << "." << endl;
        cout << "  Referencia: " << generarReferencia() << endl;
        return true;
    }

    // Valida que el monto sea positivo
    bool validarMonto(double m) {
        if (m <= 0) {
            cout << "  [!] Monto invalido." << endl;
            return false;
        }
        return true;
    }

    // Genera una referencia de pago aleatoria (simula codigo de transaccion)
    string generarReferencia() {
        srand((unsigned int)time(0));
        string ref = tipo.substr(0, 3);
        ref += "-";
        for (int i = 0; i < 6; i++) ref += to_string(rand() % 10);
        return ref;
    }

    // Cancela el pago
    bool cancelarPago() {
        if (estado == "Aprobado") {
            estado = "Cancelado";
            cout << "  Pago cancelado." << endl;
            return true;
        }
        cout << "  No se puede cancelar un pago en estado: " << estado << endl;
        return false;
    }

    void mostrar() {
        cout << "  Tipo    : " << tipo << endl;
        cout << "  Estado  : " << estado << endl;
        cout << "  Monto   : S/." << monto << endl;
        cout << "  Fecha   : " << fechaPago << endl;
    }
};

