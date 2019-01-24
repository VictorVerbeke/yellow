#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

enum tex {
    _allyPellet_tex0 = 0,
    _allyPellet_tex1,
    _allyPellet_tex2,
    _allyPellet_tex3,
    _allyPellet_tex4,
    _allyPellet_tex5,
    _allyPellet_tex6,
    _allyPellet_tex7,
    _enemyPellet_tex0,
    _enemyPellet_tex1,
    _enemyPellet_tex2,
    _enemyPellet_tex3,
    _enemyPellet_tex4,
    _enemyPellet_tex5,
    _enemyPellet_tex6,
    _enemyPellet_tex7,
    _enemy_tex1,
    _enemy_tex2,
    _enemy_tex3,
    _boss_tex1,
    _boss_tex2,
    _boss_tex3,
    _yun_still_tex,
    _yun_hurt_tex,
    _yun_hurt_f1_tex,
    _panel_lvl1_tex,
    _panel_lvl2_tex,
    _panel_lvl3_tex,
    _background_ingame_tex,
    _background_mainMenu_tex,
    _background_options_tex,
    _background_selectLvl_tex,
    _cursor_tex
};

using namespace std;

class Textures {
public:
    typedef map<tex, sf::Texture*> TexMap;
    Textures();
    ~Textures();
    void textureAffectation(tex texture, string str);
    void generateTextures();
    static TexMap texMap;

private:
    static TexMap init_map(){
        TexMap map;
        map[_allyPellet_tex0] = NULL;
        return map;
    }
};
