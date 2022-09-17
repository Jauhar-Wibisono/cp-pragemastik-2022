PROB_ID = "jenga"
PROB_SLUG = $(shell basename $(CURDIR)) 
PROB_NAME = "Bermain Jenga"
TIME_LIMIT = 1
MEM_LIMIT = 256

generate_problem:
	@cd ..; \
	bash generate-problem.sh ${PROB_ID} ${PROB_SLUG} ${PROB_NAME} ${TIME_LIMIT} ${MEM_LIMIT} "./zips/"