#include <iostream>   // Biblioteca estándar de entrada y salida en C++
#include <fstream>    // Biblioteca para operaciones de archivo en C++
#include <vector>     // Biblioteca que proporciona la clase de contenedor vector
#include <string>     // Biblioteca que proporciona la clase de cadena (string)
#include <sstream>    // Biblioteca para trabajar con cadenas de caracteres como flujos de datos
#include <algorithm>  // Biblioteca que proporciona algoritmos estándar como sort, find, etc.
#include <limits>     // Biblioteca que define las características de los tipos fundamentales
#include <queue>      // Biblioteca que proporciona la clase de contenedor cola (queue)


using namespace std; // Evita la necesidad de escribir "std::" antes de los elementos de la biblioteca estándar de C++

// PARTE DE ÁRBOLES ------------------------------------------------------------------------------------------------------------------------------

// Enumeración para definir los colores de los nodos en un árbol rojo-negro
enum Color { RED, BLACK };

// Estructura para un nodo de árbol binario
struct TreeNode {
    int val;            // Valor del nodo
    TreeNode* left;     // Puntero al hijo izquierdo
    TreeNode* right;    // Puntero al hijo derecho

    // Constructor para inicializar un nodo con un valor dado, y punteros hijos a NULL
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Estructura para un nodo de árbol rojo-negro
struct RBNode {
    int val;            // Valor del nodo
    Color color;        // Color del nodo (rojo o negro)
    RBNode* left;       // Puntero al hijo izquierdo
    RBNode* right;      // Puntero al hijo derecho
    RBNode* parent;     // Puntero al nodo padre

    // Constructor para inicializar un nodo con un valor dado, color rojo por defecto, y punteros a NULL
    RBNode(int x) : val(x), color(RED), left(NULL), right(NULL), parent(NULL) {}
};


// Funciones auxiliares para AVL

/**
 * @brief Calcula la altura de un nodo en un árbol binario.
 * 
 * @param node Puntero al nodo del cual se desea calcular la altura.
 * @return int Altura del nodo. Si el nodo es NULL, retorna 0.
 */
int height(TreeNode* node) {
    if (node == NULL) return 0;
    return 1 + std::max(height(node->left), height(node->right));
}

/**
 * @brief Verifica si un árbol binario es un árbol AVL (árbol binario de búsqueda balanceado).
 * 
 * @param root Puntero a la raíz del árbol binario.
 * @return bool true si el árbol es un AVL, false en caso contrario.
 */
bool isAVL(TreeNode* root) {
    if (root == NULL) return true;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    if (std::abs(leftHeight - rightHeight) > 1) return false;
    return isAVL(root->left) && isAVL(root->right);
}

/**
 * @brief Realiza una rotación a la derecha sobre el subárbol con raíz en y.
 * 
 * @param y Puntero a la raíz del subárbol que se va a rotar.
 * @return TreeNode* Puntero a la nueva raíz del subárbol después de la rotación.
 */
/**
 * @brief Realiza una rotación a la derecha sobre el subárbol con raíz en y.
 * 
 * @param y Puntero a la raíz del subárbol que se va a rotar.
 * @return TreeNode* Puntero a la nueva raíz del subárbol después de la rotación.
 */
TreeNode* rotateRight(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    return x;
}

/**
 * @brief Realiza una rotación a la izquierda sobre el subárbol con raíz en x.
 * 
 * @param x Puntero a la raíz del subárbol que se va a rotar.
 * @return TreeNode* Puntero a la nueva raíz del subárbol después de la rotación.
 */
TreeNode* rotateLeft(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    return y;
}

/**
 * @brief Obtiene el factor de balance de un nodo en un árbol AVL.
 * 
 * @param node Puntero al nodo del cual se desea obtener el factor de balance.
 * @return int Factor de balance del nodo. Si el nodo es NULL, retorna 0.
 */
int getBalance(TreeNode* node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}


/**
 * @brief Inserta un nuevo nodo con una clave dada en un árbol AVL y reequilibra el árbol si es necesario.
 * 
 * @param node Puntero a la raíz del subárbol en el que se va a insertar el nuevo nodo.
 * @param key Clave del nuevo nodo que se va a insertar.
 * @return TreeNode* Puntero a la nueva raíz del subárbol después de la inserción y reequilibrio.
 */
TreeNode* insertAVL(TreeNode* node, int key) {
    // Caso base: Si el nodo es NULL, crea un nuevo nodo con la clave dada
    if (node == NULL)
        return new TreeNode(key);

    // Si la clave es menor que el valor del nodo, inserta en el subárbol izquierdo
    if (key < node->val)
        node->left = insertAVL(node->left, key);
    // Si la clave es mayor que el valor del nodo, inserta en el subárbol derecho
    else if (key > node->val)
        node->right = insertAVL(node->right, key);
    // Si la clave es igual al valor del nodo, retorna el nodo (no se permiten duplicados)
    else
        return node;

    // Obtiene el factor de balance del nodo
    int balance = getBalance(node);

    // Si el nodo está desbalanceado, realiza las rotaciones necesarias para equilibrarlo

    // Caso de desbalance hacia la izquierda (izquierda-izquierda)
    if (balance > 1 && key < node->left->val)
        return rotateRight(node);

    // Caso de desbalance hacia la derecha (derecha-derecha)
    if (balance < -1 && key > node->right->val)
        return rotateLeft(node);

    // Caso de desbalance hacia la izquierda-derecha
    if (balance > 1 && key > node->left->val) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Caso de desbalance hacia la derecha-izquierda
    if (balance < -1 && key < node->right->val) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // Retorna el nodo sin cambios si está balanceado
    return node;
}

/**
 * @brief Inserta un nuevo nodo con una clave dada en un árbol binario de búsqueda (BST).
 * 
 * @param root Puntero a la raíz del subárbol en el que se va a insertar el nuevo nodo.
 * @param key Clave del nuevo nodo que se va a insertar.
 * @return TreeNode* Puntero a la nueva raíz del subárbol después de la inserción.
 */
TreeNode* insertBST(TreeNode* root, int key) {
    if (root == NULL)
        return new TreeNode(key);

    if (key < root->val)
        root->left = insertBST(root->left, key);
    else if (key > root->val)
        root->right = insertBST(root->right, key);

    return root;
}

/**
 * @brief Convierte un árbol binario de búsqueda (BST) en un árbol AVL.
 * 
 * @param root Puntero a la raíz del BST que se va a convertir.
 * @return TreeNode* Puntero a la nueva raíz del árbol AVL.
 */
TreeNode* convertToAVL(TreeNode* root) {
    if (root == NULL) return NULL;
    
    std::vector<int> nodes;
    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        nodes.push_back(node->val);
        if (node->left != NULL) q.push(node->left);
        if (node->right != NULL) q.push(node->right);
    }

