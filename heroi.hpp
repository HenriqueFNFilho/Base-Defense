#ifndef HEROI_HPP
#define HEROI_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

class Heroi {
public:
    sf::CircleShape forma;
    sf::Vector2f destino;
    int vida;
    int municao;

    Heroi();
    void definirDestino(const sf::Vector2f& novoDestino);
    void mover(float deltaTime);
    sf::Vector2f getPosicao() const;
};

#endif 