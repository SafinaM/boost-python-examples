
PYTHON_ADD_MODULE(example single.cpp some.cpp wrap.cpp)
FILE(COPY some.py DESTINATION .)
ADD_TEST(NAME some COMMAND ${PYTHON_EXECUTABLE} some.py)

