#include "gerenciadorjogo.hpp"

GerenciadorJogo::GerenciadorJogo() 
    : janela(sf::VideoMode(800, 600), "Base Defence", sf::Style::Titlebar | sf::Style::Close), 
      base(sf::Vector2f(400.0f, 300.0f), sf::Vector2f(200.0f, 150.0f)) {
    janela.setFramerateLimit(60);

    if (!fonte.loadFromFile("arial.ttf")) {
        throw std::runtime_error("Erro ao carregar fonte!");
    }

    textoHUD.setFont(fonte);
    textoHUD.setCharacterSize(20);
    textoHUD.setFillColor(sf::Color::Black);
}

void GerenciadorJogo::executar() {
    while (janela.isOpen()) {
        processarEventos();
        atualizar(relogioGeral.restart().asSeconds());
        renderizar();
    }
}

void GerenciadorJogo::processarEventos() {
    sf::Event evento;
    while (janela.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            janela.close();
        }

        // Controle do herói
        if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Right) {
            sf::Vector2f destino(static_cast<float>(evento.mouseButton.x), static_cast<float>(evento.mouseButton.y));
            heroi.definirDestino(destino);
        }

        if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Q) {
            if (heroi.municao > 0) {
                sf::Vector2f direcao = sf::Vector2f(sf::Mouse::getPosition(janela)) - heroi.getPosicao();
                float magnitude = std::sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
                if (magnitude != 0) {
                    direcao /= magnitude;
                    tirosHeroi.emplace(heroi.getPosicao(), direcao);
                    heroi.municao--;
                }
            }
        }
    }
}

void GerenciadorJogo::atualizar(float deltaTime) {
    heroi.mover(deltaTime);

    // Spawn de inimigos
    if (cronometroSpawn.getElapsedTime().asSeconds() > 2.0f) {
        float x = rand() % 800;
        float y = (rand() % 2 == 0) ? 0.0f : 600.0f;
        inimigos.emplace_back(sf::Vector2f(x, y));
        cronometroSpawn.restart();
    }

    // Movimentação dos inimigos
    for (auto& inimigo : inimigos) {
        inimigo.mover(base.getPosicao(), deltaTime);

        // Inimigos disparam projéteis
        if (rand() % 100 < 2) {
            sf::Vector2f direcao = heroi.getPosicao() - inimigo.getPosicao();
            float magnitude = std::sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
            if (magnitude != 0) {
                direcao /= magnitude;
                tirosInimigos.emplace(inimigo.getPosicao(), direcao);
            }
        }
    }

    // Atualização dos projéteis
    if (!tirosHeroi.empty()) {
        Projeteis& tiro = tirosHeroi.front();
        tiro.atualizar(deltaTime);
        if (tiro.forma.getPosition().x < 0 || tiro.forma.getPosition().x > 800 ||
            tiro.forma.getPosition().y < 0 || tiro.forma.getPosition().y > 600) {
            tirosHeroi.pop();
        }
    }

    if (!tirosInimigos.empty()) {
        Projeteis& tiro = tirosInimigos.front();
        tiro.atualizar(deltaTime);
        if (tiro.forma.getPosition().x < 0 || tiro.forma.getPosition().x > 800 ||
            tiro.forma.getPosition().y < 0 || tiro.forma.getPosition().y > 600) {
            tirosInimigos.pop();
        }
    }

    verificarColisoes();
}

void GerenciadorJogo::verificarColisoes() {
    for (auto itInimigo = inimigos.begin(); itInimigo != inimigos.end();) {
        if (!tirosHeroi.empty() && tirosHeroi.front().forma.getGlobalBounds().intersects(itInimigo->forma.getGlobalBounds())) {
            itInimigo = inimigos.erase(itInimigo);
            tirosHeroi.pop();
            inimigosMortos++;
        } else {
            ++itInimigo;
        }
    }
}

void GerenciadorJogo::renderizar() {
    janela.clear(sf::Color::White);
    janela.draw(base.forma);
    janela.draw(heroi.forma);

    for (const auto& inimigo : inimigos) {
        janela.draw(inimigo.forma);
    }

    if (!tirosHeroi.empty()) {
        janela.draw(tirosHeroi.front().forma);
    }

    if (!tirosInimigos.empty()) {
        janela.draw(tirosInimigos.front().forma);
    }

    // Atualiza HUD
    textoHUD.setString(
        "Vida Base: " + std::to_string(base.vida) +
        " | Municao: " + std::to_string(heroi.municao) +
        " | Vida Heroi: " + std::to_string(heroi.vida) +
        " | Inimigos Mortos: " + std::to_string(inimigosMortos));
    textoHUD.setPosition(60, 10);
    janela.draw(textoHUD);

    janela.display();
}
