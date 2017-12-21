#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "BASIC.h"
#include "METODI.h"



void eulero(vec phase0, pars par, double *xsaved){


	int i;

	double E0, E, err, t;

	vec phase;

	



	FILE *fp;

	char str[LEN];

	sprintf(str, "eulero_%lf_%lf.dat", par.Dt, par.tmax);
		
        fp=fopen(str, "w+");

        fprintf(fp, "#t\t x(t)\t v(t)\t E(t)\t (E(t)-E0)/E0\n");  //'legenda' commentata per gnuplot



	E0 = energia(phase0, par);



	for(i=0; i<par.Nsteps; i++){


		t = i * par.Dt;

		
		//aggiorno posizione e velocita'
		
		phase.x = phase0.x + phase0.v * par.Dt;

	       	phase.v = phase0.v - par.omega2 * phase0.x * par.Dt;


		//inserisco la posizione nell'array

		xsaved[i] = phase.x;



		//calcolo energia con relativo errore

		E = energia(phase, par);

		err = (E-E0)/E0;


		//stampa su file

		fprintf(fp, "%lf\t %lf\t %lf\t %lf\t %lf\n", t, phase.x, phase.v, E, err);



		phase0.x = phase.x;

		phase0.v = phase.v;


       }





	fclose(fp);


	return;

}




void eulerocromer(vec phase0, pars par, double *xsaved){


        int i;

        double E0, E, err, t;

	vec phase;





        FILE *fp;

	char str[LEN];

	sprintf(str, "eulerocromer_%lf_%lf.dat", par.Dt, par.tmax);

        fp=fopen(str, "w+");

        fprintf(fp, "#t\t x(t)\t v(t)\t E(t)\t (E(t)-E0)/E0\n");  //'legenda' commentata per gnuplot atm


        E0 = energia(phase0, par);



        for(i=0; i<par.Nsteps; i++){



                 t = i * par.Dt;



                 phase.v = phase0.v - par.omega2 * phase0.x * par.Dt;

		 phase.x = phase0.x + phase.v * par.Dt;


		 xsaved[i] = phase.x;



                 E = energia(phase, par);

                 err = (E-E0)/E0;



                 fprintf(fp, "%lf\t %lf\t %lf\t %lf\t %lf\n", t, phase.x, phase.v, E, err);



                 phase0.x = phase.x;
                 phase0.v = phase.v;


       }



	fclose(fp);



	return;

}




void puntocentrale(vec phase0, pars par, double *xsaved){


	int i;

	double E0, E, err, t;

	vec phase;






	FILE *fp;

	char str[LEN];

	sprintf(str, "PC_%lf_%lf.dat", par.Dt, par.tmax);


	fp=fopen(str, "w+");

	fprintf(fp, "#t\t x(t)\t v(t)\t E(t)\t (E(t)-E0)/E0\n");  //'legenda' commentata per gnuplot atm


	E0 = energia(phase0, par);



	for(i=0; i<par.Nsteps; i++){



		t = i * par.Dt;


		phase.v = phase0.v - par.omega2 * phase0.x * par.Dt;

		phase.x = phase0.x + ((phase.v + phase0.v) * 0.5) * par.Dt;


		xsaved[i] = phase.x;

		


		E = energia(phase, par);

		err = (E-E0)/E0;



		phase0.x = phase.x;

		phase0.v = phase.v;



		fprintf(fp, "%lf\t %lf\t %lf\t %lf\t %lf\n", t, phase.x, phase.v, E, err);




	}

	
	fclose(fp);

	

	return;

}





