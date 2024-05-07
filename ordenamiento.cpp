#include <iostream>
#include <fstream> // Se utiliza para leer de archivos.
#include <string> //  Proporciona las clases y funciones para manejar cadenas de caracteres en C++ de manera eficiente, como la clase string y sus operaciones.
#include <sstream> // Proporciona clases y funciones para realizar operaciones de entrada y salida con secuencias de caracteres. Por ejemplo, puedes convertir tipos de datos a cadenas de caracteres utilizando stringstream.
#include <vector> // Proporciona una implementación de contenedor de arreglo dinámico en C++. Los vectores son secuencias de elementos con tamaño variable y se pueden acceder de manera eficiente a través de índices.
#include <algorithm> // Proporciona una serie de algoritmos genéricos que trabajan en secuencias de elementos, como ordenamiento, búsqueda y manipulación de secuencias.
#include <climits> // Define constantes para límites de tipos de datos enteros en C++. Por ejemplo, INT_MAX y INT_MIN son los valores máximos y mínimos para un int, respectivamente
#include <chrono>

using namespace std;
// inicio de puntero para la lista
struct Nodo {
    string dato;
    Nodo* siguiente;

};

class ListaDinamica { // se inicializa el puntero inicio como privado para encapsulamiento
private:
    Nodo* inicio;

public:
    ListaDinamica() { // se tiene que validar que el inicio sea NULL
        inicio = nullptr;
    }

    ~ListaDinamica() {
        Nodo* actual = inicio; // se apunta el puntero actual al primer nodo de la lista inicio
        Nodo* siguiente;  
         // Dentro del bucle, guarda el puntero al siguiente nodo en siguiente.
        while (actual != nullptr) { //Borra el nodo actual utilizando el operador delete.
            siguiente = actual->siguiente;// Actualiza actual para que apunte al siguiente nodo (el que se guardó en siguiente).
            delete actual;
            actual = siguiente; // Repite el proceso hasta que actual sea nullptr, lo que indica que se ha llegado al final de la lista.
        }
    }
    
