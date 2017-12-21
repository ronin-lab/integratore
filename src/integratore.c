/*Il programma integra le equazioni differenziali di un moto armonico, utilizzando come appoggio due librerie distinte con relativi file header .h (METODI.c con i metodi di integrazione e BASIC.c con typedef e altre funzioni di "base", ovvero non specificatamente inerenti all'integrazione delle equazioni differenziali). La scelta e' stata quindi di lasciare il main (integratore.c) il piu' libero possibile, per rendere piu' chiaro il funzionamento del programma e rendere migliore il controllo di eventuali problemi. Inoltre si e' scelto di utilizzare la pratica standard del linguaggio C, ovvero di non utilizzare il file .h come se fosse una libreria, ma appunto come file header con solo le dichiarazioni delle funzioni.
La compilazione delle librerie avviene nella seguente maniera:

gcc -Wall -Wextra -lm -o BASIC.o -c BASIC.c
gcc -Wall -Wextra -lm -o METODI.o -c METODI.c

Si compila poi il programma:

gcc -Wall -Wextra -lm integratore.c

In ogni caso le librerie sono state lasciate gia' compilate (e la procedura viene descritta anche nel file README per sicurezza). In alternativa puo' essere tutto gestito con il makefile, che compila librerie e programma, esegue il programma, lancia uno script per creare automaticamente i vari grafici su gnuplot e li sposta in una cartella separata.*/






#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#include "BASIC.h" //file header della corrispondente libreria BASIC.c con funzioni utili, typedef ecc
#include "METODI.h" //file header della corrispondente libreria METODI.c con le funzioni dei metodi di integrazione




int main(int argc, char* argv[]){


	//dichiarazioni variabili
	
	vec phase0;			//struct che contiene la fase iniziale

	pars par;			//struct con i parametri del problema: k, m, Dt, tmax e metodo di integrazione

	int alg;			//scelta dell'algoritmo


	double *xsaved;			//array con posizioni per salvare i periodi

	double T;			//periodo



	//controllo immissione da terminale
	

	syntax(argc, argv);



	//assegnazione variabili passate da terminale
	

	alg = atoi(argv[1]);

	phase0.x = atof(argv[2]);

	phase0.v = atof(argv[3]);

	par.k = atof(argv[4]);

	par.m = atof(argv[5]);

	par.tmax = atof(argv[6]);

	par.Dt = atof(argv[7]);

	//par.iter = atoi(argv[8]); //numero iterazioni
	



	//calcolo numero di passi e omega2
	

	par.Nsteps = (int) (par.tmax)/(par.Dt);	//va castato meglio perche' sia int?? check

	par.omega2 = (par.k)/(par.m);
	

	printf("%lf %d", par.omega2, par.Nsteps);

	//allocazione dinamica per l'array con le posizioni e controllo allocazione
	

	xsaved = calloc(par.Nsteps, sizeof(double));

	check_array_double(xsaved);

	



	//implementazione algoritmo scelto

	if(alg == 1){


		eulero(phase0, par, xsaved);


	}else if(alg == 2){


		eulerocromer(phase0, par, xsaved);


	}else if(alg == 3){


		puntocentrale(phase0, par, xsaved);


	}else if(alg == 4){


		Vverlet(phase0, par, xsaved);


	}else if(alg == 5){


		Pverlet(phase0, par, xsaved);


	}else if(alg == 6){


		RK2(phase0, par, xsaved);


	}else if(alg == 7){


		RK4(phase0, par, xsaved);


	}else{


		fprintf(stderr, "ERRORE! Passaggio di <algoritmo> errato.\n\n");

		exit(EXIT_FAILURE);


	}





	//calcolo dei periodi

	T = period(xsaved, par);

	printf("%lf", T);




	free(xsaved);		
	



	return(0);

			

}
