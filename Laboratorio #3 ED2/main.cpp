#include <iostream>
#include <string>
#include <limits>

struct Nodo {
    int info;
    Nodo* izq;
    Nodo* der;
    Nodo(int v) : info(v), izq(nullptr), der(nullptr) {}
};

// Función que pide al usuario dirección (izq/der) y la valida.
// Devuelve true si la dirección escogida es izquierda, false si es derecha.
bool pedirDireccion(const Nodo* nodoActual) {
    std::string resp;
    while (true) {
        std::cout << "Nodo actual = " << nodoActual->info
            << ". ¿Insertar a la izquierda (i) o derecha (d)? [i/d]: ";
        if (!std::getline(std::cin, resp)) {
            // en caso de EOF, por seguridad tratar como 'd'
            return false;
        }
        if (resp == "i" || resp == "I" || resp == "izq" || resp == "IZQ" || resp == "izquierda") return true;
        if (resp == "d" || resp == "D" || resp == "der" || resp == "DER" || resp == "derecha") return false;
        std::cout << "Respuesta inválida. Escribe 'i' o 'd'.\n";
    }
}

// Inserta recursivamente: pregunta dirección en cada nodo hasta encontrar espacio.
void insertarInteractivo(Nodo* nodoActual, int valor) {
    bool izquierda = pedirDireccion(nodoActual);
    if (izquierda) {
        if (nodoActual->izq == nullptr) {
            nodoActual->izq = new Nodo(valor);
            std::cout << "Insertado " << valor << " como hijo izquierdo de " << nodoActual->info << ".\n";
        }
        else {
            // seguir bajando recursivamente por la izquierda
            insertarInteractivo(nodoActual->izq, valor);
        }
    }
    else {
        if (nodoActual->der == nullptr) {
            nodoActual->der = new Nodo(valor);
            std::cout << "Insertado " << valor << " como hijo derecho de " << nodoActual->info << ".\n";
        }
        else {
            // seguir bajando recursivamente por la derecha
            insertarInteractivo(nodoActual->der, valor);
        }
    }
}

// Preorden: para ver la estructura (raiz, izq, der)
void preorden(const Nodo* nodo) {
    if (!nodo) return;
    std::cout << nodo->info << " ";
    preorden(nodo->izq);
    preorden(nodo->der);
}

// Muestra el árbol "visual" con indentación (derecha arriba, izquierda abajo)
void mostrarDiagrama(const Nodo* nodo, int espacio = 0, int indent = 4) {
    if (!nodo) return;
    // mostrar subárbol derecho primero (para que aparezca arriba)
    mostrarDiagrama(nodo->der, espacio + indent, indent);
    // imprimir el nodo actual con indentación
    for (int i = 0; i < espacio; ++i) std::cout << ' ';
    std::cout << nodo->info << "\n";
    // mostrar subárbol izquierdo
    mostrarDiagrama(nodo->izq, space + indent, indent); // OOPS fix below
}

// CORRECCIÓN: variable erronea usada en mostrarDiagrama -> usar 'espacio' no 'space'
void mostrarDiagramaCorregido(const Nodo* nodo, int espacio = 0, int indent = 4) {
    if (!nodo) return;
    mostrarDiagramaCorregido(nodo->der, espacio + indent, indent);
    for (int i = 0; i < espacio; ++i) std::cout << ' ';
    std::cout << nodo->info << "\n";
    mostrarDiagramaCorregido(nodo->izq, espacio + indent, indent);
}

// Liberar memoria (postorden)
void liberar(Nodo* nodo) {
    if (!nodo) return;
    liberar(nodo->izq);
    liberar(nodo->der);
    delete nodo;
}

// Función auxiliar para leer entero de forma segura
bool leerEntero(int& out) {
    std::string linea;
    if (!std::getline(std::cin, linea)) return false;
    try {
        size_t pos;
        long val = std::stol(linea, &pos);
        if (pos != linea.size()) throw std::invalid_argument("Caracteres extras");
        out = static_cast<int>(val);
        return true;
    }
    catch (...) {
        return false;
    }
}

int main() {
    Nodo* raiz = nullptr;
    std::cout << "=== Implementación de un árbol binario no ordenado (interactivo) ===\n";
    std::cout << "Inserta nodos. Para terminar, escribe 'fin' cuando se pida un valor.\n";

    while (true) {
        std::cout << "\nValor del nuevo nodo (o 'fin' para terminar): ";
        std::string linea;
        if (!std::getline(std::cin, linea)) break;
        if (linea == "fin" || linea == "FIN" || linea == "Fin") break;

        // intentar convertir a entero
        int valor;
        try {
            size_t pos;
            long tmp = std::stol(linea, &pos);
            if (pos != linea.size()) throw std::invalid_argument("Entrada inválida");
            valor = static_cast<int>(tmp);
        }
        catch (...) {
            std::cout << "Entrada no es un entero válido. Intenta de nuevo.\n";
            continue;
        }

        if (raiz == nullptr) {
            raiz = new Nodo(valor);
            std::cout << "Creada raíz con valor " << valor << ".\n";
        }
        else {
            insertarInteractivo(raiz, valor);
        }
    }

    std::cout << "\n--- Árbol (preorden) ---\n";
    preorden(raiz);
    std::cout << "\n\n--- Diagrama del árbol ---\n";
    if (raiz) mostrarDiagramaCorregido(raiz);
    else std::cout << "(árbol vacío)\n";

    // liberar memoria
    liberar(raiz);
    raiz = nullptr;

    std::cout << "\nPrograma finalizado. Memoria liberada.\n";
    return 0;
}
