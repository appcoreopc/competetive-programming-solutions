SHELL:=/bin/zsh

app: main.cpp
	g++ -std=c++14 -g -o main.out main.cpp

runner: app runner.cpp
	if [[ ! -a runner.out ]]; then g++ -std=c++14 -g -o runner.out runner.cpp; fi;
	./runner.out > runner.log
	code runner.log
