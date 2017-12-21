#!/bin/bash
#
#
#######lo script e' settato in modo che l'eseguibile creato si chiami "integratore". Modificare il nome dell'eseguibile se non e' questo il caso. Si utilizza l'equivalente per scanf dello script bash per settare i parametri passati da riga comando; si e' scelto di fare cosi' in modo che possa avvenire tutto tramite il comando make (compilazione, esecuzione e creazione dei grafici). Tuttavia l'input da terminale e' stato lasciato nel caso il tutto non avvenga tramite make (lo abbiamo trovato preferibile sia stilisticamente che a livello di risorse rispetto a scanf o l'immissione tramite file). 
#Sotto a questo commento e' stato anche inserita (commentata) la procedura per la compilazione, permettendo di utilizzare quest'unico script come pseudo makefile se necessario (cosa che non ha troppo senso in quanto esiste gia' il comando make...). Decommentare le righe seguenti se si vuole seguire questa strada. 


#-------compilazione, decommentare se si vuole farla eseguire allo script----------#

#echo
#gcc -O3 -Wall -Wextra -lm -o BASIC.o -c BASIC.c
#gcc -O3 -Wall -Wextra -lm -o METODI.o -c METODI.c
#gcc -O3 -Wall -Wextra -lm integratore.c BASIC.o METODI.o -o integratore
#echo


#la prima volta si esegue il programma senza argomenti, in modo da dare il messaggio di errore e spiegare all'utente l'ordine di inserimento degli argomenti senza dover stampare ulteriormente a schermo

echo
./integratore
echo


read c x0 v0 k m tmax 

let "i = 1" 

while [ $i -lt 5 ]  
do

echo $i

echo
./integratore $c $a $b $rho $x0 $y0 $z0 $tmax $i
echo

let i++

done

echo 
read -p $'inserire numero per algoritmo integrazione:\n 1 = Velocity Verlet,\n 2 = Position Verlet,\n 3 = Runge-Kutta 2,\n 4 = Runge-Kutta 4\n \n ' c
echo

if [ $c -eq 1  ]
then 

name="Vverlet"

elif [ $c -eq 2  ]
then 

name="Pverlet"

elif [ $c -eq 3  ]
then 

name="RK2"

elif [ $c -eq 4  ]
then 

name="RK4"

 
fi

echo $name

echo 
read -p $'inserire:\n 0 per inizializazione della parte 1:\n \tparametri a=0, b=0, rho=0.2\n \tCI di x(0)=1.2, y(0)=0.5, z(0)=0;\n \n 1 per inserimento manuale\n ' g
echo 

if [ $g -eq 0 ]
then

let "a=0" 
let "b=0" 
let "rho=0.2" 
let "m=1" 
let "tmax=100"

elif [ $g -eq 1 ]
then 

echo 
let "a=0.5"
let "b=0.1"
let "x0=1.2"
let "y0=0.5"
let "z0=0.3"
read -p $'inserire: a b rho x0 y0 z0 tmax\n ' tmax rho 
echo

echo $c $a $b $x0 $y0 $z0 $tmax $rho
read 

fi




## gnuplot

echo 
read -p $'scegliere # iterazioni da plottare:\n 1 per 10^-1,\n 2 per 10^-2,\n 3 per 10^-3,\n 4 per 10^-4,\n 5 per 10^-5\n \n ' z
echo


echo 
read -p $'scegliere grafico da plottare:\n x(t) ->1\n v(t) ->2\n v(x)->3\n E(t) ->4\n E(t)-E(0)/E(0) vs t ->5\n \n ' x 
echo


if [ $x -eq 1  ] 
then 

var1="t"
var2="x"
x=1
y=2

elif [ $x -eq 2  ] 
then 

var1="t"
var2="v"
x=1
y=3


elif [ $x -eq 3  ] 
then 

var1="x"
var2="v"
x=2
y=3

elif [ $x -eq 4  ] 
then 

var1="t"
var2="E"
x=1
y=4


elif [ $x -eq 5  ] 
then 

var1="t"
var2="E(t)-E(0)/E(0)"
x=1
y=5
 
fi

echo > gnuplot.in
for FILE in *; do 
echo "set term 'x11'" >> gnuplot.in
echo "plot '${name}_${z}.dat' u ${x}:${y} title '${var2}(${var1})'" >> gnuplot.in
echo "set term post color eps" >> gnuplot.in
echo "set output '${name}_${z}.eps'" >> gnuplot.in
echo "rep" >> gnuplot.in
done

gnuplot -persist gnuplot.in

echo
mkdir risultati
mv *.dat risultati/
mv *.eps risultati/
echo 

echo
ls 
echo

echo 
rm gnuplot.in
echo


exit
