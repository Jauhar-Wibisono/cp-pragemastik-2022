PROB_ID = "closest cell"
PROB_SLUG = $(shell basename $(CURDIR)) 
PROB_NAME = "Closest Cell 2"
TIME_LIMIT = 1
MEM_LIMIT = 256

generate_problem:
	@cd ..; \
	bash generate-problem.sh ${PROB_ID} ${PROB_SLUG} ${PROB_NAME} ${TIME_LIMIT} ${MEM_LIMIT} "./zips/"