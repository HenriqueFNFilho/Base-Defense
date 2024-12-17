#include <SFML/Graphics.hpp>
#include "heroi.hpp"
#include "inimigo.hpp"
#include "base.hpp"
#include "projeteis.hpp"
#include <vector>
#include <cmath>
#include <iostream>

int main() {
    // Configurando a janela do jogo
    sf::RenderWindow janela(sf::VideoMode(800, 600), "Base Defence", sf::Style::Titlebar | sf::Style::Close);
    janela.setFramerateLimit(60);

    // Criando os elementos principais do jogo
    Heroi heroi;
    Base base(sf::Vector2f(400.0f, 300.0f), sf::Vector2f(200.0f, 150.0f)); // Base menor
    std::vector<Inimigo> inimigos;
    std::vector<Projeteis> tiros;

    sf::Clock cronometroSpawn; // Cronômetro para spawn dos inimigos
    sf::Clock relogioGeral; // Controle geral de tempo

    // Loop principal do jogo
    while (janela.isOpen()) {
        sf::Event evento;
        while (janela.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                janela.close();
            }

            // Controle de movimentação do herói com o mouse
            if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Right) {
                sf::Vector2f destino(static_cast<float>(evento.mouseButton.x), static_cast<float>(evento.mouseButton.y));
                heroi.definirDestino(destino);
            }

            // Controle de disparo do herói
            if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Q) {
                if (heroi.municao > 0) {
                    sf::Vector2f direcao = sf::Vector2f(sf::Mouse::getPosition(janela)) - heroi.getPosicao();
                    float magnitude = std::sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
                    if (magnitude != 0) {
                        direcao /= magnitude;
                        tiros.emplace_back(heroi.getPosicao(), direcao);
                        heroi.municao--;
                    }
                }
            }
        }

        // Atualizando o estado do jogo
        float deltaTime = relogioGeral.restart().asSeconds();
        heroi.mover(deltaTime);

        // Gerando novos inimigos a cada 2 segundos
        if (cronometroSpawn.getElapsedTime().asSeconds() > 2.0f) {
            float x = rand() % 800; // Spawn aleatório horizontal
            float y = (rand() % 2 == 0) ? 0.0f : 600.0f; // Spawn no topo ou base
            inimigos.emplace_back(sf::Vector2f(x, y));
            cronometroSpawn.restart();
        }

        // Movendo inimigos e verificando colisões
        for (auto& inimigo : inimigos) {
            inimigo.mover(base.getPosicao(), deltaTime);
        }

        // Atualizando tiros e verificando colisões
        for (auto& tiro : tiros) {
            tiro.atualizar(deltaTime);
        }

        // Renderizando elementos
        janela.clear(sf::Color::White); // Fundo branco
        janela.draw(base.forma);
        janela.draw(heroi.forma);
        for (const auto& inimigo : inimigos) {
            janela.draw(inimigo.forma);
        }
        for (const auto& tiro : tiros) {
            janela.draw(tiro.forma);
        }
        janela.display();
    }

    return 0;
}

