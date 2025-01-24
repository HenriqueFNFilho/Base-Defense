
#include "projeteis.hpp"

Projeteis::Projeteis(const sf::Vector2f& posicaoInicial, const sf::Vector2f& direcao) 
    : posicaoInicial(posicaoInicial) {
    forma.setRadius(5.0f);
    forma.setFillColor(sf::Color::Black);
    forma.setPosition(posicaoInicial);
    velocidade = direcao * 300.0f;
    distanciaPercorrida = 0.0f;
}

void Projeteis::atualizar(float deltaTime) {
    sf::Vector2f movimento = velocidade * deltaTime;
    forma.move(movimento);
    distanciaPercorrida += std::sqrt(movimento.x * movimento.x + movimento.y * movimento.y);
}

float Projeteis::getDistanciaPercorrida() const {
    return distanciaPercorrida;
}
