project(external_code)

add_executable(ext Vector.cpp Vector.h main.cpp Menu.cpp Menu.h TruthTable.cpp TruthTable.h)

set(EXECUTABLE_OUTPUT_PATH ..)