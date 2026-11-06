#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NOME_MAX 40

typedef struct {
char nome[NOME_MAX + 1];
char sexo; // m, f ou n
int idade;
} Cliente;

typedef struct {
Cliente cliente;
int numero_itens;
char franquia; // A, B ou C
float valor_total;
} Compra;

void limpar_buffer(void);
void carregar_compras(Compra **c, int *qtd, int *cap);
void salvar_compras_append(Compra *c, int inicio, int fim);
void menu_principal(Compra **c, int *qtd, int *cap);
void cadastrar_compras(Compra **c, int *qtd, int *cap);
void pesquisar_por_cliente(Compra *c, int qtd);
void relatorio_geral(Compra *c, int qtd);

int main() {
    
Compra *compras = NULL;
int qtd = 0, cap = 0;
carregar_compras(&compras, &qtd, &cap);
menu_principal(&compras, &qtd, &cap);
free(compras);

return 0;
}

void limpar_buffer(void) {
int c;
while ((c = getchar()) != '\n' && c != EOF);
}

void carregar_compras(Compra **c, int *qtd, int *cap) {
FILE *f = fopen("quitanda.txt", "r");
*cap = 10;
*qtd = 0;
*c = malloc(*cap * sizeof(Compra));
if (!f) return;
while (!feof(f)) {
    
Compra x;
if (fscanf(f, "%40[^,],%c,%d,%d,%c,%f\n",
x.cliente.nome,
&x.cliente.sexo,
&x.cliente.idade,
&x.numero_itens,
&x.franquia,

&x.valor_total) == 6) {
if (*qtd >= *cap) {
*cap *= 2;
*c = realloc(*c, *cap * sizeof(Compra));
}
(*c)[(*qtd)++] = x;
}

}
fclose(f);
}

void salvar_compras_append(Compra *c, int inicio, int fim) {
FILE *f = fopen("quitanda.txt", "a");
for (int i = inicio; i < fim; i++) {
fprintf(f, "%s,%c,%d,%d,%c,%.2f\n",
c[i].cliente.nome,
c[i].cliente.sexo,
c[i].cliente.idade,
c[i].numero_itens,
c[i].franquia,
c[i].valor_total);
}
fclose(f);
}

void menu_principal(Compra **c, int *qtd, int *cap) {
int op;

do {
printf("\n=== QUITANDA ===\n");
printf("1 - Cadastrar compras\n");
printf("2 - Pesquisar compra por cliente\n");
printf("3 - Ver informacoes de todas as compras\n");
printf("4 - Encerrar o programa\n");
printf("Opcao: ");
scanf("%d", &op);

limpar_buffer();

switch (op) {
case 1: cadastrar_compras(c, qtd, cap); break;
case 2: pesquisar_por_cliente(*c, *qtd); break;
case 3: relatorio_geral(*c, *qtd); break;
}
} while (op != 4);
}
void cadastrar_compras(Compra **c, int *qtd, int *cap) {
int continuar = 1;
while (continuar) {
Compra x;

do {
printf("Nome do cliente (min 4 letras): ");
fgets(x.cliente.nome, NOME_MAX, stdin);
x.cliente.nome[strcspn(x.cliente.nome, "\n")] = '\0';
} while (strlen(x.cliente.nome) < 4);

do {
printf("Sexo (m/f/n): ");
scanf(" %c", &x.cliente.sexo);
x.cliente.sexo = tolower(x.cliente.sexo);
} while (x.cliente.sexo != 'm' && x.cliente.sexo != 'f' && x.cliente.sexo != 'n');
do {
    
printf("Idade (>0): ");
scanf("%d", &x.cliente.idade);
} while (x.cliente.idade <= 0);
do {
    
printf("Numero de itens (>0): ");
scanf("%d", &x.numero_itens);
} while (x.numero_itens <= 0);
do {
    
printf("Franquia (A/B/C): ");
scanf(" %c", &x.franquia);
x.franquia = toupper(x.franquia);

} while (x.franquia != 'A' && x.franquia != 'B' && x.franquia != 'C');
do {
    
printf("Valor total da compra (>=0): ");
scanf("%f", &x.valor_total);
} while (x.valor_total < 0);
limpar_buffer();
if (*qtd >= *cap) {
*cap *= 2;
*c = realloc(*c, *cap * sizeof(Compra));
}
(*c)[(*qtd)++] = x;
salvar_compras_append(*c, *qtd - 1, *qtd);
printf("Compra cadastrada com sucesso!\n");
printf("Deseja cadastrar outra compra? (1-Sim / 0-Nao): ");
scanf("%d", &continuar);
limpar_buffer();

}
}

void pesquisar_por_cliente(Compra *c, int qtd) {
char nome[NOME_MAX + 1];
printf("Nome do cliente: ");
fgets(nome, NOME_MAX, stdin);
nome[strcspn(nome, "\n")] = '\0';

float soma = 0;
int cont = 0;

for (int i = 0; i < qtd; i++) {
if (strcasecmp(c[i].cliente.nome, nome) == 0) {
printf("Valor: %.2f | Itens: %d | Franquia: %c\n",
c[i].valor_total, c[i].numero_itens, c[i].franquia);
soma += c[i].valor_total;
cont++;
}
}

if (cont > 0)
printf("Media das compras: %.2f\n", soma / cont);
else

printf("Nenhuma compra encontrada.\n");
}

void relatorio_geral(Compra *c, int qtd) {
int entre50e100 = 0, tres_itens = 0, franquiaAB = 0, masc = 0;
float total = 0, menores18 = 0;
int maior_nome = 0;
int menor_idade = 0;

for (int i = 0; i < qtd; i++) {
if (c[i].valor_total >= 50 && c[i].valor_total <= 100) entre50e100++;
if (c[i].numero_itens == 3) tres_itens++;
if (c[i].franquia == 'A' || c[i].franquia == 'B') franquiaAB++;
if (c[i].cliente.sexo == 'm') masc++;
if (c[i].cliente.idade < 18) menores18 += c[i].valor_total;
total += c[i].valor_total;
if (i == 0 || strlen(c[i].cliente.nome) > strlen(c[maior_nome].cliente.nome))
maior_nome = i;
if (i == 0 || c[i].cliente.idade < c[menor_idade].cliente.idade)
menor_idade = i;
}

printf("\n--- RELATORIO GERAL ---\n");
printf("Compras entre 50 e 100 reais: %d\n", entre50e100);
printf("Compras com exatamente 3 itens: %d\n", tres_itens);
printf("Compras da franquia A ou B: %d\n", franquiaAB);
printf("Compradores do sexo masculino: %d\n", masc);
printf("Valor total comprado por menores de 18 anos: %.2f\n", menores18);
printf("Valor total das compras: %.2f\n", total);

printf("Valor medio das compras: %.2f\n", total / qtd);
printf("\nCliente com maior nome:\n");
printf("Nome: %s | Valor: %.2f\n",
c[maior_nome].cliente.nome,
c[maior_nome].valor_total);
printf("\nCliente mais novo:\n");
printf("Nome: %s | Idade: %d | Valor: %.2f\n",
c[menor_idade].cliente.nome,
c[menor_idade].cliente.idade,
c[menor_idade].valor_total);
}