    TreeNode* avlRoot = NULL;
    for (int val : nodes) {
        avlRoot = insertAVL(avlRoot, val);
    }
    return avlRoot;
}

/**
 * @brief Realiza una rotación a la izquierda sobre el subárbol con raíz en pt en un árbol rojo-negro.
 * 
 * @param root Referencia al puntero a la raíz del árbol rojo-negro.
 * @param pt Referencia al puntero al nodo que se va a rotar.
 */
void leftRotate(RBNode*& root, RBNode*& pt) {
    RBNode* pt_right = pt->right;
    pt->right = pt_right->left;

    if (pt->right != NULL)
        pt->right->parent = pt;

    pt_right->parent = pt->parent;

    if (pt->parent == NULL)
        root = pt_right;
    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;
    else
        pt->parent->right = pt_right;

    pt_right->left = pt;
    pt->parent = pt_right;
}


/**
 * @brief Realiza una rotación a la derecha sobre el subárbol con raíz en pt en un árbol rojo-negro.
 * 
 * @param root Referencia al puntero a la raíz del árbol rojo-negro.
 * @param pt Referencia al puntero al nodo que se va a rotar.
 */
void rightRotate(RBNode*& root, RBNode*& pt) {
    RBNode* pt_left = pt->left;   // Almacena el hijo izquierdo de pt
    pt->left = pt_left->right;    // El hijo derecho de pt_left se convierte en el hijo izquierdo de pt

    // Actualiza el padre del nuevo hijo izquierdo de pt, si no es NULL
    if (pt->left != NULL)
        pt->left->parent = pt;

    pt_left->parent = pt->parent; // Actualiza el padre de pt_left

    // Actualiza la raíz del árbol o el hijo izquierdo/derecho del padre de pt
    if (pt->parent == NULL)
        root = pt_left;
    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;
    else
        pt->parent->right = pt_left;

    pt_left->right = pt;   // pt se convierte en el hijo derecho de pt_left
    pt->parent = pt_left;  // pt_left se convierte en el padre de pt
}


/**
 * @brief Realiza el reequilibrio después de la inserción de un nodo en un árbol rojo-negro.
 * 
 * @param root Referencia al puntero a la raíz del árbol rojo-negro.
 * @param pt Referencia al puntero al nodo recién insertado.
 */
void balanceInsert(RBNode*& root, RBNode*& pt) {
    RBNode* parent_pt = NULL;
    RBNode* grand_parent_pt = NULL;

    // Realiza el reequilibrio mientras el nodo insertado no sea la raíz, no sea negro y su padre sea rojo
    while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        if (parent_pt == grand_parent_pt->left) { // Caso 1: El padre de pt es el hijo izquierdo del abuelo de pt
            RBNode* uncle_pt = grand_parent_pt->right; // Tío de pt

            if (uncle_pt != NULL && uncle_pt->color == RED) { // Caso 1.1: El tío de pt es rojo
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt; // Mueve el punto de referencia al abuelo de pt
            } else { // Caso 1.2: El tío de pt es negro o NULL
                if (pt == parent_pt->right) { // Caso 1.2.1: pt es un hijo derecho
                    leftRotate(root, parent_pt); // Rotación a la izquierda sobre el padre de pt
                    pt = parent_pt; // Actualiza pt al padre original de pt
                    parent_pt = pt->parent; // Actualiza el padre de pt al abuelo original de pt
                }
                rightRotate(root, grand_parent_pt); // Rotación a la derecha sobre el abuelo de pt
                std::swap(parent_pt->color, grand_parent_pt->color); // Intercambia los colores del padre y el abuelo de pt
                pt = parent_pt; // Actualiza pt al padre original de pt
            }
        } else { // Caso 2: El padre de pt es el hijo derecho del abuelo de pt
            RBNode* uncle_pt = grand_parent_pt->left; // Tío de pt

            if (uncle_pt != NULL && uncle_pt->color == RED) { // Caso 2.1: El tío de pt es rojo
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt; // Mueve el punto de referencia al abuelo de pt
            } else { // Caso 2.2: El tío de pt es negro o NULL
                if (pt == parent_pt->left) { // Caso 2.2.1: pt es un hijo izquierdo
                    rightRotate(root, parent_pt); // Rotación a la derecha sobre el padre de pt
                    pt = parent_pt; // Actualiza pt al padre original de pt
                    parent_pt = pt->parent; // Actualiza el padre de pt al abuelo original de pt
                }
                leftRotate(root, grand_parent_pt); // Rotación a la izquierda sobre el abuelo de pt
                std::swap(parent_pt->color, grand_parent_pt->color); // Intercambia los colores del padre y el abuelo de pt
                pt = parent_pt; // Actualiza pt al padre original de pt
            }
        }
    }
    root->color = BLACK; // La raíz siempre debe ser negra
}


/**
 * @brief Inserta un nuevo nodo con un valor dado en un árbol rojo-negro y realiza el reequilibrio necesario.
 * 
 * @param root Puntero a la raíz del árbol rojo-negro.
 * @param val Valor del nuevo nodo que se va a insertar.
 * @return RBNode* Puntero a la raíz del árbol rojo-negro después de la inserción y el reequilibrio.
 */
RBNode* insertRB(RBNode* root, int val) {
    RBNode* pt = new RBNode(val);

    if (root == NULL) {
        pt->color = BLACK; // Si la raíz es NULL, el nuevo nodo se convierte en la raíz y se establece como negro
        return pt;
    }

    RBNode* current = root;
    RBNode* parent = NULL;

    while (current != NULL) { // Encuentra el lugar adecuado para insertar el nuevo nodo
        parent = current;
        if (pt->val < current->val)
            current = current->left;
        else if (pt->val > current->val)
            current = current->right;
        else
            return root; // Los duplicados no están permitidos
    }

    pt->parent = parent;
    if (pt->val < parent->val)
        parent->left = pt;
    else
        parent->right = pt;

    balanceInsert(root, pt); // Realiza el reequilibrio después de la inserción

    return root;
}


