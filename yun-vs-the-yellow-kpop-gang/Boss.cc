#include "Boss.hh"


Boss::Boss():
    Enemy(0,0,0,100,NULL, null),
    _name(none),
    _phase(0),
    _specialFireCD(0){}

Boss::Boss(float x, float y, float size, int hp,
     sf::Texture* tex, Pattern pattern, Name name)
:
    Enemy(x, y, size, hp, tex, pattern),
    _name(name),
    _phase(0),
    _specialFireCD(0){}

Boss::~Boss(){
}

Pellet* Boss::SpecialFire(float size){
    switch (_phase) {
        case 1 :
            if (_specialFireCD > 0) {
                _specialFireCD --;
                return NULL; // Exception sur push_back(NULL) à faire
            }
            else {
                _specialFireCD = SPECIALFIRECD1;
                return NULL; // TODO Faire la création de Pellet
            }
            break;

        case 2 :
            if (_specialFireCD > 0) {
                _specialFireCD --;
                return NULL; // Exception sur push_back(NULL) à faire
            }
            else {
                _specialFireCD = SPECIALFIRECD2;
                return NULL; // TODO Faire la création de Pellet
            }
            break;

        case 3 :
            if (_specialFireCD > 0) {
                _specialFireCD --;
                return NULL; // Exception sur push_back(NULL) à faire
            }
            else {
                _specialFireCD = SPECIALFIRECD3;
                return NULL; // TODO Faire la création de Pellet
            }
            break;

        default :
            return NULL;
            break;
    }
}

void Boss::nextPhase(){
    _phase++;
    _specialFireCD = 5 * SPECIALFIRECD1;
    _fireCD = 5 * SPECIALFIRECD1;
    // On laisse un peu le temps de souffler entre les phases.
}
