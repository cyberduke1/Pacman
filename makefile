CC = g++
Debug = -Isource/Include -Lsource/lib -Isource/sources/headerfile
MAINFILELOCATION = source/sources/src/main.cpp
TESTFILELOCATION = source/sources/src/test.cpp
HEADERS := -Isource/sources/headerfile
OBJECTFILE = main
BUILDDIR = source/build
LIBRARIES = -lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf  -lSDL2_mixer -lSDL2
BIN_DIR = source/bin

all:
	@${CC} ${Debug} ${MAINFILELOCATION} -o ${BIN_DIR}/${OBJECTFILE} ${LIBRARIES}

test: ${TESTFILELOCATION}
	${CC} ${Debug} ${TESTFILELOCATION} -o ${BIN_DIR}/${OBJECTFILE} ${LIBRARIES}