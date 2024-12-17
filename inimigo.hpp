#ifndef INIMIGO_HPP
#define INIMIGO_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

class Inimigo {
public:
    sf::CircleShape forma;      // Forma circular do inimigo
    sf::Vector2f velocidade;    // Velocidade do inimigo
    sf::Clock relogioDisparo;   // Cronômetro para controlar o tempo de disparo

    // Construtor: inicializa o inimigo em uma posição inicial
    Inimigo(const sf::Vector2f& posicaoInicial);

    // Método para movimentar o inimigo em direção a um alvo
    void mover(const sf::Vector2f& alvo, float deltaTime);

    // Método para verificar se o inimigo deve disparar
    bool deveDisparar() const;

    // Retorna a posição atual do inimigo
    sf::Vector2f getPosicao() const;
};

#endif // INIMIGO_HPP
