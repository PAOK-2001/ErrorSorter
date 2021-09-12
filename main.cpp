// Actividad 1.3: Integracion de Concpetos
// Fecha: 12/09/2021
// Descripción: el programa lee un archivo .txt correspondiente a una bitácora de errores,
// crea objetos de Error a partir de cada uno de los registros y los almacena en un vector, 
// mismos que se ordena utilizando el algoritmo mergeSort.
// Autores:
// Pablo Agustín Ortega Kral A00344664
// Jose Antonio Chaires Monroy A0160114
// Adrian Becerra Meza A01639813
#include <iostream>
#include <vector> 
#include <fstream> 
#include <string> 
#include <cmath> 
using namespace std;
// month2absolute
// IN: Recibe dos strings, correspondiente al mes y dia
// OUT: Un float
// Descripción: convierte el mes y día recibidos al número del año total al que corresponde utilizando condicionales
// de este modo, tiene un rango de salida de 1 (1 Enero) a 365 (31 Diciembre).
float month2absolute(string month, string day){ 
  if(month == "Jan"){ 
    return (stoi(day));
  }
  if(month == "Feb"){ 
    return (31 + stoi(day));
  }
  if(month == "Mar"){ 
    return (59 + stoi(day));
  }
  if(month == "Apr"){ 
    return (89 + stoi(day));
  }
  if(month == "May"){ 
    return (120 + stoi(day));
  }
  if(month == "Jun"){ 
    return (150 + stoi(day));
  }
  if(month == "Jul"){ 
    return (181 + stoi(day));
  }
  if(month == "Aug"){ 
    return (212 + stoi(day));
  }
  if(month == "Sep"){ 
    return (243 + stoi(day));
  }
  if(month == "Oct"){ 
    return (273 + stoi(day));
  }
  if(month == "Nov"){ 
    return (304 + stoi(day));
  }
  if(month == "Dec"){ 
    return (334 + stoi(day));
  } 
  else{ 
    return -1;
  }
}
// time2float
// IN: Recibe un string, correspondiente a la hora en formato hr:min:sec
// OUT: Un float
// Descripción: se divide el string utilizando como referencia ":" y se guardan los valores en un array
// de esta forma, se tiene la hora, minutos y segundos separados. Posteriormente se convierte todo a segundos y 
// se regresa un flot correspondiente a la fracción del día que representan.
float time2float(string time){
  string fields[3];
  int npos = 0;
  int token;
  float timeReturn;
  string split = ":";

  for (int i = 0; i < 3; i++){
      token = time.find(split);
      fields[i] = time.substr(npos,token);
      time.erase(0, token + split.length());
  }
  timeReturn =  stoi(fields[0])*3600 + stoi(fields[1])*60 + stoi(fields[2]);   
  return timeReturn/86400;
}
// Clase Error
class Error{ 
  private:
    // float que representa el tiempo absoluto del año
    float time;
    // string que almacena la entrada registrada en bitácora
    string log;
  public:
    // Error
    // Descripción: constructor de la clase error, que asigna los atributos time y log respectivamente
    Error(float t, string l){
      time = t;
      log = l;
    }
    // fromTxtLine
    // IN: recibe un string, correspondiente a el error registando en formato: "Mes Dia IP hr:min:seg Razón"
    // OUT: un objeto Error
    // Descripción: función estática que toma un string y lo divide basado en el char " ", generando un array 
    // almacenando separadamente Mes, Día, Fecha. Con los valores separados, se llama la función month2absolute y la función
    // time2float para tener un float correspondiente al tiempo. Finalmente, se genera un objeto Error, utilizando el tiempo
    // en float y el string en sí para constuir el objeto.
    static Error fromTxtLine(string line){
      float returnTime;
      string temp = line;
      string fields[3];
      int npos = 0;
      int token;
      string split = " ";
      for (int i = 0; i < 3; i++){
          token = line.find(split);
          fields[i] = line.substr(npos,token);
          line.erase(0, token + split.length());
      }
      Error returnError = Error(month2absolute(fields[0],fields[1]) + time2float(fields[2]),temp);
      return returnError;
    } 
    // printLog
    // IN: No tiene argumentos.
    // OUT: No hay.
    // Descripción: imprime el atributo log a consola.
    void printLog(){ 
      cout << this->log << endl;
    }
    // printTime
    // IN: No tiene argumentos.
    // OUT: No hay.
    // Descripción: imprime el atributo time a consola. 
    void printTime(){ 
      cout << this->time << endl; 
    } 
    // getLog
    // IN: No tiene argumentos.
    // OUT: String correspondiente al valor log.
    // Descripción: retorna el valor de log.
    string getLog(){ 
      return this->log;
    }
    // getTime
    // IN: No tiene argumentos.
    // OUT: Float correspondiente al valor de time.
    // Descripción: retorna el valor del atributo time.
    float getTime(){
      return this->time;
    }
};
// getData
// IN: Recibe un string, correspondiente al nombre del archivo
// OUT: un vector de objetos de Error.
// Descripción: utilizando fstream, se abre el archivo del nombre del string pasado y se utiliza la función predefinida getline
// para leer cada línea del archivo y guardar su valor en un string, el cual se pasa a la función fromTxtLine para generar un 
// objeto Error, el cuál se almacena en un vector.
vector<Error> getData(string route){ 
    vector<Error> returnVector;
    ifstream Data;
    string line;
    Data.open(route);
    while(Data.good()){
      getline(Data, line);
      returnVector.push_back(Error::fromTxtLine(line));
    }
    return returnVector;      
  }
