#ifndef BASE_HPP
#define BASE_HPP

#include <SFML/Graphics.hpp>

class Base {
public:
    sf::RectangleShape forma;
    int vida;

    Base(const sf::Vector2f& posicao, const sf::Vector2f& tamanho);
    sf::Vector2f getPosicao() const;
};

#endif 