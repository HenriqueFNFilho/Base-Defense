# Base-Defense

Produzido por: HENRIQUE FRANCISCO DO NASCIMENTO FILHO

Para a disciplina de Linguagem de Programação I - UFRN
Profº ISAAC FRANCO FERNANDES

Tratata-se da criação de um jogo 2D, onde o objetivo é protejer a base, elimininando o máximo de inimigos possíveis.
O deslocamento se dá com o clique direito do mouse e os disparos se dá com a tecla Q, para onde o ponteiro do mouse estiver apontando no momento.

O Repositório encontra-se em https://github.com/HenriqueFNFilho/Base-Defense

O vídeo de apresentação do check point 1 encontra-se em https://youtu.be/nTI1QAGPEfQ

EXECUÇÃO DO PROGRAMA

Descompacte o arquivo no diretório desejado. Acesse a pasta /Base_Defense pelo terminal. ex: 
$ cd /home/usuario/Base_Defense/

Para compilar, digite no terminal: $ make

Para executar, digite no terminal: $ make run


Check Points

Para o primeiro check point, foram implementados o movimento dos inimigos em direção ao herói; o clique no botão direito do mouse, para informar para onde o herói se deslocará; a letra Q para o disparo de tiros; o HUD, que por enquanto só está contabilizando (decrescendo) a munição e (somando) o número de inimigos eliminados.

Das taréfas básicas, estão faltando a colisão dos projéteis com a base e com o herói, bem como o decréscimo de vida de ambos. Também está faltando o encerramento do jogo (quando a base ou o herói não possui mais vida), bem como limitar o alcance dos projéteis.


