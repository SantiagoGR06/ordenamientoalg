

#include <iostream>
#include <fstream> // Se utiliza para leer de archivos.
#include <string> //  Proporciona las clases y funciones para manejar cadenas de caracteres en C++ de manera eficiente, como la clase string y sus operaciones.
#include <sstream> // Proporciona clases y funciones para realizar operaciones de entrada y salida con secuencias de caracteres. Por ejemplo, puedes convertir tipos de datos a cadenas de caracteres utilizando stringstream.
#include <vector> // Proporciona una implementación de contenedor de arreglo dinámico en C++. Los vectores son secuencias de elementos con tamaño variable y se pueden acceder de manera eficiente a través de índices.
#include <algorithm> // Proporciona una serie de algoritmos genéricos que trabajan en secuencias de elementos, como ordenamiento, búsqueda y manipulación de secuencias.
#include <climits> // Define constantes para límites de tipos de datos enteros en C++. Por ejemplo, INT_MAX y INT_MIN son los valores máximos y mínimos para un int, respectivamente
#include <ctime> // se utiliza para cronometrar el tiempo de ejecución de cada método

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
    clock_t start = clock(); // Inicia el temporizador

    Nodo *i, *j, *min;
    string temp;
    int paso = 0; // Variable para mantener el número de pasos

    for (i = inicio; i != nullptr; i = i->siguiente) {
        min = i;
        for (j = i->siguiente; j != nullptr; j = j->siguiente) {
            if (stoi(j->dato) < stoi(min->dato)) {
                min = j;
            }
            paso++; // Incrementa el número de pasos en cada comparación
        }
        if (min != i) {
            temp = i->dato;
            i->dato = min->dato;
            min->dato = temp;
        }
    }

    clock_t end = clock(); // Finaliza el temporizador
    double duration = double(end - start) / CLOCKS_PER_SEC; // Calcula la duración en segundos

    cout << "Iteraciones: " << paso << endl; // Imprime el número total de iteraciones
    cout << "Lista ordenada mediante el algoritmo de selección." << endl;
    cout << "El método de ordenamiento por selección se demoró " << duration << " segundos en ejecutar." << endl;
}


    // bubbleSort
 void ordenarBubbleSort() {
    clock_t start = clock(); // Inicia el temporizador

    bool swapped;
    Nodo* ptr1;
    Nodo* lptr = nullptr;
    int iteraciones = 0; // Variable para mantener el número total de iteraciones

    if (inicio == nullptr || inicio->siguiente == nullptr)
        return;

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
            iteraciones++; // Incrementa el número de iteraciones en cada comparación
        }

        lptr = ptr1;
    } while (swapped);

    clock_t end = clock(); // Finaliza el temporizador
    double duration = double(end - start) / CLOCKS_PER_SEC; // Calcula la duración en segundos

    cout << "Iteraciones: " << iteraciones << endl; // Imprime el número total de iteraciones
    cout << "Lista ordenada mediante el algoritmo de Bubble Sort." << endl;
    cout << "El método de ordenamiento Bubble sort se demoró " << duration << " segundos en ejecutar." << endl;
}


