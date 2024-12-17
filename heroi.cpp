#include "heroi.hpp"

Heroi::Heroi() {
    forma.setRadius(20.0f);
    forma.setFillColor(sf::Color::Blue);
    forma.setPosition(400.0f, 300.0f); // Inicia no centro
    vida = 100;
    municao = 100;
    destino = forma.getPosition(); // Inicialmente, o herói não se move

}

void Heroi::definirDestino(const sf::Vector2f& novoDestino) {
    destino = novoDestino;
}

void Heroi::mover(float deltaTime) {
    sf::Vector2f direcao = destino - forma.getPosition();
    float distancia = std::sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
    if (distancia > 1.0f) {
        direcao /= distancia;
        forma.move(direcao * 200.0f * deltaTime);
    }
}

sf::Vector2f Heroi::getPosicao() const {
    return forma.getPosition();
}
