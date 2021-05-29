#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
//#include <vector>
#include "Zmogus.h"
#include "Vector.h"
using namespace std;

class Studentas : public Zmogus {
    private:
        Vector<int> pazymiai;
        int egzaminas;
        double vidurkis;
    public:
        Studentas() : vidurkis(0) { Zmogus::vardas = "", Zmogus::pavarde = ""; }
        Studentas(string vardas, string pavarde, int egzaminas, Vector<int> pazymiai) : vidurkis(0) { vardas = vardas; pavarde = pavarde; }

        //Copy konstruktorius
        Studentas (const Studentas& a) : egzaminas(a.getEgzaminas()) , vidurkis(a.getVidurkis()){
            vardas = a.getVardas();
            pavarde = a.getPavarde();
            
            pazymiai.reserve(a.getPazymiai().size());
            for(int i : a.getPazymiai()){
                pazymiai.push_back(i);
            }
        }

        // Copy assignment operatorius
        Studentas& operator=(const Studentas& a) {
            if(&a == this) return *this;

            vardas = a.getVardas();
            pavarde = a.getPavarde();
            egzaminas = a.getEgzaminas();
            vidurkis = a.getVidurkis();
            pazymiai.clear();
            pazymiai.shrink_to_fit();
            pazymiai.reserve(a.getPazymiai().size());
            for(int i : a.getPazymiai()) {
                pazymiai.push_back(i);
            }
            return *this;
        }

        //Objekto destruktorius
        ~Studentas(){}

        //get
        //inline string getVardas() const {return vardas; }
        //inline string getPavarde() const {return pavarde; }
        inline Vector<int> getPazymiai() const {return pazymiai; }
        inline int getEgzaminas() const {return egzaminas; }
        inline double getVidurkis() const {return vidurkis; }
        //set
        //inline void setVardas(string vardas) {Studentas::vardas = vardas; }
        //inline void setPavarde(string pavarde) {Studentas::pavarde = pavarde; }
        inline void setPazymiai(Vector<int> pazymiai) {Studentas::pazymiai = pazymiai; }
        inline void setEgz(int egz) {Studentas::egzaminas = egz; }
        inline void setVidurkis(double vidurkis) {Studentas::vidurkis = vidurkis; }
        inline void setPazymys(int pazymys) {pazymiai.push_back(pazymys); }
};

#endif