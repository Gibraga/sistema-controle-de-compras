# sistema-controle-de-compras
Sistema de controle de compras de uma quitanda em C, com cadastro, busca por cliente e relatório geral.

# Quitanda – Trabalho Final

Programa em linguagem C para registrar e consultar as compras de uma quitanda, com os dados salvos em arquivo de texto.

Trabalho final da disciplina [nome da disciplina] – [curso], [instituição], [ano].

## Funcionalidades

- **Cadastrar compras:** registra nome do cliente, sexo (m, f ou n), idade, número de itens, franquia (A, B ou C) e valor total. As entradas são validadas e cada compra é gravada no arquivo `quitanda.txt`.
- **Pesquisar compra por cliente:** busca pelo nome (sem diferenciar maiúsculas de minúsculas), mostra valor, itens e franquia de cada compra e calcula a média dos valores.
- **Relatório geral:**
  - compras entre R$ 50 e R$ 100
  - compras com exatamente 3 itens
  - compras das franquias A ou B
  - compradores do sexo masculino
  - valor total comprado por menores de 18 anos
  - valor total e valor médio das compras
  - cliente com o maior nome
  - cliente mais novo

## Como executar

Compile e execute no terminal:

```bash
gcc quitanda.c -o quitanda
./quitanda
```

Ou rode online, sem instalar nada: [OnlineGDB](https://www.onlinegdb.com/hap9Y45Ck)

## Formato do arquivo de dados

O programa lê e grava o arquivo `quitanda.txt` na mesma pasta, uma compra por linha:

```
nome,sexo,idade,numero_itens,franquia,valor_total
```

Exemplo: `Maria Silva,f,25,3,A,72.50`

Se o arquivo não existir, ele é criado ao cadastrar a primeira compra.

## Conceitos utilizados

- Structs (`Cliente` e `Compra`)
- Alocação dinâmica de memória (`malloc` e `realloc`)
- Leitura e escrita em arquivos de texto
- Funções e menu interativo
- Validação de entrada

## Autor

[Giovanna Braga] – [https://github.com/Gibraga]
