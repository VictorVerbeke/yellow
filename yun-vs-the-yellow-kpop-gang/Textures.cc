#include "Textures.hh"

Textures::Textures(){
}

Textures::~Textures(){
    // Comme les textures sont des pointeurs sur texture, il faut les libérer.
    // On delete donc toutes les valeurs associées aux clés.
    map<tex, sf::Texture*>::iterator it = texMap.begin();
    for ( ; it != texMap.end(); it++) delete(it->second);
}

Textures::TexMap Textures::texMap = init_map();

void Textures::generateTextures(){

    // Initialisation : chaque clé est associée à un pointeur sur texture vide.
    cout << "[TEXTURES] Initialisation des Textures." << endl;
    texMap[_allyPellet_tex0] = new sf::Texture();
    texMap[_allyPellet_tex1] = new sf::Texture();
    texMap[_allyPellet_tex2] = new sf::Texture();
    texMap[_allyPellet_tex3] = new sf::Texture();
    texMap[_allyPellet_tex4] = new sf::Texture();
    texMap[_allyPellet_tex5] = new sf::Texture();
    texMap[_allyPellet_tex6] = new sf::Texture();
    texMap[_allyPellet_tex7] = new sf::Texture();
    texMap[_enemyPellet_tex0] = new sf::Texture();
    texMap[_enemyPellet_tex1] = new sf::Texture();
    texMap[_enemyPellet_tex2] = new sf::Texture();
    texMap[_enemyPellet_tex3] = new sf::Texture();
    texMap[_enemyPellet_tex4] = new sf::Texture();
    texMap[_enemyPellet_tex5] = new sf::Texture();
    texMap[_enemyPellet_tex6] = new sf::Texture();
    texMap[_enemyPellet_tex7] = new sf::Texture();
    texMap[_enemy_tex1] = new sf::Texture();
    texMap[_enemy_tex2] = new sf::Texture();
    texMap[_enemy_tex3] = new sf::Texture();
    texMap[_boss_tex1] = new sf::Texture();
    texMap[_boss_tex2] = new sf::Texture();
    texMap[_boss_tex3] = new sf::Texture();
    texMap[_pUp_power_tex] = new sf::Texture();
    texMap[_pUp_speed_tex] = new sf::Texture();
    texMap[_pUp_invul_tex] = new sf::Texture();
    texMap[_yun_still_tex] = new sf::Texture();
    texMap[_yun_hurt_tex] = new sf::Texture();
    texMap[_yun_hurt_f1_tex] = new sf::Texture();
    texMap[_panel_lvl1_tex] = new sf::Texture();
    texMap[_panel_lvl2_tex] = new sf::Texture();
    texMap[_panel_lvl3_tex] = new sf::Texture();
    texMap[_background_ingame_tex] = new sf::Texture();
    texMap[_background_mainMenu_tex] = new sf::Texture();
    texMap[_background_options_tex] = new sf::Texture();
    texMap[_background_selectLvl_tex] = new sf::Texture();
    texMap[_cursor_tex] = new sf::Texture();

    // Affectation : on charge les textures via textureAffectation().
    cout << "[TEXTURES] Toutes les textures ont été initialisées." << endl;
    cout << "[TEXTURES] Affectation des textures." << endl;
    textureAffectation(_allyPellet_tex0, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/pellets/ally_spr_0.png");
    textureAffectation(_allyPellet_tex1, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/pellets/ally_spr_1.png");
    textureAffectation(_allyPellet_tex2, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/pellets/ally_spr_2.png");
    textureAffectation(_allyPellet_tex3, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/pellets/ally_spr_3.png");
    textureAffectation(_allyPellet_tex4, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/pellets/ally_spr_4.png");
    textureAffectation(_allyPellet_tex5, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/pellets/ally_spr_5.png");
    textureAffectation(_allyPellet_tex6, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/pellets/ally_spr_6.png");
    textureAffectation(_allyPellet_tex7, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/pellets/ally_spr_7.png");
    textureAffectation(_enemyPellet_tex0, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/pellets/enemy_spr_0.png");
    textureAffectation(_enemyPellet_tex1, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/pellets/enemy_spr_1.png");
    textureAffectation(_enemyPellet_tex2, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/pellets/enemy_spr_2.png");
    textureAffectation(_enemyPellet_tex3, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/pellets/enemy_spr_3.png");
    textureAffectation(_enemyPellet_tex4, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/pellets/enemy_spr_4.png");
    textureAffectation(_enemyPellet_tex5, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/pellets/enemy_spr_5.png");
    textureAffectation(_enemyPellet_tex6, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/pellets/enemy_spr_6.png");
    textureAffectation(_enemyPellet_tex7, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/pellets/enemy_spr_7.png");
    textureAffectation(_enemy_tex1, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/idol1_32.png");
    textureAffectation(_enemy_tex2, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/idol2_32.png");
    textureAffectation(_enemy_tex3, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/idol3_32.png");
    textureAffectation(_boss_tex1, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/beenzino_256.png");
    textureAffectation(_boss_tex2, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/girls_generation_256.png");
    textureAffectation(_boss_tex3, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/jonghyun_256.png");
    textureAffectation(_pUp_invul_tex, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/pup_invul_32.png");
    textureAffectation(_pUp_speed_tex, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/pup_speed_32.png");
    textureAffectation(_pUp_power_tex, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/pup_power_32.png");
    textureAffectation(_yun_still_tex, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/yun_still_64.png");
    textureAffectation(_yun_hurt_tex, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/yun_hurt_64.png");
    textureAffectation(_yun_hurt_f1_tex, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/yun_hurt_f1_64.png");
    textureAffectation(_panel_lvl1_tex, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/Beenzino_panel_390_290.png");
    textureAffectation(_panel_lvl2_tex, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/GirlGeneration_panel_390_290.png");
    textureAffectation(_panel_lvl3_tex, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/Jonghyun_panel_390_290.png");
    textureAffectation(_background_ingame_tex, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/ingame_bg.jpg");
    textureAffectation(_background_mainMenu_tex, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/main_menu_bg.png");
    textureAffectation(_background_options_tex, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/options_bg.png");
    textureAffectation(_background_selectLvl_tex, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/select_lvl_bg.png");
    textureAffectation(_cursor_tex, "/usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/cursor_24.png");

    // Fin de l'affectation : tout a marché !
    cout << "[TEXTURES] Fin d'affectation." << endl << endl;
}

void Textures::textureAffectation(tex texture, string str){

    // Grâce à cette fonction, le jeu se ferme si une texture n'est pas chargée.
    // On vérifie donc le chargement grâce à res (res == 0 si ça a bien marché).
    int res = texMap[texture]->loadFromFile(str);
    if (!res) {
        cout << "Erreur lors du chargement de la texture (\"" << str <<"\"), fin du programme." << endl;
        exit(1);
    } else {
        cout << "[TEXTURES] " << str << " chargé." << endl;
    }
}
