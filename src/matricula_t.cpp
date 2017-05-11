#include <cmath>

#include "matricula_t.hpp"
#include "modo_ejecucion.hpp"

extern int contador;  // Se importa la variable global contador como variable externa
extern modo_ejecucion MODO;  // Se importa la variable global MODO como variable externa

// Constructor por defecto
matricula_t::matricula_t (void)
{
    for (int i=0; i<7; i++){
        valor_[i] = 0;
    }
}

// Constructor parametrizado
matricula_t::matricula_t (string valor)
{
    contador ++;
    for (int i=0; i<7; i++){
        valor_[i] = valor[i];
    }
}

// Destructor
matricula_t::~matricula_t (void)
{

}

// // Sobrecarga del operador int
// matricula_t::operator int (void)
// {
//     int aux = 0;
//     for (int i=0; i<7; i++){
//         aux += valor_[i] * pow(10, fabs(i-6));
//     }
//
//     return aux;
// }

// Sobrecarga del operador ==
bool matricula_t::operator == (const matricula_t &matricula) const
{
    // if (MODO == estadistico){  // Si se está ejecutando el programa en modo estadístico...
    //     contador ++;  // Se aumenta el contador
    // }

    bool iguales = true;
    int i = 0;
    // Se comprueba que los valores de las matrículas, en la misma posición, coincidan
    while ((i < 7) && (iguales == true)){
        if (valor_[i] != matricula.valor_[i]){
            iguales = false;
        }
        i ++;
    }

    return iguales;
}

// Sobrecarga del operador <
bool matricula_t::operator < (const matricula_t &matricula) const
{
    // if (MODO == estadistico){  // Si se está ejecutando el programa en modo estadístico...
    //     contador ++;  // Se aumenta el contador
    // }

    int i = 0;
    bool menor = true;

    // Se comparan los caracteres de las matrículas uno a uno
    while ((i < 7) && (menor)){
        // Si el caracter de la matrícula de la izquierda es menor que el de la de la derecha,
        // se sale del bucle con i=7+1
        if (valor_[i] < matricula.valor_[i]){
            i = 7;
        }
        // Si no...
        else{
            // Si el caracter de la matrícula de la izquierda es mayor que el de la de la derecha,
            // se sale del bucle con menor=false e i igual al número de iteración +1
            if (valor_[i] > matricula.valor_[i]){
                menor = false;
            }
        }
        i ++;
    }

    // Si se ha salido del bucle con i=7, la matrícula de la izquierda NO es menor que la de la derecha
    if (i == 7){
        return false;
    }
    // Si NO se ha salido del bucle con i=7, se devuelve el valor de 'menor'
    else{
        return menor;
    }
}

// Sobrecarga del operador >
bool matricula_t::operator > (const matricula_t &matricula) const
{
    // if (MODO == estadistico){  // Si se está ejecutando el programa en modo estadístico...
    //     contador ++;  // Se aumenta el contador
    // }

    int i = 0;
    bool mayor = true;

    // Se comparan los caracteres de las matrículas uno a uno
    while ((i < 7) && (mayor)){
        // Si el caracter de la matrícula de la izquierda es mayor que el de la de la derecha,
        // se sale del bucle con i=7+1
        if (valor_[i] > matricula.valor_[i]){
            i = 7;
        }
        // Si no...
        else{
            // Si el caracter de la matrícula de la izquierda es menor que el de la de la derecha,
            // se sale del bucle con menor=false e i igual al número de iteración +1
            if (valor_[i] < matricula.valor_[i]){
                mayor = false;
            }
        }
        i ++;
    }

    // Si se ha salido del bucle con i=7, la matrícula de la izquierda NO es mayor que la de la derecha
    if (i == 7){
        return false;
    }
    // Si NO se ha salido del bucle con i=7, se devuelve el valor de 'menor'
    else{
        return mayor;
    }
}

// Sobrecarga del operador <=
bool matricula_t::operator <= (const matricula_t &matricula) const
{
    // if (MODO == estadistico){  // Si se está ejecutando el programa en modo estadístico...
    //     contador ++;  // Se aumenta el contador
    // }

    int i = 0;
    bool menor_igual = true;

    // Se comparan los caracteres de las matrículas uno a uno
    while ((i < 7) && (menor_igual)){
        // Si el caracter de la matrícula de la izquierda es menor que el de la de la derecha,
        // se sale del bucle
        if (valor_[i] < matricula.valor_[i]){
            i = 6;
        }
        // Si no...
        else{
            // Si el caracter de la matricula de la izquierda es mayor que el de la de la derecha,
            // se sale del bucle con menor_igual=false
            if (valor_[i] > matricula.valor_[i]){
                menor_igual = false;
            }
        }
        i ++;
    }

    return menor_igual;
}

// Sobrecarga del operador >=
bool matricula_t::operator >= (const matricula_t &matricula) const
{
    // if (MODO == estadistico){  // Si se está ejecutando el programa en modo estadístico...
    //     contador ++;  // Se aumenta el contador
    // }

    int i = 0;
    bool mayor_igual = true;

    // Se comparan los caracteres de las matrículas uno a uno
    while ((i < 7) && (mayor_igual)){
        // Si el caracter de la matrícula de la izquierda es mayor que el de la de la derecha,
        // se sale del bucle
        if (valor_[i] > matricula.valor_[i]){
            i = 6;
        }
        // Si no
        else{
            // Si el caracter de la matricula de la izquierda es menor que el de la de la derecha,
            // se sale del bucle con mayor_igual=false
            if (valor_[i] < matricula.valor_[i]){
                mayor_igual = false;
            }
        }
        i ++;
    }

    return mayor_igual;
}

// Se muestra la matrícula formateada por la salida especificada
ostream& matricula_t::write (ostream& os) const
{
    if (valor_[0] == '\0'){  // Si la matrícula no contiene ningún valor...
        os << "N/A";
    }
    else{
        os << valor_;
    }
    return os;
}
