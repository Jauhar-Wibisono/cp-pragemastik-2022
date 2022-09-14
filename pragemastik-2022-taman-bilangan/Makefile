PROB_ID = "taman"
PROB_SLUG = $(shell basename $(CURDIR)) 
PROB_NAME = "Taman Bilangan"
TIME_LIMIT = 2
MEM_LIMIT = 256

generate_problem:
	@cd ..; \
	bash generate-problem.sh ${PROB_ID} ${PROB_SLUG} ${PROB_NAME} ${TIME_LIMIT} ${MEM_LIMIT} "./zips/"