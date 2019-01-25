#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

enum tex {
    _allyPellet_tex0 = 0,   // Tous ces enums servent à définir les
    _allyPellet_tex1,       // clés du map contenu dans la classe.
    _allyPellet_tex2,       // En effet, chaque texture est accessible
    _allyPellet_tex3,       // via une des clés présentes à gauche.
    _allyPellet_tex4,       // En faisant texMap[_allyPellet_tex0] par exemple,
    _allyPellet_tex5,       // on accède à la texture _allyPellet_tex0. Ca
    _allyPellet_tex6,       // sert à éviter la création de multiples textures
    _allyPellet_tex7,       // à chaque création d'objet. En effet, avant,
    _enemyPellet_tex0,      // nous faisions un loadFromFile(path) pour chaque
    _enemyPellet_tex1,      // nouvel objet créé, et donc un chargement étant
    _enemyPellet_tex2,      // potentiellement long, le jeu pouvait se mettre
    _enemyPellet_tex3,      // à ralentir (surtout lors des tests en mettant
    _enemyPellet_tex4,      // les fireCD à 1, faisant apparaître autant de
    _enemyPellet_tex5,      // balles par frame qu'il y avait d'ennemi à
    _enemyPellet_tex6,      // l'écran). Il s'agit d'une optimisation que
    _enemyPellet_tex7,      // nous jugions nécessaire.
    _enemy_tex1,
    _enemy_tex2,            // De plus, tout est rangé dans un map car c'est
    _enemy_tex3,            // quand même plus pratique. Le map est d'un
    _boss_tex1,             // type spécifique, regardez dans la classe
    _boss_tex2,             // directement, vous comprendrez.
    _boss_tex3,
    _pUp_speed_tex,
    _pUp_power_tex,
    _pUp_invul_tex,
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
    // Nous définissons donc un type, TexMap, qui correspond à une map entre
    // des clés de type vu plus haut et des pointeurs sur Texture.
    // Pourquoi des pointeurs ? Car sinon, les textures définies dans un scope
    // sont perdues, et tous les opérateurs par copie sont rendus inutiles.
    // Il faut donc prendre en compte des pointeurs afin de garder les textures.
    typedef map<tex, sf::Texture*> TexMap;

    // Créateurs, Destructeur
    Textures();
    ~Textures();

    // Méthode d'affectation des textures aux clés.
    void textureAffectation(tex texture, string str);
    void generateTextures();

    // Attribut : la map en question.
    static TexMap texMap;

private:

    // Méthode privée, utilisée pour initialiser le tableau (sinon, on obtient
    // une "undefined reference" en erreur de compilation).
    static TexMap init_map(){
        TexMap map;
        map[_allyPellet_tex0] = NULL;
        return map;
    }
};
