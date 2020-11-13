#include <iostream>
#include <vector>           //librería estándar de los vectores

using std::cout;
using std::endl;
using std::cin;
using std::vector;

//using namespace std;
//PROTOTIPO DE FUNCIONES
int** crearMatrix(int, int, bool);
void printMatrix(int**, int, int);

int main(int argc, char** argv) {
    int op = 0, sizeV=0;
    vector<int**> matrices;                                  //almacena las matrices
    vector<int> tamanosF;                                 //almacena el # de filas de una matriz
    vector<int> tamanosC;                                 //almacena el # de columnas de una matriz
    
    while(op!=4){
        cout << "CALCULADORA DE MATRICES" << endl;
        cout << "1. Ingresar matriz" << endl;
        cout << "2. Generar matriz" << endl;
        cout << "3. Realizar operación entre matrices" << endl;
        cout << "4. Salir" << endl;
        cout << "" << endl;
        cout << "Ingresa opción: ";
        cin  >> op;
        
        switch(op){
            case 1: {
                int filas=0, columnas=0;
                cout << "Filas: ";
                cin >> filas;
                cout << "Columnas: ";
                cin >> columnas;
                
                int** matrixTemp = crearMatrix(filas, columnas, false);        //inicializa la matriz en 0
                
                matrices.push_back(matrixTemp);
                tamanosF.push_back(filas);
                tamanosC.push_back(columnas);                           //añado todo a los vectores
                cout << "" << endl;;
            } break;
            case 2: {
                int filas=0, columnas=0;
                cout << "Filas: ";
                cin >> filas;
                cout << "Columnas: ";
                cin >> columnas;
                
                int** matrixTemp = crearMatrix(filas, columnas, true);        //inicializa la matriz en 0
                
                matrices.push_back(matrixTemp);
                tamanosF.push_back(filas);
                tamanosC.push_back(columnas);                           //añado todo a los vectores
            } break;
            case 3:{
                for(int i = 0; i < matrices.size(); i++){
                    cout << "Matriz " << i << endl;
                    printMatrix(matrices[i], tamanosF[i], tamanosC[i]);
                    cout << "" << endl;
                }
            } break;
            case 4: {
                cout << "Nos vemos vuelva pronto hehe" << endl;
            } break;
            
            default: cout << "Opción no válida" << endl;
        }
    }
    return 0;
}

int** crearMatrix(int size, int size2, bool llenadoAutom){
    int** matriz = NULL;
    if(size>1 && size2>1){                                                      //SAFE CODE
        matriz = new int*[size];                                    //filas

        for(int i=0; i < size; i++){
            matriz[i] = new int[size2];                             //columnas
        }
        
        for(int i=0; i<size; i++){
            for(int j=0; j<size2; j++){
                int temp=0;
                if(!llenadoAutom){
                    cout << "elemento["<<size<<"]["<<size2<<"]: " << endl;
                    cin >> temp;
                } else {
                    temp = (-50) + rand()%((50+1) - (-50));
                }
                matriz[i][j] = temp;                                   //inicializo en 0
            }
        }
    }
    return matriz;
}

void printMatrix(int** matrix, int filas, int columnas){
    if(matrix!=NULL){                                                 //SAFE CODE
        for(int i=0; i<filas; i++){
            for(int j=0; j<columnas; j++){
                cout << std::to_string(matrix[i][j]) +"\t";
            }
            cout << "" << endl;
        }
    }
}
