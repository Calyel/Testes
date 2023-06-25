//Autor: Calyel Junio de Andrade dos Santos
//Codigo Utilizando FFmpeg pra abrir e repoduzir video

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdio>

using namespace std;

 //Criação da classe VideoPlayer
class VideoPlayer {
public:
    //Metodo responsavel pelo player do video
    void Play(const string& nome) {

        //Comando para reproduzir o vídeo utilizando o ffplay
        string command = "ffplay -i " + nome;

        //Executa o comando no prompt
        int result = system(command.c_str());

        //Verifica se houve algum erro na reprodução do video
        if (result != 0) {
            throw runtime_error("Erro ao reproduzir o video.");
        }
    }
    
    //Metodo responsavel por tratar das exeções
    void VideoException(const string& nome) {

        //Exibe uma mensagem de erro informando que o arquivo não foi encontrado
        cerr << "Erro: o arquivo '" << nome << "' nao foi encontrado na pasta." << endl;
    }


    //Metodo responsavel por exibir o codec do video
    void Codec(const string& nome) {

        //Comando para obter informações sobre o codec do vídeo utilizando o ffprobe
        string command = "ffprobe -v error -select_streams v:0 -show_entries stream=codec_name -of default=noprint_wrappers=1 " + nome;

        //Abre um pipe para capturar a saída do comando
        FILE* pipe = popen(command.c_str(), "r");

        //Verifica se o pipe foi aberto corretamente
        if (!pipe) {
            throw runtime_error("Erro: falha ao executar o comando 'ffprobe'.");
        }

        char buffer[128];
        string result;

        //Lê a saída do comando linha por linha e armazena na variável result
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result += buffer;
        }

        //Fecha o pipe
        pclose(pipe);

        //Verifica se não foi encontrado nenhum codec para o arquivo de video
        if (result.empty()) {
            throw runtime_error("Erro: nenhum codec encontrado para o arquivo '" + nome + "'.");
        }

        // Exibe o codec do video na saida
        cout << "Codec do video: " << result << endl;
    }
};

int main() {

    // Cria um objeto da classe VideoPlayer
    VideoPlayer player;
    string nome;
    cout << "Informe o nome do arquivo de video: ";
    //Lê o nome do arquivo de vídeo usando getline que lê com caracteres especial ou espaços sem inteferir
    getline(cin, nome);

    try {
        //chama o metodo codec e exibe o codec do video
        player.Codec(nome);
        //chama o metodo Pay e reproduz o video
        player.Play(nome);
    } catch (const runtime_error& e) {
        //Trata as exceções lançadas, exibindo uma mensagem de erro 
        player.VideoException(nome);
    }

    return 0;
}