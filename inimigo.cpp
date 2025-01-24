
#include "inimigo.hpp"

Inimigo::Inimigo(const sf::Vector2f& posicaoInicial) {
    forma.setRadius(10.0f);
    forma.setFillColor(sf::Color::Green); // cor dos inimigos (verde)
    forma.setPosition(posicaoInicial);
}

bool Inimigo::deveDisparar() const {
    return relogioDisparo.getElapsedTime().asSeconds() > 1.0f;
}

void Inimigo::mover(const sf::Vector2f& alvo, float deltaTime) {
    sf::Vector2f direcao = alvo - forma.getPosition();
    float distancia = std::sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
    if (distancia > 1.0f) {
        direcao /= distancia;
        forma.move(direcao * 100.0f * deltaTime);
    }
}

sf::Vector2f Inimigo::getPosicao() const {
    return forma.getPosition();
}