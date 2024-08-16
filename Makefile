all : manager

manager : main.o manager.o graph.o label.o informant.o
	g++ main.o manager.o graph.o label.o informant.o -o manager -lsfml-graphics -lsfml-window -lsfml-system


main.o : main.cpp
	g++ -c main.cpp

manager.o : manager.cpp
	g++ -c manager.cpp

graph.o : graph.cpp
	g++ -c graph.cpp

label.o : label.cpp
	g++ -c label.cpp

informant.o : informant.cpp
	g++ -c informant.cpp

clean:
	rm -rf *.o manager
