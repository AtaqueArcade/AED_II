#include <iostream>				//Realizado por Daniel Ibáñez Molero y Ginés Miguel Cánovas Méndez
#include <string>				//[!] Versión con salida por pantalla del progreso del programa [!]
#include <math.h>  				//usado para rand().
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct respuesta{				//Tipo auxiliar que usaremos para representar nuestras cadenas respuesta.
	int i;						//Comienzo de la cadena respuesta.
	int j;						//Fin de nuestra cadena.
	int numpares;				//Numero de pares en nuestra cadena.
};
int n;							//Tamaño que tiene nuestra cadena C
string C;						//Cadena introducida en la que buscar.
string C1;						//Primer conjunto del que sacar caracteres.
string C2;						//Segundo conjunto del que sacar caracteres.
const int m=2;					//Tamaño mínimo.
int t;							//Tamaño que tendrá nuestra cadena solución.

bool contenidoEnCadena(string cadena, char ch){	//Funcion para hallar si el caracter ch está contenido en el conjunto C.
	return cadena.find(ch) != string::npos;
}
bool pequenio(int i, int j){					//FUNCION PEQUEÑO
	return j-i<=m;								//Nuestro tamaño escogido es 2.
}
respuesta solucionDirecta(int i, int j){		//FUNCION SOLUCIONDIRECTA
	cout << "[S.Directa]" << endl;
	respuesta directa = {0, 0, -1};				//Halla de forma lineal la solucion en el caso mínimo.
	int npares = 0;								//EN nuestro caso, el caso mínimo será 2.
	for (int cont = i; cont < j;cont++){
		if (contenidoEnCadena(C1, C[cont]) && cont!=j){
			if(contenidoEnCadena(C2, C[cont+1])){
				npares++;cont++;
			}
		}
	}
	directa.i = i;								//Almacena la solución mínima.
	directa.j = j;
	directa.numpares = npares;
	cout << "Directa devuelve (" << directa.i << "," << directa.j << ") con npares " << directa.numpares << "." << endl;
	return(directa);							//Devuelve la solución mínima.
}
respuesta combinar(respuesta SolIzq,respuesta SolDer){				//FUNCION COMBINAR
	cout << "[Combinar]" << endl;									//Compararemos que cadena tiene el mayor numero de pares.
	cout << "Evalúo SolIzq(" <<SolIzq.i << "," << SolIzq.j << "), SolDer(" <<SolDer.i << "," << SolDer.j << ")." << endl;
	respuesta mejor = {0, 0, -1};									//Si la de la izquierda, la de la derecha, o una combinación de estas.

	if (SolIzq.numpares > mejor.numpares){							//Evaluamos la cadena izquierda.
		mejor.i = SolIzq.i;
		mejor.j = SolIzq.j;
		mejor.numpares = SolIzq.numpares;
		cout << " En analisis individual guardo (" << SolIzq.i << "," << SolIzq.j << ") con npares= " << SolIzq.numpares << " en mejor..." << endl;
	}

	int auxi = SolDer.i-t;int auxj = auxi+t-1;						//Los parametros Aux servirán para delimitar
	for (int cont = 0; cont < t-1;cont++){							//las cadenas intermedias creadas en bucle.
		int nparesaux = 0;											//Calculo y comparación de las respuestas de en medio.
		auxi++;auxj++;
		cout << "Combinar examina: (" << auxi << "," << auxj << ")..." << endl;
		if (auxi >= SolIzq.i && auxj <= SolDer.j){
			for (int caux = auxi; caux < auxj;caux++){
				cout << "En el for analizo el par: " << caux << ", " << caux+1 << "..." <<endl;
				if (contenidoEnCadena(C1, C[caux]) && contenidoEnCadena(C2, C[caux+1])){
					nparesaux++;
					caux++;
				}
			}
			if (nparesaux > mejor.numpares){
				cout << "Guardo (" << auxi << "," << auxj << ") con npares= " << nparesaux << " en mejor..." << endl;
				mejor.i = auxi;
				mejor.j = auxj;
				mejor.numpares = nparesaux;
			}
		}
		else cout << "La subcadena queda fuera de rango..." << endl;
	}

	if (SolDer.numpares > mejor.numpares){							//Evaluamos la cadena derecha.		
		mejor.i = SolDer.i;
		mejor.j = SolDer.j;
		mejor.numpares = SolDer.numpares;
		cout << " En analisis individual guardo (" << SolDer.i << "," << SolDer.j << ") con npares= " << SolDer.numpares << " en mejor..." << endl;
	}
	cout << "Combinar devuelve (" << mejor.i << "," << mejor.j << ") con npares = " << mejor.numpares << "." << endl;
	return(mejor);													//Devuelve el resultado.
}
respuesta dyv(int i,int j){					//FUNCION DIVIDEYVENCERÁS
	cout << "[Comienzo DyV]" << endl;
	cout << "Valores: i= " << i << ", j= " << j << "." << endl;
	if(pequenio(i,j)){						//Analiza si el caso es Pequeño.
		return solucionDirecta(i,j);		//De serlo, lo analiza directamente.
	}
	else{									//Si no, divide la cadena
		cout << "DyV parte la cadena..." << endl;
		int div = (i+j)/2;
		respuesta solIzq = dyv(i,div);
		respuesta solDer = dyv(div+1,j);
		return combinar(solIzq,solDer);		//Y devuelve Combinar de ambas partes.
	}
}
int main(int argc, char const *argv[]) {							//CUERPO PRINCIPAL DEL PROGRAMA
	cout << "Introduzca el primer conjunto C1." << endl;			//Lee y muestra los datos introducidos por pantalla.
	cin >> C1;
	cout << "Introduzca el segundo conjunto C2." << endl;
	cin >> C2;
	cout << "Los conjuntos son "<< C1 << " y " << C2 << "." <<endl;
	cout << "Introduzca la longitud de la cadena C en la que desea buscar los pares." << endl;
	cin >> n;
    srand(time(NULL));
    for(int i=0; i <n; i++){
		char caracter;
        caracter = 97 + rand() % (122 - 97);
		C = C + caracter;
	}
    cout << "Cadena: " << C << "." << endl;
	cout << "Introduzca el tamaño de la respuesta deseado." << endl;
    cin >> t;
	if (t > C.length()){
		cout << "[!]ERROR: t no puede ser mayor que el tamaño de la cadena." << endl;
		cout << ">En lugar de " << t << " tomaremos para t el mayor tamaño posible: " << C.length() << "." << endl;
		t = C.length();
	}
	respuesta cadena = dyv(0, C.length()-1);						//Aplica divide y vencerás.
/*
	if (cadena.j-cadena.i < t-1){									//Comprueba si la respuesta dada es demasiado corta.
		while (cadena.i > 0 || cadena.j-cadena.i == t-1) cadena.i--;//De serlo, añade caracteres para que cumpla el tamaño deseado.
		while (cadena.j < C.length()-1 || cadena.j-cadena.i == t-1) cadena.j++;
	}																//Actualmente redundante. Combinar ya añadirá estos.
*/
	cout << "Subcadena: ";											//Muestra en pantalla el resultado obtenido.
	for (int cont = cadena.i; cont < cadena.j+1;cont++) cout << C[cont];
	cout << "." << endl;
	cout << "Contiene: " << cadena.numpares << " pares de caracteres." << endl;
	cout << "La subcadena hallada comienza en la posicion: " << cadena.i+1 << "º." << endl;
return 0;
}
