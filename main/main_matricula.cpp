#include <climits>
#include <vector>
#include <ctime>
#include <map>

using namespace std;

#include "../src/modo_ejecucion.hpp"
modo_ejecucion MODO;  // Variabla global que contendrá el modo de ejecución del programa
int contador;  // Variable global que contendrá el número de comparaciones por iteración de cada algoritmo
#include "../src/matricula_t.hpp"
#include "../src/ABB_t.hpp"


// Estructura en la que se guardarán las estadísticas
struct estadisticas_t {
    int min = INT_MAX;
    int med = 0;
    int max = INT_MIN;
};

int main (void)
{
    int opcion = 0;  // Opción para el menú principal

    //  Menú principal del programa
    while (opcion != 3){  // Mientras no se elija la opción para salir...
        cout << endl;
        cout << "----- MENU -----" << endl;
        cout << "\t1. Modo demostracion" << endl;
        cout << "\t2. Modo estadistico" << endl;
        cout << "\t3. Salir" << endl;
        cout << "Elija el modo de ejecucion: ";
        cin >> opcion;
        cout << endl;

        // Se procede según la opción introducida
        switch (opcion){
            case 1:{  // Si se ha elegido el modo demostración...
                MODO = demostracion;  // Se establece el modo de ejecución a demostracion

                cout << "Creando arbol binario de busqueda vacio...";
                ABB_t<matricula_t> ABB;  // Se crea el ABB vacío
                cout << "HECHO!" << endl;
                cout << endl;
                ABB.write(cout);  // Se muestra el ABB vacío
                cout << endl;

                int opcion_demo = 0;
                // Menú del modo demostración
                while (opcion_demo != 3){  // Mientras no se elija la opción para salir...
                    cout << endl;
                    cout << "----- MODO DEMOSTRACION -----" << endl;
                    cout << "\t1. Insertar clave" << endl;
                    cout << "\t2. Eliminar clave" << endl;
                    cout << "\t3. Menu principal" << endl;
                    cout << "Elija el modo de ejecucion: ";
                    cin >> opcion_demo;
                    cout << endl;

                    // Se procede según la opción introducida
                    switch (opcion_demo){
                        case 1:{  // Si se quiere insertar una clave...
                            char matricula[8];  // Variable que contendrá el valor de la matrícula a introducir
                            cout << "Introduzca la clave a insertar: ";
                            cin >> matricula;
                            matricula_t aux(matricula);  // Se crea un objeto matricula_t auxiliar con el valor introducido
                            ABB.insertar(aux);  // Se inserta el objeto matricula_t en el ABB
                            cout << endl;
                            ABB.write(cout);  // Se muestra cómo ha quedado el ABB tras la inserción
                            cout << endl;
                            break;
                        }
                        case 2:{  // Si se quiere eliminar una clave...
                            char matricula[8];  // Variable que contendrá el valor de la matrícula a eliminar
                            cout << "Introduzca la clave a eliminar: ";
                            cin >> matricula;
                            matricula_t aux(matricula);  // Se crea un objeto matricula_t auxiliar con el valor a eliminar
                            ABB.eliminar(aux);  // Se elimina el objeto matricula_t del ABB
                            cout << endl;
                            ABB.write(cout);  // Se muestra cómo ha quedado el ABB tras la eliminación
                            cout << endl;
                            break;
                        }
                        case 3:{  // Si se elige salir del modo demostración...
                            break;
                        }
                        default:{  // Si no se ha elegido una opción de entre las del menú...
                            cerr << "OPCION INCORRECTA!" << endl;
                        }
                    }
                }
                break;
            }
            case 2:{  // Si se ha elegido el modo estadístico...
                MODO = estadistico;  // Se establece el modo de ejecución a estadistico
                srand(time(NULL));  // Se inicializa la semilla de generación aleatoria con la hora

                int N;  // Tamaño del ABB
                int nPruebas;  // Número de pruebas
                int med_aux = 0;  // Variable auxiliar para calcular el número medio de comparaciones
                char matricula[8];  // Cadena auxiliar para guardar las matrículas generadas aleatoriamente
                bool iguales;  // Variable auxiliar para evitar que se guarden matrículas iguales en el banco de pruebas
                vector<int> pos;  // Vector auxiliar para guardar las posiciones que se evaluarán del banco de pruebas
                vector<matricula_t> banco_pruebas;  // Banco de pruebas que contendrá las matrículas a insertar y buscar
                ABB_t<matricula_t> ABB;  // Se crea el ABB vacío
                estadisticas_t estadist_busq;  // Estadísticas de la búsqueda
                estadisticas_t estadist_inse;  // Estadísticas de la inserción

                cout << "----- MODO ESTADISTICO -----" << endl;
                cout << "\nTamaño del arbol: ";
                cin >> N;
                cout << "Numero de pruebas: ";
                cin >> nPruebas;
                while ((nPruebas < 1) || (nPruebas > N)){
                    cerr << "Numero de pruebas fuera de rango!" << endl;
                    cout << "Numero de pruebas: ";
                    cin >> nPruebas;
                }

                banco_pruebas.clear();
                banco_pruebas.resize(2*N);  // Se redimensiona el banco de pruebas

                // Se rellena el banco de pruebas con matrículas aleatorias
                for (int i=0; i<banco_pruebas.size(); i++){
                    iguales = true;
                    while (iguales){
                        // Se generan las 4 letras de la matrícula
                        for (int j=0; j<4; j++){
                            matricula[j] = rand() % 10 + 48;
                        }
                        // Se generan los 3 números de la matrícula
                        for (int j=4; j<7; j++){
                            matricula[j] = rand() % 26 + 65;
                        }
                        matricula_t aux(matricula);  // Se crea un objeto matricula_t con la matrícula generada

                        iguales = false;
                        int j = 0;
                        // Se comprueba que la matrícula generada no esté repetida
                        while ((j<i) && (!iguales)){  // Mientras no se haya recorrido todas las matrículas introducidas y no se haya encontrado ninguna coincidencia...
                            // Si se encuentra una matrícula igual en el banco de pruebas, se sale del bucle y se genera otra de forma aleatoria
                            if (aux == banco_pruebas[j]){
                                iguales = true;
                            }
                            j ++;
                        }

                        // Si la matrícula no está repetida, se añade al banco de pruebas
                        if (!iguales){
                            banco_pruebas[i] = aux;
                        }
                    }
                }

                // Se insertan en el árbol las N primeras matrículas del banco de pruebas
                for (int i=0; i<N; i++){
                    ABB.insertar(banco_pruebas[i]);
                }


                ////////// ESTUDIO DE LA BÚSQUEDA //////////
                med_aux = 0;  // Se reinicia la variable auxiliar para calcular la media
                pos.clear();  // Se limpia el vector de posiciones por si no estuviera vacío
                pos.resize(nPruebas);  // Se redimensiona el vector de posiciones según el número de pruenas que se vaya a realizar
                // Se realiza la búsqueda en el ABB de los nPruebas elementos extraídos de las N primeras posiciones del banco de pruebas
                for (int i=0; i<nPruebas; i++){
                    contador = 0;  // Se reinicia el contador
                    iguales = true;
                    // Mientras la posición generada ya haya sido escogida, se escoge otra aleatoriamente
                    while (iguales){
                        pos[i] = rand() % N;  // Se genera una posición aleatoria entre 0 y N

                        iguales = false;
                        int j = 0;
                        // Se comprueba que la posición generada no esté repetida
                        while ((j<i) && (!iguales)){  // Mientras no se haya recorrido todas las posiciones introducidas y no se haya encontrado ninguna coincidencia...
                            // Si se encuentra una posición igual en el vector de posiciones, se sale del bucle y se genera otra de forma aleatoria
                            if (pos[i] == pos[j]){
                                iguales = true;
                            }
                            j ++;
                        }
                    }

                    ABB.buscar(banco_pruebas[pos[i]]);  // Se busca en el ABB el elemento del banco de pruebas correspondiente a la última posición generada
                    // Si el nuevo contador es menor que el mínimo, el contador pasa a ser el nuevo mínimo
                    if (contador < estadist_busq.min){
                        estadist_busq.min = contador;
                    }
                    // Si el nuevo contador es mayor que el máximo, el contador pasa a ser el nuevo máximo
                    if (contador > estadist_busq.max){
                        estadist_busq.max = contador;
                    }
                    med_aux += contador;  // Se suma el contador a los anteriores
                }
                estadist_busq.med = med_aux / nPruebas;  // Se guarda el valor medio de comparaciones


                ////////// ESTUDIO DE LA INSERCIÓN //////////
                med_aux = 0;  // Se reinicia la variable auxiliar para calcular la media
                pos.clear();  // Se limpia el vector de posiciones por si no estuviera vacío
                pos.resize(nPruebas);  // Se redimensiona el vector de posiciones según el número de pruenas que se vaya a realiza
                // Se realiza la búsqueda en el ABB de los nPruebas elementos extraídos de las N últimas posiciones del banco de pruebas
                for (int i=0; i<nPruebas; i++){
                    contador = 0;  // Se reinicia el contador
                    iguales = true;
                    // Mientras la posición generada ya haya sido escogida, se escoge otra aleatoriamente
                    while (iguales){
                        pos[i] = rand() % N + N;  // Se genera una posición aleatoria entre N y 2N

                        iguales = false;
                        int j = 0;
                        // Se comprueba que la posición generada no esté repetida
                        while ((j<i) && (!iguales)){  // Mientras no se haya recorrido todas las posiciones introducidas y no se haya encontrado ninguna coincidencia...
                            // Si se encuentra una posición igual en el vector de posiciones, se sale del bucle y se genera otra de forma aleatoria
                            if (pos[i] == pos[j]){
                                iguales = true;
                            }
                            j ++;
                        }
                    }

                    ABB.buscar(banco_pruebas[pos[i]]);  // Se busca en el ABB el elemento del banco de pruebas correspondiente a la última posición generada
                    // Si el nuevo contador es menor que el mínimo, el contador pasa a ser el nuevo mínimo
                    if (contador < estadist_inse.min){
                        estadist_inse.min = contador;
                    }
                    // Si el nuevo contador es mayor que el máximo, el contador pasa a ser el nuevo máximo
                    if (contador > estadist_inse.max){
                        estadist_inse.max = contador;
                    }
                    med_aux += contador;  // Se suma el contador a los anteriores
                }
                estadist_inse.med = med_aux / nPruebas;  // Se guarda el valor medio de comparaciones

                ////////// SE MUESTRA LOS RESULTADOS OBTENIDOS //////////
                cout << "\n\t\t----- NUMERO DE COMPARACIONES -----\n" << endl;
                cout << setw(15) << "" << setw(10) << "MINIMO" << setw(10) << "MEDIO" << setw(10) << "MAXIMO" << endl;
                cout << setw(15) << "Busqueda" << setw(10) << estadist_busq.min << setw(10) << estadist_busq.med << setw(10) << estadist_busq.max << endl;
                cout << setw(15) << "Insercion" << setw(10) << estadist_inse.min << setw(10) << estadist_inse.med << setw(10) << estadist_inse.max << endl;
                cout << endl;

                break;
            }
            case 3:{  // Si se elige salir del programa...
                break;
            }
            default:{  // Si no se ha elegido una opción de entre las del menú...
                cerr << "OPCION INCORRECTA!" << endl;
            }
        }
    }

    return 0;
}