/**
 * @brief Convierte un árbol binario de búsqueda (BST) en un árbol rojo-negro.
 * 
 * @param root Puntero a la raíz del BST que se va a convertir.
 * @return RBNode* Puntero a la raíz del árbol rojo-negro.
 */
RBNode* convertToRB(TreeNode* root) {
    if (root == NULL) return NULL;
    
    std::vector<int> nodes;
    std::queue<TreeNode*> q;
    q.push(root);

    // Realiza un recorrido en anchura (BFS) del BST y almacena los valores de los nodos en un vector
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        nodes.push_back(node->val);
        if (node->left != NULL) q.push(node->left);
        if (node->right != NULL) q.push(node->right);
    }

    RBNode* rbRoot = NULL;
    for (int val : nodes) {
        rbRoot = insertRB(rbRoot, val); // Inserta los valores del vector en un árbol rojo-negro utilizando la función insertRB
    }
    return rbRoot; // Retorna la raíz del árbol rojo-negro
}


/**
 * @brief Imprime los valores de los nodos de un árbol rojo-negro y sus colores.
 * 
 * @param root Puntero a la raíz del árbol rojo-negro.
 */
void printRBTree(RBNode* root) {
    if (root == NULL) return;
    
    std::queue<RBNode*> q;
    q.push(root);
    
    // Realiza un recorrido en anchura (BFS) del árbol rojo-negro e imprime los valores y colores de los nodos
    while (!q.empty()) {
        RBNode* node = q.front();
        q.pop();
        std::cout << node->val << (node->color == RED ? "R " : "B "); // Imprime el valor y el color del nodo
        if (node->left != NULL) q.push(node->left);
        if (node->right != NULL) q.push(node->right);
    }
    std::cout << std::endl;
}

/**
 * @brief Imprime los valores de los nodos de un árbol binario.
 * 
 * @param root Puntero a la raíz del árbol binario.
 */
void printTree(TreeNode* root) {
    if (root == NULL) return;
    
    std::queue<TreeNode*> q;
    q.push(root);
    
    // Realiza un recorrido en anchura (BFS) del árbol binario e imprime los valores de los nodos
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        std::cout << node->val << " "; // Imprime el valor del nodo
        if (node->left != NULL) q.push(node->left);
        if (node->right != NULL) q.push(node->right);
    }
    std::cout << std::endl;
}

/**
 * @brief Genera un archivo .dot representando el árbol binario en formato DOT.
 * 
 * @param root Puntero a la raíz del árbol binario.
 * @param file Referencia a un objeto de archivo de salida.
 */
void generateDot(TreeNode* root, std::ofstream& file) {
    if (root == NULL) return;
    
    std::queue<TreeNode*> q;
    q.push(root);
    
    // Realiza un recorrido en anchura (BFS) del árbol binario y escribe las relaciones entre nodos en el archivo .dot
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        if (node->left != NULL) {
            file << "    " << node->val << " -> " << node->left->val << ";\n"; // Escribe la relación entre el nodo actual y su hijo izquierdo en el archivo .dot
            q.push(node->left);
        }
        if (node->right != NULL) {
            file << "    " << node->val << " -> " << node->right->val << ";\n"; // Escribe la relación entre el nodo actual y su hijo derecho en el archivo .dot
            q.push(node->right);
        }
    }
}


/**
 * @brief Genera un archivo .dot representando el árbol rojo-negro en formato DOT.
 * 
 * @param root Puntero a la raíz del árbol rojo-negro.
 * @param file Referencia a un objeto de archivo de salida.
 */
void generateDot(RBNode* root, std::ofstream& file) {
    if (root == NULL) return;
    
    std::queue<RBNode*> q;
    q.push(root);
    
    // Realiza un recorrido en anchura (BFS) del árbol rojo-negro y escribe los nodos y relaciones en el archivo .dot
    while (!q.empty()) {
        RBNode* node = q.front();
        q.pop();
        file << "    " << node->val << " [style=filled, fillcolor="
             << (node->color == RED ? "red" : "gray") << "];\n"; // Escribe el nodo con su respectivo color en el archivo .dot
        if (node->left != NULL) {
            file << "    " << node->val << " -> " << node->left->val << ";\n"; // Escribe la relación entre el nodo actual y su hijo izquierdo en el archivo .dot
            q.push(node->left);
        }
        if (node->right != NULL) {
            file << "    " << node->val << " -> " << node->right->val << ";\n"; // Escribe la relación entre el nodo actual y su hijo derecho en el archivo .dot
            q.push(node->right);
        }
    }
}


/**
 * @brief Genera un archivo .dot representando un árbol binario de búsqueda (BST).
 * 
 * @param root Puntero a la raíz del árbol binario de búsqueda.
 * @param filename Nombre del archivo .dot a generar.
 */
void printBSTTreeDot(TreeNode* root, const std::string& filename) {
    std::ofstream file(filename); // Abre el archivo de salida
    file << "digraph BST {\n"; // Escribe la cabecera del archivo .dot para un árbol binario de búsqueda
    generateDot(root, file); // Genera el contenido del árbol binario de búsqueda en el archivo .dot
    file << "}\n"; // Escribe el cierre del archivo .dot
    file.close(); // Cierra el archivo
}

/**
 * @brief Genera un archivo .dot representando un árbol AVL.
 * 
 * @param root Puntero a la raíz del árbol AVL.
 * @param filename Nombre del archivo .dot a generar.
 */
void printAVLTreeDot(TreeNode* root, const std::string& filename) {
    std::ofstream file(filename); // Abre el archivo de salida
    file << "digraph AVL {\n"; // Escribe la cabecera del archivo .dot para un árbol AVL
    generateDot(root, file); // Genera el contenido del árbol AVL en el archivo .dot
    file << "}\n"; // Escribe el cierre del archivo .dot
    file.close(); // Cierra el archivo
}

/**
 * @brief Genera un archivo .dot representando un árbol rojo-negro.
 * 
 * @param root Puntero a la raíz del árbol rojo-negro.
 * @param filename Nombre del archivo .dot a generar.
 */
void printRBTreeDot(RBNode* root, const std::string& filename) {
    std::ofstream file(filename); // Abre el archivo de salida
    file << "digraph RBTree {\n"; // Escribe la cabecera del archivo .dot para un árbol rojo-negro
    generateDot(root, file); // Genera el contenido del árbol rojo-negro en el archivo .dot
    file << "}\n"; // Escribe el cierre del archivo .dot
    file.close(); // Cierra el archivo
}


