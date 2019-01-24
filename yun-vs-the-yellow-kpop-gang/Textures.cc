#include "Textures.hh"

Textures::Textures(){
}

Textures::~Textures(){
    delete(_allyPellet_tex0);
    delete(_allyPellet_tex1);
    delete(_allyPellet_tex2);
    delete(_allyPellet_tex3);
    delete(_allyPellet_tex4);
    delete(_allyPellet_tex5);
    delete(_allyPellet_tex6);
    delete(_allyPellet_tex7);
    delete(_enemyPellet_tex0);
    delete(_enemyPellet_tex1);
    delete(_enemyPellet_tex2);
    delete(_enemyPellet_tex3);
    delete(_enemyPellet_tex4);
    delete(_enemyPellet_tex5);
    delete(_enemyPellet_tex6);
    delete(_enemyPellet_tex7);
    delete(_enemy_tex1);
    delete(_enemy_tex2);
    delete(_enemy_tex3);
    delete(_boss_tex1);
    delete(_boss_tex2);
    delete(_boss_tex3);
    delete(_yun_still_tex);
    delete(_yun_hurt_tex);
    delete(_yun_hurt_f1_tex);
    delete(_panel_lvl1_tex);
    delete(_panel_lvl2_tex);
    delete(_panel_lvl3_tex);
    delete(_background_ingame_tex);
    delete(_background_mainMenu_tex);
    delete(_background_options_tex);
    delete(_background_selectLvl_tex);
    delete(_cursor_tex);
}

void Textures::generateTextures(){

    cout << "[TEXTURES] Initialisation des Textures." << endl;
    // Initialisation :
    _allyPellet_tex0 = new sf::Texture();
    _allyPellet_tex1 = new sf::Texture();
    _allyPellet_tex2 = new sf::Texture();
    _allyPellet_tex3 = new sf::Texture();
    _allyPellet_tex4 = new sf::Texture();
    _allyPellet_tex5 = new sf::Texture();
    _allyPellet_tex6 = new sf::Texture();
    _allyPellet_tex7 = new sf::Texture();
    _enemyPellet_tex0 = new sf::Texture();
    _enemyPellet_tex1 = new sf::Texture();
    _enemyPellet_tex2 = new sf::Texture();
    _enemyPellet_tex3 = new sf::Texture();
    _enemyPellet_tex4 = new sf::Texture();
    _enemyPellet_tex5 = new sf::Texture();
    _enemyPellet_tex6 = new sf::Texture();
    _enemyPellet_tex7 = new sf::Texture();
    _enemy_tex1 = new sf::Texture();
    _enemy_tex2 = new sf::Texture();
    _enemy_tex3 = new sf::Texture();
    _boss_tex1 = new sf::Texture();
    _boss_tex2 = new sf::Texture();
    _boss_tex3 = new sf::Texture();
    _yun_still_tex = new sf::Texture();
    _yun_hurt_tex = new sf::Texture();
    _yun_hurt_f1_tex = new sf::Texture();
    _panel_lvl1_tex = new sf::Texture();
    _panel_lvl2_tex = new sf::Texture();
    _panel_lvl3_tex = new sf::Texture();
    _background_ingame_tex = new sf::Texture();
    _background_mainMenu_tex = new sf::Texture();
    _background_options_tex = new sf::Texture();
    _background_selectLvl_tex = new sf::Texture();
    _cursor_tex = new sf::Texture();

    cout << "[TEXTURES] Toutes les textures ont été initialisées." << endl;
    cout << "[TEXTURES] Affectation des textures." << endl;
    // Affectation
    textureAffectation(_allyPellet_tex0, "images/pellets/ally_spr_0.png");
    textureAffectation(_allyPellet_tex1, "images/pellets/ally_spr_1.png");
    textureAffectation(_allyPellet_tex2, "images/pellets/ally_spr_2.png");
    textureAffectation(_allyPellet_tex3, "images/pellets/ally_spr_3.png");
    textureAffectation(_allyPellet_tex4, "images/pellets/ally_spr_4.png");
    textureAffectation(_allyPellet_tex5, "images/pellets/ally_spr_5.png");
    textureAffectation(_allyPellet_tex6, "images/pellets/ally_spr_6.png");
    textureAffectation(_allyPellet_tex7, "images/pellets/ally_spr_7.png");
    textureAffectation(_enemyPellet_tex0, "images/pellets/enemy_spr_0.png");
    textureAffectation(_enemyPellet_tex1, "images/pellets/enemy_spr_1.png");
    textureAffectation(_enemyPellet_tex2, "images/pellets/enemy_spr_2.png");
    textureAffectation(_enemyPellet_tex3, "images/pellets/enemy_spr_3.png");
    textureAffectation(_enemyPellet_tex4, "images/pellets/enemy_spr_4.png");
    textureAffectation(_enemyPellet_tex5, "images/pellets/enemy_spr_5.png");
    textureAffectation(_enemyPellet_tex6, "images/pellets/enemy_spr_6.png");
    textureAffectation(_enemyPellet_tex7, "images/pellets/enemy_spr_7.png");
    textureAffectation(_enemy_tex1, "images/idol1_32.png");
    textureAffectation(_enemy_tex2, "images/idol2_32.png");
    textureAffectation(_enemy_tex3, "images/idol3_32.png");
    textureAffectation(_boss_tex1, "images/beenzino_256.png");
    textureAffectation(_boss_tex2, "images/girls_generation_256.png");
    textureAffectation(_boss_tex3, "images/jonghyun_256.png");
    textureAffectation(_yun_still_tex, "images/yun_still_64.png");
    textureAffectation(_yun_hurt_tex, "images/yun_hurt_64.png");
    textureAffectation(_yun_hurt_f1_tex, "images/yun_hurt_f1_64.png");
    textureAffectation(_panel_lvl1_tex, "images/Beenzino_panel_390_290.png");
    textureAffectation(_panel_lvl2_tex, "images/GirlGeneration_panel_390_290.png");
    textureAffectation(_panel_lvl3_tex, "images/Jonghyun_panel_390_290.png");
    textureAffectation(_background_ingame_tex, "images/ingame_bg.jpg");
    textureAffectation(_background_mainMenu_tex, "images/main_menu_bg.png");
    textureAffectation(_background_options_tex, "images/options_bg.png");
    textureAffectation(_background_selectLvl_tex, "images/select_lvl_bg.png");
    textureAffectation(_cursor_tex, "images/cursor_24.png");

    cout << "[TEXTURES] Fin d'affectation." << endl << endl;
}
void Textures::textureAffectation(sf::Texture* tex, string str){
    int res = tex->loadFromFile(str);
    if (!res) {
        cout << "Error reading texture (\"" << str <<"\"), aborting." << endl;
        exit(1);
    } else {
        cout << "[TEXTURES] " << str << " chargé." << endl;
    }
}
