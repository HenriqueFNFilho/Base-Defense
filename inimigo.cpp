#include "inimigo.hpp"

Inimigo::Inimigo(const sf::Vector2f& posicaoInicial) {
    forma.setRadius(15.0f);
    forma.setFillColor(sf::Color::Green); // Inimigos verdes
    forma.setPosition(posicaoInicial);
}

void Inimigo::mover(const sf::Vector2f& alvo, float deltaTime) {
    sf::Vector2f direcao = alvo - forma.getPosition();
    float distancia = std::sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
    if (distancia > 1.0f) {
        direcao /= distancia;
        forma.move(direcao * 100.0f * deltaTime);
    }
}