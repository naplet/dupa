//
// Created by bobo on 25.04.18.
//

#include <iostream>
using namespace std;

class CircleException{
    // Oznacza ze nie mozna wyrysowac kola
};

class BallException : public CircleException{
    // Oznacza ze nie mozna wyrysowac kuli
};

void drawBall() {
    throw BallException();
}

int main(){
    try{
        drawBall();
    }catch(const BallException &b){
        cout << "Blad podczas rysowania kuli" << endl;
    }
    catch(const CircleException &a){
        cout << "Blad podczas rysowania kola" << endl;
    }

}