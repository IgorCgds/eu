#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>

// Definindo o número de threads que vão escrever no arquivo
#define NUM_THREADS 5

// Função que será executada pelas threads
void threadFunction(int threadID, std::mutex& mutex, std::ofstream& outputFile)
{
    // Bloqueia o mutex para que apenas uma thread acesse o arquivo por vez
    mutex.lock();

    // Escreve no arquivo
    outputFile << "Thread " << threadID << " escreveu no arquivo" << std::endl;

    // Libera o mutex para que outras threads possam acessar o arquivo
    mutex.unlock();
}

int main()
{
    // Abre o arquivo para escrita
    std::ofstream outputFile("arquivo.txt");

    // Cria um mutex
    std::mutex mutex;

    // Cria as threads que vão escrever no arquivo
    std::thread threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = std::thread(threadFunction, i, std::ref(mutex), std::ref(outputFile));
    }

    // Espera as threads terminarem de executar
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }

    // Fecha o arquivo
    outputFile.close();

    return 0;
}