   void insertar(string dato) {
    // Crea un nuevo nodo dinámico utilizando el operador 'new' y asigna su dirección de memoria al puntero nuevoNodo.
    Nodo* nuevoNodo = new Nodo;
    nuevoNodo->dato = dato; // Asigna el valor del argumento 'dato' al campo 'dato' del nuevo nodo creado.
    nuevoNodo->siguiente = nullptr; // Establece el siguiente del nuevo nodo como nullptr, ya que será el último nodo.

    if (inicio == nullptr) { // Si la lista está vacía, el nuevo nodo será el primer nodo.
        inicio = nuevoNodo;
    } else {
        Nodo* actual = inicio;
        while (actual->siguiente != nullptr) { // Busca el último nodo de la lista.
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo; // Enlaza el último nodo de la lista con el nuevo nodo.
    }
}

// insertar datos en la lista
   /*   void insertar(string dato) { // Se crea un nuevo nodo dinámico utilizando el operador new y se asigna su dirección de memoria al puntero nuevoNodo.
        Nodo* nuevoNodo = new Nodo;
        nuevoNodo->dato = dato; // Se asigna el valor dato pasado como argumento al campo dato del nuevo nodo creado.
        nuevoNodo->siguiente = inicio; // Se asigna el puntero inicio como el siguiente nodo del nuevo nodo. Esto significa que el nuevo nodo se enlaza al nodo que anteriormente era el inicio de la lista.
        inicio = nuevoNodo; // Se actualiza el puntero inicio para que apunte al nuevo nodo creado. Ahora, el nuevo nodo se convierte en el primer nodo de la lista, es decir, el inicio de la lista se mueve al nuevo nodo.
    }*/
// eliminar datos en al lista
    void eliminar(string dato) {
        Nodo* actual = inicio;   // Se inicializan dos punteros actual y anterior. actual apunta al inicio de la lista y anterior se inicializa como nullptr.
        Nodo* anterior = nullptr;

        while (actual != nullptr && actual->dato != dato) { //Se recorre la lista mientras el puntero actual no sea nullptr
            anterior = actual;                              //  el valor de dato del nodo actual no coincida con el valor dato pasado como argumento.
            actual = actual->siguiente;                     //Durante el recorrido, el puntero anterior sigue al puntero actual para mantener un rastro del nodo anterior al nodo actual.
        }

        if (actual == nullptr) {  // se verifica que en nodo este en la lista
            cout << "El elemento no se encuentra en la lista." << endl;
            return;
        }

        if (anterior == nullptr) { 
            inicio = actual->siguiente;// Si el nodo a eliminar es el primer nodo de la lista (es decir, anterior es nullptr), se actualiza el puntero inicio para que apunte al siguiente nodo (que puede ser nullptr si el nodo a eliminar es el único en la lista).
        } else {
            anterior->siguiente = actual->siguiente;//Si el nodo a eliminar no es el primer nodo de la lista, se enlaza el nodo anterior directamente al siguiente nodo del nodo a eliminar, saltándolo en la lista.
        }

        delete actual;
        cout << "Elemento eliminado: " << dato << endl; // se muestra en pantalla al usuario que se elimino el dato 
    }
//  imprimir en la consola los elementos almacenados en la lista enlazada
    void mostrar() {
        Nodo* actual = inicio; // al puntero actual se le pasa los valores de inicio 
        while (actual != nullptr) { // se valida que el actual no este vacio
            cout << actual->dato << " "; // se muestra el dato que esta apuntando el punteroa ctual vaya la ironia jaja
            actual = actual->siguiente; // el puntero actual pasa al puntero siguiente que apunta al otro nodo asi sucesivamente 
        }
        cout << endl;
    }
// de aqui a para abajo comienza las funciones de ORDENAMIENTO
// no creo qeu hace falta explicar los codigos de ORDENAMIENTO ya que pues para eso fue las exposiciones 
// selección
void ordenarSeleccion() {
    auto start = chrono::high_resolution_clock::now(); // Inicia el temporizador

    Nodo *i, *j, *min;
    string temp;
    int paso = 1; // Variable para mantener el número de pasos

    cout << "Lista original:" << endl;
    mostrar(); // Suponiendo que tienes una función mostrar() para mostrar la lista
    cout << endl;

    for (i = inicio; i != nullptr; i = i->siguiente) {
        min = i;
        for (j = i->siguiente; j != nullptr; j = j->siguiente) {
            if (stoi(j->dato) < stoi(min->dato)) {
                min = j;
            }
        }
        if (min != i) {
            temp = i->dato;
            i->dato = min->dato;
            min->dato = temp;

            // Imprime el estado actual de la lista después de intercambiar los elementos
            cout << "Iteración " << paso++ << ":" << endl;
            mostrar(); // Suponiendo que tienes una función mostrar() para mostrar la lista
            cout << endl;

            // Pausa la ejecución para que el usuario pueda ver la lista
            cout << "Presiona Enter para continuar..." << endl;
            cin.ignore(); // Ignora la entrada del usuario (incluyendo Enter)
        }
    }

    auto end = chrono::high_resolution_clock::now(); // Finaliza el temporizador
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start); // Calcula la duración

    cout << "Lista ordenada mediante el algoritmo de selección." << endl;
    cout << "La función se demoró " << duration.count() << " microsegundos en ejecutar." << endl;
}


    // bubbleSort
 void ordenarBubbleSort() {
    auto start = chrono::high_resolution_clock::now(); // Inicia el temporizador

    bool swapped;
    Nodo* ptr1;
    Nodo* lptr = nullptr;
    int paso = 1; // Variable para mantener el número de pasos

    if (inicio == nullptr || inicio->siguiente == nullptr)
        return;

    cout << "Lista original:" << endl;
    mostrar(); // Suponiendo que tienes una función mostrar() para mostrar la lista
    cout << endl;

    do {
        swapped = false;
        ptr1 = inicio;

        while (ptr1->siguiente != lptr) {
            if (stoi(ptr1->dato) > stoi(ptr1->siguiente->dato)) {
                string temp = ptr1->dato;
                ptr1->dato = ptr1->siguiente->dato;
                ptr1->siguiente->dato = temp;
                swapped = true;
            }
            ptr1 = ptr1->siguiente;
        }

        // Imprime el estado actual de la lista después de cada iteración
        cout << "Iteración " << paso++ << ":" << endl;
        mostrar(); // Suponiendo que tienes una función mostrar() para mostrar la lista
        cout << "Swapped: " << (swapped ? "true" : "false") << endl;
        cout << endl;

        // Pausa la ejecución para que el usuario pueda ver la lista
        cout << "Presiona Enter para continuar..." << endl;
        cin.ignore(); // Ignora la entrada del usuario (incluyendo Enter)

        lptr = ptr1;
    } while (swapped);

    auto end = chrono::high_resolution_clock::now(); // Finaliza el temporizador
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start); // Calcula la duración

