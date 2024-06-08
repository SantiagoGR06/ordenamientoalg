Árboles
Un árbol es una estructura de datos jerárquica que consiste en nodos conectados por aristas. Los árboles se utilizan para representar estructuras en las que los elementos tienen una relación jerárquica, como los sistemas de archivos, las organizaciones empresariales, las expresiones matemáticas, etc.

Componentes de un Árbol
Nodo: La unidad básica de un árbol. Cada nodo puede tener un valor o dato y referencias a otros nodos (sus hijos).
Raíz: El nodo superior del árbol, el cual no tiene padre.
Hijo: Un nodo directamente descendiente de otro nodo.
Padre: Un nodo que tiene uno o más hijos.
Hoja: Un nodo que no tiene hijos.
Altura: La longitud del camino más largo desde la raíz hasta una hoja.
Subárbol: Un árbol que es parte de un árbol más grande.

Implementación de un Árbol Binario en C++
Un árbol binario es un tipo de árbol en el que cada nodo tiene como máximo dos hijos, denominados hijo izquierdo y hijo derecho.

aqui un resumen de lo que se encarga el codigo 
Tipos de Estructuras de Árbol:

Árbol Binario de Búsqueda (BST): Un árbol donde cada nodo tiene un valor, y para cualquier nodo dado, todos los valores en el subárbol izquierdo son menores y todos los valores en el subárbol derecho son mayores.
Árbol AVL: Un tipo especial de árbol binario de búsqueda que está balanceado, lo que significa que para cada nodo, la diferencia de altura entre el subárbol izquierdo y derecho no puede ser mayor que 1.
Árbol Rojo-Negro: Otro tipo de árbol binario de búsqueda que se auto-balancea, donde cada nodo tiene un color (rojo o negro) y sigue ciertas reglas para asegurar el balance.
Funciones para Trabajar con Árboles Binarios de Búsqueda (BST):

Altura: Calcula la altura de un árbol.
Verificar si es AVL: Comprueba si un árbol binario de búsqueda es también un árbol AVL.
Rotaciones: Funciones para rotar nodos a la derecha o izquierda, utilizadas para balancear el árbol AVL.
Balancear el Árbol AVL: Inserta nodos en un árbol AVL de manera que el árbol se mantenga balanceado.
Insertar en un BST: Inserta un nodo en el árbol BST siguiendo las reglas básicas (menores a la izquierda, mayores a la derecha).

Convertir un BST en un AVL: Recoge todos los nodos de un BST y los re-inserta en un árbol AVL para balancearlo.

Funciones para Trabajar con Árboles Rojo-Negro (RB):

Rotaciones: Funciones para rotar nodos a la derecha o izquierda, utilizadas para balancear el árbol RB.
Balancear después de la Inserción: Asegura que el árbol RB se mantenga balanceado y siga las reglas de color después de insertar un nuevo nodo.
Insertar en un Árbol Rojo-Negro: Inserta un nodo en el árbol RB y luego llama a la función de balanceo para mantener las propiedades del árbol RB.
Proceso General:

Insertar Nodos en un BST: Se puede insertar nodos en un BST de manera directa.
Convertir el BST a un AVL: Después de tener un BST, se puede convertir a un AVL reinsertando los nodos de manera que se mantenga el balance.
Insertar Nodos en un RB: Similar a la inserción en un BST, pero con balanceo adicional basado en las reglas de color y rotaciones para mantener el balance del árbol.

En esta sección mostraremos un ejemplo básico de implementación de un árbol binario en C++.

ARBOLES EJEMPLO: Un arbol NO AVL que ingresa el usuario y se balancea usando el case b del submenu de arboles y luego, se balancea de manera RB



