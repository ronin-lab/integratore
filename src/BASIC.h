//Questo header ha i prototipi delle funzioni di base (eg somma e prodotto per struct, calcolo dei periodi), i typedef per le struct e la definizione delle costanti


#ifndef BASIC_H_
#define BASIC_H_


#define LEN 40	//lunghezza della stringa per i nomi dei file con i risultati
#define A 8	//numero di argomenti passati da riga di comando

//costanti per far variare il passo di integrazione nel programma 

#define I 0.1
#define II 0.01
#define III 0.001
#define IV 0.0001
#define V 0.00001



//---------------------------------typedef----------------------------------//

//struct per le coordinate

typedef struct{


	double x;

	double v;


}vec;


//struct per i parametri

typedef struct{


	double m;		//massa

	double k;		//costante elastica

	double Dt;		//passo d'integrazione

	double tmax;		//tempo massimo di integrazione	

	int Nsteps;		//numero di passi

	double omega2;		//omega2 = k/m



}pars;

//------------------------prototipi delle funzioni--------------------------//




void syntax(int, char **);			//controllo sintassi di immissione

void check_array_double(double *);		//controlla che un array double dinamicamente allocato non sia vuoto

vec sum(vec, vec);				//somma per le struct

vec prod(vec, double);				//prodotto per le struct

vec velocity(vec, pars);			//calcola le velocita' secondo le eq differenziali del problema

vec ksum(vec, vec, vec, vec);			//somma con i coefficienti per Runge-Kutta 4, ovvero k1 + 2 k2 + 2 k3 + k4

vec forza(vec, pars);				//restituisce la derivata di x e v

double energia(vec, pars);			//calcola l'energia

double period(double *, pars);			//calcolo dei periodi




#endif

/*END BASIC.h*/
