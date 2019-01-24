#include "Boss.hh"


Boss::Boss():
    Enemy(0,0,0,100,NULL, null),
    _name(none),
    _phase(0),
    _specialFireCD(0){}

Boss::Boss(Name name, sf::Texture* tex)
:
    Enemy(600, 200, 256, 100*Character::_enemyStandardHP, tex, null),
    _name(name),
    _phase(0),
    _specialFireCD(0)
{
    _directionVariation = 2;
}

Boss::~Boss(){
}

// Overloads
void Boss::operator-(const float &b) {
    this->setHp(this->getHp() - b);
    cout << "Le boss a perdu " << b << " hp et est à " << this->getHp() << " hp." << endl;
}

// Methodes
vector<Pellet> Boss::SpecialFire(){
    switch (_phase) {
        case 1 :
            _specialFireCD = SPECIALFIRECD1;
            // TODO Faire la création de Pellet
            break;

        case 2 :
            _specialFireCD = SPECIALFIRECD2;
             // TODO Faire la création de Pellet
            break;

        case 3 :
            _specialFireCD = SPECIALFIRECD3;
            // TODO Faire la création de Pellet
            break;

        default :
            break;
    }
}

void Boss::move(){
    float newX, newY;
    if (getX() > 500) newX = getX() - 2;
    else newX = getX();
    _direction += _directionVariation;
    newY = 200 + sin(_direction * PI / 180) * 150;
    this->setPosition(newX, newY);
}

void Boss::nextPhase(){
    _phase++;
    _specialFireCD = 5 * SPECIALFIRECD1;
    _fireCD = 5 * SPECIALFIRECD1;
    // On laisse un peu le temps de souffler entre les phases.
}
