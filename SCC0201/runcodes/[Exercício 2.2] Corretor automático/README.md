# Trabalho do Corretor Automático

## Resumo
Essa implementação utiliza de um parser de json completo para recuperar as
informações contidas na resposta da API do Twitter. Além disso, para armazenar
as palavras únicas um Hashset é utilizado.

## Componentes centrais

## Lendo o JSON
Para ler JSON dois módulos trabalham em conjunto. O mais importante deles é o
`json_model`. O `json_model` é capaz de extrair de uma entrada JSON apenas as
informações necessárias, sem precisar alocar espaço adicional para nenhuma outra
informação. Esses dados extraídos do JSON são colocados numa estrutura
predefinida (um `struct`). Dessa forma é possível criar tipos de dados em C que
espelham a estrutra do JSON a ser lido. Para isso, o módulo `generic` permite
descrever esses structs customizados em tempo de execução, tornando a operação
possível.

## Armazenando palavras únicas
Todas as palavras são armazenadas utilizando o módulo `hashset` que implementa
uma estrutura de Hashset com chaining.

## Detalhes da implementação

### Representando estrutura JSON em C
Uma estrutura JSON pode conter alguns tipos de valor e para cada um deles existe
um análogo na linguagem C. Alguns exemplos:

#### **Objeto**
JSON
```json
{
    "chave1": "Hello",
    "chave2": 7
}
```
C
```c
// Nome do campo é a chave e o tipo deve representar o tipo no JSON
struct <nome> {
    char *chave1;
    double chave2;
};
```

#### **Array**
JSON
```json
[ 1, 2, 3, 4, 5, 6 ]
```

C
```c
struct <nome> {
    double *vec; // Precisa ser ponteiro e estar na primeira posição.
    int size;    // Precisa ser int e estar na segunda posição.
};
```

#### **Outros tipos**
Todos os números em JSON serão representados por `double` em C. O valor `null`
será representado por um ponteiro com qualquer tipo interno. O valor `undefined`,
quando presente no JSON, não deve estar representado em C. Caso esteja, o valor
não será atribuído. Ou seja, não há representação em C para `undefined`. Além
disso valores de tipo booleano são representados com `bool` da `<stdbool.h>` em C.

### Genéricos
O módulo `generic` é responsável por definir uma forma de descrever tipos em C
em tempo de execução. Isto é, mesmo após a compilação, essas estruturas 
representam tipos de dados como `struct`, `array` e outros dos tipos primitivos
de C. Dessa forma é possível saber em tempo de execução metadados sobre alguma
estrutura qualquer. Portanto não é necessário utilizar de tipos estáticos em
certas funções, dado que um `generic_t` seja providenciado explicando o tipo de
dados. Nesse sentido, uma função do tipo `func(void *data, generic_t *generic)`
pode performar operações diferentes em `data` de acordo com as informações
contidas em `generic`.

Genéricos podem representar uma série de tipos.
- structs: `generic_struct_t`
- arrays (estáticos): `generic_array_t`
- ponteiros: `generic_pointer_t`
- booleanos: `generic_bool_t`
- char: `generic_char_t`
- float: `generic_float_t`
- double: `generic_double_t`
- int: `generic_int_t`

Além disso, novos genéricos podem ser construídos utilizando as bases como por
exemplo `generic_string_t` que é simplesmente um `generic_pointer_t` com tipo
interno `generic_char_t`.

### Representando tipos com genéricos
Para representar um tipo com um `generic_t` é necessário utilizar os construtores
disponibilizados pelo módulo. Alguns exemplos:
```c
struct comida {
    char *nome;
    double preco;
};
struct pessoa {
    char *nome;
    int idade;
    double carteira;
    struct comida *favorita;
};
// Representado por:
generic_t *carteira = GEN_DOUBLE;
generic_t *idade = GEN_INT;
generic_t *nome = GEN_STRING;

// Uma declaração mais direta
generic_t *comida = GEN_STRUCT(2,   // <-- o número de campos do struct.
    GEN_SFIELD("nome", GEN_STRING), // <-- primeiro campo.
    GEN_SFIELD("preco", GEN_DOUBLE) // <-- segundo campo.
);

generic_t *pessoa = GEN_STRUCT(4,
    GEN_SFIELD("nome", nome),
    GEN_SFIELD("idade", idade),
    GEN_SFIELD("carteira", carteira),
    GEN_SFIELD("comida", comida)
);
```

Para mais informações, leia `src/generic.h`.

#### Limitações de genéricos
Atualmente não é possível descrever estruturas recursivas como um struct que
possui um ponteiro para si mesmo, de maneira natural. Além disso, todos os
structs utilizados devem ser precedidos de um `#pragma pack(1)` para remover
padding dentro dos structs.

## Testes unitários
Para melhor compreender o comportamento de cada parte, os arquivos dentro do
diretório `tests/` podem ser usados de referência. Neles há diversos testes para
averiguar o funcionamento da maioria das funções públicas dos módulos mais
relevantes.

Para rodar a bateria de testes, basta executar
```
make test
```
