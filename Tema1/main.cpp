#include <iostream>

class Footballer {
    private:
    std::string name;
    std::string teamName;
    int nrOfGoals;
    int nrOfAssists;

    public:
    //destructor
    ~Footballer() { 
        std::cout << "Destructor of class Footballer" << std::endl;
    }

    //constructor default
    Footballer()
    : name(),
      teamName(),
      nrOfGoals(0),
      nrOfAssists(0)
    { 
        std::cout << "Default constructor of class Footballer " << std::endl; 
    }

    // item 4, constructor cu member initialization list
    Footballer(std::string name, std::string team, int goals, int assists)
    : name(name),
      teamName(team),
      nrOfGoals(goals),
      nrOfAssists(assists)
    { 
        std::cout << "Constructor with member initialization list of class Footballer" << std::endl; 
    }  

    // item 5, copy constructor declarat de noi
    Footballer(const Footballer& F) {
        std::cout << "Copy constructor of class Footballer" << std::endl;
        this->name = F.name;
        this->teamName = F.teamName;
        this->nrOfGoals = F.nrOfGoals;
        this->nrOfAssists = F.nrOfAssists;
    }

    // copy assignment operator
    Footballer& operator = (const Footballer& F) {
        std::cout << "Copy assignment operator of class Footballer" << std::endl;
    }

    // functie pentru calcularea contributiilor ofensive
    int goalContributions () {
        int goalContributions = 0;
        goalContributions = this->nrOfGoals + this->nrOfAssists;

        return goalContributions;
    }
};

class Defender :public Footballer {
    private:
    int nrOfCleanSheets;

    public:
    // destructor
    ~Defender() {
        std::cout << "Destructor of class Defender" << std::endl;
    }

    // default constructor
    Defender() :Footballer() {}

    Defender(std::string name, std::string team, int goals, int assists, int cleanSheets )
    : Footballer(name, team, goals, assists),
      nrOfCleanSheets(cleanSheets)
    {
        std::cout << "Constructor of class Defender" << std::endl;
    }

    // copy constructor si copy assignment operator dezactivate
    Defender(const Defender&) = delete;
    Defender& operator = (const Defender&) = delete;

    // functie pentru returnarea numarului de meciuri fara gol primit
    int getCleanSheets() {
        return this->nrOfCleanSheets;
    }
};

int main() {
    Footballer f1;
    Footballer f2("Adi", "Liverpool", 10, 6);
    std::cout << f2.goalContributions() << std::endl;

    Footballer f3(f2); // copy constructor
    Footballer f4;
    f4 = f3; // copy assignment operator

    Defender d1("Koulibaly", "Chelsea", 2, 4, 18);
    int cleanSheetsd1 = d1.getCleanSheets();
    std:: cout << cleanSheetsd1 << std::endl;

    // item 6, urmatoarele linii vor da eroare deoarece copy constructorul si copy assignment operator au fost dezactivate

    // Defender d2(d1);
    // Defender d3;
    // d3 = d1;
}