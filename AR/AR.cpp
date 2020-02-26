#include <iostream>
#include <vector>
#include<ctime> 

using namespace std;
struct Moneda{
	float v;//valor
	float p;//peso
};
int N;
vector<int> sol1;
vector<int> sol2;
vector<Moneda> tipos;
const int INFINITO = 9999999;

void MonedaPesada(int val){
	vector<int> S(N);
	for (int i = 0; i < N; i++) S[i] = 0;
	float rate[N];
	int resto = val;
	for(int i = 0; i<N;i++) rate[i] = tipos[i].p/tipos[i].v;

	while(resto != 0){
		float micero = 0;
		int tipoescogido = 0;
		for (int i = 0; i < N; i++){//SELECT
			if (rate[i] >= micero && ((resto - tipos[i].v) >= 0)){
				tipoescogido = i;
				micero = rate[i];
			}
		}
		S[tipoescogido]++;
		resto = resto - tipos[tipoescogido].v;
	}
	sol1 = S;
}

void MonedaLigera(int val){
	vector<int> S(N);
	for (int i = 0; i < N; i++) S[i] = 0;
	float rate[N];
	int resto = val;
	for(int i = 0; i<N;i++) rate[i] = tipos[i].p/tipos[i].v;
	while(resto != 0){
		float micero = INFINITO;
		int tipoescogido = 0;
		for (int i = 0; i < N; i++){//SELECT
			if (rate[i] <= micero && ((resto - tipos[i].v) >= 0)){
				tipoescogido = i;
				micero = rate[i];
			}
		}
		S[tipoescogido]++;
		resto = resto - tipos[tipoescogido].v;
	}
	sol2 = S;
}

int main(int argc, char const *argv[]) {
	int casos;
	int V;
	cin >> casos;
	for (int cont = 0; cont<casos;cont++){
		cin >> N;
		if (N > 300) {
			cout << "ERROR: N demasiado grande." << endl;
			return(1);
		}
		cin >> V;
		sol1.resize(N);
		sol2.resize(N);
		tipos.resize(N);
		for (int i = 0; i < N; i++)	cin >> tipos[i].v;
		for (int i = 0; i < N; i++)	cin >> tipos[i].p;


    int start_s=clock() ;

		MonedaPesada(V);
		MonedaLigera(V);
		int pesoP = 0;int pesoL = 0;
		for (int i = 0; i< N ;i++) pesoP =pesoP+tipos[i].p*sol1[i];
		for (int i = 0; i< N ;i++) pesoL =pesoL+tipos[i].p*sol2[i];
		cout << pesoP-pesoL << endl;
		for (int i = 0; i< N ;i++) cout << sol1[i] << " ";
		cout << endl;
		for (int i = 0; i< N ;i++) cout << sol2[i] << " ";
		cout << endl;

    int stop_s=clock();
    cout<<(stop_s-start_s)/double(CLOCKS_PER_SEC)*1000;
	}


}
