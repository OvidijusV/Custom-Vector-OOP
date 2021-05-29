#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <algorithm>
#include <vector>
#include <sstream>
#include <chrono>
#include <list>
#include <deque>
#include <iterator>
#include <utility>
#include "Studentas.h"
#include "Vector.h"
using namespace std;

class Timer {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
    public:
        Timer() : start{std::chrono::high_resolution_clock::now()} {}
        void reset() {
        start = std::chrono::high_resolution_clock::now();
        }
        double elapsed() const {
        return std::chrono::duration<double>
        (std::chrono::high_resolution_clock::now() - start).count();
        }
};

void checkInputChar(char &tn);
bool palyginimas(const Studentas& pirmas, const Studentas& antras);
int generationNumber();
void generateFile(int numberStudents);
void countAvg(Vector<Studentas> &studentai);
void sortStudentsVector(Vector<Studentas> &studentai);
int whichRead();
void countAvg2(Studentas &studentai);

struct mokslincius {
	bool operator() (const Studentas& kietas)
	{
		return (kietas.getVidurkis() >= 5.00);
	}
};
struct varduPal {
    bool operator()(const Studentas& vienas, const Studentas& du)
    {
        return (vienas.getVardas().compare(du.getVardas())) < 0;
    }
};


template<class T>
void generatedFileRead(T& studentai, int numm){
    Studentas student;
    string line, vardas, pavarde;
    Vector<int> grades;

    ifstream input;

    try
    {
        string pavadinimas = "studentai" + to_string(numm) + ".txt";;
        input.open(pavadinimas);
        if(!input.is_open())
            throw 1;
        else cout << "Failas nuskaitomas..." << endl;
    }
    catch(int error)
    {
        std::cout << "Failas nerastas... Patikrinkite ar failo teisingas failo pavadinimas ir formatas (kursiokai.txt)" << endl;
        cout << "Programa stabdoma";
        exit(0);
    }

    input.ignore(256, '\n');

    Timer t;

    try
    {
        while(true){
        input >> vardas >> pavarde;
        getline(input, line);

        stringstream ndpazymiai(line);
        int n;
        double galutinisvid = 0;
        while(ndpazymiai >> n){
            grades.push_back(n);
            galutinisvid += n;
        }

        galutinisvid -= n;
        grades.pop_back();
        student.setEgz(n);
        galutinisvid = galutinisvid / grades.size();
        student.setVidurkis(0.4 * galutinisvid + 0.6 * student.getEgzaminas());
        student.setVardas(vardas);
        student.setPavarde(pavarde);
        student.setPazymiai(grades);
        studentai.push_back(student);
        grades.clear();

        if(input.eof())
            break;
        }
    }
    catch(std::bad_alloc& exception)
    {
        std::cout << "Faile yra klaidu" << endl;
        input.ignore(256, '\n');
    }
    

    //
    input.close();

    cout << numm << " studentu nuskaitymas baigtas ir uztruko " << t.elapsed() << "s" << endl << endl;
};

#endif