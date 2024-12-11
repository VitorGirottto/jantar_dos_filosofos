#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>
#include <vector>

using namespace std;

const int NUM_FILOSOFOS = 5;
enum Estado { PENSANDO, FAMINTO, COMENDO };

Estado estados[NUM_FILOSOFOS];
mutex mtx;
mutex mtx_impressao;
condition_variable cond[NUM_FILOSOFOS];

void imprimirEstado(int i, const string& acao) {
    unique_lock<mutex> lock(mtx_impressao);
    cout << "Filósofo " << i << " está " << acao << "." << endl;
}

void testar(int i) {
    if (estados[i] == FAMINTO &&
        estados[(i + NUM_FILOSOFOS - 1) % NUM_FILOSOFOS] != COMENDO &&
        estados[(i + 1) % NUM_FILOSOFOS] != COMENDO) {
        estados[i] = COMENDO;
        cond[i].notify_one();
    }
}

void pegarHashis(int i) {
    unique_lock<mutex> lock(mtx);
    estados[i] = FAMINTO;
    imprimirEstado(i, "faminto");
    // Evitar deadlock: tenta pegar o hashi na ordem (esquerda, direita)
    testar(i);

    while (estados[i] != COMENDO) {
        cond[i].wait(lock);
    }
    imprimirEstado(i, "comendo");
}

void soltarHashis(int i) {
    unique_lock<mutex> lock(mtx);
    estados[i] = PENSANDO;
    imprimirEstado(i, "pensando");
    testar((i + NUM_FILOSOFOS - 1) % NUM_FILOSOFOS);
    testar((i + 1) % NUM_FILOSOFOS);
}

void filosofo(int i) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> pensar(1000, 3000);
    uniform_int_distribution<> comer(2000, 5000);

    while (true) {
        imprimirEstado(i, "pensando");
        this_thread::sleep_for(chrono::milliseconds(pensar(gen)));

        pegarHashis(i);

        imprimirEstado(i, "comendo");
        this_thread::sleep_for(chrono::milliseconds(comer(gen)));

        soltarHashis(i);
    }
}

int main() {
    cout << "Pressione Enter para iniciar o jantar dos filósofos..." << endl;
    cin.ignore();

    for (int i = 0; i < NUM_FILOSOFOS; ++i) {
        estados[i] = PENSANDO;
    }

    thread filosofos[NUM_FILOSOFOS];
    for (int i = 0; i < NUM_FILOSOFOS; ++i) {
        filosofos[i] = thread(filosofo, i);
    }

    for (int i = 0; i < NUM_FILOSOFOS; ++i) {
        filosofos[i].join();
    }

    return 0;
}
