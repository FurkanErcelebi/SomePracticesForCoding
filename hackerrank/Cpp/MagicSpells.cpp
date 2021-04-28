#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Spell { 
    private:
        string scrollName;
    public:
        Spell(): scrollName("") { }
        Spell(string name): scrollName(name) { }
        virtual ~Spell() { }
        string revealScrollName() {
            return scrollName;
        }
};

class Fireball : public Spell { 
    private: int power;
    public:
        Fireball(int power): power(power) { }
        void revealFirepower(){
            cout << "Fireball: " << power << endl;
        }
};

class Frostbite : public Spell {
    private: int power;
    public:
        Frostbite(int power): power(power) { }
        void revealFrostpower(){
            cout << "Frostbite: " << power << endl;
        }
};

class Thunderstorm : public Spell { 
    private: int power;
    public:
        Thunderstorm(int power): power(power) { }
        void revealThunderpower(){
            cout << "Thunderstorm: " << power << endl;
        }
};

class Waterbolt : public Spell { 
    private: int power;
    public:
        Waterbolt(int power): power(power) { }
        void revealWaterpower(){
            cout << "Waterbolt: " << power << endl;
        }
};

class SpellJournal {
    public:
        static string journal;
        static string read() {
            return journal;
        }
}; 
string SpellJournal::journal = "";

void counterspell(Spell *spell) {

    if(Fireball *fireball = dynamic_cast<Fireball*>(spell)) {
        fireball->revealFirepower();
    }
    else if(Frostbite *fortbite = dynamic_cast<Frostbite*>(spell)) {
        fortbite->revealFrostpower();
    }
    else if(Thunderstorm *thunderstrom = dynamic_cast<Thunderstorm*>(spell)) {
        thunderstrom->revealThunderpower();
    }
    else if(Waterbolt *waterbolt = dynamic_cast<Waterbolt*>(spell)) {
        waterbolt->revealWaterpower();
    } 
    else {
        int len_str = spell->revealScrollName().length();
        int len_sub = SpellJournal::journal.length();
        int i,j,lcs[len_str + 1][len_sub + 1];
        for(i = 0; i <= len_str;i++){
            lcs[i][0] = 0;
        }
        for(j = 0;j <= len_sub;j++){
            lcs[0][j] = 0;
        }
        for(i = 1; i <= len_str;i++){
            for(j = 1;j <= len_sub;j++){
                if(spell->revealScrollName().at(i - 1) == SpellJournal::journal.at(j - 1)){
                    lcs[i][j] = lcs[i - 1][j - 1] + 1;
                }
                else{
                    lcs[i][j] = max(lcs[i][j - 1],lcs[i - 1][j]);
                }
            }
        }
    
        cout << lcs[len_str][len_sub] << endl;
    }

}