    cout << "Lista ordenada mediante el algoritmo de Bubble Sort." << endl;
    cout << "La función se demoró " << duration.count() << " microsegundos en ejecutar." << endl;
}

// Insertion
void ordenarInsertionSort() {
    auto start = chrono::high_resolution_clock::now(); // Inicia el temporizador

    if (inicio == nullptr || inicio->siguiente == nullptr) {
        cout << "La lista está vacía o tiene un solo elemento, ya está ordenada." << endl;
        return;
    }

    cout << "Lista original:" << endl;
    mostrar(); // Suponiendo que tienes una función mostrar() para mostrar la lista
    cout << endl;

    Nodo* i = inicio->siguiente;
    int iteracion = 1;

    while (i != nullptr) {
        string valorActual = i->dato;
        Nodo* j = inicio;

        while (j != i && stoi(j->dato) < stoi(valorActual)) {
            j = j->siguiente;
        }

        // Mover los elementos mayores a la derecha
        while (j != i) {
            string temp = j->dato;
            j->dato = valorActual;
            valorActual = temp;
            j = j->siguiente;
        }

        // Insertar el valor actual en la posición correcta
        j->dato = valorActual;

        cout << "Iteración " << iteracion++ << ": ";
        mostrar(); // Suponiendo que tienes una función mostrar() para mostrar la lista
        cout << endl;

        i = i->siguiente;
    }

    auto end = chrono::high_resolution_clock::now(); // Finaliza el temporizador
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start); // Calcula la duración

    cout << "Lista ordenada mediante el algoritmo de Insertion Sort." << endl;
    cout << "La función se demoró " << duration.count() << " microsegundos en ejecutar." << endl;
}



// mergeSort
void merge(Nodo** inicio, Nodo* inicioA, Nodo* inicioB) {
    Nodo* resultado = nullptr;
    Nodo* ultimoResultado = nullptr;

    while (inicioA != nullptr && inicioB != nullptr) {
        if (stoi(inicioA->dato) <= stoi(inicioB->dato)) {
            if (resultado == nullptr) {
                resultado = inicioA;
                *inicio = resultado;
            } else {
                ultimoResultado->siguiente = inicioA;
            }
            ultimoResultado = inicioA;
            inicioA = inicioA->siguiente;
        } else {
            if (resultado == nullptr) {
                resultado = inicioB;
                *inicio = resultado;
            } else {
                ultimoResultado->siguiente = inicioB;
            }
            ultimoResultado = inicioB;
            inicioB = inicioB->siguiente;
        }
    }

    if (inicioA != nullptr) {
        ultimoResultado->siguiente = inicioA;
    } else {
        ultimoResultado->siguiente = inicioB;
    }
}

void split(Nodo* inicio, Nodo** inicioA, Nodo** inicioB) {
    Nodo* fast;
    Nodo* slow;

    if (inicio == nullptr || inicio->siguiente == nullptr) {
        *inicioA = inicio;
        *inicioB = nullptr;
    } else {
        slow = inicio;
        fast = inicio->siguiente;

        while (fast != nullptr) {
            fast = fast->siguiente;
            if (fast != nullptr) {
                slow = slow->siguiente;
                fast = fast->siguiente;
            }
        }

        *inicioA = inicio;
        *inicioB = slow->siguiente;
        slow->siguiente = nullptr;
    }
}

void mergeSort(Nodo** inicio) {
    Nodo* head = *inicio;
    Nodo* a;
    Nodo* b;

    if (head == nullptr || head->siguiente == nullptr) {
        return;
    }

    split(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    merge(inicio, a, b);
}

void ordenarMergeSort() {
    auto start = chrono::high_resolution_clock::now(); // Inicia el temporizador

    mergeSort(&inicio);

    auto end = chrono::high_resolution_clock::now(); // Finaliza el temporizador
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start); // Calcula la duración

    cout << "Lista ordenada mediante el algoritmo de Merge Sort." << endl;
    cout << "La función se demoró " << duration.count() << " microsegundos en ejecutar." << endl;
}

