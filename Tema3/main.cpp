#include <iostream>
#include <memory>

class Footballer {
    private:
    std::string name;
    std::string teamName;
    int nrOfGoals;
    int nrOfAssists;
    bool suspended; // pentru item 14

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
      nrOfAssists(0),
      suspended(false)
    { 
        std::cout << "Default constructor of class Footballer " << std::endl; 
    }

    // item 4, constructor cu member initialization list
    Footballer(std::string name, std::string team, int goals, int assists)
    : name(name),
      teamName(team),
      nrOfGoals(goals),
      nrOfAssists(assists),
      suspended(false)
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
        if( this == &F) {
             std::cout << "It's the same object" << std::endl;
             return *this;
        }  // item 11, handle assignment to self in operator =

        std::cout << "Copy assignment operator of class Footballer" << std::endl;
        return *this;     // item 10, assignment operators return a reference to *this
    }

    // another assignment operator; item 10
    Footballer& operator += (const Footballer& F) {
        this->nrOfGoals += F.nrOfGoals;
        std::cout << "Assignment operator for += of class Footballer" << std::endl;
        return *this;
    }

    // functie pentru calcularea contributiilor ofensive
    int goalContributions () {
        int goalContributions = 0;
        goalContributions = this->nrOfGoals + this->nrOfAssists;

        return goalContributions;
    }

    void setSuspended (bool value) {
        this->suspended = value;
    }
};

// pentru item 14:
// am "mimat" actiunile de lock si unlock, pentru a seta statusul de suspendat sau nesuspendat al fotbalistului 
void lock(Footballer *F) {
    F->setSuspended(true);
    std::cout << "Fotbalistul a fost suspendat" << std::endl;
}

void unlock(Footballer *F) {
    F->setSuspended(false);
    std::cout << "Fotbalistul nu e suspendat " << std::endl;
}

class SuspendFootballer {
    private:
    std::shared_ptr<Footballer> footballerptr;

    public:
    explicit SuspendFootballer(Footballer *F)
    :footballerptr(F, unlock) // setam unlock ca si deleter
    {
        lock(footballerptr.get());
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

class Midfielder :public Footballer {
    private:
    int nrOfKeyPasses;

    public:
    ~Midfielder() {}
    Midfielder() {}
    
    Midfielder(std::string name, std::string team, int goals, int assists, int keyPasses) 
    :Footballer(name, team, goals, assists),
    nrOfKeyPasses(keyPasses)
    {
        std::cout << "Constructor of class Midfielder" << std::endl;
    }

    // item 12
    Midfielder(const Midfielder& M)
    :Footballer(M) {
        this->nrOfKeyPasses = M.nrOfKeyPasses;
    }

    Midfielder& operator = (const Midfielder& M) {
        if( this == &M) {
            return *this;
        }
        Footballer::operator=(M); // item 12
    }
 };

// item 13
Footballer* createFootballer(std::string name, std::string team, int goals, int assists) {
    return (new Footballer(name,team,goals,assists));
}

int main() {
    Footballer f1;
    Footballer f2("Adi", "Liverpool", 10, 6);
    std::cout << f2.goalContributions() << std::endl;

    Footballer f3(f2); // copy constructor
    Footballer f4;
    f4 = f3; // copy assignment operator

    f2 += f3; // assignment operator for +=

    f4 = f4; // item 11, assignment to self

    Defender d1("Koulibaly", "Chelsea", 2, 4, 18);
    int cleanSheetsd1 = d1.getCleanSheets();
    std:: cout << cleanSheetsd1 << std::endl;

    // item 6, urmatoarele linii vor da eroare deoarece copy constructorul si copy assignment operator au fost dezactivate

    // Defender d2(d1);
    // Defender d3;
    // d3 = d1;

    Midfielder m1("De Bruyne", "Manchester City", 14, 20, 46);
    Midfielder m2;
    m2 = m1; // item 12

    // pentru item 13:
    // folosind auto_ptr, obiectul va fi sters dupa ce va fi folosit
    std::auto_ptr<Footballer> ptrF(createFootballer("pointer F", "pointer team", 10, 20));
    std::cout << "ptr goal contributions: " << ptrF->goalContributions() << std::endl;      // merge, ptrF pointeaza catre obiectul nou creat

    std::auto_ptr<Footballer> ptrF2(ptrF);  // ptrF2 va pointa catre obiectul creeat, iar ptrF va fi null
    std::cout << "ptr2 goal contributions: " << ptrF2->goalContributions() << std::endl;
    // urmatoarea linie comentata va da eroare, deoarece ptrF este null acum

    // std::cout << ptrF->goalContributions() << std::endl;

    ptrF = ptrF2; // ptrF va pointa din nou catre obiectul creeat, si ptrF2 va fi null
    std::cout << "ptr goal contributions again: " << ptrF->goalContributions() << std::endl;

    std::shared_ptr<Footballer> sharedptrF(createFootballer("shared pointer F", "shared pointer team", 20, 5));
    std::shared_ptr<Footballer> sharedptrF2(sharedptrF);  // ambele vor pointa catre obiectul nou creat, sharedptrF nu va mai deveni null
    std::cout << "shared ptr goal contributions: " << sharedptrF->goalContributions() << std::endl;
    std::cout << "shared ptr2 goal contributions: " << sharedptrF2->goalContributions() << std::endl;  // ambele cout-uri vor avea acelasi rezultat

    sharedptrF = sharedptrF2; // in continuare ambele vor pointa catre obiectul creat, fara ca unul sa devina null

    // item 14
    Footballer suspendFootballer;
    SuspendFootballer s1(&suspendFootballer);
    SuspendFootballer s2(s1); // fotbalistul devine suspendat dupa care expira suspendarea
}