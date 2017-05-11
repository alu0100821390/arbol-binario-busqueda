#pragma once

#include <cstdio>
#include <vector>

#include "nodoBB_t.hpp"

using namespace std;

/* Cola de 2 elementos para la impresión de un ABB */
template <class T>
class cola_imprimir_ABB_t
{
private:
    int size_;  // Tamaño de la cola
    vector<nodoBB_t<T>* > nodo_;  // Vector de nodos
    vector<int> nivel_;  // Vector de niveles

public:
    /* Constructor por defecto */
    cola_imprimir_ABB_t (void):
    size_(0)  // Tamaño incial de la cola es 0
    {
        nodo_.clear();  // Se limpia el vector de nodos por si contiene algo
        nivel_.clear();  // Se limpia el vector de niveles por si contiene algo
    }

    /* Destructor por defecto */
    ~cola_imprimir_ABB_t (void)
    {

    }

    /* Inserta elementos en la cola */
    void insertar (nodoBB_t<T>* nodo, int nivel)
    {
        nodo_.push_back(nodo);  // Inserta el nodo por el final del vector
        nivel_.push_back(nivel);  // Inserta el nivel por el final del vector
        size_ ++;  // Aumenta el tamaño de la cola
    }

    /* Extrae elementos de la cola */
    void extraer (nodoBB_t<T>* &nodo, int &nivel)
    {
        nodo = nodo_[0];  // Valor del nodo que se extrae
        nivel = nivel_[0];  // Valor del nivel que se extrae
        nodo_.erase(nodo_.begin());  // Se elimina el nodo extraído
        nivel_.erase(nivel_.begin());  // Se elimina el nivel extraído
        size_ --;  // Se decrementa el tamaño de la cola
    }

    /* Comprueba si la cola está vacía */
    bool vacia (void)
    {
        if (size_ < 1){
            return true;
        }
        else{
            return false;
        }
    }
};
