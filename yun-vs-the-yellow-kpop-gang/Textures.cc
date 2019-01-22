#include "Textures.hh"

Textures::Textures(){

    // Initialisation :
    _ally_tex0 = new sf::Texture();
    _ally_tex1 = new sf::Texture();
    _ally_tex2 = new sf::Texture();
    _ally_tex3 = new sf::Texture();
    _ally_tex4 = new sf::Texture();
    _ally_tex5 = new sf::Texture();
    _ally_tex6 = new sf::Texture();
    _ally_tex7 = new sf::Texture();
    _enemy_tex0 = new sf::Texture();
    _enemy_tex1 = new sf::Texture();
    _enemy_tex2 = new sf::Texture();
    _enemy_tex3 = new sf::Texture();
    _enemy_tex4 = new sf::Texture();
    _enemy_tex5 = new sf::Texture();
    _enemy_tex6 = new sf::Texture();
    _enemy_tex7 = new sf::Texture();

    _ally_tex0->loadFromFile("images/pellets/ally_spr_0.png");
    _ally_tex1->loadFromFile("images/pellets/ally_spr_1.png");
    _ally_tex2->loadFromFile("images/pellets/ally_spr_2.png");
    _ally_tex3->loadFromFile("images/pellets/ally_spr_3.png");
    _ally_tex4->loadFromFile("images/pellets/ally_spr_4.png");
    _ally_tex5->loadFromFile("images/pellets/ally_spr_5.png");
    _ally_tex6->loadFromFile("images/pellets/ally_spr_6.png");
    _ally_tex7->loadFromFile("images/pellets/ally_spr_7.png");
    _enemy_tex0->loadFromFile("images/pellets/enemy_spr_0.png");
    _enemy_tex1->loadFromFile("images/pellets/enemy_spr_1.png");
    _enemy_tex2->loadFromFile("images/pellets/enemy_spr_2.png");
    _enemy_tex3->loadFromFile("images/pellets/enemy_spr_3.png");
    _enemy_tex4->loadFromFile("images/pellets/enemy_spr_4.png");
    _enemy_tex5->loadFromFile("images/pellets/enemy_spr_5.png");
    _enemy_tex6->loadFromFile("images/pellets/enemy_spr_6.png");
    _enemy_tex7->loadFromFile("images/pellets/enemy_spr_7.png");
    
}
