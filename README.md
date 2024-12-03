# ArvoreAVL
Trabalho de estrutura de dados

## O que é uma árvore AVL?
Uma árvore AVL é uma árvore binária de busca (onde cada nó tem, no máximo, dois filhos) que tem uma característica especial: ela sempre se mantém balanceada. Isso significa que a diferença de altura entre as subárvores à esquerda e à direita de qualquer nó nunca pode ser maior que 1.

## Por que isso é importante?
Imagine que você tem uma lista de nomes em uma ordem desorganizada. Para encontrar um nome, você teria que olhar um por um. Mas em uma árvore binária de busca, os nomes estão organizados de forma que seja mais rápido encontrá-los, como um jogo de "adivinhe o número", onde você elimina metade das opções a cada passo.

Agora, se a árvore ficar muito torta (ou seja, muito mais "profunda" em um lado do que no outro), ela começa a parecer uma lista comum e perde essa vantagem. Uma árvore AVL resolve isso se ajustando automaticamente para manter o equilíbrio.

## Como a árvore AVL se ajusta?
Quando inserimos ou removemos um elemento, verificamos a altura de cada lado da árvore em relação a cada nó.

- Altura: é o número de níveis entre o nó atual e a folha mais distante.
- Fator de balanceamento: é a diferença entre as alturas da subárvore esquerda e direita.
- Fator de balanceamento = Altura da esquerda - Altura da direita.
- Valores aceitáveis: -1, 0, ou 1.

Se o fator de balanceamento ultrapassar esses valores (por exemplo, ficar +2 ou -2), a árvore faz uma rotação.

## O que é uma rotação?
Uma rotação é como reposicionar os galhos de uma árvore para que ela volte a ficar equilibrada. Existem quatro tipos principais:

- Rotação simples à direita (RR): Usada quando a subárvore da esquerda está mais pesada.
- Rotação simples à esquerda (LL): Usada quando a subárvore da direita está mais pesada.
- Rotação dupla à direita (LR): Uma combinação de rotação à esquerda e à direita.
- Rotação dupla à esquerda (RL): Uma combinação de rotação à direita e à esquerda.
  
Essas rotações movem os nós de maneira que a árvore fique balanceada sem perder a ordem.

## Exemplo prático:
Imagine uma árvore com os números 10, 20, e 30.

Inserimos 10 → tudo bem, só temos um nó.
Inserimos 20 → 20 vai para a direita de 10 (ainda balanceado).
Inserimos 30 → agora temos um problema: a subárvore direita ficou muito pesada!
Para corrigir:

Fazemos uma rotação simples à esquerda (LL) no nó 10.
O resultado será:

        20
       /  \
     10    30
               
Agora está balanceado novamente!

## Por que usar árvores AVL?
As árvores AVL garantem que as operações de busca, inserção e remoção sejam rápidas. A altura da árvore é sempre 
𝑂
(
log
⁡
𝑛
)
O(logn), o que significa que, mesmo com muitos elementos, o tempo para acessar qualquer um deles continua eficiente. Isso é crucial em sistemas como bancos de dados e jogos, onde você precisa encontrar informações rapidamente.

## Mais exemplos:
inserir 50, 10, 100, nesta ordem

      50

10 à esquerda por ser menor que 50

        50
       /  
     10

100 à direita, por ser maior que 50


        50
       /  \  
     10    100

# 

agora, inserir 10, 40, 23, nesta ordem

        10

40 a direita, por ser maior que 10

        10
           \
            40

23 a esquerda de 40. pois é maior que 10 e menor que 40

        10
          \
           40
          /
        23
para corrigir este desequlibrio criado...
1º passo: Rotação simples à direita em 40. nó 23 sobe e 40 se pendura a direita de 23.

    10
      \
       23
         \
          40
2º passo: Rotação simples à esquerda em 10. 23 sobe, e o nó 10 se pendura para a esquerda de 23.

       23
      /  \
    10    40

balanceado.

