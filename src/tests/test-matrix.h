#pragma once
#include <iostream>
#include <iomanip>
#include "ludwig/types/types.h"

namespace ludwig::test
{
    static void print_matrix(Matrix<f64>& m)
    {
        std::cout << "\n    dim2:";
        for (u32 j = 0; j < m.dim2; j++)
            std::cout << std::setw(8) << j;
        std::cout << std::endl;
        std::cout << "-----------------------------------------------------\n";
        for (u32 i=0; i < m.dim1; i++)
        {
            std::cout << "dim1: " << i << " |";
            for (u32 j = 0; j < m.dim2; j++)
                std::cout << std::fixed << std::setw(8) << std::setprecision(3) << m(i,j);
            std::cout << std::endl;
        } 

        std::cout << std::endl;
        std::cout << "Memory Layout: ";
        for (u64 i = 0; i < m.size; i++)
            std::cout << std::fixed << std::setprecision(3) << std::setw(8) << m[i];
        std::cout << std::endl;
        std::cout << std::endl;

    }
    static void test_matrix_construction()
    {
        // Matrix default constructor
        std::cout << "======= Matrix() ====================================\n"; 
        std::cout << " >> Matrix<f64> M;\n";
        Matrix<f64> M;
        std::cout << "M.size: " << M.size << "\nM[0]: " << M[0] <<std::endl;
        M[0] = 1.01l;
        std::cout << " >> M[0] = 1.01l;\n";
        std::cout << "M.size: " << M.size << "\nM[0]: " << M[0] <<std::endl;

        // Matrix with size
        std::cout << "========= Matrix(u32 d1, u32 d2) ====================\n"; 
        std::cout << " >> Matrix<f64> M2x2(2,2);\n";
        Matrix<f64> M2x2(2,2);
        std::cout << "M.size: " << M2x2.size << std::endl;
        print_matrix(M2x2);
        std::cout << " >> M2x2(0,1) = 2.01l;\n";
        std::cout << " >> M2x2(1,1) = 3.01l;\n";
        M2x2(0,1) = 2.01l;
        M2x2(1,1) = 3.01l;
        print_matrix(M2x2);

        // Matrix with size and initial value
        std::cout << "========= Matrix(u32 d1, u32 d2, T init) ============\n"; 
        std::cout << " >> Matrix<f64> M2x2c(2,2, 3.2l);\n";
        Matrix<f64> M2x2c(2,2, 3.2l);
        std::cout << "M.size: " << M2x2c.size << std::endl;
        print_matrix(M2x2c);
        std::cout << " >> M2x2c(0,1) = 2.01l;\n";
        std::cout << " >> M2x2c(1,1) = 3.01l;\n";
        M2x2c(0,1) = 2.01l;
        M2x2c(1,1) = 3.01l;
        print_matrix(M2x2c);

        // Matrix with size and initial value array
        std::cout << "========= Matrix(u32 d1, u32 d2, T* init) ===========\n"; 
        std::cout << " >> f64 inital_values[4] = {0.0, 1.0, 2.0, 3.0};\n";
        f64 initial_vaules[4] = {0.0, 1.0, 2.0, 3.0};
        std::cout << " >> Matrix<f64> M2x2a(2,2, initial_values);\n";
        Matrix<f64> M2x2a(2,2,initial_vaules);
        std::cout << "M.size: " << M2x2a.size << std::endl;
        print_matrix(M2x2a);
        std::cout << " >> M2x2a(0,1) = 2.01l;\n";
        std::cout << " >> M2x2a(1,1) = 3.01l;\n";
        M2x2a(0,1) = 2.01l;
        M2x2a(1,1) = 3.01l;
        print_matrix(M2x2a);

        // Matrix copy
        std::cout << "========= Matrix(Matrix& other) ===========\n"; 
        std::cout << " >> Matrix<f64> Mcopy = M2x2a;\n";
        Matrix<f64> Mcopy = M2x2a;
        std::cout << "M.size: " << Mcopy.size << std::endl;
        print_matrix(Mcopy);
        std::cout << " >> Mcopy = M2x2c;\n";
        Mcopy = M2x2c;
        print_matrix(Mcopy);
        {
            // Matrix Move
            std::cout << "========= Matrix(Matrix&& other) ===========\n"; 
            std::cout << " >> f64 data[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};\n";
            std::cout << " >> Matrix<f64> A(3,3,data);\n";
            f64 data[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
            Matrix<f64> A(3,3,data);
            print_matrix(A);
            Matrix<f64> B = std::move(A);
            print_matrix(A);
            print_matrix(B);
        }
    }

    static void test_matrix_arithmatic()
    {
        {
            // Equality
            std::cout << "========= Matrix A == Matrix B ===================\n"; 
            std::cout << " >> Matrix<f64> A(2,3,1.0l);\n";
            std::cout << " >> Matrix<f64> B(2,3,1.0l);\n";
            std::cout << " >> Matrix<f64> C(3,2,1.0l);\n";
            std::cout << " >> Matrix<f64> D(2,2,2.0l);\n";
            std::cout << " >> Matrix<f64> E(2,2,0.0l);\n";
            Matrix<f64> A(2,3,1.0l);
            Matrix<f64> B(2,3,1.0l);
            Matrix<f64> C(3,2,1.0l);
            Matrix<f64> D(2,2,2.0l);
            Matrix<f64> E(2,2,0.0l);
            std::cout << " A == B : (expect 1) " << (A == B) << std::endl; 
            std::cout << " B == A : (expect 1) " << (B == A) << std::endl; 
            std::cout << " A == C : (expect 0) " << (A == C) << std::endl; 
            std::cout << " A == D : (expect 0) " << (A == D) << std::endl; 
            std::cout << " D == A : (expect 0) " << (D == A) << std::endl; 
            std::cout << " A == 0 : (expect 0) " << (A == 0) << std::endl; 
            std::cout << " A == 1 : (expect 0) " << (A == 1) << std::endl; 
            std::cout << " E == 0 : (expect 1) " << (E == 0) << std::endl; 
            std::cout << " E == 1 : (expect 0) " << (E == 1) << std::endl; 
        }

        {
            std::cout << "========= Matrix A + scalar ======================\n"; 

            std::cout << " >> f64 data[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};\n";
            std::cout << " >> Matrix<f64> A(2,3,data);\n";
            f64 data[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
            Matrix<f64> A(2,3,data);
            std::cout << " --- A --- \n";
            print_matrix(A);

            std::cout << " >> Matrix<f64> B = A + 5.0;\n";
            Matrix<f64> B = A + 5.0;
            std::cout << " --- A --- \n";
            print_matrix(A);
            std::cout << " --- B --- \n";
            print_matrix(B);

            std::cout << " >> Matrix<f64> C = 5.0 + A;\n";
            Matrix<f64> C = 5.0 + A;
            std::cout << " --- A --- \n";
            print_matrix(A);
            std::cout << " --- C --- \n";
            print_matrix(C);
            std::cout << " >> A += 5.0;\n";
            A += 5.0;
            print_matrix(A);
        }
    
        {
            std::cout << "========= Matrix A + Matrix B =======================\n"; 

            std::cout << " >> f64 dataA[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};\n";
            std::cout << " >> f64 dataB[7] = {1.0, 3.0, 5.0, 7.0, 9.0, 11.0};\n";
            std::cout << " >> Matrix<f64> A(2,3,dataA);\n";
            std::cout << " >> Matrix<f64> B(2,3,dataB);\n";
            f64 dataA[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
            f64 dataB[7] = {1.0, 3.0, 5.0, 7.0, 9.0, 11.0};
            Matrix<f64>  A(2, 3, dataA);
            Matrix<f64>  B(2, 3, dataB);

            std::cout << " --- A --- \n";
            print_matrix(A);
            std::cout << " --- B --- \n";
            print_matrix(B);
        
            std::cout << " >> Matrix<f64> C = A + B;\n";
            Matrix<f64> C = A + B;
            std::cout << " --- A --- \n";
            print_matrix(A);
            std::cout << " --- C --- \n";
            print_matrix(C);
            std::cout << " >> A += C;\n";
            A += C;
            print_matrix(A);
        }
        {
            std::cout << "========= Matrix A x Matrix B =======================\n"; 
            std::cout << " >> f64 dataA[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};\n";
            std::cout << " >> f64 dataB[7] = {1.0, 3.0, 5.0, 7.0, 9.0, 11.0};\n";
            std::cout << " >> Matrix<f64> A(2,3,dataA);\n";
            std::cout << " >> Matrix<f64> B(3,2,dataB);\n";
            f64 dataA[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
            f64 dataB[7] = {1.0, 3.0, 5.0, 7.0, 9.0, 11.0};
            Matrix<f64>  A(2, 3, dataA);
            Matrix<f64>  B(3, 2, dataB);

            std::cout << " --- A --- \n";
            print_matrix(A);
            std::cout << " --- B --- \n";
            print_matrix(B);

            std::cout << " >> Matrix<f64> C = A * B;\n";
            Matrix<f64> C = A * B;
            std::cout << " --- A --- \n";
            print_matrix(A);
            std::cout << " --- C --- \n";
            print_matrix(C);
        
            std::cout << " >> Matrix<f64> D = B * A;\n";
            Matrix<f64> D = B * A; 
            std::cout << " --- D --- \n";
            print_matrix(D);

            std::cout << " >> Matrix<f64> D *= 0.5;\n";
            D *= 0.5; 
            std::cout << " --- D --- \n";
            print_matrix(D);
        }
        {
            std::cout << "========= Identity Matrix: I=======================\n"; 
            Matrix<f64> I3 = IdentityMatrix<f64>(3);
            print_matrix(I3);
            Matrix<f64> I5 = IdentityMatrix<f64>(5);
            print_matrix(I5);
            f64 data[9] = {2.0, 1.0, 0.0, 1.0, 0.0, 3.0, 1.0, 1.0, 1.0};
            Matrix<f64> A(3,3,data);
            A = IdentityMatrix<f64>(A);
            print_matrix(A);
        }
    }
    static void test_matrix_determinant()
    {
        std::cout << "========= |Matrix A| =============================\n"; 
        f64 data[9] = {
            2.0, 1.0, 1.0,
            1.0, 0.0, 1.0, 
            0.0, 3.0, 1.0
        };
        Matrix<f64> A(3,3,data);
        print_matrix(A);
        f64 d = Determinant(A);
        std::cout << " |A| = " << d << std::endl;
    }

    static void test_matrix()
    {
        test_matrix_construction();
        test_matrix_arithmatic();
        test_matrix_determinant();
        // test_matrix_submatrix();
        // test_matrix_inverse();
    }
}
