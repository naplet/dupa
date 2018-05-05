
#include "Matrix.h"
using namespace algebra;
Matrix::Matrix() {};
Matrix::~Matrix(){
    for(int i=0; i<Rows; i++)
        delete [] this->Matrix_Complex[i];
    delete [] this->Matrix_Complex;
};
Matrix::Matrix(int R, int C) {
    this->Cols=C;
    this->Rows=R;
    this->Matrix_Complex= new std::complex<double>*[Rows];
    for(int i=0;i<Rows;i++){
        this->Matrix_Complex[i]= new std::complex<double>[Cols];
    }
}
Matrix::Matrix(const Matrix &Ptr) {
    this->Cols=Ptr.Cols;
    this->Rows=Ptr.Rows;
    this->Matrix_Complex= new std::complex<double>*[Rows];
    for(int i=0;i<Rows;i++){
        Matrix_Complex[i]= new std::complex<double>[Cols];

    }
    for(int i=0;i<Rows;i++){
        for(int j=0;j<Cols;j++){
            Matrix_Complex[i][j]=Ptr.Matrix_Complex[i][j];
        }
    }
}
Matrix::Matrix(std::string Text) {
    int n = 1, m = 1;

    std::string::size_type sz;

    std::string number = "",
            real = "",
            imag = "";

    double double_number,
            double_real,
            double_imag;

    for (std::string::iterator it = Text.begin(); it != Text.end(); it++) {
        if (*it == 32) {
            m++;
        }
        if (*it == 59) {
            n++;
        }
    }

    m = m / n;

    this->Rows = n;
    this->Cols = m;

    this->Matrix_Complex = new std::complex<double>*[n];

    for (int i = 0; i < n; ++i) {
        this->Matrix_Complex[i] = new std::complex<double>[m];
    }

    int i = 0,
            j = 0;

    for (std::string::iterator it = Text.begin(); it != Text.end(); it++) {
        if ((*it <= 57 && *it >= 48) ||  *it == 105 || *it == 46) {
            number += *it;
        } else if (*it == ' ' || *it == ']') {
            if (number.find("i") != std::string::npos) {
                real = number.substr(0, number.find("i"));
                imag = number.substr(number.find("i") + 1, number.length() - number.find("i"));

                double_real = stod(real, &sz);
                double_imag = stod(imag, &sz);

                this->Matrix_Complex[i][j] = std::complex<double>(double_real, double_imag);

                j++;
                number = "";
                real = "";
                imag = "";
            } else {
                double_number = stod(number, &sz);
                this->Matrix_Complex[i][j] = std::complex<double>(double_number);

                j++;
                number = "";
            }
        } else if (*it == 59) {
            if (number.find("i") != std::string::npos) {
                real = number.substr(0, number.find("i"));
                imag = number.substr(number.find("i") + 1, number.length() - number.find("i"));

                double_real = stod(real, &sz);
                double_imag = stod(imag, &sz);

                this->Matrix_Complex[i][j] = std::complex<double>(double_real, double_imag);

                i++;
                j = 0;
                number = "";
                real = "";
                imag = "";
            } else {
                double_number = stod(number, &sz);
                this->Matrix_Complex[i][j] = std::complex<double>(double_number);

                i++;
                j = 0;
                number = "";

            }
            *it++;
        }
    }

}
std::string Matrix::Print() const {
    std::string number_in_string;
    number_in_string += "[";

    for (int o = 0; o < this->Rows; o++) {
        for (int p = 0; p < this->Cols; p++) {
            std::string data = std::to_string(this->Matrix_Complex[o][p].real());

            for (int j = 0; j < data.length(); j++){
                bool slice = true;
                for (int k = data.length() - 1; k >= j; k -= 1){
                    if (data[k] != '0'){
                        slice = false;
                    }
                }
                if (slice){
                    data = data.substr(0, j);
                    break;
                }
            }

            if (data[data.length() - 1] == '.'){
                data = data.substr(0, data.length() - 1);
            }

            number_in_string += data;

            if (this->Matrix_Complex[o][p].imag() != 0) {
                std::string data2 = std::to_string(this->Matrix_Complex[o][p].imag());
                for (int j = 0; j < data2.length(); j++){
                    bool slice = true;
                    for (int k = data2.length() - 1; k >= j; k -= 1){
                        if (data2[k] != '0'){
                            slice = false;
                        }
                    }
                    if (slice) {
                        data2 = data2.substr(0, j);
                        break;
                    }
                }

                if (data2[data2.length() - 1] == '.') {
                    data2 = data2.substr(0, data2.length() - 1);
                }

                number_in_string += "i" + data2;
            } else {
                number_in_string += "i0";
            }
            number_in_string += ", ";
        }
        number_in_string = number_in_string.substr(0, number_in_string.length() - 2);
        number_in_string += "; ";
    }

    number_in_string = number_in_string.substr(0, number_in_string.length() - 2);
    number_in_string += "]";

    return number_in_string;
}
int Matrix::GetCols() {
    return this->Cols;
}
int Matrix::GetRows() {
    return this->Rows;
}
std::complex<double>** Matrix::GetMatrix() {
    return this->Matrix_Complex;
}
int Matrix::SetElement(int R, int C, double Value) {
    this->Matrix_Complex[R][C]=Value;
    return 0;
}
std::pair<size_t, size_t> Matrix::Size() {
    return std::pair<size_t, size_t>(Rows, Cols);
}
Matrix::Matrix(std::initializer_list<std::vector<std::complex<double>>> matrix_list) {
    int row_number = int(matrix_list.size());
    unsigned long col_number = 0;


    for(auto row : matrix_list) {
        col_number = row.size();
        break;
    }

    this->Rows = row_number;
    this->Cols = int(col_number);


    std::complex<double> **new_matrix = new std::complex<double> *[this->Rows];
    for(int i=0; i<this->Rows; i++)
        new_matrix[i] = new std::complex<double>[this->Cols];

    this->Matrix_Complex = new_matrix;
    this->Matrix_Complex[0][0] = 1.0 + 1.0i;

    int i=0;
    int k=0;

    for(auto row : matrix_list) {
        k = 0;
        for(auto element : row) {
            this->Matrix_Complex[i][k] = element;
            k++;
        }
        i++;
    }

}
//działania
Matrix Matrix::Add(const Matrix Matrix_ToAdd) const {
    if(this->Rows!=Matrix_ToAdd.Rows || this->Cols!=Matrix_ToAdd.Cols){
        throw "Different sizes!";
    }
    Matrix Result(Rows,Cols);
    for(int i=0;i<Rows;i++){
        for(int j=0;j<Rows;j++){
            Result.Matrix_Complex[i][j]=this->Matrix_Complex[i][j]+Matrix_ToAdd.Matrix_Complex[i][j];
        }
    }
    return Result;
}
Matrix Matrix::Sub(const Matrix Matrix_ToSub) const{
    if(this->Rows!=Matrix_ToSub.Rows || this->Cols!=Matrix_ToSub.Cols){
        throw "Different sizes!";
    }
    Matrix Result(Rows,Cols);
    for(int i=0;i<Rows;i++){
        for(int j=0;j<Rows;j++){
            Result.Matrix_Complex[i][j]=this->Matrix_Complex[i][j]-Matrix_ToSub.Matrix_Complex[i][j];
        }
    }
    return Result;
}
Matrix Matrix::Mul(const Matrix &Matrix_ToMul)const {
    if(this->Cols!=Matrix_ToMul.Rows ){
        throw "Different sizes!";
    }
    Matrix Result(Rows,Matrix_ToMul.Cols);
    for(int i=0;i<Rows;i++){
        for(int j=0;j<Matrix_ToMul.Cols;j++){
            Result.Matrix_Complex[i][j]+= this->Matrix_Complex[i][j]*Matrix_ToMul.Matrix_Complex[i][j];
        }
    }
    return Result;
}
Matrix Matrix::Mul(std::complex<double> Number)const {
    Matrix Result(this->Rows,this->Cols);
    for(int i=0;i<Rows;i++){
        for(int j=0;j<Cols;j++){
            Result.Matrix_Complex[i][j]=Number*Result.Matrix_Complex[i][j];
        }
    }
    return Result;
}
Matrix Matrix::Pow(int Number)const {
    Matrix Result = *this;

    for(int i=1; i<Number; i++)
        Result = Result.Mul(*this);

    return Result;
}
