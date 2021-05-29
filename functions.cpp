#include "declarations.h"

void checkInputChar(char &tn){
    while(tn != 't' && tn != 'n'){
        cout << "Galimas pasirinkimas tik taip(t) arba ne(n)!" << endl;
        cout << "Pakartokite pasirinkima(t/n): ";
        cin >> tn;
    }
}

bool palyginimas(const Studentas& pirmas, const Studentas& antras){
    if(pirmas.getPavarde() == antras.getPavarde()) return pirmas.getVardas() < antras.getVardas();
    return pirmas.getPavarde() < antras.getPavarde();
};

void countAvg(Vector<Studentas> &studentai){
    for(int i = 0; i < studentai.size(); i++){
            double galutinisvid = 0;

            for(int j = 0; j < studentai[i].getPazymiai().size(); j++)
                galutinisvid += studentai[i].getPazymiai()[j];

            galutinisvid = galutinisvid / studentai[i].getPazymiai().size();
            studentai[i].setVidurkis(galutinisvid * 0.4 + studentai[i].getEgzaminas() * 0.6);
    }
}

void countAvg2(Studentas &studentai){
    
        double galutinisvid = 0;

        for(int j = 0; j < studentai.getPazymiai().size(); j++)
            galutinisvid += studentai.getPazymiai()[j];

        galutinisvid = galutinisvid / studentai.getPazymiai().size();
        studentai.setVidurkis(galutinisvid * 0.4 + studentai.getEgzaminas() * 0.6);
}

int generationNumber(){
    int skaicius;
    char tn;
    cout << "Pasirinkite kiek studentu generuoti: " << endl
         << "(1) 1000" << endl
         << "(2) 10000" << endl
         << "(3) 100000" << endl
         << "(4) 1000000" << endl
         << "(5) 10000000" << endl;
    cin >> skaicius;
    int number;
    while(true){
        switch (skaicius)
        {
        
        case 1:
            number = 1000;
            generateFile(number);

            break;

        case 2:
            number = 10000;
            generateFile(number);

            break;

        case 3:
            number = 100000;
            generateFile(number);
            
            break;

        case 4:
            number = 1000000;
            generateFile(number);
            
            break;

        case 5:
            number = 10000000;
            generateFile(number);

            break;
            
        default:
        {
            cout << "Blogas pasirinkimas. Galimi pasirinkimai nuo 1 iki 7";
            cin >> skaicius;
            continue;
        }
        }
    break;
    }
    return number;
}

void generateFile(int numberStudents){

    string file;
    int kieknd = rand() % 10 + 5;
    file = "studentai" + to_string(numberStudents) + ".txt";

    cout << "Pradedamas generavimas..." << endl;
    Timer t;

    ofstream generate;
    generate.open(file);

    generate << left << setw(20) << "Vardas" << setw(20) << "Pavarde";
    for (int i = 0; i < kieknd; i++){
        generate << setw(7) << "ND" + to_string(i + 1);
    };
    generate << setw(7) << "Egz." << endl;

    for(int i = 0; i < numberStudents; i++){
        generate << left << setw(20) << "Vardas" + to_string(i + 1) << setw(20) << "Pavarde" + to_string(i + 1);
        
        for (int j = 0; j < kieknd; j++){
            generate << setw(7) << rand() % 10 + 1;
        }
        generate << setw(7) << rand() % 10 + 1;
        if(i != numberStudents - 1) generate << endl;
    }

    generate.close();

    cout << numberStudents << " studentu generavimas baigtas ir uztruko " << t.elapsed() << "s" << endl << endl;
};


void sortStudentsVector(Vector<Studentas> &studentai){
    Vector<Studentas> moksliukai;
    cout << "Pradedamas studentu rusiavimas..." << endl;
    Timer t;
    auto it = partition(studentai.begin(), studentai.end(), mokslincius());
    moksliukai.assign(studentai.begin(), it);
    studentai.erase(studentai.begin(), it);
    /*for(auto it = studentai.begin(); it != studentai.end(); ++it){

        if (it->vidurkis >= 5.00){
            moksliukai.push_back(*it);
            it = studentai.erase(it);
        }
    }*/
    
    sort(moksliukai.begin(), moksliukai.end(), varduPal());
    sort(studentai.begin(), studentai.end(), varduPal());
    

    cout << moksliukai.size() + studentai.size() << " studentu rusiavimas baigtas ir uztruko " << t.elapsed() << "s" << endl << endl;


    cout << "Studentu duomenis isvedami i failus..." << endl;

    ofstream moksl;
    moksl.open("moksliukai.txt");

    moksl << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(10) << "Vidurkis" << endl;

    for(int i = 0; i < moksliukai.size(); i++){
        moksl << left << setw(20) << moksliukai[i].getVardas() << setw(20) << moksliukai[i].getPavarde() << setw(10) << setprecision(3) << moksliukai[i].getVidurkis();
        if(i != moksliukai.size() - 1) moksl << endl;
    }
    moksl.close();

    ofstream nepat;
    nepat.open("nepatenkinami.txt");

    nepat << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(10) << "Vidurkis" << endl;

    for(int i = 0; i < studentai.size(); i++){
        nepat << left << setw(20) << studentai[i].getVardas() << setw(20) << studentai[i].getPavarde() << setw(10) << setprecision(3) << studentai[i].getVidurkis();
        if(i != studentai.size() - 1) nepat << endl;
    }
    nepat.close();

    cout << moksliukai.size() + studentai.size() << " studentu isvedimas baigtas ir uztruko " << t.elapsed() << "s" << endl;
};

int whichRead(){
    int skaicius;
    char tn;
    cout << "Pasirinkite kuri studentu faila nuskaityti: " << endl
         << "(1) studentai1000.txt" << endl
         << "(2) studentai10000.txt" << endl
         << "(3) studentai100000.txt" << endl
         << "(4) studentai1000000.txt" << endl
         << "(5) studentai10000000.txt" << endl;
    cin >> skaicius;
    int number;
    while(true){
        switch (skaicius)
        {
        
        case 1:
            number = 1000;

            break;

        case 2:
            number = 10000;

            break;

        case 3:
            number = 100000;
            
            break;

        case 4:
            number = 1000000;
            
            break;

        case 5:
            number = 10000000;

            break;
            
        default:
        {
            cout << "Blogas pasirinkimas. Galimi pasirinkimai nuo 1 iki 7";
            cin >> skaicius;
            continue;
        }
        }
    break;
    }
    return number;
}