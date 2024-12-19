#ifndef GERENCIADORJOGO_HPP
#define GERENCIADORJOGO_HPP

#include <SFML/Graphics.hpp>
#include "heroi.hpp"
#include "inimigo.hpp"
#include "base.hpp"
#include "projeteis.hpp"
#include <queue>
#include <list>
#include <iostream>

class GerenciadorJogo {
private:
    sf::RenderWindow janela;
    Heroi heroi;
    Base base;
    std::list<Inimigo> inimigos;
    std::queue<Projeteis> tirosHeroi;
    std::queue<Projeteis> tirosInimigos;
    sf::Font fonte;
    sf::Text textoHUD;

    sf::Clock cronometroSpawn;
    sf::Clock relogioGeral;

    int inimigosMortos = 0;

    void processarEventos();
    void atualizar(float deltaTime);
    void renderizar();
    void verificarColisoes();

public:
    GerenciadorJogo();
    void executar();
};

#endif // GERENCIADORJOGO_HPP
