#include "gerenciadorjogo.hpp"

int main() {
    try {
        GerenciadorJogo jogo; // Inicializa o gerenciador do jogo
        jogo.executar();      // Inicia o loop principal do jogo
    } catch (const std::exception& e) {
        // Exibe mensagens de erro no console caso algo dê errado
        std::cerr << "Erro: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
