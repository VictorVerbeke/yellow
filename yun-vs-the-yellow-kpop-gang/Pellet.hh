#pragma once
#include "Entity.hh"

class Pellet : public Entity {
    public:
        Pellet(float x, float y, float size, string imagePath,
               float speed, float direction, int damage, int target);
        ~Pellet();

        void nextFrame();
        void initializeTextures();

        // Les textures de chaque sprite : static, la même pour toutes
        // les pellets.
        static sf::Texture _ally_tex0;
        static sf::Texture _ally_tex1;
        static sf::Texture _ally_tex2;
        static sf::Texture _ally_tex3;
        static sf::Texture _ally_tex4;
        static sf::Texture _ally_tex5;
        static sf::Texture _ally_tex6;
        static sf::Texture _ally_tex7;
        static sf::Texture _enemy_tex0;
        static sf::Texture _enemy_tex1;
        static sf::Texture _enemy_tex2;
        static sf::Texture _enemy_tex3;
        static sf::Texture _enemy_tex4;
        static sf::Texture _enemy_tex5;
        static sf::Texture _enemy_tex6;
        static sf::Texture _enemy_tex7;

        float _speed;
        float _direction;
        int _damage;
        int _target; //0 pour joueur, 1 pour enemy
        int _frameCounter;  // De 0 à 3
    private:
        int _frameNumber;   // De 0 à 7

};
