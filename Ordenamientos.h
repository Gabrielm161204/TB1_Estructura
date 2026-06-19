#pragma once


// --- Bubble Sort (Burbuja) ---
// Compara pares adyacentes e intercambia si estan en orden incorrecto
// Complejidad: O(n^2)
void bubbleSort(vector<double>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// --- Selection Sort (Seleccion) ---
// Busca el minimo y lo coloca al inicio en cada iteracion
// Complejidad: O(n^2)
void selectionSort(vector<double>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        double temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

// --- Insertion Sort (Insercion) ---
// Inserta cada elemento en su posicion correcta dentro de la parte ordenada
// Complejidad: O(n^2) peor caso, O(n) mejor caso
void insertionSort(vector<double>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        double key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// --- Quick Sort (Recursivo) ---
// RECURSIVIDAD: la funcion se llama a si misma con subproblemas mas pequenos
// Complejidad: O(n log n) promedio
int particion(vector<double>& arr, int bajo, int alto) {
    double pivote = arr[alto];
    int i = bajo - 1;
    for (int j = bajo; j < alto; j++) {
        if (arr[j] <= pivote) {
            i++;
            double temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }
    double temp = arr[i + 1]; arr[i + 1] = arr[alto]; arr[alto] = temp;
    return i + 1;
}

void quickSort(vector<double>& arr, int bajo, int alto) {
    if (bajo < alto) {
        int pi = particion(arr, bajo, alto);
        quickSort(arr, bajo, pi - 1);   // Recursion izquierda
        quickSort(arr, pi + 1, alto);   // Recursion derecha
    }
}

// ============================================================
// FISHER-YATES SHUFFLE
// Genera permutacion aleatoria sin sesgo - O(n)
// ============================================================
template<typename T>
void fisherYates(vector<T>& arr) {
    srand((unsigned int)time(0));
    int n = arr.size();
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);   // indice aleatorio entre 0 e i
        T temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// Mostrar vector de doubles
void mostrarVector( vector<double>& arr, string titulo) {
    cout << titulo << ": [ ";
    for (double x : arr) cout << x << " ";
    cout << "]" << endl;
}

