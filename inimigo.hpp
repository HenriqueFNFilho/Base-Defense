#ifndef INIMIGO_HPP
#define INIMIGO_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

class Inimigo {
public:
    sf::CircleShape forma;
    sf::Vector2f velocidade;

    Inimigo(const sf::Vector2f& posicaoInicial);
    void mover(const sf::Vector2f& alvo, float deltaTime);
};

#endif 