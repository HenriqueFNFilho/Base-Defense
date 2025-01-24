
#ifndef PROJETEIS_HPP
#define PROJETEIS_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

class Projeteis {
private:
    sf::CircleShape forma;             // Forma gráfica do projétil
    sf::Vector2f velocidade;           // Direção e velocidade do projétil
    sf::Vector2f posicaoInicial;       // Posição inicial do projétil
    float distanciaPercorrida = 0.0f;  // Distância total percorrida pelo projétil

public:
    Projeteis(const sf::Vector2f& posicaoInicial, const sf::Vector2f& direcao);

    void atualizar(float deltaTime);

    // Retorna a distância total percorrida pelo projétil
    float getDistanciaPercorrida() const;

    // Retorna a forma gráfica do projétil (para renderização)
    const sf::CircleShape& getForma() const { return forma; }
};

#endif // PROJETEIS_HPP

