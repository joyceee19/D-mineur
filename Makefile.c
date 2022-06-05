all: exec

  demineur: demineur.c 
          gcc -o demineur demineur.c 

exec: demineur
        ./demineur