// PARTE DE GRAFOS -------------------------------------------------------------------------------------------------------------------------
// Estructura para representar un grafo
/**
 * @brief Estructura para representar un grafo mediante una matriz de adyacencia.
 */
struct Graph {
    vector<vector<int>> adjacencyMatrix; ///< Matriz de adyacencia del grafo.
};

/**
 * @brief Estructura para representar una arista con origen, destino y peso.
 */
struct Edge {
    int src;    ///< Nodo de origen de la arista.
    int dest;   ///< Nodo de destino de la arista.
    int weight; ///< Peso de la arista.
};

/**
 * @brief Imprime una matriz de adyacencia en la consola.
 * 
 * @param matrix La matriz de adyacencia a imprimir.
 */
void printAdjacencyMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            cout << value << " "; // Imprime el valor de cada celda de la matriz
        }
        cout << endl; // Salta a la siguiente línea después de imprimir una fila completa
    }
}

/**
 * @brief Lee una matriz de adyacencia desde un archivo de texto.
 * 
 * @param filename Nombre del archivo de texto que contiene la matriz de adyacencia.
 * @return vector<vector<int>> Matriz de adyacencia leída desde el archivo.
 */
vector<vector<int>> readAdjacencyMatrixFromFile(const string& filename) {
    vector<vector<int>> matrix; // Inicializa una matriz vacía para almacenar los datos del archivo
    ifstream file(filename); // Abre el archivo de texto para lectura
    if (file.is_open()) { // Verifica si el archivo se ha abierto correctamente
        string line;
        while (getline(file, line)) { // Lee cada línea del archivo
            stringstream ss(line); // Crea un stringstream para analizar la línea
            vector<int> row; // Inicializa un vector para almacenar los valores de una fila
            int value;
            while (ss >> value) { // Lee cada valor separado por espacios en la línea
                row.push_back(value); // Agrega el valor al vector de fila
                if (ss.peek() == ',') // Ignora las comas que separan los valores si existen
                    ss.ignore();
            }
            matrix.push_back(row); // Agrega la fila a la matriz
        }
        file.close(); // Cierra el archivo después de leer todos los datos
    } else {
        cerr << "Error: No se pudo abrir el archivo." << endl; // Imprime un mensaje de error si no se puede abrir el archivo
    }
    return matrix; // Devuelve la matriz de adyacencia leída desde el archivo
}

/**
 * @brief Lee un grafo desde un archivo de texto.
 * 
 * @param filename Nombre del archivo de texto que contiene el grafo.
 * @return Graph Grafo leído desde el archivo.
 */
Graph readGraphFromFile(const string& filename) {
    Graph graph; // Inicializa un objeto de grafo
    graph.adjacencyMatrix = readAdjacencyMatrixFromFile(filename); // Lee la matriz de adyacencia desde el archivo
    return graph; // Devuelve el grafo leído desde el archivo
}


/**
 * @brief Genera y guarda un archivo DOT para un grafo.
 * 
 * @param graph El grafo para el cual se generará el archivo DOT.
 * @param filename Nombre del archivo DOT a guardar.
 * @param isDirectedWeighted Booleano que indica si el grafo es dirigido y ponderado.
 */
void generateDotFile(const Graph& graph, const string& filename, bool isDirectedWeighted) {
    ofstream dotFile(filename); // Abre el archivo DOT para escritura
    if (dotFile.is_open()) { // Verifica si el archivo se ha abierto correctamente
        if (isDirectedWeighted) { // Si el grafo es dirigido y ponderado
            dotFile << "digraph G {" << endl; // Escribe la cabecera para un grafo dirigido
            for (int i = 0; i < graph.adjacencyMatrix.size(); ++i) { // Itera sobre cada fila de la matriz de adyacencia
                for (int j = 0; j < graph.adjacencyMatrix[i].size(); ++j) { // Itera sobre cada elemento de la fila
                    if (graph.adjacencyMatrix[i][j] != 0) { // Si hay un peso diferente de cero en la posición (i, j)
                        dotFile << i << " -> " << j << " [label=\"" << graph.adjacencyMatrix[i][j] << "\"];" << endl; // Escribe la relación con el peso como etiqueta
                    }
                }
            }
            dotFile << "}"; // Escribe el cierre del grafo dirigido
        } else { // Si el grafo es no dirigido y ponderado
            dotFile << "graph G {" << endl; // Escribe la cabecera para un grafo no dirigido
            for (int i = 0; i < graph.adjacencyMatrix.size(); ++i) { // Itera sobre cada fila de la matriz de adyacencia
                for (int j = i + 1; j < graph.adjacencyMatrix[i].size(); ++j) { // Itera sobre los elementos de la mitad superior de la matriz
                    if (graph.adjacencyMatrix[i][j] != 0) { // Si hay un peso diferente de cero en la posición (i, j)
                        dotFile << i << " -- " << j << " [label=\"" << graph.adjacencyMatrix[i][j] << "\"];" << endl; // Escribe la relación con el peso como etiqueta
                    }
                }
            }
            dotFile << "}"; // Escribe el cierre del grafo no dirigido
        }
        dotFile.close(); // Cierra el archivo después de escribir
    } else {
        cerr << "Error: No se pudo abrir el archivo DOT para escritura." << endl; // Imprime un mensaje de error si no se puede abrir el archivo
    }
}

/**
 * @brief Algoritmo de Floyd-Warshall para encontrar todas las distancias más cortas entre todos los pares de vértices.
 * 
 * @param graph El grafo para el cual se calcularán las distancias más cortas.
 */
void floydWarshall(const Graph& graph) {
    int V = graph.adjacencyMatrix.size(); // Número de vértices en el grafo
    vector<vector<int>> dist(V, vector<int>(V, numeric_limits<int>::max())); // Matriz de distancias inicializada con infinito

    // Inicializar la matriz de distancias con los pesos de las aristas
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            dist[i][j] = graph.adjacencyMatrix[i][j]; // Asignar el peso de la arista si hay una conexión, o infinito si no hay conexión
        }
    }
// Imprimir las distancias mínimas entre todos los pares de vértices
cout << "Distancias mínimas entre todos los pares de vértices (Floyd-Warshall):" << endl;
for (int i = 0; i < V; ++i) {
    for (int j = 0; j < V; ++j) {
        if (dist[i][j] == numeric_limits<int>::max())
            cout << "INF "; // Si la distancia es infinita, imprime "INF"
        else
            cout << dist[i][j] << " "; // Imprime la distancia mínima entre los vértices i y j
    }
    cout << endl; // Salto de línea después de imprimir una fila completa
}

