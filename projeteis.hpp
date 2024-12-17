#ifndef PROJETEIS_HPP
#define PROJETEIS_HPP

#include <SFML/Graphics.hpp>

class Projeteis {
public:
    sf::CircleShape forma;
    sf::Vector2f velocidade;

    Projeteis(const sf::Vector2f& posicaoInicial, const sf::Vector2f& direcao);
    void atualizar(float deltaTime);
};

#endif 
