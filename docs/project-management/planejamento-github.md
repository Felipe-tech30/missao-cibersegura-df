# Planejamento de Project Management no GitHub

## 1. Modelo operacional

O GitHub será a fonte única de verdade para código, documentação, decisões e trabalho planejado. O modelo recomendado é **Kanban com marcos de release**, adequado ao tamanho atual da equipe e à necessidade de demonstrar rastreabilidade à banca.

### Repositório

- Nome: `missao-cibersegura-df`
- Branch padrão: `main`, sempre demonstrável e compilável.
- Branches de trabalho: `feat/<tema>`, `fix/<tema>`, `docs/<tema>`, `security/<tema>`.
- Integração: pull request com issue vinculada; squash merge recomendado.
- Releases: tags semânticas (`v0.2.0`, `v0.3.0`) com notas e hash do binário quando houver distribuição.

## 2. GitHub Project

Criar o projeto **Missão Cibersegura DF — Roadmap** com as seguintes colunas/status:

```text
Backlog → Pronto → Em andamento → Em revisão → Validação → Concluído
```

Campos recomendados:

| Campo | Valores |
|---|---|
| Prioridade | P0 crítica, P1 alta, P2 média, P3 baixa |
| Área | Produto, Conteúdo, Jogo, UX, Segurança, Cloud, Docs |
| Esforço | 1, 2, 3, 5, 8 pontos |
| Marco | Banca, Validação, MVP Web, Piloto |
| Responsável | usuário GitHub da pessoa proprietária |
| Risco | Baixo, Médio, Alto |

Limite de trabalho em andamento: no máximo duas issues em “Em andamento” por pessoa.

## 3. Labels

| Label | Uso |
|---|---|
| `type:feature` | nova capacidade |
| `type:bug` | comportamento incorreto |
| `type:docs` | documentação ou apresentação |
| `type:research` | descoberta, validação ou experimento |
| `area:content` | conteúdo educativo |
| `area:gameplay` | mecânica e balanceamento |
| `area:ux` | interface, acessibilidade e pesquisa |
| `area:security` | segurança, privacidade e supply chain |
| `area:cloud` | build web, hosting e operação |
| `priority:P0` a `priority:P3` | ordem de decisão |
| `status:blocked` | dependência externa explícita |
| `good-first-issue` | contribuição de baixo risco |

## 4. Marcos

### M1 — Banca acadêmica (`v0.3.0`)

Objetivo: apresentação reproduzível, documentação coerente e demonstração funcional. Saída: deck, roteiro, screenshot, build Windows e repositório público organizado.

### M2 — Validação formativa (`v0.4.0`)

Objetivo: revisar conteúdo e testar compreensão/usabilidade com amostra pequena. Saída: protocolo, consentimentos aplicáveis, achados e backlog revisado.

### M3 — MVP Web (`v0.5.0`)

Objetivo: executar em navegador sem backend e publicar em ambiente estático. Saída: build WebAssembly, CI/CD, headers de segurança e teste cross-browser.

### M4 — Piloto educacional (`v0.6.0`)

Objetivo: aplicação mediada em contexto educacional aprovado. Saída: guia do facilitador, avaliação de aprendizagem e relatório agregado.

## 5. Backlog inicial rastreável

| ID | Issue proposta | Prioridade | Área | Aceite resumido |
|---|---|---:|---|---|
| MC-01 | Validar as sete categorias com especialista | P0 | Conteúdo | texto aprovado ou corrigido, com data e responsável |
| MC-02 | Executar checklist completo da demonstração | P0 | Produto | build, save, screenshot e apresentação testados |
| MC-03 | Implementar quiz final de sete itens | P1 | Jogo | uma questão por categoria, feedback e resultado local |
| MC-04 | Adicionar remapeamento e alternativas de controle | P1 | UX | ações principais configuráveis e persistidas localmente |
| MC-05 | Criar modo alto contraste e redução de movimento | P1 | UX | opções aplicadas sem perda de informação |
| MC-06 | Extrair regras para testes automatizados | P1 | Jogo | testes de progresso, dano, save e vitória sem janela |
| MC-07 | Revisar parser e integridade do arquivo de save | P1 | Segurança | entradas inválidas falham com segurança e sem travamento |
| MC-08 | Adaptar loop para WebAssembly | P1 | Cloud | jogo inicia e completa nos navegadores-alvo |
| MC-09 | Configurar CI de build e análise estática | P1 | Segurança | PR bloqueada quando build ou análise falhar |
| MC-10 | Conduzir cinco testes moderados de usabilidade | P1 | Pesquisa | protocolo, observações anonimizadas e recomendações |
| MC-11 | Produzir guia do professor/facilitador | P2 | Docs | sessão de 30–45 min, perguntas e cuidados definidos |
| MC-12 | Avaliar privacidade do piloto | P0 antes do piloto | Segurança | inventário de dados, base legal e retenção aprovados |

## 6. Cadência e cerimônias

- **Refinamento semanal (30 min):** esclarecer problema, risco e critério de aceite.
- **Planejamento quinzenal (45 min):** selecionar capacidade de acordo com WIP e marco.
- **Check-in assíncrono:** comentário curto na issue com feito, próximo e bloqueio.
- **Review por marco (45 min):** demonstrar incremento e coletar aceite.
- **Retrospectiva (30 min):** registrar uma melhoria concreta do processo.

## 7. Definition of Ready

Uma issue está pronta quando possui problema, resultado esperado, critérios de aceite testáveis, prioridade, área, responsável, dependências e avaliação inicial de segurança/privacidade quando aplicável.

## 8. Definition of Done

- critérios de aceite demonstrados;
- compilação sem novos avisos;
- teste proporcional ao risco;
- documentação, screenshot e apresentação atualizados quando afetados;
- nenhuma credencial, save ou dado pessoal no diff;
- revisão de pelo menos uma pessoa para release;
- issue vinculada ao PR e encerrada somente após validação.

## 9. Gestão de mudanças e decisões

Mudanças de escopo são issues `type:feature`. Decisões arquiteturais significativas entram na seção de ADRs do documento de arquitetura. Riscos novos entram no plano de segurança ou produto. Não se altera uma orientação educativa apenas para “caber” na UI: primeiro revisa-se o conteúdo, depois o componente.

## 10. Indicadores de fluxo

- lead time por issue;
- cycle time entre “Em andamento” e “Concluído”;
- idade de itens bloqueados;
- proporção planejado/concluído por marco;
- defeitos reabertos;
- cobertura de requisitos por evidências de teste.

Esses indicadores avaliam o processo; não devem ser usados para comparar ou punir indivíduos.