// quickSort
void quickSort(Nodo** inicio) {
    auto start = chrono::high_resolution_clock::now(); // Inicia el temporizador

    if (*inicio == nullptr || (*inicio)->siguiente == nullptr)
        return;

    Nodo* pivot = *inicio;
    Nodo* lesserHead = nullptr;
    Nodo* greaterHead = nullptr;

    Nodo* current = (*inicio)->siguiente;

    while (current != nullptr) {
        Nodo* next = current->siguiente;
        if (stoi(current->dato) < stoi(pivot->dato)) {
            current->siguiente = lesserHead;
            lesserHead = current;
        } else {
            current->siguiente = greaterHead;
            greaterHead = current;
        }
        current = next;
    }

    // Imprimir los pasos
    cout << "Menores al pivot: ";
    mostrar(); // Suponiendo que mostrar() imprime los valores de los nodos
    cout << endl;

    cout << "Pivot: " << pivot->dato << endl;

    cout << "Mayores al pivot: ";
    mostrar(); // Suponiendo que mostrar() imprime los valores de los nodos
    cout << endl;

    quickSort(&lesserHead);
    quickSort(&greaterHead);

    if (lesserHead == nullptr) {
        *inicio = pivot;
    } else {
        *inicio = lesserHead;
        Nodo* endOfLesser = lesserHead;
        while (endOfLesser->siguiente != nullptr) {
            endOfLesser = endOfLesser->siguiente;
        }
        endOfLesser->siguiente = pivot;
    }

    pivot->siguiente = greaterHead;

    auto end = chrono::high_resolution_clock::now(); // Finaliza el temporizador
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start); // Calcula la duración

    cout << "Lista ordenada mediante el algoritmo de Quicksort." << endl;
    cout << "La función se demoró " << duration.count() << " microsegundos en ejecutar." << endl;
}

void ordenarQuickSort() {
    auto start = chrono::high_resolution_clock::now(); // Inicia el temporizador

    quickSort(&inicio);

    auto end = chrono::high_resolution_clock::now(); // Finaliza el temporizador
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start); // Calcula la duración

    cout << "Lista ordenada mediante el algoritmo de Quicksort." << endl;
    cout << "La función se demoró " << duration.count() << " microsegundos en ejecutar." << endl;
}


// bucketSort
void bucketSort() {
    auto start = chrono::high_resolution_clock::now(); // Inicia el temporizador

    int maxVal = INT_MIN;
    int minVal = INT_MAX;
    Nodo* current = inicio;

    while (current != nullptr) {
        int val = stoi(current->dato);
        if (val > maxVal) maxVal = val;
        if (val < minVal) minVal = val;
        current = current->siguiente;
    }

    int numBuckets = maxVal - minVal + 1;
    vector<vector<string>> buckets(numBuckets);

    current = inicio;
    while (current != nullptr) {
        int val = stoi(current->dato);
        buckets[val - minVal].push_back(current->dato);
        current = current->siguiente;
    }

    current = inicio;
    for (int i = 0; i < numBuckets; ++i) {
        sort(buckets[i].begin(), buckets[i].end());
        for (const auto& val : buckets[i]) {
            current->dato = val;
            current = current->siguiente;
        }

        // Imprimir el estado actual de la lista después de cada iteración
        cout << "Iteración " << i + 1 << ": ";
        mostrar(); // Suponiendo que tienes una función mostrar() para mostrar la lista
        cout << endl;
    }

    auto end = chrono::high_resolution_clock::now(); // Finaliza el temporizador
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start); // Calcula la duración

    cout << "Lista ordenada mediante el algoritmo de Bucket Sort." << endl;
    cout << "La función se demoró " << duration.count() << " microsegundos en ejecutar." << endl;
}


//shellSort
void shellSort() {
    auto start = chrono::high_resolution_clock::now(); // Inicia el temporizador

    int n = 0;
    Nodo* current = inicio;

    while (current != nullptr) {
        ++n;
        current = current->siguiente;
    }

    int gap = n / 2;

    while (gap > 0) {
        for (int i = gap; i < n; ++i) {
            string temp = getElemento(i);

            int j = i;
            while (j >= gap && stoi(getElemento(j - gap)) > stoi(temp)) {
                setElemento(j, getElemento(j - gap));
                j -= gap;
            }
            setElemento(j, temp);

            // Imprimir el estado actual de la lista después de cada iteración
            cout << "Iteración gap=" << gap << ", i=" << i << ": ";
            mostrar(); // Suponiendo que tienes una función mostrar() para mostrar la lista
            cout << endl;
        }

        gap /= 2;
    }

    auto end = chrono::high_resolution_clock::now(); // Finaliza el temporizador
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start); // Calcula la duración

    cout << "Lista ordenada mediante el algoritmo de Shell Sort." << endl;
    cout << "La función se demoró " << duration.count() << " microsegundos en ejecutar." << endl;
}



