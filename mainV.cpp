// Kompiliavimo komanda mac'ui: clang++ -std=c++11 -stdlib=libc++ -o prog mainV.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

const vector<string> nameList{"Nojus", "Domas", "Arvydas", "Rokas", "Vytautas", "Aurimas", "Joris", "Ramunas", "Povilas", "Mindaugas"};
const vector<string> surnameList{"Vaicekauskas", "Kateiva", "Kardauskas", "Zalionis", "Norkus", "Ozelis", "Stasiunas", "Oginskas", "Petrauskas", "Pakuckas"};
const int paz = 15; // pazymiu skaicius
const int st = 10;  // generuojamu studentu skaicius
string file;        // failo pavadinimas

struct User
{
    string name;       // vardas
    string surname;    // pavarde
    vector<int> hwRes; // namu darbu rezultatai
    int exRes;         // egzamino rezultatai
};

void Read(vector<User> &stud);       // skaitymo funkcija
void ReadFile(vector<User> &stud);   // skaitymo is failo funkcija
void Result(vector<User> &stud);     // rezultatu isvedimo i ekrana funkcija
double Average(User stud);           // galutinio vidurkio skaiciavimo funkcija
double Median(User stud);            // galutines medianos skaiciavimo funkcija
int RandNumber();                    // atstiktinio skaiciaus 1-10 generavimas
void SortChoice(vector<User> &stud); // rusiavimo funkcija

int main()
{
    vector<User> stud;
    int choice;
    cout << "Sveiki!\nProgramos eigos pasirinkimas - (\"1\" - skaitymas is failu; \"2\" - ivedimas ranka / generavimas; \"3\" - baigti darba)";
    cin >> choice;
    if (choice == 3)
        exit(0);
    if (choice == 2)
    {
        Read(stud);
        SortChoice(stud);
        Result(stud);
    }
    if (choice == 1)
    {
        int avgTime = 0;
        int count = 1;
        while (true)
        {
            int choice;
            cout << "Pasirinikite failo dydi - (\"1\" - 100; \"2\" - 1000; \"3\" - 10000; \"4\" - baigti darba)";
            cin >> choice;
            if (choice == 4)
                exit(0);
            if (choice == 3)
                file = "studentai10000.txt";
            if (choice == 2)
                file = "studentai1000.txt";
            if (choice == 1)
                file = "studentai100.txt";
            auto start = high_resolution_clock::now();
            ReadFile(stud);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Nuskaitymo laikas: "
                 << duration.count() << " mikrosekundes" << endl;
            avgTime += (int)duration.count();
            cout << "Laiku vidurkis: " << avgTime / count << " mikrosekundes" << endl;
            count++;
        }
    }

    return 0;
}

void SortChoice(vector<User> &stud)
{
    int choice;
    cout << "Rusiavimo pasirinikimas - (\"1\" - pagal varda; \"2\" - pagal pavarde; \n\"3\" - pagal vidurkio galutini; \"4\" - pagal medianos galutini): ";
    cin >> choice;
    if (choice == 1)
        sort(stud.begin(), stud.end(), [](const User &a, const User &b)
             { return a.name < b.name; });
    if (choice == 2)
        sort(stud.begin(), stud.end(), [](const User &a, const User &b)
             { return a.surname < b.surname; });
    if (choice == 3)
        sort(stud.begin(), stud.end(), [](const User &a, const User &b)
             { return Average(a) < Average(b); });
    if (choice == 4)
        sort(stud.begin(), stud.end(), [](const User &a, const User &b)
             { return Median(a) < Median(b); });
}

int RandNumber()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10);
    return dis(gen);
}

void ReadFile(vector<User> &stud)
{
    ifstream rd(file);
    string line;
    User temp;
    int grade;
    rd.ignore(1000, '\n');
    while (getline(rd, line))
    {
        istringstream iss(line);
        iss >> temp.name >> temp.surname;
        for (int i = 0; i < paz; i++)
        {
            iss >> grade;
            temp.hwRes.push_back(grade);
        }
        iss >> temp.exRes;
        stud.push_back(temp);
    }
    rd.close();
}

void Read(vector<User> &stud)
{
    int hw;
    int choice;
    cout << "Programos eigos pasirinkimas -  (\"1\" - ivedimas ranka; \"2\" - generuoti pazymius; \"3\" - generuoti pazymius, bei studentu vardus; \"4\" - baigti darba): ";
    cin >> choice;

    if (choice == 4)
    {
        cout << "Programos uzdarymas" << endl;
        exit(0);
    }

    if (choice == 3)
    {
        for (int i = 0; i < st; i++)
        {
            User temp;
            temp.name = nameList[RandNumber() - 1];
            temp.surname = surnameList[RandNumber() - 1];
            for (int i = 0; i < paz; i++)
                temp.hwRes.push_back(RandNumber());
            temp.exRes = RandNumber();
            stud.push_back(temp);
        }
    }

    if (choice == 1 || choice == 2)
    {
        while (true)
        {
            User temp;
            cout << "Vardas (\"exit\", kad uzbaigti): ";
            cin >> temp.name;
            if (temp.name == "exit")
                break;
            cout << "Pavarde: ";
            cin >> temp.surname;

            if (choice == 3)
            {
                for (int i = 0; i < paz; i++)
                    temp.hwRes.push_back(RandNumber());
                temp.exRes = RandNumber();
            }

            else
            {
                while (true)
                {
                    cout << "Namu darbu pazymys (\"-1\", kad uzbaigti): ";
                    cin >> hw;
                    if (hw == -1)
                        break;
                    temp.hwRes.push_back(hw);
                }
                cout << "Egzamino pazymys: ";
                cin >> temp.exRes;
            }
            stud.push_back(temp);
        }
    }
}

void Result(vector<User> &stud)
{
    cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(15) << "Galutinis (Med.)" << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << fixed << setprecision(2);
    for (const auto &i : stud)
        cout << left << setw(15) << i.surname << setw(15) << i.name << setw(20) << Average(i) << setw(15) << Median(i) << endl;
}

double Average(User stud)
{
    double avg;
    for (const double &value : stud.hwRes)
        avg += value;
    avg = avg / stud.hwRes.size();
    return 0.4 * avg + 0.6 * stud.exRes;
}

double Median(User stud)
{
    double med;
    sort(stud.hwRes.begin(), stud.hwRes.end());
    if (stud.hwRes.size() % 2 != 0)
        med = (double)stud.hwRes[stud.hwRes.size() / 2];
    med = (double)(stud.hwRes[(stud.hwRes.size() - 1) / 2] + stud.hwRes[stud.hwRes.size() / 2]) / 2.0;
    return 0.4 * med + 0.6 * stud.exRes;
}