// Generar archivo DOT para visualizar el resultado de Floyd-Warshall
ofstream dotFile("floyd_warshall.dot"); // Abre un archivo DOT para escritura
if (dotFile.is_open()) { // Verifica si el archivo se ha abierto correctamente
    dotFile << "graph G {" << endl; // Escribe la cabecera para un grafo no dirigido
    for (int i = 0; i < V; ++i) { // Itera sobre cada fila de la matriz de distancias
        for (int j = 0; j < V; ++j) { // Itera sobre cada elemento de la fila
            if (dist[i][j] != numeric_limits<int>::max() && i != j) { // Si la distancia es finita y los vértices no son el mismo
                dotFile << i << " -- " << j << " [label=\"" << dist[i][j] << "\"];" << endl; // Escribe la relación con la distancia como etiqueta
            }
        }
    }
    dotFile << "}" << endl; // Escribe el cierre del grafo no dirigido
    dotFile.close(); // Cierra el archivo después de escribir
    cout << "Archivo DOT generado para Floyd-Warshall: floyd_warshall.dot" << endl; // Imprime un mensaje de confirmación
}

// Función para verificar si el archivo DOT se ha generado correctamente y generar la imagen PNG correspondiente
void checkAndGenerateImage() {
    ifstream checkFile("floyd_warshall.dot"); // Abre el archivo DOT para verificar su existencia
    if (checkFile.is_open()) { // Verifica si el archivo DOT se ha abierto correctamente
        checkFile.close(); // Cierra el archivo después de verificar
        // Genera la imagen PNG a partir del archivo DOT
        if (system("dot -Tpng floyd_warshall.dot -o floyd_warshall.png") == 0) { // Ejecuta el comando DOT para convertir el archivo DOT en PNG
            cout << "Imagen de Floyd-Warshall generada como 'floyd_warshall.png'." << endl; // Imprime un mensaje de confirmación si se genera correctamente
            system("start floyd_warshall.png"); // Abre la imagen generada con el visor de imágenes predeterminado
        } else {
            cerr << "Error: No se pudo generar la imagen de Floyd-Warshall." << endl; // Imprime un mensaje de error si no se puede generar la imagen
        }
    } else {
        cerr << "Error: El archivo DOT de Floyd-Warshall no se generó correctamente." << endl; // Imprime un mensaje de error si el archivo DOT no se ha generado correctamente
    }
}

// Función para el algoritmo de Dijkstra
void dijkstra(const Graph& graph, int startNode) {
    int numNodes = graph.adjacencyMatrix.size(); // Número de nodos en el grafo
    vector<int> dist(numNodes, numeric_limits<int>::max()); // Vector para almacenar las distancias mínimas desde el nodo inicial hasta cada nodo
    vector<bool> visited(numNodes, false); // Vector para realizar un seguimiento de los nodos visitados durante el proceso

    dist[startNode] = 0; // La distancia del nodo inicial a sí mismo es 0

    for (int count = 0; count < numNodes - 1; ++count) {
        int minDist = numeric_limits<int>::max(); // Inicializa la distancia mínima con un valor máximo
        int minIndex = -1; // Índice del nodo con la distancia mínima

        // Encontrar el nodo no visitado con la distancia mínima
        for (int i = 0; i < numNodes; ++i) {
            if (!visited[i] && dist[i] < minDist) { // Si el nodo no se ha visitado y su distancia es menor que la distancia mínima actual
                minDist = dist[i]; // Actualiza la distancia mínima
                minIndex = i; // Actualiza el índice del nodo con la distancia mínima
            }
        }

        if (minIndex == -1)
            break; // Si no se encuentra un nodo con distancia mínima válida, se detiene el bucle

        visited[minIndex] = true; // Marca el nodo seleccionado como visitado

        // Actualizar las distancias de los nodos adyacentes al nodo seleccionado
        for (int i = 0; i < numNodes; ++i) {
            if (!visited[i] && graph.adjacencyMatrix[minIndex][i] && 
                dist[minIndex] != numeric_limits<int>::max() &&
                dist[minIndex] + graph.adjacencyMatrix[minIndex][i] < dist[i]) { // Si el nodo no se ha visitado, hay una conexión entre los nodos y
                                                                                  // la distancia actual es finita, y la suma de la distancia desde el nodo inicial al nodo seleccionado
                                                                                  // y la distancia desde el nodo seleccionado al nodo adyacente es menor que la distancia actual al nodo adyacente
                dist[i] = dist[minIndex] + graph.adjacencyMatrix[minIndex][i]; // Actualiza la distancia al nodo adyacente
            }
        }
    }
}


 // Función para imprimir las distancias mínimas desde el nodo inicial según el algoritmo de Dijkstra
void printDijkstraDistances(const vector<int>& dist, int startNode, int numNodes) {
    cout << "Distancias mínimas desde el nodo " << startNode << " (Dijkstra):" << endl; // Imprime un encabezado indicando el nodo inicial
    for (int i = 0; i < numNodes; ++i) { // Itera sobre cada nodo
        cout << "Nodo " << i << ": " << dist[i] << endl; // Imprime la distancia mínima desde el nodo inicial al nodo actual
    }
}

