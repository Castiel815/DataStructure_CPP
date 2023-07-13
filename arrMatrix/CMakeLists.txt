include_directories(../base)

project(arrMatrix)

add_executable(arrMatrix main.cpp matrix.h matrix.cpp diagonalMatrix.cpp diagonalMatrix.h
        triDiagonalMatrix.cpp triDiagonalMatrix.h lowerTriangularMatrix.cpp lowerTriangularMatrix.h)