// Insertion
void ordenarInsertionSort() {
    clock_t start = clock(); // Inicia el temporizador

    if (inicio == nullptr || inicio->siguiente == nullptr) {
        cout << "La lista está vacía o tiene un solo elemento, ya está ordenada." << endl;
        return;
    }

    Nodo* i = inicio->siguiente;
    int iteraciones = 0; // Variable para mantener el número total de iteraciones

    while (i != nullptr) {
        string valorActual = i->dato;
        Nodo* j = inicio;

        while (j != i && stoi(j->dato) < stoi(valorActual)) {
            j = j->siguiente;
            iteraciones++; // Incrementa el número de iteraciones en cada comparación
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

        i = i->siguiente;
    }

    clock_t end = clock(); // Finaliza el temporizador
    double duration = double(end - start) / CLOCKS_PER_SEC; // Calcula la duración en segundos

    cout << "Iteraciones: " << iteraciones << endl; // Imprime el número total de iteraciones
    cout << "Lista ordenada mediante el algoritmo de Insertion Sort." << endl;
    cout << "El método Insertion sort se demoró " << duration << " segundos en ejecutar." << endl;
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

void mergeSort(Nodo** inicio, int& iteraciones) {
    Nodo* head = *inicio;
    Nodo* a;
    Nodo* b;

    if (head == nullptr || head->siguiente == nullptr) {
        return;
    }

    split(head, &a, &b);

    mergeSort(&a, iteraciones);
    mergeSort(&b, iteraciones);

    merge(inicio, a, b);
    iteraciones++;
}

void ordenarMergeSort() {
    clock_t start = clock(); // Inicia el temporizador

    int iteraciones = 0; // Variable para mantener el número total de iteraciones
    mergeSort(&inicio, iteraciones);

    clock_t end = clock(); // Finaliza el temporizador
    double duration = double(end - start) / CLOCKS_PER_SEC; // Calcula la duración en segundos

    cout << "Iteraciones: " << iteraciones << endl; // Imprime el número total de iteraciones
    cout << "Lista ordenada mediante el algoritmo de Merge Sort." << endl;
    cout << "El método Merge sort se demoró " << duration << " segundos en ejecutar." << endl;
}


// quickSort
void quickSort(Nodo** inicio, int& paso) {
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
        paso++; // Incrementa el número de pasos en cada comparación
    }

    quickSort(&lesserHead, paso);
    quickSort(&greaterHead, paso);

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
}

void ordenarQuickSort() {
    clock_t start = clock(); // Inicia el temporizador

    int paso = 0; // Variable para mantener el número de pasos
    quickSort(&inicio, paso);

    clock_t end = clock(); // Finaliza el temporizador
    double duration = double(end - start) / CLOCKS_PER_SEC; // Calcula la duración en segundos

    cout << "Iteraciones: " << paso << endl; // Imprime el número total de iteraciones
    cout << "Lista ordenada mediante el algoritmo de Quicksort." << endl;
    cout << "El método Quicksort se demoró " << duration << " segundos en ejecutar." << endl;
}

// bucketSort
void bucketSort() {
    clock_t start = clock(); // Inicia el temporizador

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

    int iteraciones = numBuckets; // El número de iteraciones es igual al número de buckets

    clock_t end = clock(); // Finaliza el temporizador
    double duration = double(end - start) / CLOCKS_PER_SEC; // Calcula la duración en segundos

    cout << "Iteraciones: " << iteraciones << endl; // Imprime el número total de iteraciones
    cout << "Lista ordenada mediante el algoritmo de Bucket Sort." << endl;
    cout << "El método Bucket sort se demoró " << duration << " segundos en ejecutar." << endl;
}


//shellSort
void shellSort() {
    clock_t start = clock(); // Inicia el temporizador

    int n = 0;
    Nodo* current = inicio;

    while (current != nullptr) {
        ++n;
        current = current->siguiente;
    }

    int gap = n / 2;
    int iteraciones = 0; // Variable para mantener el número total de iteraciones

    while (gap > 0) {
        for (int i = gap; i < n; ++i) {
            string temp = getElemento(i);

            int j = i;
            while (j >= gap && stoi(getElemento(j - gap)) > stoi(temp)) {
                setElemento(j, getElemento(j - gap));
                j -= gap;
                iteraciones++; // Incrementa el número de iteraciones en cada comparación
            }
            setElemento(j, temp);
        }

        gap /= 2;
    }

    clock_t end = clock(); // Finaliza el temporizador
    double duration = double(end - start) / CLOCKS_PER_SEC; // Calcula la duración en segundos

    cout << "Iteraciones: " << iteraciones << endl; // Imprime el número total de iteraciones
    cout << "Lista ordenada mediante el algoritmo de Shell Sort." << endl;
    cout << "El metodo de ordenamiento Shell sort se demoró " << duration << " segundos en ejecutar." << endl;
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
    clock_t start = clock(); // Inicia el temporizador

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

    int iteraciones = range; // El número de iteraciones es igual al rango

    clock_t end = clock(); // Finaliza el temporizador
    double duration = double(end - start) / CLOCKS_PER_SEC; // Calcula la duración en segundos

    cout << "Iteraciones: " << iteraciones << endl; // Imprime el número total de iteraciones
    cout << "El método de ordenamiento Counting Sort se demoró " << duration << " segundos en ejecutar." << endl;
}



// radixSort

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

int getSize() {
    int count = 0;
    Nodo* current = inicio;
    while (current != nullptr) {
        count++;
        current = current->siguiente;
    }
    return count;
}

void countingSort(int arr[], int n, int exp, int &iteraciones) {
    int output[n]; // Arreglo de salida
    int i, count[10] = {0};

    // Almacena la cantidad de ocurrencias de cada dígito en count[]
    for (i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
        iteraciones++; // Incrementa el contador de iteraciones
    }

    // Cambia count[i] para que contenga la posición real de este dígito en output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Construye el arreglo de salida
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copia el arreglo de salida a arr[], así arr[] contiene los números ordenados
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort() {
    clock_t start = clock(); // Inicia el temporizador

    int n = getSize();
    int arr[n];
    Nodo* current = inicio;
    int i = 0;
    int iteraciones = 0; // Inicializa el contador de iteraciones

    // Llena el arreglo con los elementos de la lista
    while (current != nullptr) {
        arr[i++] = stoi(current->dato);
        current = current->siguiente;
    }

    // Encuentra el valor máximo para saber cuántos dígitos tiene
    int m = getMax(arr, n);

    // Aplica el counting sort para cada dígito. En lugar de pasar exp, pasamos 10^i donde i es el dígito actual
    for (int exp = 1; m / exp > 0; exp *= 10)
        countingSort(arr, n, exp, iteraciones);

    // Actualiza la lista con los valores ordenados
    current = inicio;
    for (int i = 0; i < n; ++i) {
        current->dato = to_string(arr[i]);
        current = current->siguiente;
    }

    clock_t end = clock(); // Finaliza el temporizador
    double duration = double(end - start) / CLOCKS_PER_SEC; // Calcula la duración en segundos

    cout << "Número total de iteraciones: " << iteraciones << endl; // Imprime el número total de iteraciones
    cout << "El método de ordenamiento Radix Sort se demoró " << duration << " segundos en ejecutar." << endl;
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
