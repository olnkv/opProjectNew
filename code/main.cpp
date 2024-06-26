#include "func.h"

int main()
{
    std::vector<Student> studVector;
    std::vector<Student> best;
    int choice;

    Student Student0;
    Student Student1("Edvin", "Olenkovic");
    Student Student2("Vardenis", "Pavardenis");
    Student Student3(Student1);
    Student Student4(std::move(Student2));
    Student0 = Student1;
    Student0 = std::move(Student4);
    std::cout << "Sveiki!" << std::endl;
    while (true)
        try
        {
            std::cout << "Programos eigos pasirinkimas: \"1\" - Ivedimas ranka; \"2\" - Generavimas; \"3\" - Skaitymas is failo; \"4\" - Generuoti faila; \"5\" - Atrinkti studentus; \"6\" - Rezultatu isvedimas; \"7\" - Baigti darba" << std::endl;
            std::cin >> choice;
            if (std::cin.fail())
                CinError();
            if (choice < 1 || choice > 7)
                throw std::runtime_error("Klaidinga ivestis");
            if (choice == 1)
                ReadUser(studVector);
            if (choice == 2)
            {
                int size, hw;
                std::cout << "Studentu skaicius: ";
                std::cin >> size;
                if (size < 1)
                    throw std::runtime_error("Klaidinga ivestis");
                if (std::cin.fail())
                    CinError();
                std::cout << "Namu darbu skaicius: ";
                std::cin >> hw;
                if (std::cin.fail())
                    CinError();
                if (hw < 1)
                    throw std::runtime_error("Klaidinga ivestis");
                GenUser(studVector, size, hw);
            }
            if (choice == 3)
                ReadFile(studVector);
            if (choice == 4)
            {
                int size, hw;
                std::cout << "Studentu skaicius: ";
                std::cin >> size;
                if (std::cin.fail())
                    CinError();
                if (size < 1)
                    throw std::runtime_error("Klaidinga ivestis");
                std::cout << "Namu darbu skaicius: ";
                std::cin >> hw;
                if (std::cin.fail())
                    CinError();
                if (hw < 1)
                    throw std::runtime_error("Klaidinga ivestis");
                GenFile(size, hw);
            }
            if (choice == 5)
            {
                std::cout << "Pagal ka atrinkti? \"1\" - Pagal vidurki; \"2\" - Pagal mediana" << std::endl;
                std::cin >> choice;
                if (std::cin.fail())
                    CinError();
                if (choice < 1 || choice > 2)
                    throw std::runtime_error("Klaidinga ivestis");
                Selection(studVector, best, choice);
            }
            if (choice == 6)
                Results(studVector);
            if (choice == 7)
                break;
            system("pause");
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

    return 0;
}