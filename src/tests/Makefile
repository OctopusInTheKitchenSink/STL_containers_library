FLAGS = -lgtest -lgmock -lgtest_main -pthread -g -O0 -fprofile-arcs -ftest-coverage
GCOV = gcov *.gcno *.gcda
GCOVR = gcovr -r . --html --html-details -o coverage_report.html --filter
CC = g++
OPEN_REP = open coverage_report.html

.PHONY: clean test_queue gcov_queue test_stack gcov_stack test2 test_set gcov_set rb valgrind gcov_map test_map

clean:
	rm *.gcno *.gcda *.gcov *.html *.css test_stack test_queue test_list test test_vector test_map test_array test_multiset test_set

all: gcov_common

test_queue: 
	$(CC) s21_test_queue.cpp -o $@ ../Container_Adaptor/queue/s21_queue.cpp $(FLAGS)
	./$@
	
test_list:
	$(CC) s21_test_list.cpp -o $@ ../Sequence_Containers/list/s21_list.cpp $(FLAGS)
	./$@

gcov_list: test_list
	$(GCOV)
	$(GCOVR) "../Sequence_Containers/list/s21_list.*" 
	$(OPEN_REP)

test_map:
	$(CC) s21_test_map.cpp -o test_map ../Sorted_Container/map/s21_map.cpp $(FLAGS)
	./$@

gcov_map: test_map
	$(GCOV)
	$(GCOVR) "../Sorted_Container/map/s21_map.*" 
	$(OPEN_REP)

gcov_queue: test_queue
	$(GCOV)
	$(GCOVR) "../Container_Adaptor/queue/s21_queue.h"
	$(OPEN_REP)

test_stack: 
	$(CC) s21_test_stack.cpp -o $@ ../Container_Adaptor/stack/s21_stack.cpp $(FLAGS)
	./$@

gcov_stack: test_stack
	$(GCOV)
	gcovr -r . --html --html-details -o coverage_report.html
	$(OPEN_REP)

test_vector: 
	$(CC) s21_test_vector.cpp -o $@ ../Sequence_Containers/vector/s21_vector.cpp $(FLAGS)
	./$@

gcov_vector: test_vector
	$(GCOV)
	$(GCOVR) "../Sequence_Containers/vector/s21_vector.*" 
	$(OPEN_REP)

test_set:
	$(CC) s21_test_set.cpp -o test_set ../Sorted_Container/Set_Conteiner/s21_set.cpp $(FLAGS)
	./$@

gcov_set: test_set
	$(GCOV)
	gcovr -r . --html --html-details -o coverage_report.html
	$(OPEN_REP)

test_multiset:
	g++ -std=c++20 s21_test_multiset.cpp ../Sorted_Container/Set_Conteiner/s21_multiset.cpp -o test_multiset $(FLAGS)
	./$@

gcov_multiset: test_multiset
	$(GCOV)
	$(GCOVR) "../Sorted_Container/Set_Conteiner/s21_multiset.h"
	$(OPEN_REP)

gcov_common: test_queue test_stack test_set test_multiset test_vector test_map test_list
	gcov --branch-probabilities --branch-probabilities --object-directory *.gcno *.gcda 
	$(GCOVR)="../Sorted_Container/Set_Conteiner/s21_multiset.h" \
	--filter="../Sorted_Container/Set_Conteiner/s21_set.h" \
	--filter="../Container_Adaptor/stack/s21_stack.h" \
	--filter="../Container_Adaptor/queue/s21_queue.h" \
	--filter="../Sequence_Containers/vector/s21_vector.*" \
	--filter="../Sorted_Container/map/s21_map.*" \
	--filter="../Sequence_Containers/list/s21_list.*" 
	$(OPEN_REP)
