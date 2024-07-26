parametrosCompilacao = -g -I/usr/include/x86_64-linux-gnu -lallegro_main -lallegro_font -lallegro_primitives -lallegro_image -lallegro -lm

all: shadowCombat

shadowCombat: main.o stateMachine.o character.o fighter.o health.o screen.o joystick.o 
	gcc -o shadowCombat main.o stateMachine.o character.o fighter.o health.o screen.o joystick.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

stateMachine.o: ../include/stateMachine.h stateMachine.c
	gcc -c stateMachine.c $(parametrosCompilacao)

character.o: ../include/character.h character.c
	gcc -c character.c $(parametrosCompilacao)

fighter.o: ../include/fighter.h fighter.c
	gcc -c fighter.c $(parametrosCompilacao)

health.o: ../include/health.h health.c
	gcc -c health.c $(parametrosCompilacao)

screen.o: ../include/screen.h screen.c
	gcc -c screen.c $(parametrosCompilacao)

joystick.o: ../include/joystick.h joystick.c
	gcc -c joystick.c $(parametrosCompilacao)

clean:
	rm -f *.o

purge:
	rm -f *.o shadowCombat
