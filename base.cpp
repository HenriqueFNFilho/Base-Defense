
#include "base.hpp"

Base::Base(const sf::Vector2f& posicao, const sf::Vector2f& tamanho) {
    forma.setSize(tamanho);
    forma.setFillColor(sf::Color::Red);
    forma.setOrigin(tamanho / 2.0f);
    forma.setPosition(posicao);
    vida = 100;
}

sf::Vector2f Base::getPosicao() const {
    return forma.getPosition();
}