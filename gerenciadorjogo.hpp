
    #ifndef GERENCIADORJOGO_HPP
    #define GERENCIADORJOGO_HPP

    #include <SFML/Graphics.hpp>
    #include "heroi.hpp"
    #include "inimigo.hpp"
    #include "base.hpp"
    #include "projeteis.hpp"
    #include <queue>
    #include <list>
    #include <iostream>
    #include <random>

    class GerenciadorJogo {
    private:
        sf::RenderWindow janela;
        Heroi heroi;
        Base base;
        std::list<Inimigo> inimigos;
        std::queue<Projeteis> tirosHeroi;
        std::queue<Projeteis> tirosInimigos;
        sf::Font fonte;
        sf::Text textoHUD;

        sf::Clock cronometroSpawn;
        sf::Clock relogioGeral;

        int inimigosMortos = 0;

        // atributo para armazenar quadrados (bonus deixados pelos inimigos)
        struct QuadradoMunicao {
            sf::RectangleShape forma;
            int valor;
            int incremento;
        };

        std::list<QuadradoMunicao> quadradosMunicao;

        bool jogoAtivo = true; // Verifica se o jogo ainda está ativo

        bool vitoria = false; // Variável para controlar a exibição da tela de vitória

        float alcanceMaximoTiros = 400.0f; // Alcance máximo dos projéteis

        void processarEventos();
        void atualizar(float deltaTime);
        void renderizar();
        void verificarColisoes();

        // Funções auxiliares
        bool projeteisForaDoAlcance(const Projeteis& proj);
        void atualizarProjeteis(std::queue<Projeteis>& tiros, float deltaTime, float alcanceMaximo);
        void mostrarGameOver();
        void mostrarVitoria();

    public:
        GerenciadorJogo();
        void executar();
    };

    #endif // GERENCIADORJOGO_HPP
