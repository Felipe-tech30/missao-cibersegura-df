# Documento de Elicitação de Requisitos

## 1. Identificação e técnicas

**PCDF: Missão Cibersegura** é um protótipo acadêmico, educativo e não oficial para adolescentes de 12 a 17 anos. A plataforma atual é Windows; navegador é alvo futuro. O objetivo é conscientizar sobre crimes e riscos cibernéticos por uma missão interativa situada no DF.

A elicitação combinou análise do legado, workshop de escopo, proto-personas, jornada, 5W2H, cenários, riscos e prototipação. Antes do piloto, complementar com entrevistas a adolescentes, professores, responsáveis e especialistas, sempre com cenários hipotéticos — nunca exigindo relatos de vitimização.

## 2. 5W2H

| Dimensão | Definição |
|---|---|
| What | jogo 2D com 12 alertas em 7 categorias e feedback preventivo |
| Why | aumentar reconhecimento, reduzir impulso e ensinar preservação/apoio |
| Who | adolescentes; professores/responsáveis mediadores; especialistas validadores |
| Where | computador escolar/doméstico; offline e, futuramente, site estático |
| When | sessão de 8–15 min em aula, feira, banca ou atividade orientada |
| How | C99/raylib, scanner não violento, dicas contextuais e síntese final |
| How much | baixo custo computacional; maior custo em revisão, teste e acessibilidade |

## 3. Stakeholders

| Stakeholder | Interesse | Envolvimento |
|---|---|---|
| Adolescente | experiência clara, segura e respeitosa | teste de compreensão |
| Professor | material aplicável e roteiro | coautoria do piloto |
| Responsável | proteção e privacidade | transparência e consentimento aplicável |
| Desenvolvimento | requisitos testáveis | execução e manutenção |
| Segurança | precisão e controles | aprovação de conteúdo/threat model |
| Pedagogia/UX | adequação etária | linguagem, pesquisa e acessibilidade |
| Jurídico/DPO | LGPD, menores e marca | gate antes de piloto |
| PCDF | referência temática | nenhuma afiliação presumida; autorização se houver parceria |
| Banca | evidência e viabilidade | avaliação acadêmica |

## 4. Público e escopo

O público varia em leitura, experiência, hardware e capacidade motora. Precisa de objetivo explícito, controles simples, ausência de culpa, exemplos cotidianos, tempo de leitura controlado, ajuda acionável e privacidade.

**Incluído:** mapa cartunesco, movimento, física, 12 ameaças, scanner, proteção, dicas, menus, save e screenshot. **Excluído:** login, chat, ranking, anúncios, compras, denúncia real, integração policial, geolocalização, multiplayer e telemetria obrigatória.

## 5. Regras de negócio

- RN-01: somente ameaça ativa pode ser resolvida.
- RN-02: cada ocorrência incrementa progresso uma vez.
- RN-03: ao resolver, o mundo pausa até a leitura ser registrada.
- RN-04: vitória somente após 12 alertas e última orientação.
- RN-05: proteção zero leva à falha, sem linguagem de morte.
- RN-06: scanner é a única ferramenta de contenção.
- RN-07: save incompatível ou inválido falha com segurança.
- RN-08: aviso de projeto não oficial permanece em todos os materiais.

## 6. Requisitos funcionais

| ID | Requisito | Pri. | Aceite |
|---|---|---:|---|
| RF-01 | menu iniciar/instruções/continuar/sair | Must | teclado e mouse funcionam |
| RF-02 | movimento, salto e colisão | Must | não atravessa tiles sólidos |
| RF-03 | 12 ocorrências em 7 categorias | Must | tipos e contagem conferem |
| RF-04 | scanner direcional | Must | resolve apenas área atingida |
| RF-05 | orientação específica por categoria | Must | título e três ações corretos |
| RF-06 | integridade, dano e recarga | Must | limites 0–100 |
| RF-07 | HUD e progresso | Must | refletem estado atual |
| RF-08 | save local versionado | Must | válido restaura; inválido rejeita |
| RF-09 | pausa e retorno | Must | mundo não atualiza na pausa/dica |
| RF-10 | falha e reinício | Must | reinicia sem resíduos |
| RF-11 | vitória e protocolo final | Must | após leitura do 12º alerta |
| RF-12 | screenshot F12 | Should | PNG no caminho documentado |
| RF-13 | quiz de sete itens | Should | backlog P1, sem identidade |
| RF-14 | remapear controles | Should | backlog P1 |

## 7. Requisitos não funcionais

| ID | Requisito | Meta verificável |
|---|---|---|
| RNF-01 | desempenho | 60 FPS alvo em 1280×720 no hardware de referência |
| RNF-02 | inicialização | utilizável em até 3 s no hardware de referência |
| RNF-03 | portabilidade | C99/raylib, Windows validado e plano WebAssembly |
| RNF-04 | manutenibilidade | `main` sem regra; módulos com responsabilidade única |
| RNF-05 | segurança | nenhum segredo/dado pessoal; build com avisos |
| RNF-06 | privacidade | zero telemetria no MVP |
| RNF-07 | acessibilidade | teclado e leitura controlada; WCAG 2.2 AA na web |
| RNF-08 | confiabilidade | save inválido não causa crash/estado impossível |
| RNF-09 | usabilidade | meta: ≥80% concluem teste sem ajuda |
| RNF-10 | auditabilidade | mudança vinculada a issue/commit |

Requisitos complementares: releases com hash; dependências documentadas; MFA e branch protection; CSP/headers na web; avaliação de privacidade antes de dados; cor nunca como único sinal; foco visível; linguagem não culpabilizante; alto contraste e redução de movimento no roadmap.

## 8. Custo computacional

### Cliente

- CPU: loop 2D, até 12 ameaças e tilemap 120×22;
- GPU: primitivas geométricas, sem texturas externas pesadas;
- memória: estruturas fixas; expectativa de dezenas de MB incluindo runtime/driver;
- armazenamento: executável de poucos MB e save textual abaixo de 10 KB;
- rede: zero no modo offline.

Estimativas devem ser validadas por profiling em hardware escolar. O maior custo é humano: revisão de conteúdo, segurança, UX, acessibilidade e pesquisa. Hosting estático tende a baixo custo, mas deve ser cotado na calculadora oficial do provedor.

## 9. Rastreabilidade

| Objetivo | Requisitos | Evidência |
|---|---|---|
| reconhecer riscos | RF-03, RF-05, RF-13 | walkthrough e pré/pós-teste |
| concluir missão | RF-01, RF-02, RF-04, RF-11 | teste ponta a ponta e screenshot |
| proteger privacidade | RNF-05, RNF-06 | inspeção de rede/código |
| manter/evoluir | RNF-04, RNF-10 | arquitetura, issues e PRs |
| incluir | RNF-07 e requisitos UX | auditoria e teste com usuários |

## 10. Aceite para a banca

Compilar sem novos avisos; iniciar estável; demonstrar ocorrência, orientação, progresso e save; apresentar screenshot e roteiro de vitória; manter documentos coerentes; não incluir binário, save ou segredo no commit; declarar IA e caráter não oficial.

## 11. Questões em aberto

- Quem validará institucionalmente o conteúdo?
- Qual hardware e navegadores representam o cliente?
- Haverá autorização para usar o nome PCDF externamente?
- Qual protocolo será seguido diante de relato real?
- O piloto precisa de comitê de ética, consentimento e RIPD?

São gates de decisão e não devem ser preenchidos por suposição técnica.
