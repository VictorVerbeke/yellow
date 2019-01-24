#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Textures {
public:

    Textures();
    ~Textures();
    void textureAffectation(sf::Texture* tex, string str);
    void generateTextures();
    static sf::Texture* _allyPellet_tex0;
    static sf::Texture* _allyPellet_tex1;
    static sf::Texture* _allyPellet_tex2;
    static sf::Texture* _allyPellet_tex3;
    static sf::Texture* _allyPellet_tex4;
    static sf::Texture* _allyPellet_tex5;
    static sf::Texture* _allyPellet_tex6;
    static sf::Texture* _allyPellet_tex7;
    static sf::Texture* _enemyPellet_tex0;
    static sf::Texture* _enemyPellet_tex1;
    static sf::Texture* _enemyPellet_tex2;
    static sf::Texture* _enemyPellet_tex3;
    static sf::Texture* _enemyPellet_tex4;
    static sf::Texture* _enemyPellet_tex5;
    static sf::Texture* _enemyPellet_tex6;
    static sf::Texture* _enemyPellet_tex7;
    static sf::Texture* _enemy_tex1;
    static sf::Texture* _enemy_tex2;
    static sf::Texture* _enemy_tex3;
    static sf::Texture*_boss_tex1;
    static sf::Texture*_boss_tex2;
    static sf::Texture*_boss_tex3;
    static sf::Texture* _yun_still_tex;
    static sf::Texture* _yun_hurt_tex;
    static sf::Texture* _yun_hurt_f1_tex;
    static sf::Texture* _panel_lvl1_tex;
    static sf::Texture* _panel_lvl2_tex;
    static sf::Texture* _panel_lvl3_tex;
    static sf::Texture* _background_ingame_tex;
    static sf::Texture* _background_mainMenu_tex;
    static sf::Texture* _background_options_tex;
    static sf::Texture* _background_selectLvl_tex;
    static sf::Texture* _cursor_tex;
};
