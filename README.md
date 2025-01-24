# Base-Defense

Produzido por: HENRIQUE FRANCISCO DO NASCIMENTO FILHO
Matrícula: 20200119319

Para a disciplina de Linguagem de Programação I - IMD - UFRN
Profº ISAAC FRANCO FERNANDES

Tratata-se da criação de um jogo 2D, onde o objetivo é protejer a base, elimininando o máximo de inimigos possíveis, antes de o herói morrer, ou a base ser destruída.
O deslocamento se dá com o clique direito do mouse e os disparos se dá com a tecla Q, para onde o ponteiro do mouse estiver apontando no momento.
A cada inimigo morto, uma carga-bonus é deixada com um valor aleatório, que varia de 1 a 10. O valor do bonus será incrementado dependendo da cor da carga. Se for lilás, será incrementada a munição. Se for amarela, será incrementada a vida da base. E se for laranja, será incrementada a vida do herói.

O Repositório encontra-se em https://github.com/HenriqueFNFilho/Base-Defense

O vídeo de apresentação do check point 1 encontra-se em https://youtu.be/nTI1QAGPEfQ

EXECUÇÃO DO PROGRAMA

Descompacte o arquivo no diretório desejado. Acesse a pasta /Base_Defense pelo terminal. ex: 
$ cd /home/usuario/Base_Defense/

Para compilar, digite no terminal: $ make

Para executar, digite no terminal: $ make run


Check Points

1º Check Point:
Para o primeiro check point, foram implementados o movimento dos inimigos em direção ao herói; o clique no botão direito do mouse, para informar para onde o herói se deslocará; a letra Q para o disparo de tiros; o HUD, que por enquanto só está contabilizando (decrescendo) a munição e (somando) o número de inimigos eliminados.

Das taréfas básicas, estão faltando a colisão dos projéteis com a base e com o herói, bem como o decréscimo de vida de ambos. Também está faltando o encerramento do jogo (quando a base ou o herói não possui mais vida), bem como limitar o alcance dos projéteis.

2ºCheck Point:
No segundo check point, foram criadas as colisões entre projéteis e a base ou herói. Foi feito o decréscimo da vida de ambos, ao serem atingido. Foi limitado o alcance dos projéteis. Foi criado o ponto de encerramento do jogo (quando a base ou o herói não possui mais vida). E foram criadas as cargas-bonus, que funcionam como drops de mantimentos para a recarga da vida do herói ou da base, bem como o reabastecimento de munição.