// Función para generar el archivo DOT para visualizar el resultado del algoritmo de Dijkstra
void generateDijkstraDotFile(const vector<int>& dist, int startNode, int numNodes) {
    ofstream dotFile("dijkstra.dot"); // Abre un archivo DOT para escribir
    if (dotFile.is_open()) { // Verifica si el archivo DOT se ha abierto correctamente
        dotFile << "graph G {" << endl; // Escribe la cabecera para un grafo no dirigido
        for (int i = 0; i < numNodes; ++i) { // Itera sobre cada nodo
            if (dist[i] != numeric_limits<int>::max() && i != startNode) { // Si la distancia al nodo es finita y no es el nodo inicial
                dotFile << startNode << " -- " << i << " [label=\"" << dist[i] << "\"];" << endl; // Escribe la relación con la distancia como etiqueta
            }
        }
        dotFile << "}" << endl; // Escribe el cierre del grafo no dirigido
        dotFile.close(); // Cierra el archivo después de escribir
        cout << "Archivo DOT generado para Dijkstra: dijkstra.dot" << endl; // Imprime un mensaje de confirmación
        // Verificar si el archivo DOT se ha generado correctamente
        ifstream checkFile("dijkstra.dot"); // Abre el archivo DOT para verificar su existencia
        if (checkFile.is_open()) { // Verifica si el archivo DOT se ha abierto correctamente
            checkFile.close(); // Cierra el archivo después de verificar
            // Generar la imagen PNG a partir del archivo DOT
            if (system("dot -Tpng dijkstra.dot -o dijkstra.png") == 0) { // Ejecuta el comando DOT para convertir el archivo DOT en PNG
                cout << "Imagen de Dijkstra generada como 'dijkstra.png'." << endl; // Imprime un mensaje de confirmación si se genera correctamente
                system("start dijkstra.png"); // Abre la imagen generada con el visor de imágenes predeterminado
            } else {
                cerr << "Error: No se pudo generar la imagen de Dijkstra." << endl; // Imprime un mensaje de error si no se puede generar la imagen
            }
        } else {
            cerr << "Error: El archivo DOT de Dijkstra no se generó correctamente." << endl; // Imprime un mensaje de error si el archivo DOT no se ha generado correctamente
        }
    } else {
        cerr << "Error: No se pudo abrir el archivo DOT para escribir." << endl; // Imprime un mensaje de error si no se puede abrir el archivo DOT
    }
}

// Función para encontrar la raíz del conjunto al que pertenece un nodo en la estructura de conjuntos disjuntos (Union-Find)
int find(vector<int>& parent, int i) {
    if (parent[i] == -1) // Si el nodo es la raíz del conjunto, devuelve el índice del nodo
        return i;
    return find(parent, parent[i]); // Si no es la raíz del conjunto, busca recursivamente la raíz del conjunto al que pertenece
}


// Función para unir dos conjuntos en un solo conjunto
void unionSets(vector<int>& parent, int x, int y) {
    int xSet = find(parent, x); // Encuentra el conjunto al que pertenece el nodo x
    int ySet = find(parent, y); // Encuentra el conjunto al que pertenece el nodo y
    parent[xSet] = ySet; // Une ambos conjuntos estableciendo el padre del conjunto de x como el conjunto de y
}

// Función para comparar el peso de dos aristas
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight; // Compara las aristas basándose en el peso, para ordenarlas de menor a mayor
}

// Algoritmo de Kruskal para encontrar un árbol de expansión mínima en un grafo ponderado y no dirigido
void kruskal(const Graph& graph) {
    int V = graph.adjacencyMatrix.size(); // Número de nodos en el grafo
    vector<Edge> result(V - 1); // El árbol de expansión mínima tendrá (V - 1) aristas
    vector<int> parent(V, -1); // Vector de padres para representar los conjuntos disjuntos

    vector<Edge> edges; // Lista de aristas ordenadas por peso
    for (int i = 0; i < V; ++i) {
        for (int j = i + 1; j < V; ++j) {
            if (graph.adjacencyMatrix[i][j] != 0) { // Si hay una arista entre los nodos i y j
                edges.push_back({i, j, graph.adjacencyMatrix[i][j]}); // Agrega la arista a la lista con su peso
            }
        }
    }
    // Ordenar las aristas por peso
    sort(edges.begin(), edges.end(), compareEdges);

    int edgeCount = 0; // Contador de aristas agregadas al árbol de expansión mínima
    int i = 0;
    // Itera sobre las aristas ordenadas por peso
    while (edgeCount < V - 1 && i < edges.size()) {
        Edge nextEdge = edges[i++]; // Obtiene la siguiente arista en orden de peso
        int x = find(parent, nextEdge.src); // Encuentra el conjunto al que pertenece el nodo fuente de la arista
        int y = find(parent, nextEdge.dest); // Encuentra el conjunto al que pertenece el nodo destino de la arista
        if (x != y) { // Si los nodos no pertenecen al mismo conjunto (no forman un ciclo)
            result[edgeCount++] = nextEdge; // Agrega la arista al árbol de expansión mínima
            unionSets(parent, x, y); // Une los conjuntos de los nodos fuente y destino
        }
    }
}


   // Algoritmo de Kruskal para encontrar un árbol de expansión mínima en un grafo ponderado y no dirigido
void kruskal(const Graph& graph) {
    int V = graph.adjacencyMatrix.size(); // Número de nodos en el grafo
    vector<Edge> result(V - 1); // El árbol de expansión mínima tendrá (V - 1) aristas
    vector<int> parent(V, -1); // Vector de padres para representar los conjuntos disjuntos

    vector<Edge> edges; // Lista de aristas ordenadas por peso
    for (int i = 0; i < V; ++i) {
        for (int j = i + 1; j < V; ++j) {
            if (graph.adjacencyMatrix[i][j] != 0) { // Si hay una arista entre los nodos i y j
                edges.push_back({i, j, graph.adjacencyMatrix[i][j]}); // Agrega la arista a la lista con su peso
            }
        }
    }
    // Ordenar las aristas por peso
    sort(edges.begin(), edges.end(), compareEdges);

    int edgeCount = 0; // Contador de aristas agregadas al árbol de expansión mínima
    int i = 0;
    // Itera sobre las aristas ordenadas por peso
    while (edgeCount < V - 1 && i < edges.size()) {
        Edge nextEdge = edges[i++]; // Obtiene la siguiente arista en orden de peso
        int x = find(parent, nextEdge.src); // Encuentra el conjunto al que pertenece el nodo fuente de la arista
        int y = find(parent, nextEdge.dest); // Encuentra el conjunto al que pertenece el nodo destino de la arista
        if (x != y) { // Si los nodos no pertenecen al mismo conjunto (no forman un ciclo)
            result[edgeCount++] = nextEdge; // Agrega la arista al árbol de expansión mínima
            unionSets(parent, x, y); // Une los conjuntos de los nodos fuente y destino
        }
    }

    // Imprimir el árbol de expansión mínima
    cout << "Árbol de expansión mínima (Kruskal):" << endl;
    for (int i = 0; i < V - 1; ++i) {
        cout << result[i].src << " -- " << result[i].dest << " [peso=" << result[i].weight << "]" << endl;
    }

    // Generar archivo DOT para visualizar el resultado de Kruskal
    ofstream dotFile("kruskal.dot");
    if (dotFile.is_open()) {
        dotFile << "graph G {" << endl;
        for (int i = 0; i < V - 1; ++i) {
            dotFile << result[i].src << " -- " << result[i].dest << " [label=\"" << result[i].weight << "\"];" << endl;
        }
        dotFile << "}" << endl;
        dotFile.close();
        cout << "Archivo DOT generado para Kruskal: kruskal.dot" << endl;

        // Verificar si el archivo DOT se ha generado correctamente
        ifstream checkFile("kruskal.dot");
        if (checkFile.is_open()) {
            checkFile.close();
            // Generar la imagen PNG a partir del archivo DOT
            if (system("dot -Tpng kruskal.dot -o kruskal.png") == 0) {
                cout << "Imagen de Kruskal generada como 'kruskal.png'." << endl;
                system("start kruskal.png"); // Abre la imagen en el visor de imágenes predeterminado
            } else {
                cerr << "Error: No se pudo generar la imagen de Kruskal." << endl;
            }
        } else {
            cerr << "Error: El archivo DOT de Kruskal no se generó correctamente." << endl;
        }
    } else {
        cerr << "Error: No se pudo abrir el archivo DOT para escribir." << endl;
    }
}


