depend: capstone-depend
capstone-depend:
	cdeps src/capstone > src/capstone/depends.makefile

tests: capstone-tests
capstone-tests: test/list-primes
capstone-tests: test/list-indices
capstone-tests: capstone-utils

run-tests: run-capstone-tests
run-capstone-tests:
	sh run-tests.sh test/list-primes test/list-indices

test/list-primes: LDLIBS += -lm
test/list-primes: \
	src/capstone/test/list-primes/test.o \
	src/capstone/list-primes.o \
	src/capstone/is-prime.o \

test/list-indices: \
	src/capstone/test/list-indices/test.o \
	src/capstone/tuple-index.o \

bin/prime-sums: LDLIBS += -lm
bin/prime-sums: \
	src/capstone/util/prime-sums/util.o \
	src/range/alloc.o \
	src/capstone/prime-sums.o \
	src/table/pointer.o \
	src/window/alloc.o \
	src/capstone/list-primes.o \
	src/capstone/tuple-index.o \
	src/capstone/is-prime.o \

capstone-utils: bin/prime-sums

C_PROGRAMS += test/list-primes
C_PROGRAMS += test/list-indices
C_PROGRAMS += bin/prime-sums
