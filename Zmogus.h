#ifndef ZMOGUS_H
#define ZMOGUS_H

using namespace std;

class Zmogus {
    protected:
        string vardas;
        string pavarde;
    public:
        //Klasę paverčiam abstrakčia
        Zmogus() {}
        //Virtualaus destruktoriaus deklaraciją
        virtual ~Zmogus() = 0;

        //get
        inline string getVardas() const {return vardas; }
        inline string getPavarde() const {return pavarde; }
        //set
        inline void setVardas(string vardas) {Zmogus::vardas = vardas; }
        inline void setPavarde(string pavarde) {Zmogus::pavarde = pavarde; }
};

inline Zmogus::~Zmogus() {}

#endif