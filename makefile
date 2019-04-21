all: main analysis

main: main.cpp searches.cpp
	g++ main.cpp searches.cpp -o main

analysis: analysis.cpp searches.cpp
	g++ analysis.cpp searches.cpp -o analysis
