LD=g++
CXX=g++ -g -c

EXEC_SRC=\
	testGrayLevelImage2D.cpp\
	testColorImage2D.cpp\
	invert-red-blue.cpp\
    save-green-channel.cpp\
	save-channels.cpp\
    cathodic-screen.cpp\
    generate-histogramme.cpp\
    egaliseur-graylevel.cpp\
    egaliseur-couleur.cpp\
    sepia.cpp

MODULE_SRC=\

MODULE_OBJ=${MODULE_SRC:.cpp=.o}
EXEC_OBJ=${EXEC_SRC:.cpp=.o}

EXEC_PRG=${EXEC_SRC:.cpp=}

all: ${EXEC_PRG} ${MODULE_OBJ} ${EXEC_OBJ}

testGrayLevelImage2D: testGrayLevelImage2D.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

testColorImage2D: testColorImage2D.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

invert-red-blue: invert-red-blue.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

save-green-channel: save-green-channel.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

save-channels: save-channels.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

cathodic-screen: cathodic-screen.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

generate-histogramme: generate-histogramme.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

egaliseur-graylevel: egaliseur-graylevel.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

egaliseur-couleur: egaliseur-couleur.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

sepia: sepia.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

.cpp.o: %.cpp %.hpp
	${CXX} $<

clean:
	rm -f ${EXEC_PRG} ${MODULE_OBJ} ${EXEC_OBJ}