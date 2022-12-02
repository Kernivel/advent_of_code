#include <iostream>
using namespace std;

class Voiture{
    private:
        int portes;
    public:
        Voiture(int nbPortes){
            portes = nbPortes;
        }

};


class Modele:public Voiture{
    private:
        string modele;
    public:
        Modele(string modeleType,int nbPortes) : Voiture(nbPortes){
            modele = modeleType;
        }

};

int main(){
    
    return EXIT_SUCCESS;
}