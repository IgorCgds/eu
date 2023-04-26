#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx;



void escrever_no_arquivo(int id) {
    ofstream arquivo("arquivo.txt", ios::app);
    if (arquivo.is_open()) {
        mtx.lock();
        
        arquivo << "Thread " << (id+1) << " escreveu no arquivo" << endl;
        std::cout << "Thread " << (id+1) << " escreveu no arquivo" << endl;
        mtx.unlock();
        arquivo.close();
    }
}

int main() {
    thread threads[5];
    for (int i = 0; i < 5; i++) {
        threads[i] = thread(escrever_no_arquivo, i);
    }
    for (int i = 0; i < 5; i++) {
        threads[i].join();
    }
    return 0;
}