//countingSort
string getElemento(int pos) {
    Nodo* current = inicio;
    for (int i = 0; i < pos && current != nullptr; ++i) {
        current = current->siguiente;
    }
    if (current != nullptr) {
        return current->dato;
    } else {
        return ""; 
    }
}

void setElemento(int pos, string valor) {
    Nodo* current = inicio;
    for (int i = 0; i < pos && current != nullptr; ++i) {
        current = current->siguiente;
    }
    if (current != nullptr) {
        current->dato = valor;
    } else {
        // Manejo del caso en el que no se encuentra el elemento
    }
}

void countingSort() {
    auto start = chrono::high_resolution_clock::now(); // Inicia el temporizador

    int minVal = INT_MAX;
    int maxVal = INT_MIN;
    Nodo* current = inicio;

    while (current != nullptr) {
        int val = stoi(current->dato);
        minVal = min(minVal, val);
        maxVal = max(maxVal, val);
        current = current->siguiente;
    }

    int range = maxVal - minVal + 1;

    vector<int> count(range, 0);

    current = inicio;
    while (current != nullptr) {
        int val = stoi(current->dato);
        count[val - minVal]++;
        current = current->siguiente;
    }

    current = inicio;
    for (int i = 0; i < range; ++i) {
        while (count[i] > 0) {
            current->dato = to_string(i + minVal);
            count[i]--;
            current = current->siguiente;

            // Imprimir el estado actual de la lista después de cada iteración
            cout << "Iteración " << ": ";
            mostrar(); // Suponiendo que tienes una función mostrar() para mostrar la lista
            cout << endl;
        }
    }

    auto end = chrono::high_resolution_clock::now(); // Finaliza el temporizador
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start); // Calcula la duración

    cout << "Lista ordenada mediante el algoritmo de Counting Sort." << endl;
    cout << "La función se demoró " << duration.count() << " microsegundos en ejecutar." << endl;
}


// radixSort
int getSize() {
    int count = 0;
    Nodo* current = inicio;
    while (current != nullptr) {
        count++;
        current = current->siguiente;
    }
    return count;
}

void radixSort() {
    auto start = chrono::high_resolution_clock::now(); // Inicia el temporizador

    int maxVal = INT_MIN;
    Nodo* current = inicio;

    // Encontrar el valor máximo en la lista
    while (current != nullptr) {
        int val = stoi(current->dato);
        maxVal = max(maxVal, val);
        current = current->siguiente;
    }

    // Realizar el ordenamiento por cada dígito, comenzando desde el dígito menos significativo
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortByDigit(exp);

        // Imprimir el estado actual de la lista después de cada iteración
        cout << "Después de ordenar por el dígito " << exp << ": ";
        mostrar(); // Suponiendo que tienes una función mostrar() para mostrar la lista
        cout << endl;
    }

    auto end = chrono::high_resolution_clock::now(); // Finaliza el temporizador
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start); // Calcula la duración

    cout << "Lista ordenada mediante el algoritmo de Radix Sort." << endl;
    cout << "La función se demoró " << duration.count() << " microsegundos en ejecutar." << endl;
}

void countingSortByDigit(int exp) {
    int range = 10; // Dígitos de 0 a 9

    // Inicializar el arreglo de conteo
    vector<int> count(range, 0);

    // Contar la frecuencia de cada dígito
    Nodo* current = inicio;
    while (current != nullptr) {
        int val = (stoi(current->dato) / exp) % 10;
        count[val]++;
        current = current->siguiente;
    }

    // Calcular las posiciones finales de cada dígito en el arreglo ordenado
    for (int i = 1; i < range; ++i) {
        count[i] += count[i - 1];
    }

    // Construir el arreglo ordenado
    vector<string> output(getSize());
    current = inicio;
    while (current != nullptr) {
        int val = (stoi(current->dato) / exp) % 10;
        output[count[val] - 1] = current->dato;
        count[val]--;
        current = current->siguiente;
    }

    // Actualizar la lista con el arreglo ordenado
    current = inicio;
    for (int i = 0; i < getSize(); ++i) {
        current->dato = output[i];
        current = current->siguiente;
    }
}


};