// Algoritmo de Prim para encontrar un árbol de expansión mínima en un grafo ponderado y no dirigido
void prim(const Graph& graph) {
    int V = graph.adjacencyMatrix.size(); // Número de nodos en el grafo
    vector<int> key(V, numeric_limits<int>::max()); // Vector para almacenar las claves de los nodos
    vector<bool> inMST(V, false); // Vector para marcar los nodos que ya están en el árbol de expansión mínima
    vector<int> parent(V, -1); // Vector para almacenar los padres de los nodos en el árbol de expansión mínima
    key[0] = 0; // La clave del primer nodo es 0 (seleccionado como nodo inicial)

    // Itera sobre todos los nodos del grafo
    for (int count = 0; count < V - 1; ++count) {
        int minKey = numeric_limits<int>::max(); // Inicializa la clave mínima
        int u = -1; // Inicializa el índice del nodo con la clave mínima

        // Encuentra el nodo con la clave mínima que no está en el árbol de expansión mínima
        for (int v = 0; v < V; ++v) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        inMST[u] = true; // Marca el nodo seleccionado como parte del árbol de expansión mínima

        // Actualiza las claves y los padres de los nodos adyacentes al nodo seleccionado
        for (int v = 0; v < V; ++v) {
            if (graph.adjacencyMatrix[u][v] && !inMST[v] && graph.adjacencyMatrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph.adjacencyMatrix[u][v];
            }
        }
    }

    // Imprimir el árbol de expansión mínima
    cout << "Árbol de expansión mínima (Prim):" << endl;
    for (int i = 1; i < V; ++i) {
        cout << parent[i] << " -- " << i << " [peso=" << graph.adjacencyMatrix[i][parent[i]] << "]" << endl;
    }

    // Generar archivo DOT para visualizar el resultado de Prim
    ofstream dotFile("prim.dot");
    if (dotFile.is_open()) {
        dotFile << "graph G {" << endl;
        for (int i = 1; i < V; ++i) {
            dotFile << parent[i] << " -- " << i << " [label=\"" << graph.adjacencyMatrix[i][parent[i]] << "\"];" << endl;
        }
        dotFile << "}" << endl;
        dotFile.close();
        cout << "Archivo DOT generado para Prim: prim.dot" << endl;

        // Verificar si el archivo DOT se ha generado correctamente
        ifstream checkFile("prim.dot");
        if (checkFile.is_open()) {
            checkFile.close();
            // Generar la imagen PNG a partir del archivo DOT
            if (system("dot -Tpng prim.dot -o prim.png") == 0) {
                cout << "Imagen de Prim generada como 'prim.png'." << endl;
                system("start prim.png"); // Abre la imagen en el visor de imágenes predeterminado
            } else {
                cerr << "Error: No se pudo generar la imagen de Prim." << endl;
            }
        } else {
            cerr << "Error: El archivo DOT de Prim no se generó correctamente." << endl;
        }
    } else {
        cerr << "Error: No se pudo abrir el archivo DOT para escribir." << endl;
    }
}

// INT MAIn

