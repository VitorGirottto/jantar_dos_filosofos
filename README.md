# Jantar dos Filósofos

## Visão Geral
Este projeto implementa a solução do problema clássico do "Jantar dos Filósofos" utilizando C++ e programação concorrente. O problema ilustra a dificuldade de sincronização entre processos que competem por recursos compartilhados, neste caso, os hashis (garfos) que os filósofos precisam para comer.

## Requisitos
- Compilador C++ (g++ ou similar) com suporte a C++11 ou superior.
- Ambiente de terminal para compilar e executar o código.

## Funcionalidade
O código simula cinco filósofos que alternam entre os estados de "pensando", "faminto" e "comendo". Cada filósofo tenta pegar os hashis à sua esquerda e à sua direita para comer. O uso de mutexes e variáveis de condição garante que os filósofos não entrem em deadlock.

### Estrutura do Código
- **Enums e Variáveis**: O código define um enum `Estado` para representar os estados dos filósofos e um array `estados` para armazenar o estado de cada filósofo.
- **Funções**:
  - `imprimirEstado(int i, const string& acao)`: Imprime o estado atual de um filósofo.
  - `testar(int i)`: Verifica se um filósofo pode começar a comer.
  - `pegarHashis(int i)`: Tenta pegar os hashis e muda o estado para "faminto".
  - `soltarHashis(int i)`: Libera os hashis e muda o estado para "pensando".
  - `filosofo(int i)`: Representa o comportamento de cada filósofo em um loop infinito.
- **Main**: Inicializa os estados dos filósofos e cria as threads.

## Compilação e Execução
Para compilar e executar o código, siga os passos abaixo:

1. Salve o código em um arquivo chamado `jantar_dos_filosofos.c`.
2. Abra um terminal e navegue até o diretório onde o arquivo está salvo.
3. Compile o código com o seguinte comando:

   ```bash
   gcc -o jantar_dos_filosofos jantar_dos_filosofos.c -lpthread

 4. Execute o programa:

   ```bash
./jantar_dos_filosofos