![image](https://github.com/SantiagoGR06/proyectofinalestructura/assets/159094418/0a4bfc88-d263-4fb4-b5dc-eb2667359450)
![image](https://github.com/SantiagoGR06/proyectofinalestructura/assets/159094418/e96a4637-129a-4a80-8298-9b7e0bf8aeab)
![image](https://github.com/SantiagoGR06/proyectofinalestructura/assets/159094418/7a67e24b-ac7b-4d3e-aff2-3ea9a9831388)


Después de insertar el "30", hacemos una rotación a la izquierda en el nodo con valor "10"

![image](https://github.com/SantiagoGR06/proyectofinalestructura/assets/159094418/e3c26c07-1bbc-4f45-980d-1c17cf19934f)
![image](https://github.com/SantiagoGR06/proyectofinalestructura/assets/159094418/8f38199d-fc46-4ca8-98b0-acd6f34dcd99)

Después de insertar el "50", hacemos una rotación a la izquierda en el nodo con valor "30"

![image](https://github.com/SantiagoGR06/proyectofinalestructura/assets/159094418/05af9dbb-a07e-4760-845f-f42f2d33c576)

Después de insertar el "25", hacemos una rotación Derecha - Izquierda en el nodo con valor "20"


ARBOL RB: ejemplo de un arbol=[7, 3, 18, 10, 22, 8, 11, 26]

![image](https://github.com/SantiagoGR06/proyectofinalestructura/assets/159094418/1c81f951-8764-4adc-a283-5b24f76827c5)
![image](https://github.com/SantiagoGR06/proyectofinalestructura/assets/159094418/8b57ebb1-8f37-41ac-8300-a73db19f26a9)

Después de insertar "3", realiza Insertar en el nodo con valor "3"

![image](https://github.com/SantiagoGR06/proyectofinalestructura/assets/159094418/a7b46cff-30fb-4208-a5d0-7579001c1bcc)

Después de insertar "18", realiza Insertar en el nodo con valor "18".

![image](https://github.com/SantiagoGR06/proyectofinalestructura/assets/159094418/bb88db4c-ed70-4bc5-b45f-b5d95c8f5c5c)

Después de insertar "10", realiza Ajuste en el nodo con valor "7".

![image](https://github.com/SantiagoGR06/proyectofinalestructura/assets/159094418/59d448b5-e527-4cc1-8349-647ae3bfbe23)

Después de insertar !22", realiza Insertar en el nodo con valor "22".

![image](https://github.com/SantiagoGR06/proyectofinalestructura/assets/159094418/3bb8428e-8502-4889-8578-982019bc8bcd)

Después de insertar "8", realiza Ajuste en el nodo con valor "18".

![image](https://github.com/SantiagoGR06/proyectofinalestructura/assets/159094418/7df022f3-12e2-47ec-8197-98ec62fdcc01)

Después de insertar "11", realiza Insertar en el nodo con valor "11".

![image](https://github.com/SantiagoGR06/proyectofinalestructura/assets/159094418/1692379f-874c-41f9-a33c-707e1cd8d84e)

Después de insertar "26", realiza Insertar en el nodo con valor "26".

Los grafos son estructuras matemáticas utilizadas para modelar relaciones entre objetos. Un grafo consiste en un conjunto de nodos (también llamados vértices) y un conjunto de aristas (también llamadas arcos o enlaces) que conectan pares de nodos. Los grafos se utilizan en una variedad de campos, incluyendo informática, ingeniería, biología, ciencias sociales y más, para representar y analizar sistemas complejos de relaciones.

Componentes de un Grafo
Nodos (Vértices): Los puntos fundamentales de un grafo que representan entidades u objetos.
Aristas (Arcos o Enlaces): Las líneas que conectan pares de nodos y representan las relaciones entre ellos.
Tipos de Grafos
Grafo Dirigido (Digrafo): Las aristas tienen una dirección, es decir, van de un nodo a otro específico. Se representan comúnmente con flechas.

Ejemplo: Un grafo que modela un sistema de navegación GPS, donde las carreteras tienen direcciones específicas.
Grafo No Dirigido: Las aristas no tienen una dirección, es decir, la relación es bidireccional.

Ejemplo: Un grafo que representa las conexiones entre amigos en una red social, donde la amistad es mutua.
Grafo Ponderado: Las aristas tienen un peso asociado que representa el costo, la distancia, o alguna otra medida de la relación.

Ejemplo: Un grafo que modela un mapa de carreteras donde las aristas representan distancias entre ciudades.
Grafo No Ponderado: Las aristas no tienen peso y simplemente representan la presencia o ausencia de una relación.

![image](https://github.com/SantiagoGR06/proyectofinalestructura/assets/141601959/8b4c63a8-eea6-421d-92fd-aef5d199ceae)
![image](https://github.com/SantiagoGR06/proyectofinalestructura/assets/141601959/73846080-7549-4b29-8f96-1190b09f0155)


Funcionalidades
Árboles Binarios de Búsqueda Autobalanceados
Inserción de nodos en un ABB:

Permite al usuario ingresar una lista de nodos para construir un ABB.
Visualización del ABB inicial:

Muestra el ABB ingresado y verifica si es un AVL.
Conversión a AVL:

Convierte el ABB inicial a un Árbol AVL y lo visualiza.
Conversión a Árbol Rojo-Negro:

Convierte el ABB inicial a un Árbol Rojo-Negro y lo visualiza.
Grafos
Ingreso de la matriz de adyacencias:

Permite al usuario ingresar una matriz de adyacencias desde un archivo.
Visualización del grafo inicial:

Genera un archivo DOT y una imagen PNG para visualizar el grafo.
Algoritmos de caminos más cortos:

Dijkstra: Encuentra los caminos más cortos desde un nodo inicial.
Floyd-Warshall: Encuentra los caminos más cortos entre todos los pares de nodos.
Algoritmos de árboles de expansión mínima:

Kruskal: Encuentra el árbol de expansión mínima usando el algoritmo de Kruskal.
Prim: Encuentra el árbol de expansión mínima usando el algoritmo de Prim.

Archivos DOT y Visualización
El programa genera archivos DOT para visualizar los árboles y grafos. Estos archivos se pueden convertir a imágenes PNG usando Graphviz:
dot -Tpng archivo.dot -o archivo.png

Estructura del Proyecto
|-- main.cpp            # Archivo principal con la implementación del menú y las funciones.
|-- graph.h             # Definiciones de estructuras y funciones relacionadas con grafos.
|-- tree.h              # Definiciones de estructuras y funciones relacionadas con árboles.
|-- dijkstra.dot        # Archivo DOT generado por el algoritmo de Dijkstra.
|-- floyd_warshall.dot  # Archivo DOT generado por el algoritmo de Floyd-Warshall.
|-- kruskal.dot         # Archivo DOT generado por el algoritmo de Kruskal.
|-- prim.dot            # Archivo DOT generado por el algoritmo de Prim.
|-- bst_tree.dot        # Archivo DOT del ABB inicial.
|-- avl_tree.dot        # Archivo DOT del árbol AVL.
|-- rb_tree.dot         # Archivo DOT del árbol Rojo-Negro.
|-- graph.png           # Imagen PNG del grafo.
|-- dijkstra.png        # Imagen PNG del resultado de Dijkstra.
|-- floyd_warshall.png  # Imagen PNG del resultado de Floyd-Warshall.
|-- kruskal.png         # Imagen PNG del resultado de Kruskal.
|-- prim.png            # Imagen PNG del resultado de Prim.
|-- bst_tree.png        # Imagen PNG del ABB inicial.
|-- avl_tree.png        # Imagen PNG del árbol AVL.
|-- rb_tree.png         # Imagen PNG del árbol Rojo-Negro.

Asegúrate de tener Graphviz instalado para generar las imágenes PNG a partir de los archivos DOT:

sudo apt-get install graphviz
![image](https://github.com/SantiagoGR06/proyectofinalestructura/assets/141601959/eed223b6-7f5f-4202-a2a6-19142691ec10)

 una ves instalado mire bien la instalacion y dele a esta opcion
 ![image](https://github.com/SantiagoGR06/proyectofinalestructura/assets/141601959/2d6612e7-5731-4fb7-8c05-b9fdb07c0905)


para confirmar el la intalacion aplique este comando 
![image](https://github.com/SantiagoGR06/proyectofinalestructura/assets/141601959/8aa4215a-5697-45db-abc1-9153cf3a461b)






