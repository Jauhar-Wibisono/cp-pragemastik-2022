PROB_ID = "pensil"
PROB_SLUG = $(shell basename $(CURDIR)) 
PROB_NAME = "Kotak Pensil"
TIME_LIMIT = 1
MEM_LIMIT = 256

generate_problem:
	@cd ..; \
	bash generate-problem.sh ${PROB_ID} ${PROB_SLUG} ${PROB_NAME} ${TIME_LIMIT} ${MEM_LIMIT} "./zips/"

grade:
	g++ -std=c++17 solution.cpp -o solution
	
	g++ -std=c++17 scorer.cpp -o scorer
	./runner grade --solution=./solution --scorer=./scorer