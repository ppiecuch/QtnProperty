bison.name = Bison ${QMAKE_FILE_IN}
bison.input = BISON_SOURCES
bison.output = ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.parser.cpp

win32:bison.commands = win_bison -d -o ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.parser.cpp ${QMAKE_FILE_IN}
linux:bison.commands = bison -d -o ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.parser.cpp ${QMAKE_FILE_IN}
# prefere /opt/local/bin/bison over bison from path (we need recent version of bison)
macx:exists(/opt/local/bin/bison):bison.commands = /opt/local/bin/bison -d -o ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.parser.cpp ${QMAKE_FILE_IN}
else:bison.commands = bison -d -o ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.parser.cpp ${QMAKE_FILE_IN}

#-Wmidrule-value -t

bison.CONFIG += targets_predeps
bison.variable_out = GENERATED_SOURCES
silent:bison.commands = @echo Bison ${QMAKE_FILE_IN} && $$bison.commands
QMAKE_EXTRA_COMPILERS += bison
