#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 50
#define MAX_HISTORY 20
#define MAX_HISTORY_LENGTH 100

void printInitialMessage();
void newAccount();
int login();
int validateLogin(char cpf[20], char password[50]);
bool cpfIsRegistered(char cpf[20]);
void printMenu();
void printUserMenu(int id);
float deposit(float b, int id);
float withdraw(float b, int id);
void printHistory(int id);

typedef struct {
  char name[50];
  char password[50];
  char cpf[20];
  float balance;
  int historyLength;
  char history[MAX_HISTORY][MAX_HISTORY_LENGTH];
} User;

// ISNTANTIATES users ARRAY AND SETS A DEMO/TEST USER
User users[MAX_USERS] = {{"nome", "senha", "123", 0, 0.0f, 0}};
int totalUsers = 1;

int main() {
  printInitialMessage();

  char buffer[100];
  int activeUser = -1;

  // IF ACTIVE USER IS DIFFERENT THAN '-1', IT IS THE ID OF THE CURRENT ACTIVE
  // USER
  while (true) {
    if (activeUser < 0)
      printMenu();
    else
      printUserMenu(activeUser);

    // GETS INPUT FROM THE USER AS STRING (SAFER THAN scanf)
    fgets(buffer, sizeof(buffer), stdin);

    // CONVERTS INPUT TO SHORT
    short option = (short)strtol(buffer, NULL, 10);

    switch (option) {
    case 0:
      if (activeUser < 0) {
        printf("\nObrigado por escolher a TOP.\nSeção finalizada.\n");
        return 0;
      } else {
        printf("\nDesconectando...\nVoltando para o menu...\n\n");
        activeUser = -1;
      }
      break;
    case 1:
      if (activeUser < 0)
        newAccount();
      else
        users[activeUser].balance =
            deposit(users[activeUser].balance, activeUser);
      break;
    case 2:
      if (activeUser < 0)
        activeUser = login();
      else
        users[activeUser].balance =
            withdraw(users[activeUser].balance, activeUser);
      break;
    case 3:
      if (activeUser >= 0)
        printHistory(activeUser);
      else
        printf("Opção inválida.\n\n");
      break;
    default:
      printf("\nOpção inválida.\n\n");
      break;
    }
  }
}

void printHistory(int id) {
  printf("\n*********************\n");
  printf("Imprimindo extrato...\n");
  printf("*********************\n");

  if (users[id].historyLength == 0) {
    printf("\nSem transações\n\n");
    return;
  }

  for (int i = 0; i < users[id].historyLength; i++) {
    printf("%d. %s\n", i + 1, users[id].history[i]);
  }

  printf("\nSaldo atual: %.2f\n\n", users[id].balance);
}

float deposit(float b, int id) {
  char buffer[100];

  printf("\nIniciando depósito...\n");
  printf("Informe o valor a depositar: R$");
  fgets(buffer, sizeof(buffer), stdin);
  float valor = strtof(buffer, NULL);

  if (valor <= 0) {
    printf("Valor inválido.\n\n");
    return b;
  }

  float newBalance = valor + b;
  if (users[id].historyLength < MAX_HISTORY) {
    sprintf(users[id].history[users[id].historyLength++],
            "Depositou: R$%.2f - Saldo: R$%.2f", valor, newBalance);
  }
  printf("\nDepósito realizado com sucesso, seu novo saldo é R$%.2f\n\n",
         newBalance);
  return newBalance;
}

float withdraw(float b, int id) {
  char buffer[100];

  printf("\nIniciando saque...\n");
  printf("Informe o valor a sacar: R$");
  fgets(buffer, sizeof(buffer), stdin);
  float valor = strtof(buffer, NULL);

  if (valor <= 0) {
    printf("Valor inválido.\n\n");
    return b;
  }

  if (valor > b) {
    printf("\nErro ao realizar saque: saldo insuficiente.\n\n");
    return b;
  }

  float newBalance = b - valor;
  if (users[id].historyLength < MAX_HISTORY) {
    sprintf(users[id].history[users[id].historyLength++],
            "Sacou: R$%.2f - Saldo: R$%.2f", valor, newBalance);
  }
  printf("\nSaque realizado com sucesso. Seu novo saldo é R$%.2f\n\n",
         newBalance);
  return newBalance;
}

