#pragma once

/*
 Funcion: bubbleSort
 Ordena un vector de doubles usando el algoritmo Bubble Sort (burbuja).
 Compara pares adyacentes e intercambia si estan en orden incorrecto.
 Complejidad: O(n^2) en todos los casos.
*/
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

/*
 Funcion: selectionSort
 Ordena un vector de doubles usando el algoritmo Selection Sort (seleccion).
 En cada iteracion busca el minimo del subarreglo no ordenado y lo coloca al inicio.
 Complejidad: O(n^2) en todos los casos.
*/
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

/*
 Funcion: insertionSort
 Ordena un vector de doubles usando el algoritmo Insertion Sort (insercion).
 Inserta cada elemento en su posicion correcta dentro de la parte ya ordenada.
 Complejidad: O(n^2) peor caso, O(n) mejor caso (arreglo casi ordenado).
*/
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

/*
 Funcion: particion
 Funcion auxiliar del Quick Sort.
 Coloca el pivote (ultimo elemento) en su posicion correcta
 y reorganiza los elementos: menores a la izquierda, mayores a la derecha.
 Retorna el indice final del pivote.
*/
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

/*
 Funcion: quickSort
 Ordena un vector de doubles usando el algoritmo Quick Sort de forma recursiva.
 Divide el arreglo en dos subarreglos respecto al pivote y los ordena recursivamente.
 Complejidad: O(n log n) promedio, O(n^2) peor caso.
*/
void quickSort(vector<double>& arr, int bajo, int alto) {
    if (bajo < alto) {
        int pi = particion(arr, bajo, alto);
        quickSort(arr, bajo, pi - 1);   // Recursion sobre el subarreglo izquierdo
        quickSort(arr, pi + 1, alto);   // Recursion sobre el subarreglo derecho
    }
}

/*
 Funcion: fisherYates
 Genera una permutacion aleatoria sin sesgo del vector usando el algoritmo Fisher-Yates.
 Recorre el arreglo de atras hacia adelante e intercambia cada elemento
 con uno en una posicion aleatoria dentro del rango [0, i].
 Complejidad: O(n).
*/
template<typename T>
void fisherYates(vector<T>& arr) {
    srand((unsigned int)time(0));
    int n = arr.size();
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        T temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

/*
 Funcion: mostrarVector
 Muestra en consola los elementos de un vector de doubles con un titulo.
*/
void mostrarVector(vector<double>& arr, string titulo) {
    cout << titulo << ": [ ";
    for (double x : arr) cout << x << " ";
    cout << "]" << endl;
}
