#include <iostream>
#include <chrono>
#include "Vector.h"
#include "declarations.h"

using namespace std;

int main(){

    //Push_back
    Timer t;
    unsigned int sz = 10000;  // 100000, 1000000, 10000000, 100000000
    std::vector<int> v;
    for (int i = 1; i <= sz; ++i)
        v.push_back(i);
    double laikas = t.elapsed();
    cout << sz << " elementu uzpildymas std::vector<int> uztruko: " << laikas << endl;
    v.clear();

    Vector<int> v2;
    for (int i = 1; i <= sz; ++i)
        v.push_back(i);
    cout << sz << " elementu uzpildymas Vector<int> (custom) uztruko: " << t.elapsed() - laikas << endl;
    v2.clear();

    //Perskirstymai
    cout << "Perskirstymas su 100000000 irasu...\n";
        int n = 0;
        for (long long int i = 1; i <= 100000000; i++) {
            v.push_back(i);
            if (v.capacity() == v.size())
                n++;
        }
    v.clear();
        cout << "std::vector<int> perskirstymu skaicius: " << n << endl;

        n = 0;
        for (long long int i = 1; i <= 100000000; i++) {
            v2.push_back(i);
            if (v2.capacity() == v2.size())
                n++;
        }
        cout << "Vector<int> perskirstymu skaicius: " << n << endl;
    v2.clear();
    srand(time(NULL));

    Vector<Studentas> studentai;

    char tn;
    char gen;
    cout << "Ar norite sugeneruoti nauja faila?(t/n): ";
    cin >> gen;
    if(gen == 't'){
        generationNumber();
    } else {
            

        Vector<Studentas> studentai;
        int skai = whichRead();
        generatedFileRead(studentai, skai);
        sortStudentsVector(studentai);

    }

    
}