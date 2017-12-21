/*libreria con funzioni generiche non inerenti al problema dell'integrazione di equazioni differenziali. Il corrispondente file header e' BASIC.h*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#include "BASIC.h"





//controllo sintassi di immissione

void syntax(int argc, char* argv[]){


	if(argc != A){


		fprintf(stderr,"ERROR! Syntax: %s <algorithm> <x0> <v0> <k> <m> <tmax> <Dt>\n", argv[0]);

		fprintf(stderr,"<algorithm>:\n\n\t1 for Euler;\n\t2 for Euler-Cromer;\n\t3 for central poinnt;\n\t4 for Velocity Verlet;\n\t5 for Position Verlet;\n\t6 for Runge-Kutta 2;\n\t7 for Runge-Kutta 4.\n\n");

		exit(EXIT_FAILURE);


	}


}


void check_array_double(double *array){


	if(array == NULL){


		fprintf(stderr, "ERRORE! Allocazione dinamica di memoria non riuscita.\n\n");

		exit(EXIT_FAILURE);


	}



}



//somma per vec 

vec sum(vec a, vec b){


	vec res;


	res.x = a.x + b.x;

	res.v = a.v + b.v;

	

	return res;


}




//prodotto per vec


vec prod(vec a, double scalar){

	vec res;


	res.x = scalar * a.x;

	res.v = scalar * a.v;


	return res;


}



//coefficienti per RK4 (k1 + 2*k2 + 2*k3 + k4)


vec ksum(vec a, vec b, vec c, vec d){


	vec res;


	res.x = a.x + 2 * b.x + 2 * c.x + d.x;

	res.v = a.v + 2 * b.v + 2 * c.v + d.v;


	return res;


}



vec forza(vec phase, pars par){


	vec res;


	res.x = phase.v;

	res.v = -(par.omega2) * phase.x;


	return res;


}



//calcola l'energia


double energia(vec phase, pars p){


	return ((0.5 * p.m * (phase.v * phase.v)) + (0.5 * p.k * (phase.x * phase.x)));


}







//calcolo dei periodi con metodo dei semiperiodi

double period(double xsaved[], pars par){


 
	int i, j = 0;
	  
	double rif = 1.;		//posizione di riferimento 

	double *intercept, *difference;	//array per le intercette e differenze
  
	int Nint;			//numero intercette, ie lunghezza per l'array



  
	FILE *fp;

	double Aavg, Bavg, Asum, Bsum, T;

	int M;

  

	for(i = 0; i <= par.Nsteps; i++){  


		if( (xsaved[i] - rif) * (xsaved[i + 1] - rif) <= 0.){
      
			Nint++;
    
		}
  
	}




	intercept = (double *)calloc(Nint, sizeof(double));

	difference = (double *)calloc(Nint, sizeof(double));




	if(intercept == NULL || difference == NULL){

  
		fprintf(stderr, "ERRORE! Allocazione di memoria non riuscita. (periodi)\n");
    
    
		exit(EXIT_FAILURE);
  
	}



	//calcolo i tempi da mettere nell'array delle intercette

	for(i = 0; i <= par.Nsteps; i++){


		if( (xsaved[i] - rif) * (xsaved[i + 1] - rif) <= 0.){



			intercept[j] =  (i * par.Dt) - par.Dt * (xsaved[i] - rif) / (xsaved[i + 1] - xsaved[i]); 


		if(j < Nint){
			
			
				j++;
		
		
			} 

	
	
		if( (xsaved[i + 1] - rif) == 0){ //per non mettere lo stesso valore due volte, salta un ciclo se 0
		
		
			i++;
		

			}


		}


	}





	//mette in difference[j] le differenze fra le intercette
	


	for(j = 0; j < Nint; j++){


		difference[j] = intercept[j + 1] - intercept[j];


	}




	//salvo le intercette e le differenze su un file... giusto per sicurezza
	


	fp = fopen("int-diff.dat", "w+");



	if(fp == NULL){


		fprintf(stderr, "Errore nella creazione del file!\n");
		
		exit(EXIT_FAILURE);
	
	
	}




	for(j = 0; j < (Nint - 1); j++){ //uso Nint - 1 perche' sia coerente con gli altri dati


	
		fprintf(fp, "%d\t\t%.10lf\t\t %.10lf\n", j, intercept[j], difference[j]);
	

	}




	//calcolo dei semiperiodi medi
	

	M = 0;	
	
	
	for(i = (int)((Nint - 1)/2.); i < (Nint - 1); i += 2){


		Asum += difference[i];
		
		M++;


	}
	
	
	Aavg = Asum / (double)(M);




	M = 0;

	for(i = ( (int)((Nint - 1)/2.) + 1 ); i < (Nint - 1); i += 2){


		Bsum += difference[i];
		
		M++;
	
	
	}


	Bavg = Bsum / (double)(M);




	
	free(intercept);
	
	free(difference);

	//il periodo e' la somma dei semiperiodi medi
	

	T = Aavg + Bavg;
	
	
	
	return T;
}
  
