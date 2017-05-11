#pragma once

#include <cstdio>

using namespace std;

template <class T>
class nodoBB_t
{
private:
    T dato_;  // Valor del contenido del nodo
    nodoBB_t<T> *izq_;  // Nodo hijo izquierdo
    nodoBB_t<T> *dch_;  // Nodo hijo derecho

public:
    /* Constructor por defecto */
    nodoBB_t (void):
    izq_(NULL),
    dch_(NULL)
    {

    }

    /* Constructor parametrizado */
    nodoBB_t (const T dato, nodoBB_t<T> *izq=NULL, nodoBB_t<T> *dch=NULL):
    dato_(dato),
    izq_(izq),
    dch_(dch)
    {

    }

    /* Destructor */
    ~nodoBB_t (void)
    {
        if (izq_ != NULL){
            delete izq_;
            izq_ = NULL;
        }
        if (dch_ != NULL){
            delete dch_;
            dch_ = NULL;
        }
    }

    /* Devuelve el dato del nodo */
    T get_dato (void)
    {
        return dato_;
    }

    /* Asigna un valor al dato del nodo */
    void set_dato (T dato){
        dato_ = dato;
    }

    /* Devuelve el nodo raíz del sub-árbol izquierdo */
    nodoBB_t<T>*& get_izq (void)
    {
        return izq_;
    }

    /* Devuelve el nodo raíz del sub-árbol derecho */
    nodoBB_t<T>*& get_dch (void)
    {
        return dch_;
    }

    /* Imprime el nodo formateado */
    ostream& write (ostream& os) const
    {
        // Si el nodo está vacío...
        if (this == NULL){
            os << "[.]";
        }
        // Si el nodo NO está vacío...
        else{
            os << "[";
            dato_.write(os);
            cout << "]";
        }
        return os;
    }
};