void Vverlet(vec phase0, pars par, double *xsaved){


	int i;

	double E0, E, err, t;

	vec phase;





	FILE *fp;

	char str[LEN];

	sprintf(str, "Vverlet_%lf_%lf.dat", par.Dt, par.tmax);


	fp=fopen(str, "w+");

	fprintf(fp, "#t\t x(t)\t v(t)\t E(t)\t (E(t)-E0)/E0\n");  //'legenda' commentata per gnuplot


	E0 = energia(phase0, par);



	for(i=0; i<par.Nsteps; i++){



		t = i * par.Dt;


		phase.x = phase0.x + (phase0.v * par.Dt) - 0.5 * (par.omega2 * phase0.x) * (par.Dt * par.Dt);

		phase.v = phase0.v - 0.5 * ((par.omega2 * phase0.x) + (par.omega2 * phase.x)) * par.Dt;


		xsaved[i] = phase.x;



		E = energia(phase, par);

		err = (E-E0)/E0;



		phase0.x = phase.x;

		phase0.v = phase.v;



		fprintf(fp, "%lf\t %lf\t %lf\t %lf\t %lf\n", t, phase.x, phase.v, E, fabs(err));




	}



	fclose(fp);


	return;


}




void Pverlet(vec phase0, pars par, double *xsaved){



	int i;

	double E0, E, err, t;

	vec phase;





	FILE *fp;

	char str[LEN];

	sprintf(str, "Pverlet_%lf_%lf.dat", par.Dt, par.tmax);


	fp=fopen(str, "w+");

	fprintf(fp, "#t\t x(t)\t v(t)\t E(t)\t (E(t)-E0)/E0\n");  //'legenda' commentata per gnuplot atm




	E0 = energia(phase0, par);

	double x1 = phase0.x + ((phase0.v * par.Dt) - (0.5 * (par.omega2 * (par.Dt * par.Dt))));




	for(i=0; i<par.Nsteps; i++){


		t = i * par.Dt;


		phase.x = (2 * x1) - phase0.x - ((par.omega2 * x1) * (par.Dt * par.Dt));

		phase.v = (phase.x - phase0.x)*0.5;


		xsaved[i] = phase.x;


		E = energia(phase, par);

		err = (E-E0)/E0;



		phase0.x = x1;

		x1 = phase.x;


		fprintf(fp, "%lf\t %lf\t %lf\t %lf\t %lf\n", t, phase.x, phase.v, E, fabs(err));




	}

	
	fclose(fp);


	return;

}



//integrazione con Runge-Kutta 2


void RK2(vec phase, pars par, double *xsaved){


        int i;

	double t, E, E0, err;




        FILE *fp;

	char str[LEN];

	sprintf(str, "rk2_%lf_%lf.dat", par.Dt, par.tmax);

        fp=fopen(str, "w+");

        fprintf(fp, "#t\t x(t)\t y(t)\t z(t)\t (E(t)-E0)/E0\n");



	E0 = energia(phase, par);





	for(i=0; i<par.Nsteps; i++){


		t = i * par.Dt;



		//phase = 


		xsaved[i] = phase.x;



		E = energia(phase, par);

		err = ((E - E0) / E0);



		fprintf(fp, "%.14lf\t %.14lf\t %.14lf\t %.14lf\t %.14lf\n", t, phase.x, phase.v, E, fabs(err));

		



       }

	fclose(fp);



	return;



}






//integrazione con Runge-Kutta 4

void RK4(vec phase, pars par, double *xsaved){


	int i;

	double t, E0, E, err;

	vec k1, k2, k3, k4;





	FILE *fp;

	char str[LEN];

	sprintf(str, "rk4_%lf.dat", par.Dt);

	fp = fopen(str, "w+");

	fprintf(fp, "#t\t x(t)\t v(t)\t E(t)\t E(t)-E0/E0\n");  //'legenda' commentata per gnuplot



	E0 = energia(phase, par);		





	for(i=0; i<par.Nsteps; i++){


		t = i * par.Dt;



		k1 = forza(phase, par);

		k2 = forza(sum(phase, prod(k1, (0.5 * par.Dt))), par);

		k3 = forza(sum(phase, prod (k2, (0.5 * par.Dt))), par);

		k4 = forza(sum(phase, prod(k3, par.Dt)), par);


		phase = sum(phase, prod(ksum(k1, k2, k3, k4), (par.Dt/6)));


		xsaved[i] = phase.x;	






		E = energia(phase, par);


		err = ((E - E0) / E0);




		fprintf(fp, "%lf\t %lf\t %lf\t %lf\t %.14lf\n", t, phase.x, phase.v, E, fabs(err));







	}


	fclose(fp);


	return;


}
