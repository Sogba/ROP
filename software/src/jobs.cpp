#include <iostream>
#include <fstream>
#include <thread>
#include <random>
#include <functional>
#include <cstring>

namespace hidden {
    void transcribe(char* input, char* output, size_t length, int thread){
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> rng(0, length - 1);

        std::ofstream file("output.txt", std::ios::app);

        while(std::memcmp(output, input, length) != 0){
            int i = rng(mt);
          output[i] = input[i];
          file << "Thread " << thread << ": " << output << "\n";
          file.flush();
          std::this_thread::sleep_for(std::chrono::milliseconds(1));

        }

        file << "Thread " << thread << " finished\n";
        file.flush();
    }
}



void transcribe(std::function<void()> syncStart, std::function<void()> syncEnd){
    char input[] = "Merry christmas";
    size_t length = strlen(input);
    char output[17] = {};

    std::thread t1(hidden::transcribe, input, output, length, 1);
    std::thread t2(hidden::transcribe, input, output, length, 2);

    t1.join();
    t2.join();
}
