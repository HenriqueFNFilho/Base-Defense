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
    std::vector<Projeteis> tirosHeroi;
    std::vector<Projeteis> tirosInimigos;

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
                        tirosHeroi.emplace_back(heroi.getPosicao(), direcao);
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

            // Inimigos disparam projéteis em direção ao herói
            if (rand() % 100 < 2) { // Pequena chance de disparo a cada frame
                sf::Vector2f direcao = heroi.getPosicao() - inimigo.getPosicao();
                float magnitude = std::sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
                if (magnitude != 0) {
                    direcao /= magnitude;
                    tirosInimigos.emplace_back(inimigo.getPosicao(), direcao);
                }
            }
        }

        // Atualizando tiros do herói
        for (auto& tiro : tirosHeroi) {
            tiro.atualizar(deltaTime);
        }

        // Atualizando tiros dos inimigos
        for (auto& tiro : tirosInimigos) {
            tiro.atualizar(deltaTime);
        }

        // Verificando colisões entre tiros do herói e inimigos
        for (auto itTiro = tirosHeroi.begin(); itTiro != tirosHeroi.end();) {
            bool tiroRemovido = false;
            for (auto itInimigo = inimigos.begin(); itInimigo != inimigos.end();) {
                if (itTiro->forma.getGlobalBounds().intersects(itInimigo->forma.getGlobalBounds())) {
                    itInimigo = inimigos.erase(itInimigo);
                    itTiro = tirosHeroi.erase(itTiro);
                    tiroRemovido = true;
                    break;
                } else {
                    ++itInimigo;
                }
            }
            if (!tiroRemovido) {
                ++itTiro;
            }
        }


        // Renderizando elementos
        janela.clear(sf::Color::White); // Fundo branco
        janela.draw(base.forma);
        janela.draw(heroi.forma);
        for (const auto& inimigo : inimigos) {
            janela.draw(inimigo.forma);
        }
        for (const auto& tiro : tirosHeroi) {
            janela.draw(tiro.forma);
        }
        for (const auto& tiro : tirosInimigos) {
            janela.draw(tiro.forma);
        }
        janela.display();
    }

    return 0;
}

