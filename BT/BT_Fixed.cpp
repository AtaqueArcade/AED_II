#include <iostream>									  //Trabajo realizado por Daniel Ibáñez Molero y Ginés Miguel Cánovas Méndez. 
#include <vector>
#include<ctime>
													  //[!] Quitar de comentario los cout para ver el recorrido del programa.
using namespace std;

struct aux{											  //Tipo auxiliar definido para indicar que tareas están ocupadas con qué mecánico.
	bool val; 
	int tareaasig;
};

int M; int A; 										  //M = num mecánicos, A = num averías.
vector< vector<int> > C;							  //Matriz introducida. Indica que mecanicos pueden hacer que tareas.

vector<int> s;										  //s de nuestro arbol. Serán los mecánicos.
int nivel;											  //nivel de nuestro arbol. Serán las tareas.

int numtareas = 0;									  //Cantidad de tareas realizadas actualmente.
int ntot = -1;										  //Cantidad mayor de tareas realizadas.

vector<aux> libre;									  //Vector auxiliar con los mecanicos.
vector<aux> asig;									  //Vector en el que introduciremos la solución.

void Generar(){									  //FUNCION GENERAR
	if (s[nivel] > -1 && libre[s[nivel]].val == false) {  //Libera al anterior mecánico.
//cout << "Libero " << s[nivel] << " al comienzo de generar." << endl;
		libre[s[nivel]].val = true;
		libre[s[nivel]].tareaasig = -1;
		numtareas--;
	}
	while ((s[nivel]+1 < M) && ((!libre[s[nivel]+1].val)||(C[s[nivel]+1][nivel] == 0))) {//Bucle de bloqueo de mecanicos.
//cout << "He entrado a bloqueo de repetidos: "<< s[nivel]+1 << " ya está asignado."  << endl;
		s[nivel]++;
	}
	s[nivel]++;										  //Avanzo s[nivel].									
//cout << "Entro a generar "<< nivel << " "  << s[nivel]<< endl;
	if(s[nivel] < M) {								  //Analizo el nivel.
		if (C[s[nivel]][nivel] == 1){
			numtareas++;
			libre[s[nivel]].val = false;
			libre[s[nivel]].tareaasig = nivel;
//cout << "Bloqueo en avance " << s[nivel] << endl;
		}
	}
}

bool Criterio(){									 	 //FUNCION CRITERIO
	if (nivel >= A-1) return false;
	else if (ntot >= M) return false;
	else if (ntot >= A) return false;
	return true;
}														 //y no se haya obtenido aun el mayor resultado posible.

bool Solucion(){									  //FUNCION SOLUCION
	return (nivel == A-1 || ntot == A || ntot == M);  //Tendremos una solución si se han evaluado todos los mecánicos o se han asignado todas las tareas.
}

bool MasHermanos(){									//FUNCION MASHERMANOS
	return (s[nivel] < M);							//Devuelve si hay mas tareas para analizar en el nivel.
}

void Retroceder(){									  //FUNCION RETROCEDER
//cout << "Entro a retroceder" << endl;
	s[nivel]=-1;									  //Resetea s[nivel].
	nivel--;										  //Retrocede un nivel.
}

void Backtracking (){								  //FUNCION BACKRACKING
	nivel = 0;
	s.resize(A);
	numtareas = 0;
	ntot = -1;
	for (int i = 0; i<A;i++) s[i] = -1;
	asig.resize(M);									  //Inicialización del vector solucion.
	for (int i = 0; i<M;i++) asig[i].val = true;
	for (int i = 0; i<M;i++) asig[i].tareaasig = -1;
	libre.resize(M);								  //Inicializacion del vector auxiliar.
	for (int i = 0; i<M;i++) libre[i].val = true;
	for (int i = 0; i<M;i++) libre[i].tareaasig = -1;
	while(nivel >= 0){								  //Bucle principal de la función.
		Generar();									  //Sigue el esquema general de backtracking.
//cout << "Ntareas es: " <<  numtareas << endl;
		if(Solucion()&&(numtareas > ntot)){
//cout << "Entro a Solucion"<< endl;
			ntot = numtareas;
			for (int i = 0; i < M; i++){
				asig[i].val = libre[i].val;			  //Guarda el mejor resultado en asig.
				asig[i].tareaasig = libre[i].tareaasig;
			}
		}
		if(Criterio()) nivel++;
		else while (!MasHermanos() && (nivel >= 0)){
			Retroceder();
//cout << "Tras retroceder nivel = " << nivel << " y nodo = "<< s[nivel] << " y ntareas = "<< numtareas << endl;
		}
	}
}

int main(int argc, char const *argv[]) {		 	  //CUERPO PRINCIPAL DEL PROGRAMA
	int casos;
	cin >> casos;									  //Lee el número de casos.
	for (int cont = 0; cont<casos;cont++){
		cin >> M >> A;								  //Para cada caso, lee A y M.
		C.resize(M);
		for (int i = 0;i<M;i++) C[i].resize(A);
		for (int i = 0; i < M; i++){				  //Para cada caso, lee la matriz introducida.
			for (int j = 0; j < A; j++) cin >> C[i][j];
		}

    int start_s=clock() ;

		Backtracking();								  //Llama a Backracking para obtener los resultados.
		if (cont == 0) cout << casos << endl;
		cout << ntot << endl;

		for (int i = 0; i < A; i++){
			bool impreso= false;			  //Los imprime por pantalla.
			for (int j = 0; j < M; j++){if(asig[j].tareaasig == i) {cout << j+1; impreso = true;j = M;}}
			if (!impreso) cout << 0;
			if(i != A-1) cout << " ";
		}
		cout << endl;
    int stop_s=clock();
    cout<<(stop_s-start_s)/double(CLOCKS_PER_SEC)*1000;
	}
}