// merge
// IN: Recibe un vector de objetos Error(arr) por referencia, y tres enteros.
// OUT: No hay salida.
// Descripción: toma un vector y crea subarrays, los cuales combina nuevamente en el mismo vector.
// Complejidad: O(N), lineal.
void merge(vector<Error> &arr, int l, int r, int m){ 
      int size1 = m - l + 1;
      int size2 = r - m; 
      vector<Error> leftArray, rightArray; 
      // Copias de los vectores
      for(int i = 0; i < size1; i++){ 
          leftArray.push_back(arr[l+i]);
      } 
      for(int j = 0; j < size2; j++){ 
          rightArray.push_back(arr[m+j+1]); 
      }  
      // Merge 
      int i = 0; 
      int j = 0; 
      int k = l;
      while(i < size1 && j < size2){ 
          if(leftArray[i].getTime() <= rightArray[j].getTime()){ 
              arr[k] = leftArray[i]; 
              i++;
          } else { 
              arr[k] = rightArray[j]; 
              j++; 
          } 
          k++;
      }  
      // Agregar elementos restantes
      while(j < size2){ 
          arr[k] = rightArray[j]; 
          j++; 
          k++;
      }
      while(i < size1){ 
          arr[k] = leftArray[i]; 
          i++; 
          k++;
      }  
    }
// ordenaMerge
// IN: Recibe un vector de objetos Eror(arr) por referencia, y tres enteros
// OUT: No hay salida
// Descripción: algoritmo recursivo que divide el vector tomado por referencia para mandar los subconjuntos 
// creados a merge, donde se ordenan y juntan.
// Complejidad: O(nlog(n)).       
void ordenaMerge(vector<Error> &arr, int l, int r){ 
  if(l < r){ 
    int m = floor((l+r)/2); 
    ordenaMerge(arr, l, m); 
    ordenaMerge(arr,m+1,r); 
    merge(arr,l,r,m);
  } 
} 
int main(){ 
  // Se abre el archivo "sorted.txt" en modo escritura
  ofstream sorted;
  sorted.open("sorted.txt");
  // creación del vector de errores, utilizando getData
  vector<Error> ErrorList=getData("bitacora.txt");
  // se ordena el vector creado utilizando el algoritmo Merge Sort
  ordenaMerge(ErrorList, 0, ErrorList.size());
  // se escribe los errores ordenaos en el archivo "sorted.txt"
  for (int i = 0; i < ErrorList.size(); i++){
      sorted << ErrorList[i].getLog()<<endl;
  } 
  string lmonth, lday, hmonth, hday; 
  float low, hi;
  bool Valid = true;
  // Ciclo de validación que pide al usuario ingresar fechas validas hasta que estas
  // correspondan a un mes válido, y el rango esté bien definido.
  while(Valid){
    cout << " Introduce el mes inicial: ";
    cin >> lmonth; // Se guarda el mes inicial en lmonth
    cout << endl;
      
    cout << "Introduce el día inicial: "; 
    cin >> lday; // Se guarda el dia inicial en lday
    cout << endl;
    // Se convierte el día y mes a tiempo absoluto utilizando month2absolute
    low = month2absolute(lmonth, lday); 

    cout << " Introduce el mes final: ";
    cin >> hmonth; // Se guarda el mes final en hmonth
    cout << endl;
      
    cout << "Introduce el día final: "; 
    cin >> hday; // Se guarda el dia final en hday
    cout << endl;
    hi = month2absolute(hmonth, hday);
    // Se realiza la validación de datos
    if (low<hi && low!=-1 && hi!=-1){
      Valid = false;
    } else { 
      cout<<"Error, input invalido"<<endl;
    }
  }
  // Se recorre el vector ordenado y se imprime los valores buscados, 
  // realizando una búsqueda secuencial.
  for(int i = 0; i < ErrorList.size(); i++){
    if(ErrorList[i].getTime() > hi){
      break;
    }
    if(ErrorList[i].getTime() >= low && ErrorList[i].getTime() <= hi){ 
      ErrorList[i].printLog();
    }
  }
  return 0;
}