#pragma once

#include <cstdio>

#include "nodoBB_t.hpp"
#include "cola_imprimir_ABB_t.hpp"

using namespace std;

extern int contador;  // Se importa la variable global contador como variable externa
extern modo_ejecucion MODO;  // Se importa la variable global MODO como variable externa

template <class T>
class ABB_t
{
private:
    nodoBB_t<T> *raiz_;  // Nodo raíz del árbol

public:
    /* Constructor por defecto */
    ABB_t (void):
    raiz_(NULL)
    {

    }

    /* Constructor parametrizado */
    ABB_t (nodoBB_t<T>* raiz):
    raiz_(raiz)
    {

    }

    /* Destructor */
    ~ABB_t (void)
    {
        podar(raiz_);
    }

    /* Elimina la rama cuya raíz se pasa como parámetro */
    void podar (nodoBB_t<T>* &nodo)
    {
        if (nodo != NULL){  // Si el nodo no está vacío...
            podar(nodo->get_izq());  // Elimina el sub-árbol izquierdo
            podar(nodo->get_dch());  // Elimina el sub-árbol derecho
            delete nodo;  // Elimina el nodo
            nodo = NULL;
        }
    }

    /* Busca un dato en todo el árbol */
    nodoBB_t<T>* buscar (T dato)
    {
        return buscar_rama (raiz_, dato);
    }

    /* Busca un dato en una rama */
    nodoBB_t<T>* buscar_rama (nodoBB_t<T>* nodo, T dato)
    {
        if (MODO == estadistico){  // Si se está ejecutando el programa en modo estadístico...
            contador ++;  // Se aumenta el contador
        }

        // Si el nodo está vacío, no se ha encontrado el dato buscado
        if (nodo == NULL){
            return NULL;
        }
        // Si el dato coincide con el buscado, se ha encontrado el dato buscado
        if (dato == nodo->get_dato()){
            return nodo;
        }
        // Si el dato es mayor que el buscado, se busca en la rama izquierda
        if (dato < nodo->get_dato()){
            return buscar_rama (nodo->get_izq(), dato);
        }
        // Si el dato es menor que el buscado, se busca en la rama derecha
        if (dato > nodo->get_dato()){
            return buscar_rama (nodo->get_dch(), dato);
        }
    }

    /* Inserta un dato en todo el árbol */
    void insertar (T dato)
    {
        insertar_rama(raiz_, dato);
    }

    /* Inserta un dato en una rama */
    void insertar_rama (nodoBB_t<T>* &nodo, T dato)
    {
        // Si el nodo está vacío, lo inserta en ese nodo
        if (nodo == NULL){
            nodo = new nodoBB_t<T>(dato);
        }
        else{
            // Si el dato es igual que el que se quiere insertar, se muestra un mensaje de error
            if (dato == nodo->get_dato()){
                cerr << "Clave ya insertada!" << endl;
            }
            // Si el dato NO es igual que el que se quiere insertar...
            else{
                // Si el dato es mayor que el que se quiere insertar, se inserta en la rama izquierda
                if (dato < nodo->get_dato()){
                    insertar_rama(nodo->get_izq(), dato);
                }
                // Si el dato NO es mayor que el que se quiere insertar...
                else{
                    // Si el dato es menor que el que se quiere insertar, se inserta en la rama derecha
                    if (dato > nodo->get_dato()){
                        insertar_rama(nodo->get_dch(), dato);
                    }
                }
            }
        }
    }

    /* Elimina un dato de todo el árbol */
    void eliminar (T dato){
        eliminar_rama(raiz_, dato);
    }

    /* Elimina un dato de una rama */
    void eliminar_rama (nodoBB_t<T>* &nodo, T dato)
    {
        // Si la rama de la que se va a eliminar está vacía...
        if (nodo == NULL){
            cerr << "El nodo a eliminar no esta en el arbol!" << endl;
        }
        // Si la rama de la que se va a eliminar NO está vacía...
        else{
            // Si el dato es igual al que se quiere eliminar...
            if (dato == nodo->get_dato()){
                // Si la rama derecha está vacía, se sustituye el nodo a eliminar por el nodo raíz de la rama izquierda
                if (nodo->get_dch() == NULL){
                    nodo = nodo->get_izq();
                }
                // Si la rama derecha NO está vacía...
                else{
                    // Si la rama izquierda está vacía, se sustituye el nodo a eliminar por el nodo raíz de la rama derecha
                    if (nodo->get_izq() == NULL){
                        nodo = nodo->get_dch();
                    }
                    // Si el nodo tiene 2 hijos, se intercambia el dato a eliminar con el mayor de la rama izquierda
                    else{
						nodoBB_t<T>* eliminar = nodo;  // Nodo que se pretende eliminar
                        sustituir(eliminar, nodo->get_izq());
                    }
                }
            }
            // Si el dato NO es igual al que se quiere eliminar...
            else{
                // Si el dato es mayor que el que se quiere eliminar, se vuelve a llamar al método con la rama izquierda
                if (dato < nodo->get_dato()){
                    eliminar_rama(nodo->get_izq(), dato);
                }
                // Si el dato NO es mayor que el que se quiere eliminar...
                else{
                    // Si el dato es menor que el que se quiere eliminar, se vuelve a llamar al método con la rama derecha
                    if (dato > nodo->get_dato()){
                        eliminar_rama(nodo->get_dch(), dato);
                    }
                }
            }
        }
    }

    /* Intercambia el dato a eliminar con el mayor de la rama especificada (normalmente la izquierda) */
    void sustituir (nodoBB_t<T>* &eliminar, nodoBB_t<T>* &sust)
    {
        // Si el nodo tiene hijo derecho (mayor), vuelve a llamar a la función con dicho hijo derecho
        if (sust->get_dch() != NULL){
            sustituir(eliminar, sust->get_dch());
        }
        // Si el nodo no tiene hijo derecho, ya se ha encontrado el valor mayor de la rama
        else{  // Se intercambia el dato a eliminar con el valor mayor encontrado
            eliminar->set_dato(sust->get_dato());
            eliminar = sust;
            sust = sust->get_izq();
        }
    }

    /* Imprime el árbol formateado */
    ostream& write (ostream& os) const
    {
        cola_imprimir_ABB_t<T> cola;  // Cola para guardar los nodos por niveles
        nodoBB_t<T>* nodo;  // Nodo auxiliar
        int nivel = 0;  // Nivel auxiliar
        int nivel_actual = 0;  // Nivel actual
        cola.insertar(raiz_, nivel);  // Se inserta el primer nodo y nivel (nodo raíz y nivel 0)
        os << "Nivel 0: ";
        // Mientras la cola no esté vacía...
        while (!cola.vacia()){
            cola.extraer(nodo, nivel);  // Se extrae un nodo y nivel
            // Si el nivel extraído es mayor que el nivel actual, se aumenta el nivel actual
            if (nivel > nivel_actual){
                nivel_actual = nivel;
                os << "\nNivel " << nivel_actual << ": ";
            }
            nodo->write(os);
            // Si el nodo extraído no está vacío, se insertan sus dos hijos en la cola
            if (nodo != NULL){
                cola.insertar(nodo->get_izq(), nivel+1);
                cola.insertar(nodo->get_dch(), nivel+1);
            }
        }
    }
};
