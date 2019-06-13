//
// Created by gomonuk on 05.01.19.
//

#include <iostream>
#include <valarray>
class Matrix {
    std::valarray<int> data;
    std::valarray<int> data1;
    int dim;
public:
    Matrix(int r, int c) : data(r*c), dim(c) {}
    int& operator()(int r, int c) {return data[r*dim + c];}
    int trace() const {
        data1 = data[std::slice(0, dim, dim+1)].sum();
        return
    }
};
int main()
{
    Matrix m(3,3);
    int n = 0;
    for(int r=0; r<3; ++r)
        for(int c=0; c<3; ++c)
            m(r, c) = ++n;
    std::cout << "Trace of the matrix (1,2,3) (4,5,6) (7,8,9) is " << m.trace() << '\n';
}