int main() {
   ListaDinamica lista;// es una variable llamada listaDinamica la cual tiene una variable lista 

    cout << "Ingrese elementos separados por espacios (Escriba 'fin' para terminar) o el nombre del archivo a leer: ";
    string entrada;
    getline(cin, entrada); // toma lo que recibimos por consola
    string elemento; // como se necesita un elementoen string para que lo lea los punteros por ese se crea

    ifstream archivo; // Declaración de la variable archivo

    archivo.open(entrada); // Intenta abrir el archivo

    if (archivo.is_open()) { // Si el archivo se abre correctamente, leemos su contenido línea por línea
        string linea;// se utiliza para almacenar cada línea del archivo 
        while (getline(archivo, linea)) {
            istringstream stream(linea);
            int elemento; // Cambiamos el tipo de la variable elemento a int
            while (stream >> elemento) { // Ahora solo leerá números
                lista.insertar(to_string(elemento)); // Convertimos el número a string antes de insertarlo en la lista
            }
        }
        archivo.close(); // Cerramos el archivo después de leer su contenido
    } else { // Si no se pudo abrir el archivo, asumimos que el usuario ingresó elementos por consola
        istringstream stream(entrada);
        int elemento; // Cambiamos el tipo de la variable elemento a int
        while (stream >> elemento) { // Ahora solo leerá números
            lista.insertar(to_string(elemento)); // Convertimos el número a string antes de insertarlo en la lista
        }
    }


    int opcion; // se inicia el MENU se usa el do while para que si el usuario se equivoque regrese otra ves al menu 
    do {        // y luego el swich anidadado ya que toca eliminar, agregar y mirar la lista ademas el cuarto es anidado ya que es para el otro MENU de ORDENAMIENTO
        cout << "\n--- MENU ---" << endl;
        cout << "1. Mostrar lista" << endl;
        cout << "2. Eliminar elemento" << endl;
        cout << "3. Insertar elemento adicional" << endl;
        cout << "4. Ordenar lista" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Lista actual: ";
                lista.mostrar(); // la list. mostrar es por que a la ListaDinamica le estamos diciendo que llame a la funcion mostrar 
                break; // asi my coloquial si quiere mas educado se utiliza para acceder a la función mostrar() que pertenece a un objeto de tipo ListaDinamica llamado lista.
            case 2:
                cout << "Ingrese el elemento que desea eliminar: ";
                cin >> elemento;
                lista.eliminar(elemento);
                break;
            case 3:
                cout << "Ingrese el elemento adicional que desea insertar: ";
                cin >> elemento;
                lista.insertar(elemento);
                break;
            case 4:
               {
                    cout << "\n--- MENU DE ORDENAMIENTO ---" << endl;
                    cout << ". Ordenar la lista (algoritmo de selección)" << endl;
                    cout << "1. ordenar por Bubble Sort " << endl;
                    cout << "2. ordenar por Selection Sort " << endl;
                    cout << "3. ordenar por Insertion Sort" << endl;
                    cout << "4. ordenar por Merge Sort " << endl;
                    cout << "5. ordenar por Quicksort" << endl;
                    cout << "6. ordenar por Bucket Sort" << endl;
                    cout << "7. ordenar por Shell Sort " << endl;
                    cout << "8. ordenar por Counting Sort" << endl;
                    cout << "9. ordenar por Radix Sort" << endl;
                    cout << "Ingrese su opcion: ";
                    int opcionOrdenamiento;
                    cin >> opcionOrdenamiento;

                    switch (opcionOrdenamiento) {
                        case 1:
                            lista.ordenarBubbleSort(); 
                            break;
                        case 2:
                            lista.ordenarSeleccion();
                            break;
                        case 3:
                            lista.ordenarInsertionSort();
                            break;
                        case 4:
                            lista.ordenarMergeSort();
                            break;
                        case 5:
                            lista.ordenarQuickSort();
                            break;
                        case 6:
                            lista.bucketSort();
                            break;
                        case 7:
                            lista.shellSort();
                            break;
                        case 8:
                            lista.countingSort();
                            break;
                        case 9:
                             lista.radixSort();
                            break;    
                        default:
                            cout << "Opción no válida. Volviendo al menú principal." << endl;
                            break;
                    }
                }
                break;
            case 5:
                cout << "Saliendo del programa." << endl;
                break;    
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while (opcion != 5);

    return 0;
}
Codigo structura de datos.txt
Mostrando Codigo structura de datos.txt.