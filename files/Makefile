CC = g++
Debug = -IInclude -Llib 
MAINFILELOCATION = src/main.cpp
#TESTFILELOCATION = src/test.cpp
#HEADERS := -Isource/sources/headerfile
OBJECTFILE = main
LIBRARIES = -lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf  -lSDL2_mixer -lSDL2
BIN_DIR = bin

all:
	@${CC} ${Debug} ${MAINFILELOCATION} -o ${BIN_DIR}/${OBJECTFILE} ${LIBRARIES}

test: ${TESTFILELOCATION}
	${CC} ${Debug} ${TESTFILELOCATION} -o ${BIN_DIR}/${OBJECTFILE} ${LIBRARIES}