int main() {
    int opcion;
    do {
        cout << "\nMenu Principal\n" << endl;
        cout << "1. Presentar ABB Autobalanceados" << endl;
        cout << "2. Presentar Grafos" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                // Submenú para Árboles
                TreeNode* root = NULL;
                char subopcion;
                do {
                    cout << "\nSubmenu para Arboles Binarios de Busqueda Autobalanceados\n";
                    cout << "a. Ingrese la lista de nodos y el recorrido para construir el arbol\n";
                    cout << "b. Mostrar de forma visual el arbol inicial (indica si el arbol es AVL o no)\n";
                    cout << "c. Convertir en AVL el arbol inicial y mostrar la visualizacion del arbol\n";
                    cout << "d. Convertir en arbol Rojo y Negro el arbol inicial y mostrar la visualizacion del arbol\n";
                    cout << "e. Volver al menu principal\n";
                    cout << "Seleccione una opcion: ";
                    cin >> subopcion;

                    switch (subopcion) {
                        case 'a': {
                            int n, val;
                            cout << "Ingrese el numero de nodos: ";
                            cin >> n;
                            cout << "Ingrese los valores de los nodos: ";
                            for (int i = 0; i < n; ++i) {
                                cin >> val;
                                root = insertBST(root, val);
                            }
                            break;
                        }
                        case 'b': {
                            cout << "Arbol inicial (nivel por nivel):\n";
                            printTree(root);
                            printBSTTreeDot(root, "bst_tree.dot");
                            cout << "El arbol " << (isAVL(root) ? "es" : "no es") << " un AVL.\n";
                            cout << "Archivo DOT para el arbol inicial generado como 'bst_tree.dot'.\n";
                            system("dot -Tpng bst_tree.dot -o bst_tree.png");
                            cout << "Imagen del arbol inicial generada como 'bst_tree.png'.\n";
                            system("start bst_tree.png");
                            break;
                        }
                        case 'c': {
                            TreeNode* avlRoot = convertToAVL(root);
                            cout << "Arbol convertido a AVL (nivel por nivel):\n";
                            printTree(avlRoot);
                            printAVLTreeDot(avlRoot, "avl_tree.dot");
                            cout << "Archivo DOT para AVL generado como 'avl_tree.dot'.\n";
                            system("dot -Tpng avl_tree.dot -o avl_tree.png");
                            cout << "Imagen del arbol AVL generada como 'avl_tree.png'.\n";
                            system("start avl_tree.png");
                            break;
                        }
                        case 'd': {
                            RBNode* rbRoot = convertToRB(root);
                            cout << "Arbol convertido a Rojo-Negro (nivel por nivel):\n";
                            printRBTree(rbRoot);
                            printRBTreeDot(rbRoot, "rb_tree.dot");
                            cout << "Archivo DOT para Rojo-Negro generado como 'rb_tree.dot'.\n";
                            system("dot -Tpng rb_tree.dot -o rb_tree.png");
                            cout << "Imagen del arbol Rojo-Negro generada como 'rb_tree.png'.\n";
                            system("start rb_tree.png"); // Abre la imagen en el visor de imágenes predeterminado
                            break;
                        }
                        case 'e': {
                            cout << "Volviendo al menu principal...\n";
                            break;
                        }
                        default: {
                            cout << "Opcion no valida. Por favor, ingrese una opcion valida.\n";
                            break;
                        }
                    }
                } while (subopcion != 'e');
                break;
            }
            case 2: {
                // Submenú para Grafos
                Graph graph;
                char subopcion;
                do {
                    cout << "\nSubmenu para Grafos\n";
                    cout << "a. Ingrese la matriz de adyacencias\n";
                    cout << "b. Mostrar la visualizacion del grafo inicial\n";
                    cout << "c. Elija un algoritmo para encontrar el camino mas corto\n";
                    cout << "d. Elija un algoritmo para encontrar arboles de peso minimo\n";
                    cout << "e. Volver al menu principal\n";
                    cout << "Seleccione una opcion: ";
                    cin >> subopcion;

                    switch (subopcion) {
                        case 'a': {
                            string filepath;
                            cout << "Ingrese la ruta absoluta del archivo de texto: ";
                            cin >> filepath;
                            graph.adjacencyMatrix = readAdjacencyMatrixFromFile(filepath);
                            break;
                        }
                        case 'b': {
    // Verificar si es un grafo dirigido ponderado
    bool isDirectedWeighted = false;
    for (int i = 0; i < graph.adjacencyMatrix.size(); ++i) {
        for (int j = 0; j < graph.adjacencyMatrix[i].size(); ++j) {
            if (graph.adjacencyMatrix[i][j] != graph.adjacencyMatrix[j][i]) {
                isDirectedWeighted = true;
                break;
            }
        }
        if (isDirectedWeighted) break;
    }

    // Si el grafo no es dirigido ponderado, verificamos si es no dirigido ponderado
    bool isUndirectedWeighted = false;
    if (!isDirectedWeighted) {
        isUndirectedWeighted = true;
        for (int i = 0; i < graph.adjacencyMatrix.size(); ++i) {
            for (int j = 0; j < graph.adjacencyMatrix[i].size(); ++j) {
                if (graph.adjacencyMatrix[i][j] != 0 && graph.adjacencyMatrix[i][j] != graph.adjacencyMatrix[j][i]) {
                    isUndirectedWeighted = false;
                    break;
                }
            }
            if (!isUndirectedWeighted) break;
        }
    }

    if (isDirectedWeighted) {
        cout << "El grafo es dirigido ponderado." << endl;
    } else if (isUndirectedWeighted) {
        cout << "El grafo es no dirigido ponderado." << endl;
    } else {
        cout << "El grafo es no dirigido no ponderado." << endl;
    }

    // Generar el archivo DOT con las flechas si es dirigido ponderado
    generateDotFile(graph, "graph.dot", isDirectedWeighted);

    ifstream checkFile("graph.dot");
    if (checkFile.is_open()) {
        checkFile.close();
        if (system("dot -Tpng graph.dot -o graph.png") == 0) {
            cout << "Imagen del grafo generada como 'graph.png'." << endl;
            system("start graph.png");
        } else {
            cerr << "Error: No se pudo generar la imagen del grafo." << endl;
        }
    } else {
        cerr << "Error: El archivo DOT no se generó correctamente." << endl;
    }
    break;
}

                        

                        case 'c': {
                            char subChoice;
                            do {
                                cout << "\nSubmenu para algoritmos de camino mas corto:\n" << endl;
                                cout << "a. Dijkstra" << endl;
                                cout << "b. Floyd-Warshall" << endl;
                                cout << "c. Volver al submenu para Grafos" << endl;
                                cout << "Ingrese su eleccion: ";
                                cin >> subChoice;
                                switch (subChoice) {
                                    case 'a': {
                                        int startNode;
                                        cout << "Ingrese el nodo inicial para Dijkstra: ";
                                        cin >> startNode;
                                        dijkstra(graph, startNode);
                                        break;
                                    }
                                    case 'b': {
                                        floydWarshall(graph);
                                        break;
                                    }
                                    case 'c': {
                                        cout << "Volviendo al submenu para Grafos" << endl;
                                        break;
                                    }
                                    default: {
                                        cout << "Opcion no valida. Por favor, ingrese una opcion valida." << endl;
                                        break;
                                    }
                                }
                            } while (subChoice != 'c');
                            break;
                        }
                        case 'd': {
                            char subChoice;
                            do {
                                cout << "\nSubmenu para algoritmos de arboles de peso minimo:\n" << endl;
                                cout << "a. Kruskal" << endl;
                                cout << "b. Prim" << endl;
                                cout << "c. Volver al submenu para Grafos" << endl;
                                cout << "Ingrese su eleccion: ";
                                cin >> subChoice;
                                switch (subChoice) {
                                    case 'a': {
                                        kruskal(graph);
                                        break;
                                    }
                                    case 'b': {
                                        prim(graph);
                                        break;
                                    }
                                    case 'c': {
                                        cout << "Volviendo al submenu para Grafos" << endl;
                                        break;
                                    }
                                    default: {
                                        cout << "Opcion no valida. Por favor, ingrese una opcion valida." << endl;
                                        break;
                                    }
                                }
                            } while (subChoice != 'c');
                            break;
                        }
                        case 'e': {
                            cout << "Volviendo al submenu para Grafos" << endl;
                            break;
                        }
                        default: {
                            cout << "Opcion no valida. Por favor, ingrese una opcion valida." << endl;
                            break;
                        }
                    }
                } while (subopcion != 'e');
                break;
            }
            case 3: {
                cout << "Saliendo..." << endl;
                break;
            }
            default: {
                cout << "Opcion no valida. Por favor, seleccione una opcion valida." << endl;
                break;
            }
        }
    } while (opcion != 3);

    return 0;
}
