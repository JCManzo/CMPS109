MKFILE    = Makefile

#
# Definitions of list of files:
#
#HSOURCES  =
CSOURCES  = graph.cpp

ETCSRC    = README ${MKFILE}
EXECBIN   = graph
ALLCSRC   = ${CSOURCES}
OBJECTS   = ${ALLCSRC:.cpp=.o}
ALLSRC    = ${ETCSRC} ${HSOURCES} ${CSOURCES}
LISTSRC   = ${ALLSRC}

#
# Definitions of the compiler and compilation options:
#
GCC       = g++ -std=c++11

#
# The first target is always ``all'', and hence the default,
# and builds the executable images
#
all : ${EXECBIN}

#
# Build the executable image from the object files.
#
${EXECBIN} : ${OBJECTS}
	${GCC} -o ${EXECBIN} ${OBJECTS}

#
# Build an object file form a C source file.
#
%.o : %.cpp
	${GCC} -c $<

#
# Clean and spotless remove generated files.
#
clean :
	- rm -rf ${EXECBIN}

