#ifndef METODI_H_
#define METODI_H_


//prototipi dei metodi di integrazione


void eulero(vec, pars, double *);		//integrazione con metodo di Eulero

void eulerocromer(vec, pars, double *);		//integrazione con metodo di Eulero-Cromer

void leapfrog(vec, pars, double *);		//integrazione con leapfrog	
	
void puntocentrale(vec, pars, double *);	//integrazione con metodo del punto centrale

void Vverlet(vec, pars, double *);		//integrazione con Velocity Verlet

void Pverlet(vec, pars, double *);		//integrazione con Position Verlet

void RK2(vec, pars, double *);			//integrazione con Runge-Kutta 2

void RK4(vec, pars, double *);			//integrazione con Runge-Kutta 4

#endif 

/*END METODI.h*/
