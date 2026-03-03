#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void PertenceAFD(char **palavras, char *alfabeto, char *estados, char *estadoInicial, char *estadosFinais, char **transicoes, int linhasPalavras, int linhasTransicoes) {
    FILE *arquivo;

    arquivo = fopen("resultado.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao criar arquivo\n");
        return ;
    }

    int ilp = 0; //indice para linhda de palavras

    // loop para percorrer as palavras
    while(ilp != linhasPalavras){
        int icp = 0; //indice para colunas de palavras
        int ilt = 0; //indice para linha de transições

        char estadoAtual = estadoInicial[0];

        //loop para percorrer os caracteres da palavra
        
        while (palavras[ilp][icp] != '\0'){
            
            char simbolo = palavras[ilp][icp];
            bool transicaoEncontrada = false;

            //loop para achar a transição
            while (transicaoEncontrada == false && ilt != linhasTransicoes){
                if (transicoes[ilt][0] == estadoAtual && transicoes[ilt][1] == simbolo){
                    estadoAtual = transicoes[ilt][2];
                    transicaoEncontrada = true; 
                    break;
                }

                if (transicaoEncontrada == false){
                    ilt++;
                } 
            }//saiu do loop de transições
            ilt = 0;//reinicia o indice da linha do transicoes
            icp++;//proximo caracter
        }
        int i = 0;
        bool aceito = false;
        //verifica se foi aceito,estadual estando em estados finais
        while (estadosFinais[i] != '\0'){
            if (estadoAtual == estadosFinais[i]){
                aceito = true;
                break;
            }
            i++;
        }
        //se nao foi aceito coloca no arquivo de saida que a palavra foi aceita
        if (aceito == true){
            fprintf(arquivo, "M aceita a palavra <%s> \n", palavras[ilp]);
        }
        else{
            fprintf(arquivo, "M rejeita a palavra <%s> \n", palavras[ilp]);
        }
        ilp++;//proxima palavra
    }

}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo>\n", argv[0]);
        return 1;
    }
    
    char linha[50];

    //Iniciando o alfabeto
    int tamanhoAlfabeto = 1;
    char *Alfabeto = malloc(tamanhoAlfabeto * sizeof(char));

    //Iniciando os estados
    int tamanhoEstados = 1;
    char *Estados = malloc(tamanhoEstados * sizeof(char)); 

    //Iniciando os estadosIniciais
    int tamanhoEstadosInicias = 1;
    char *estadosIniciais = malloc(tamanhoEstadosInicias * sizeof(char));

    //Iniciando os estadosFinais
    int tamanhoEstadosFinais = 1;
    char *estadosFinais = malloc(tamanhoEstadosFinais * sizeof(char));

    //Iniciando transições
    int linhasTransicoes = 0;
    int colunasTransicoes = 0;
    char **transicoes = NULL;

    //Iniciando palavras
    int linhasPalavras = 0;
    int colunasPalavras = 0;
    char **palavras = NULL;

    FILE *arquivo = fopen(argv[1], "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (linha[0] == '#') {
            printf("%s\n", linha);
            continue;
        }
        // se alfabeto
        if (linha[0] == 'A') {
            int il = 1; //começa a ler após o "A"
            while (linha[il] != '\n'){//vai até \n
                if (linha[il] == ' '){// se for espaço pula
                    il++;
                    continue;
                }
                Alfabeto[tamanhoAlfabeto - 1] = linha[il];
                il++;
                tamanhoAlfabeto++;//aumenta o tamanho do vetor alfabeto
                Alfabeto = realloc(Alfabeto, tamanhoAlfabeto * sizeof(char));//aloca mais memoria
                
            }
            printf("A: ");
            for (int iA = 0; iA < tamanhoAlfabeto - 1; iA++) {
                printf("%c ", Alfabeto[iA]);
            }
            printf("\n");
            continue;
        }
        
        if (linha[0] == 'Q') {
            int il = 1; //começa a ler após o "Q"
            while (linha[il] != '\n'){//vai até \n
                if (linha[il] == ' '){// se for espaço pula
                    il++;
                    continue;
                }
                Estados[tamanhoEstados - 1] = linha[il];
                il++;
                tamanhoEstados++;//aumenta o tamanho do vetor estados
                Estados = realloc(Estados, tamanhoEstados * sizeof(char));//aloca mais memoria
                
            }
            printf("Q: ");
            for (int iE = 0; iE < tamanhoEstados - 1; iE++) {
                printf("%c ", Estados[iE]);
            }
            printf("\n");
            continue;
        }

        if (linha[0] == 'q') {
            int il = 1; //começa a ler após o "q"
            while (linha[il] != '\n'){//vai até \n
                if (linha[il] == ' '){// se for espaço pula
                    il++;
                    continue;
                }
                if(tamanhoEstadosInicias > 1){
                    printf("Erro: mais de um estado inicial encontrado.\n");
                    return 1;
                }
                estadosIniciais[tamanhoEstadosInicias - 1] = linha[il];
                il++;
                tamanhoEstadosInicias++;//aumenta o tamanho do vetor estados iniciais
                
                
            }
            printf("q: ");
            for (int iEI = 0; iEI < tamanhoEstadosInicias - 1; iEI++) {
                printf("%c ", estadosIniciais[iEI]);
            }
            printf("\n");
            continue;
        }

        if (linha[0] == 'F') {
            int il = 1; //começa a ler após o "F"
            while (linha[il] != '\n'){//vai até \n
                if (linha[il] == ' '){// se for espaço pula
                    il++;
                    continue;
                }
                estadosFinais[tamanhoEstadosFinais - 1] = linha[il];
                il++;
                tamanhoEstadosFinais++;//aumenta o tamanho do vetor estados finais
                estadosFinais = realloc(estadosFinais, tamanhoEstadosFinais * sizeof(char));//aloca mais memoria
                
            }
            printf("F: ");
            for (int iEF = 0; iEF < tamanhoEstadosFinais - 1; iEF++) {
                printf("%c ", estadosFinais[iEF]);
            }
            printf("\n");
            continue;
        }

        if (linha[0] == 'T') {
            int il = 1; //começa a ler após o "T" iL - linha do arquivo
            
            while (linha[il] != '\n'){//vai até \n
                if (linha[il] == ' '){// se for espaço pula
                    il++;
                    continue;
                }
                if (colunasTransicoes == 0){
                    linhasTransicoes ++;
                    transicoes = realloc(transicoes, linhasTransicoes * sizeof(char*));
                    transicoes[linhasTransicoes - 1] = NULL;
            }
                
                transicoes[linhasTransicoes - 1] = realloc(transicoes[linhasTransicoes - 1], (colunasTransicoes + 1) * sizeof(char));
                transicoes[linhasTransicoes - 1][colunasTransicoes] = linha[il];
                il++;
                colunasTransicoes++;
            }
            transicoes[linhasTransicoes - 1] = realloc(transicoes[linhasTransicoes - 1], (colunasTransicoes + 1) * sizeof(char));
            transicoes[linhasTransicoes - 1][colunasTransicoes] = '\0';
            

            printf("T: ");
            for (int iT = 0; iT < colunasTransicoes; iT++) {
                printf("%c ", transicoes[linhasTransicoes - 1][iT]);
            }

            colunasTransicoes = 0;
            
            printf("\n");
            continue;
        } 
        
        
        if (linha[0] == 'P') {
            int il = 1; //começa a ler após o "T" iL - linha do arquivo
            //coluna declarada no início do código
            if (colunasPalavras == 0){
                    linhasPalavras ++;
                    palavras = realloc(palavras, linhasPalavras * sizeof(char*));
                    palavras[linhasPalavras - 1] = NULL;
            }
            
            while (linha[il] != '\n'){//vai até \n
                if (linha[il] == ' '){// se for espaço pula
                    il++;
                    continue;
                }

                palavras[linhasPalavras - 1] = realloc(palavras[linhasPalavras - 1], (colunasPalavras + 1) * sizeof(char));
                palavras[linhasPalavras - 1][colunasPalavras] = linha[il];
                il++;
                colunasPalavras++;
                
            }
            palavras[linhasPalavras - 1] = realloc(palavras[linhasPalavras - 1], (colunasPalavras + 1) * sizeof(char));
            palavras[linhasPalavras - 1][colunasPalavras] = '\0';
            
            printf("P: ");
            for (int iP = 0; iP < colunasPalavras; iP++) {
                printf("%c ", palavras[linhasPalavras - 1][iP]);
            }
            
            colunasPalavras = 0;//reinicia a coluna para a próxima palavra
        
            printf("\n");
            continue;
        }       
    
    }

    PertenceAFD(palavras,Alfabeto,Estados,estadosIniciais,estadosFinais,transicoes,linhasPalavras,linhasTransicoes);

    fclose(arquivo);

    return 0;
}