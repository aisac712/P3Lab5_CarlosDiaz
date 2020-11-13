#include <iostream>
#include <vector>           //librería estándar de los vectores
#include <string>           //librería estándar de las cadenas

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::string;
using std::to_string;

//using namespace std;
//PROTOTIPO DE FUNCIONES
int** crearMatrix(int, int, bool);
void printMatrix(int**, int, int);
int** sumarM(int**, int**, int, int, int, int);
int** restarM(int**, int**, int, int, int, int);
int** multiM(int**, int**, int, int, int, int);

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
                cout << "" << endl;
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
                cout << "" << endl;
            } break;
            case 3:{
                for(int i = 0; i < matrices.size(); i++){
                    cout << "Matriz " << i << endl;
                    printMatrix(matrices[i], tamanosF[i], tamanosC[i]);
                    cout << "" << endl;
                }    
                
                string cadena="";
                cout << "INGRESA LA CADENA DE OPERACIONES" << endl;
                cin >> cadena;

                int acum=cadena[0]-48;
                for(int i = 0; i < cadena.length(); i++){
                    //cout << cadena[i] << "." << endl;

                    int temp = cadena[i]-48;
                    if(temp>=0 && temp<=9){
                        //cout << temp;
                        if(cadena[i+1]==42){                                                    //MULTIPLICACIóN
                            int temp2 = cadena[i+2]-48;
                            cout << temp << " y " << to_string(temp2);
                            int** mTemp = multiM(matrices.at(temp), matrices.at(temp2), tamanosF.at(temp), tamanosC.at(temp), tamanosF.at(temp2), tamanosC.at(temp2));
                            matrices.push_back(mTemp);
                            tamanosF.push_back(tamanosF.at(temp));          //filas
                            tamanosC.push_back(tamanosC.at(temp2));         //columnas
                        } else if(cadena[i+1]==43){                                             //SUMA
                            int temp2 = cadena[i+2]-48;
                            //acum = acum + (cadena[i+2]-48);
                            temp = acum;
                            int** mTemp = sumarM( matrices.at(temp), matrices.at(temp2), tamanosF.at(temp), tamanosC.at(temp), tamanosF.at(temp2), tamanosC.at(temp2) );
                            matrices.push_back(mTemp);
                            tamanosF.push_back(tamanosF.at(temp));
                            tamanosC.push_back(tamanosC.at(temp2));
                        } else if(cadena[i+1]==45){                                             //RESTA
                            int temp2 = cadena[i+2]-48;
                            //acum = acum + (cadena[i+2]-48);
                            temp = acum;
                            int** mTemp = restarM( matrices.at(temp), matrices.at(temp2), tamanosF.at(temp), tamanosC.at(temp), tamanosF.at(temp2), tamanosC.at(temp2) );
                            matrices.push_back(mTemp);
                            tamanosF.push_back(tamanosF.at(temp));
                            tamanosC.push_back(tamanosC.at(temp2));
                        }
                    }

                }
                cout << "" << endl;
                printMatrix(matrices.at(matrices.size()-1), tamanosF.at(matrices.size()-1), tamanosC.at(matrices.size()-1));
                
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
                    cout << "elemento["<<i<<"]["<<j<<"]: " << endl;
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
    } else {
        cout << "Nula, no se puede calcular" << endl;
    }
}

int** sumarM(int** m1, int** m2, int f1, int c1, int f2, int c2){
    int** mR = NULL;
    if(f1==f2 && c1==c2 && m1!=NULL && m2!=NULL){
        mR = crearMatrix(f1, c2, true);                                 //inicializa la matriz
        
        for(int i=0; i<f1; i++){
            for(int j=0; j<c2; j++){
                //cout << std::to_string(matrix[i][j]) +"\t";
                mR[i][j] = m1[i][j] + m2[i][j];
            }
        }
    } else{
        cout << "No se puede operar";
    }
    return mR;
}

int** restarM(int** m1, int** m2, int f1, int c1, int f2, int c2){
    int** mR = NULL;
    if(f1==f2 && c1==c2 && m1!=NULL && m2!=NULL){
        mR = crearMatrix(f1, c2, true);                                 //inicializa la matriz
        
        for(int i=0; i<f1; i++){
            for(int j=0; j<c2; j++){
                //cout << std::to_string(matrix[i][j]) +"\t";
                mR[i][j] = m1[i][j] - m2[i][j];
            }
        }
    } else{
        cout << "No se puede operar";
    }
    return mR;
}

int** multiM(int** m1, int** m2, int f1, int c1, int f2, int c2){
    int** mR = NULL;
    if(f1==c2 && c1==f2 && m1!=NULL && m2!=NULL){
        mR = crearMatrix(f1, c2, true);                                 //inicializa la matriz
        int ii=0, jj=0;
        
        for(int i=0; i<f1; i++){
            for(int k=0; k<c2; k++){
                int acum=0;
                for(int j=0; j<c1; j++){
                    //cout << std::to_string(matrix[i][j]) +"\t";
                    
                        //cout << std::to_string(matrix[i][j]) +"\t";
                        //acum = acum +(m1[i][j] * m2[j+k][i+k]);
                        acum = acum +(m1[i][j] * m2[j][k]);
                        cout << m1[i][j] << "*" << m2[j][k] << " ";
                }
                mR[ii][jj] = acum;
                jj++;
            }
            cout << " " << endl;
            ii++;
            jj=0;                                                       //se aumenta la fila en la q estaba, y las columnas se hacen a 0 (como si fuera los 2 for)
        }
    } else{
        cout << "No se puede operar";
    }
    return mR;
}