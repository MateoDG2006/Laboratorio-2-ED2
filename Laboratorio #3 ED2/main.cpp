#include <iostream>
using namespace std;

class Node {
public:
    int value;
    Node* left;
    Node* right;

    Node(int v) {
        value = v;
        left = nullptr;
        right = nullptr;
    }
};

// Función para imprimir el encabezado del laboratorio
void printHeader() {
    cout << "==============================================\n";
    cout << "UNIVERSIDAD TECNOLÓGICA DE PANAMÁ\n";
    cout << "Estructuras de Datos II - Laboratorio N.2\n";
    cout << "Implementación: Algoritmo creador de un árbol binario no ordenado\n";
    cout << "Grupo: 1IL126\n";
    cout << "Integrantes: Mateo Del Giudice – E-8-229194\n";
    cout << "==============================================\n";
}

// Crear árbol recursivamente
Node* createTree() {
    int val;
    cout << "Ingrese el valor del nodo: ";
    cin >> val;

    Node* node = new Node(val);

    char ans;

    // Preguntar por hijo izquierdo
    cout << "¿Existe hijo izquierdo de " << val << "? (s/n): ";
    cin >> ans;
    if (ans == 's' || ans == 'S') {
        node->left = createTree();
    }

    // Preguntar por hijo derecho
    cout << "¿Existe hijo derecho de " << val << "? (s/n): ";
    cin >> ans;
    if (ans == 's' || ans == 'S') {
        node->right = createTree();
    }

    return node;
}

// Contar nodos del árbol
int countNodes(Node* node) {
    if (node == nullptr) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

// Recorrido en preorden
void preorder(Node* node) {
    if (node == nullptr) return;
    cout << node->value << " ";
    preorder(node->left);
    preorder(node->right);
}

// Liberar memoria del árbol (postorden)
void freeTree(Node* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

int main() {

    char again;

    do {
        printHeader();

        cout << "\nComenzando la creación del árbol...\n";
        Node* root = createTree();

        cout << "\nÁrbol creado exitosamente.\n";

        cout << "Recorrido en preorden: ";
        preorder(root);

        int total = countNodes(root);
        cout << "\nTotal de nodos en el árbol: " << total << "\n";

        // Liberar memoria del árbol antes de repetir
        freeTree(root);

        cout << "\n¿Desea crear otro árbol? (s/n): ";
        cin >> again;

    } while (again == 's' || again == 'S');

    cout << "\nPrograma finalizado. Hasta luego.\n";

    return 0;
}