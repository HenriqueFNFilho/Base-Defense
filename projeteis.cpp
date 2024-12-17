#include "projeteis.hpp"

Projeteis::Projeteis(const sf::Vector2f& posicaoInicial, const sf::Vector2f& direcao) {
    forma.setRadius(5.0f);
    forma.setFillColor(sf::Color::Black);
    forma.setPosition(posicaoInicial);
    velocidade = direcao * 300.0f;
}

void Projeteis::atualizar(float deltaTime) {
    forma.move(velocidade * deltaTime);
}