void newAccount() {
  if (totalUsers >= MAX_USERS) {
    printf("\nLimite máixmo de contas atingido. Não é possível criar uma nova "
           "conta.\n\n");
    return;
  }

  char name[50], cpf[20], password[50];

  printf("\nIniciando nova conta...\n");
  printf("Informe seu nome completo: ");
  fgets(name, sizeof(name), stdin);
  name[strcspn(name, "\n")] = '\0';

  printf("Informe seu cpf: ");
  fgets(cpf, sizeof(cpf), stdin);
  cpf[strcspn(cpf, "\n")] = '\0';

  if (cpfIsRegistered(cpf)) {
    printf("\nErro ao criar conta, este CPF já está cadastrado no sistema.\n");
    printf("Verifique se você digitou as informações corretamente e tente "
           "novamente.\n\n");
    printf("Se você tem certeza que as informações estão corretas, por "
           "favor, entre em contato com nosso suporte o quanto antes, "
           "através de um dos seguintes meios:\n");
    printf("Chat online: [link-do-chat]\nEmail: "
           "[endereço-de-email]\nTelefone: [numero-de-telefone]\n\n");

    printf("Retornando para o menu...\n\n");
    return;
  }

  printf("informe sua senha: ");
  fgets(password, sizeof(password), stdin);
  password[strcspn(password, "\n")] = '\0';

  int id = totalUsers;
  strncpy(users[id].name, name, sizeof(users[id].name) - 1);
  users[id].name[sizeof(users[id].name) - 1] = '\0';
  strncpy(users[id].cpf, cpf, sizeof(users[id].cpf) - 1);
  users[id].cpf[sizeof(users[id].cpf) - 1] = '\0';
  strncpy(users[id].password, password, sizeof(users[id].password) - 1);
  users[id].password[sizeof(users[id].password) - 1] = '\0';
  users[totalUsers].balance = 0.0f;
  users[id].historyLength = 0;

  totalUsers++;
  printf("\nConta criada com sucesso.\n\n");
}

int login() {
  char cpf[20], password[50];
  int id = -1;

  printf("\nIniciando login...\n");
  printf("Informe seu CPF: ");
  fgets(cpf, sizeof(cpf), stdin);
  cpf[strcspn(cpf, "\n")] = '\0';

  if (!cpfIsRegistered(cpf)) {
    printf("\nCadastro do CPF não encontrado no sistema.\n");
    printf("Retornando para o menu...\n\n");
    return -1;
  }

  printf("Informe sua senha: ");
  fgets(password, sizeof(password), stdin);
  password[strcspn(password, "\n")] = '\0';

  id = validateLogin(cpf, password);
  if (id < 0) {
    printf("\nFalha no login. Senha ou login incorretos.\nPor favor, tente "
           "novamente\n");
    printf("Retornando para o menu...\n\n");
    return -1;
  }

  printf("Login realizado com sucesso.\n\n");
  return id;
}

int validateLogin(char cpf[20], char password[50]) {
  for (int i = 0; i < totalUsers; i++) {
    if (strcmp(cpf, users[i].cpf) == 0 &&
        strcmp(password, users[i].password) == 0) {
      return i;
    }
  }
  return -1;
}

bool cpfIsRegistered(char cpf[20]) {
  for (int i = 0; i < totalUsers; i++)
    if (strcmp(cpf, users[i].cpf) == 0)
      return true;
  return false;
}

void printMenu() {
  printf("*************************\n");
  printf("Sistema bancário TOP\n");
  printf("*************************\n");
  printf("Que ação deseja realizar?\n");
  printf("1 - Criar conta\n2 - Login\n0 - Sair\n");
  printf("\nInforme o número de opção desejada: ");
}

void printUserMenu(int id) {

  printf("*************************\n");
  printf("Sistema bancário TOP\n");
  printf("*************************\n");
  printf("Bem vindo %s\n", users[id].name);
  printf("Saldo: %.2f\n", users[id].balance);
  printf("O que você deseja fazer?\n");
  printf("1 - Depósito\n2 - Saque\n3 - Extrato\n0 - Sair (Logout)\n");
  printf("\nInforme o número de opção desejada: ");
}

void printInitialMessage() {
  printf("Hey! Esse é um programa que simula um sistema bancário fictício.\n");
  printf("Feito por Leonardo Müller de Lima, 12/09/2025, para atividade "
         "prática da matéria de algoritmos e pensamento computacional.\n");
  printf(
      "Análise e Desenvolvimento de Sistemas, Universidade Cruzeiro do Sul.\n");
  printf("Iniciando sistema...\n\n");
  printf("Um usuário de testes já está criado: cpf: 123, senha: senha\n\n");
}
