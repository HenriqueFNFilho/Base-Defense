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
        if (jogoAtivo) {
            processarEventos();
            atualizar(relogioGeral.restart().asSeconds());
        }
        else {
            // Limpa recursos após o game over
            inimigos.clear();
            tirosHeroi = {};
            tirosInimigos = {};
            quadradosMunicao.clear();

            // Reinicia variáveis para um novo jogo
            heroi.vida = 100;
            heroi.municao = 100;
            base.vida = 100;
            inimigosMortos = 0;

            // Mostra tela de game over
            mostrarGameOver();

            // Espera por uma ação do usuário
            while (janela.isOpen()) {
                sf::Event event;
                while (janela.pollEvent(event)) {
                    if (event.type == sf::Event::Closed ||
                        (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                        janela.close();
                    }
                }
            }
            break; // Sai do loop principal
        }
        renderizar();
    }
}

void GerenciadorJogo::processarEventos() {
    sf::Event evento;
    while (janela.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            janela.close();
        }

        if (jogoAtivo && evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Q) {
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
         if (jogoAtivo && evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Right) {
        heroi.definirDestino(sf::Vector2f(evento.mouseButton.x, evento.mouseButton.y));
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

    // Movimentação e tiros dos inimigos
    for (auto& inimigo : inimigos) {
        inimigo.mover(base.getPosicao(), deltaTime);

        // Controle de tiros dos inimigos
        if (rand() % 100 < 2) {
            sf::Vector2f direcao = heroi.getPosicao() - inimigo.getPosicao();
            float magnitude = std::sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
            if (magnitude != 0) {
                direcao /= magnitude;
                tirosInimigos.emplace(inimigo.getPosicao(), direcao);
            }
        }
    }

    if (jogoAtivo && heroi.vida > 0 && base.vida > 0) {
        if (relogioGeral.getElapsedTime().asSeconds() > 10.0f) {
            jogoAtivo = false;
            vitoria = true; 
        }
    }

    atualizarProjeteis(tirosHeroi, deltaTime, alcanceMaximoTiros);
    atualizarProjeteis(tirosInimigos, deltaTime, alcanceMaximoTiros);

    verificarColisoes();

    // Verifica se o jogo acabou
    if (heroi.vida <= 0 || base.vida <= 0) {
        jogoAtivo = false;
    }
}

void GerenciadorJogo::atualizarProjeteis(std::queue<Projeteis>& projeteis, float deltaTime, float alcanceMax) {
    if (!projeteis.empty()) {
        Projeteis& tiro = projeteis.front();
        tiro.atualizar(deltaTime);

        if (tiro.getDistanciaPercorrida() > alcanceMax ||
            tiro.getForma().getPosition().x < 0 || tiro.getForma().getPosition().x > 800 ||
            tiro.getForma().getPosition().y < 0 || tiro.getForma().getPosition().y > 600) {
            projeteis.pop();
        }
    }
}

void GerenciadorJogo::verificarColisoes() {
    for (auto itInimigo = inimigos.begin(); itInimigo != inimigos.end();) {
        if (!tirosHeroi.empty() && tirosHeroi.front().getForma().getGlobalBounds().intersects(itInimigo->forma.getGlobalBounds())) {
            sf::RectangleShape quadrado(sf::Vector2f(20.0f, 20.0f));
            int corAleatoria = rand() % 3; // Gera um número aleatório entre 0 e 2
            int valorAleatorio = rand() % 10 + 1; // Gera um número aleatório entre 1 e 10
            
            switch (corAleatoria) {
                case 0: // Lilás (incrementa munição)
                    quadrado.setFillColor(sf::Color(200, 0, 200));
                    break;
                case 1: // Amarelo (incrementa vida da base)
                    quadrado.setFillColor(sf::Color(255, 255, 0));
                    break;
                case 2: // Laranja (incrementa vida do herói)
                    quadrado.setFillColor(sf::Color(255, 165, 0));
                    break;
            }
            
            quadrado.setPosition(itInimigo->getPosicao());
            quadradosMunicao.push_back({quadrado, corAleatoria + 1, valorAleatorio}); // Armazena a cor e o valor como valores
            itInimigo = inimigos.erase(itInimigo);
            tirosHeroi.pop();
            inimigosMortos++;
        } else {
            ++itInimigo;
        }
    }
    
    for (auto itQuadrado = quadradosMunicao.begin(); itQuadrado != quadradosMunicao.end();) {
        if (heroi.forma.getGlobalBounds().intersects(itQuadrado->forma.getGlobalBounds())) {
            switch (itQuadrado->valor - 1) { // Verifica a cor armazenada e aplica o efeito correspondente
                case 0: // Lilás
                    heroi.municao += itQuadrado->incremento;
                    break;
                case 1: // Amarelo
                    base.vida += itQuadrado->incremento;
                    break;
                case 2: // Laranja
                    heroi.vida += itQuadrado->incremento;
                    break;
            }
            
            itQuadrado = quadradosMunicao.erase(itQuadrado);
        } else {
            ++itQuadrado;
        }
    }

    while (!tirosInimigos.empty()) {
        Projeteis& tiro = tirosInimigos.front();
        if (tiro.getForma().getGlobalBounds().intersects(heroi.forma.getGlobalBounds())) {
            heroi.vida--;
            tirosInimigos.pop();
        } else if (tiro.getForma().getGlobalBounds().intersects(base.forma.getGlobalBounds())) {
            base.vida--;
            tirosInimigos.pop();
        } else {
            break;
        }
    }
}



void GerenciadorJogo::mostrarGameOver() {
    sf::Text gameOverTexto;
    gameOverTexto.setFont(fonte);
    gameOverTexto.setCharacterSize(50);
    gameOverTexto.setFillColor(sf::Color::Black);

    // Concatena o número de inimigos abatidos à mensagem
    std::string mensagemGameOver = "GAME OVER\n(Inimigos abatidos: " + std::to_string(inimigosMortos) + ")";
    gameOverTexto.setString(mensagemGameOver);

    gameOverTexto.setPosition(400.0f - gameOverTexto.getGlobalBounds().width / 2, 300.0f);
    janela.draw(gameOverTexto);
}

void GerenciadorJogo::mostrarVitoria() {
    sf::Text vitoriaTexto;
    vitoriaTexto.setFont(fonte);
    vitoriaTexto.setCharacterSize(50);
    vitoriaTexto.setFillColor(sf::Color::Black);
    vitoriaTexto.setString("YOU WIN");
    vitoriaTexto.setPosition(400.0f - vitoriaTexto.getGlobalBounds().width / 2, 300.0f);
    janela.draw(vitoriaTexto);
}



void GerenciadorJogo::renderizar() {
    janela.clear(sf::Color::White);
    janela.draw(base.forma);
    janela.draw(heroi.forma);

    for (const auto& inimigo : inimigos) {
        janela.draw(inimigo.forma);
    }

    for (const auto& quadrado : quadradosMunicao) {
        janela.draw(quadrado.forma);
    }

    if (!tirosHeroi.empty()) {
        janela.draw(tirosHeroi.front().getForma());
    }

    if (!tirosInimigos.empty()) {
        janela.draw(tirosInimigos.front().getForma());
    }

    textoHUD.setString(
        "Vida Base: " + std::to_string(base.vida) +
        " | Municao: " + std::to_string(heroi.municao) +
        " | Vida Heroi: " + std::to_string(heroi.vida) +
        " | Inimigos Mortos: " + std::to_string(inimigosMortos));
    textoHUD.setPosition(60, 10);
    janela.draw(textoHUD);

    for (const auto& quadrado : quadradosMunicao) {
        janela.draw(quadrado.forma);
        sf::Text texto;
        texto.setFont(fonte);
        texto.setCharacterSize(12);
        texto.setFillColor(sf::Color::Black);
        texto.setString(std::to_string(quadrado.incremento));
        texto.setPosition(quadrado.forma.getPosition().x + 5, quadrado.forma.getPosition().y + 5);
        janela.draw(texto);
    }

    if (!jogoAtivo) {
        mostrarGameOver();
    }

    janela.display();
}

