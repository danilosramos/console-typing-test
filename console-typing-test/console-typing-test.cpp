#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib> // Para usar std::system para limpar a tela

#ifdef _WIN32
    #include <windows.h> // Para usar Sleep no Windows
#else
    #include <unistd.h> // Para usar usleep em sistemas Unix-like
#endif

using namespace std;

class TypingTest {
private:
    vector<string> referenceWords; // Palavras de referência para comparação
    vector<string> userWords;      // Palavras digitadas pelo usuário
    int errorCount;                // Contador de erros
    chrono::steady_clock::time_point startTime; // Hora de início do teste
    chrono::steady_clock::time_point endTime;   // Hora de término do teste

public:
    // Construtor: Inicializa errorCount e garante que endTime comece zerado
    TypingTest(vector<string> refWords) : referenceWords(refWords), errorCount(0), endTime() {}

    void startTest() {
        cout << "Bem-vindo ao teste de digitação!\n";
        cout << "Digite o seguinte texto:\n";

        // Exibir texto de referência palavra por palavra
        for (size_t i = 0; i < referenceWords.size(); ++i) {
            cout << referenceWords[i] << " ";
            waitMilliseconds(500); // Aguardar 500 milissegundos entre cada palavra
        }
        cout << endl;

        // Limpar a tela e preparar
        clearScreen();
        cout << "DIGITE AGORA:\n"; // Feedback visual para começar

        // Iniciar cronômetro
        startTime = chrono::steady_clock::now();

        // Loop até o usuário terminar de digitar todas as palavras
        size_t currentWordIndex = 0;
        string inputWord;
        
        while (currentWordIndex < referenceWords.size()) {
            // Captura a entrada
            cin >> inputWord;
            userWords.push_back(inputWord);

            // Verifica erro
            if (inputWord != referenceWords[currentWordIndex]) {
                errorCount++;
            }
            
            // Atualiza feedback na tela
            displayFeedback(currentWordIndex);
            
            currentWordIndex++;
        }

        // Finalizar cronômetro
        endTime = chrono::steady_clock::now();
        displayResults();
    }

private:
    void displayFeedback(size_t currentWordIndex) {
        // Limpar a tela
        clearScreen();

        // Mostrar palavras digitadas com correções em tempo real
        for (size_t i = 0; i < userWords.size(); ++i) {
            if (i < currentWordIndex) {
                // Palavras passadas (não verificamos erro visual aqui no loop original, mas ok)
                cout << userWords[i] << " "; 
            } else if (i == currentWordIndex) { // Palavra atual (que acabou de ser digitada)
                if (userWords[i] == referenceWords[i]) {
                    cout << "\033[32m" << userWords[i] << "\033[0m "; // Verde se correto
                } else {
                    cout << "\033[31m" << userWords[i] << "\033[0m "; // Vermelho se errado
                }
            }
        }
        
        // Se imprimimos todas as userWords acima, precisamos imprimir o resto do texto referência
        // O loop original estava um pouco confuso, simplifiquei a lógica visual abaixo:
        
        // Resetar cor
        cout << "\033[0m"; 

        // Mostrar restante do texto de referência que falta digitar
        for (size_t i = userWords.size(); i < referenceWords.size(); ++i) {
            cout << referenceWords[i] << " ";
        }

        // Mostrar estatísticas parciais
        cout << "\n\n";
        // Passamos currentWordIndex + 1 pois ele acabou de digitar a palavra 'Index'
        cout << "Palavras por minuto (WPM): " << calculateWPM(currentWordIndex + 1) << endl;
        cout << "Precisão: " << fixed << setprecision(2) << calculateAccuracy(currentWordIndex) << "%" << endl;
    }

    double calculateWPM(size_t wordsTypedSoFar) {
        // Se endTime for igual ao tempo "zero" (padrão), o teste ainda está rolando.
        // Se não, o teste acabou.
        auto currentTime = (endTime == chrono::steady_clock::time_point()) ? chrono::steady_clock::now() : endTime;
        
        auto durationSeconds = chrono::duration_cast<chrono::seconds>(currentTime - startTime).count();
        
        // Evita divisão por zero se for muito rápido
        if (durationSeconds <= 0) durationSeconds = 1; 

        double minutes = durationSeconds / 60.0;
        double wpm = (static_cast<double>(wordsTypedSoFar) / minutes);
        return wpm;
    }

    double calculateAccuracy(size_t currentWordIndex) {
        // Evitar divisão por zero no início
        if (userWords.empty()) return 100.0;

        double totalWords = static_cast<double>(userWords.size());
        double accuracy = ((totalWords - errorCount) / totalWords) * 100.0;
        return accuracy;
    }

    void displayResults() {
        clearScreen();

        cout << "Teste finalizado!\n\n";
        cout << "Resultados finais:\n";
        cout << "Palavras por minuto (WPM): " << calculateWPM(referenceWords.size()) << endl;
        cout << "Precisão: " << fixed << setprecision(2) << calculateAccuracy(referenceWords.size()) << "%" << endl;
        cout << "Número total de palavras digitadas: " << userWords.size() << endl;
        cout << "Número de erros: " << errorCount << endl;

        auto duration = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();
        cout << "Tempo total gasto: " << duration << " segundos\n";
    }

    void waitMilliseconds(int milliseconds) {
        #ifdef _WIN32
            Sleep(milliseconds); 
        #else
            usleep(milliseconds * 1000); 
        #endif
    }

    void clearScreen() {
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif
    }
};

int main() {
    // Texto de referência
    vector<string> referenceWords = {
        "It", "is", "a", "truth", "universally", "acknowledged,",
        "that", "a", "single", "man", "in", "possession", "of", "a", "good", "fortune,",
        "must", "be", "in", "want", "of", "a", "wife."
    };

    TypingTest test(referenceWords);
    test.startTest();

    return 0;
}