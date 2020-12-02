# Trabalho Spotify parte 2

## Estrutura de direórios do trabalho
```
.
├── src
│   ├── main.c
│   ├── csv.c  
│   ├── knn.c
│   ├── parsing.c
│   ├── file.c
│   ├── spotify.c
│   └── utils.c
├── include
│   ├── csv.h  
│   ├── knn.h
│   ├── parsing.h
│   ├── file.h
│   ├── spotify.h
│   └── utils.h
├── obj
│   ⋮
├─ README.md
└─ Makefile
```

## Hierarquia de dependências
Ao topo, módulos mais especializados e que necessitam de mais dependências, na
base módulos que precisam de menos dependências e são mais generalizados.
```
main.c
╠══ spotify.c  <─────────────┐
║   ╚═ csv.c                 │
║      ╠═ file.c             │
║      ║  ╚═ [ parsing.c ] ─┐│
║      ╚═ parsing.c  <──────┘│
╚══ knn.c                    │
    ╠═ [ spotify.c ] ────────┘
    ╚═ utils.c
```
