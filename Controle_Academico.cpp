#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

struct Cadastro {
    char Aluno[50];
    char Curso[20];
    char CPF[19];
    char Matricula[20];
    char Turno[11];
    struct Cadastro* next;
};

struct Cadastro* createCadastro(const char* Aluno, const char* Curso, const char* CPF, const char* Matricula, const char* Turno) {
    struct Cadastro* newCadastro = (struct Cadastro*)malloc(sizeof(struct Cadastro));
    if (newCadastro) {
        strcpy(newCadastro->Aluno, Aluno);
        strcpy(newCadastro->Curso, Curso);
        strcpy(newCadastro->CPF, CPF);
        strcpy(newCadastro->Matricula, Matricula);
        strcpy(newCadastro->Turno, Turno);
        newCadastro->next = NULL;
    }
    return newCadastro;
}

void addCadastro(struct Cadastro** list, const char* Aluno, const char* Curso, const char* CPF, const char* Matricula, const char* Turno) {
    struct Cadastro* newCadastro = createCadastro(Aluno, Curso, CPF, Matricula, Turno);
    if (newCadastro) {
        newCadastro->next = *list;
        *list = newCadastro;
    }
}

void exibirCadastros(const struct Cadastro* list) {
    const struct Cadastro* current = list;
    int count = 0; // Vari�vel para contar contatos

    while (current != NULL) {
        printf("\n\nNome do aluno: %s\n", current->Aluno);
        printf("Curso: %s\n", current->Curso);
        printf("CPF do aluno: %s\n", current->CPF);
        printf("Matricula: %s\n", current->Matricula);
        printf("Turno: %s\n\n", current->Turno);
        current = current->next;
        count++;
    }

    printf("Total de alunos matriculados: %d\n\n\n\n", count); // Exibe a quantidade de alunos
}

void deleteCadastro(struct Cadastro** list, const char* CPF) {
    struct Cadastro* current = *list;
    struct Cadastro* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->CPF, CPF) == 0) {
            if (previous == NULL) {
                *list = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);

            return;
        }

        previous = current;
        current = current->next;
    }

    printf("Aluno n�o encontrado.\n");
}

void updateCadastro(struct Cadastro* list, const char* CPF, const char* newCurso) {
    while (list != NULL) {
        if (strcmp(list->CPF, CPF) == 0) {
            strcpy(list->Curso, newCurso);

            return;
        }
        list = list->next;
    }

    printf("Aluno n�o encontrado.\n");
}

int main() {
    struct Cadastro* CadastroList = NULL;
    char Aluno[50];
    char Curso[20];
    char CPF[19];
    char Matricula[20];
    char Turno[11];
    int choice;
    int schoice;
    int zchoice;
    int segundos = 1;

    while (1) {
        printf("Gerenciamento de Alunos da Instituicao @rroba:\n");
        printf("1. Cadastrar aluno\n");
        printf("2. Exibir lista de alunos\n");
        printf("3. Excluir aluno da base\n");
        printf("4. Modificar curso do Aluno\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);
		getchar(); // Consumir o caractere de nova linha
        switch (choice) {
            case 1:
                system("cls");

                printf("*NOVO ALUNO*:\n\n");

                printf(" Nome: ");
                fgets(Aluno, sizeof(Aluno), stdin);
                Aluno[strcspn(Aluno, "\n")] = 0; // Remova o caractere de nova linha

                printf(" Curso: ");
                fgets(Curso, sizeof(Curso), stdin);
                Curso[strcspn(Curso, "\n")] = 0; // Remova o caractere de nova linha

                printf(" CPF do aluno: ");
                fgets(CPF, sizeof(CPF), stdin);
                CPF[strcspn(CPF, "\n")] = 0; // Remova o caractere de nova linha

                printf(" Nova matricula: ");
                fgets(Matricula, sizeof(Matricula), stdin);
                Matricula[strcspn(Matricula, "\n")] = 0; // Remova o caractere de nova linha

                printf(" \n\nQual o turno do aluno? Informe uma das opcoes abaixo:\n\n 1: MATUTINO\n 2: VESPERTINO\n 3: NOTURNO\n -");
                scanf("%d", &zchoice);

                switch (zchoice) {

                    case 1:
                        strcpy(Turno, "Matutino");
                        addCadastro(&CadastroList, Aluno, Curso, CPF, Matricula, Turno);

                        system("cls");
                        printf("Aluno adicionado com sucesso!\n AGUARDE...");
                        sleep(segundos);
                        system("cls");
                        sleep(segundos);
                        break;

                    case 2:

                        strcpy(Turno, "Vespertino");
                        addCadastro(&CadastroList, Aluno, Curso, CPF, Matricula, Turno);

                        system("cls");
                        printf("Aluno adicionado com sucesso!\n AGUARDE...");
                        sleep(segundos);
                        system("cls");
                        sleep(segundos);
                        break;

                    case 3:
                        strcpy(Turno, "Noturno");
                        addCadastro(&CadastroList, Aluno, Curso, CPF, Matricula, Turno);

                        system("cls");
                        printf("Aluno adicionado com sucesso!\n AGUARDE...");
                        sleep(segundos);
                        system("cls");
                        sleep(segundos);
                        break;

                }
                break;

            case 2:
                system("cls");
                printf("*ALUNOS MATRICULADOS* \n\n");
                exibirCadastros(CadastroList);
                printf("Digite 1 e enter para retornar ao menu\n");
                scanf("%d", &schoice);

                switch (schoice) {
                    case 1:
                        system("cls");
                        break;
                    default:
                        system("cls");
                        break;
                }
                break;

            case 3:
                system("cls");
                printf("*EXCLUIR ALUNO DA BASE DE DADOS*: \n\n");
                printf(" CPF do aluno a ser retirado da base: ");
                fgets(CPF, sizeof(CPF), stdin);
                CPF[strcspn(CPF, "\n")] = 0; // Remova o caractere de nova linha
                deleteCadastro(&CadastroList, CPF);
                system("cls");
                printf("Aguarde...");
                sleep(segundos);
                system("cls");
                printf("Aluno excluido com sucesso!\n\n\n Retornando ao menu...");
                sleep(segundos);
                system("cls");

                break;
            case 4:
                system("cls");
                printf("*ALTERAR CURSO/SERIE DO ALUNO*: \n\n");
                printf(" CPF do aluno que recebera a atualizacao: ");
                fgets(CPF, sizeof(CPF), stdin);
                CPF[strcspn(CPF, "\n")] = 0; // Remova o caractere de nova linha
                printf(" Novo curso/serie a ser matriculado: ");
                fgets(Curso, sizeof(Curso), stdin);
                Curso[strcspn(Curso, "\n")] = 0; // Remova o caractere de nova linha
                updateCadastro(CadastroList, CPF, Curso);
                system("cls");
                printf("Aguarde...");
                sleep(segundos);
                system("cls");
                printf("Dados do aluno atualizado com sucesso!\n");
                sleep(segundos);
                system("cls");
                break;
            case 5:
                system("cls");
                printf("Encerrando programa... ");
                sleep(segundos);
                system("cls");
                printf("Aguarde...");
                sleep(segundos);
                system("cls");
                // Liberar a mem�ria alocada antes de sair
                while (CadastroList) {
                    struct Cadastro* temp = CadastroList;
                    CadastroList = CadastroList->next;
                    free(temp);
                }
                exit(0);
            default:
                printf("Escolha inv�lida. Tente novamente.\n");
        }
    }

    return 0;
}

