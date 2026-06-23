# Documento de Elicitação de Requisitos

## 1. Identificação e técnicas

**PCDF: Missão Cibersegura** é um protótipo acadêmico, educativo e não oficial para adolescentes de 12 a 17 anos. A plataforma atual é Windows, com navegador/WebAssembly como alvo futuro. O objetivo é conscientizar sobre crimes e riscos cibernéticos por meio de uma missão interativa situada em uma Brasília cartunesca, com 20 alertas distribuídos em 15 categorias.

A elicitação combinou análise do legado, workshop de escopo, proto-personas, jornada do usuário, 5W2H, cenários, riscos, prototipação e revisão documental. Antes de qualquer piloto com adolescentes, a equipe deve complementar a elicitação com entrevistas ou testes mediados por professores/responsáveis e especialistas, sempre usando cenários hipotéticos — nunca exigindo relatos pessoais de vitimização.

## 2. 5W2H

| Dimensão | Definição |
|---|---|
| What | jogo 2D educativo com 20 alertas em 15 categorias e feedback preventivo contextual |
| Why | aumentar reconhecimento de golpes, reduzir ação impulsiva e ensinar preservação de evidências/apoio |
| Who | adolescentes; professores e responsáveis mediadores; especialistas validadores; banca avaliadora |
| Where | computador escolar/doméstico; modo offline no MVP e, futuramente, site estático |
| When | sessão de 10–20 min em aula, feira, banca ou atividade orientada |
| How | C99/raylib, mapa em 5 fases, scanner não violento, dicas contextuais, HUD educativa e síntese final |
| How much | baixo custo computacional; maior custo em revisão de conteúdo, UX, segurança, acessibilidade e testes |

## 3. Stakeholders

| Stakeholder | Interesse | Envolvimento |
|---|---|---|
| Adolescente | experiência clara, segura, respeitosa e divertida | teste de compreensão e usabilidade |
| Professor | material aplicável em sala e roteiro de mediação | coautoria do piloto e avaliação pedagógica |
| Responsável | proteção, privacidade e linguagem adequada | transparência, consentimento aplicável e orientação |
| Desenvolvimento | requisitos testáveis, código modular e manutenção | execução técnica e correções |
| Segurança | precisão conceitual e controles de risco | aprovação de conteúdo, threat model e revisão de dependências |
| Pedagogia/UX | adequação etária, linguagem e acessibilidade | validação de fluxos, textos e testes com público-alvo |
| Jurídico/DPO | LGPD, menores, marca e uso de dados | gate antes de piloto ou publicação ampliada |
| PCDF | referência temática regional | nenhuma afiliação presumida; autorização formal se houver parceria |
| Banca | evidência, viabilidade e coerência acadêmica | avaliação do produto, documentação e apresentação |

### 3.1. Valores dos stakeholders

| Stakeholder | Valores |
|---|---|
| Adolescente | Primário |
| Professor | Primário |
| Responsável | Secundário |
| Desenvolvimento | Interno |
| Segurança | Especialista |
| Pedagogia/UX | Especialista |
| Jurídico/DPO | Interno |
| PCDF | Especialista |
| Banca | Avaliadora |

## 4. Premissas

| ID | Premissa |
|---|---|
| PR-01 | O público-alvo possui conhecimentos básicos para utilizar teclado e mouse sem treinamento prévio. |
| PR-02 | O jogo será utilizado principalmente em contextos educacionais, atividades de conscientização ou apresentações supervisionadas. |
| PR-03 | Os usuários possuem compreensão de leitura básica e compreensão usual de figuras compatíveis com a faixa etária proposta. |
| PR-04 | O conteúdo educacional será revisado por profissionais com conhecimento da área aplicada antes da publicação. |
| PR-05 | O hardware da máquina será capaz de executar aplicações 2D desenvolvidas em raylib. |
| PR-06 | O computador em que o programa será executado estará em pleno funcionamento, sem interferência de vírus, problemas físicos ou problemas estruturais da máquina. |
| PR-07 | O MVP será utilizado sem necessidade de conexão com a internet. |

## 5. Restrições

| ID | Restrições |
|---|---|
| RT-01 | O protótipo foi desenvolvido utilizando a biblioteca raylib. |
| RT-02 | O MVP foi feito para funcionamento em Windows. |
| RT-03 | O MVP não deve coletar, armazenar ou transmitir dados pessoais da máquina. |
| RT-04 | O sistema não inclui interações entre usuários. |
| RT-05 | O sistema não inclui nenhuma transação comercial. |
| RT-06 | O sistema não executa alterações de administrador na máquina. |
| RT-07 | O programa deve rodar sem dependência de nenhum software externo em tempo de execução. |
| RT-08 | O programa necessita da correta instalação/compilação para seu funcionamento. |

## 6. Público e escopo

O público varia em leitura, experiência digital, hardware disponível e capacidade motora. O produto precisa de objetivo explícito, controles simples, ausência de culpa, exemplos cotidianos, tempo de leitura controlado, ajuda acionável, privacidade e visual cartunesco adequado à faixa etária.

**Incluído:** mapa cartunesco ampliado, 5 fases inspiradas no DF, movimento, física, plataformas, 20 ameaças, 15 categorias educativas, scanner, proteção, dicas, menus, save versionado, screenshot e documentação. **Excluído:** login, chat, ranking, anúncios, compras, denúncia real, integração policial, geolocalização, multiplayer e telemetria obrigatória.

## 7. Regras de negócio

- RN-01: somente ameaça ativa pode ser resolvida.
- RN-02: cada ocorrência incrementa progresso uma única vez.
- RN-03: ao resolver uma ocorrência, o mundo pausa até a leitura da orientação ser registrada.
- RN-04: vitória somente após 20 alertas e última orientação.
- RN-05: proteção zero leva à falha, sem linguagem de morte ou punição.
- RN-06: scanner é a única ferramenta de contenção; o jogo não usa armas.
- RN-07: save incompatível ou inválido falha com segurança.
- RN-08: aviso de projeto não oficial permanece nos materiais.
- RN-09: o jogo deve comunicar fase/progresso sem depender apenas de cor.

## 8. Requisitos funcionais

| ID | Requisito | Pri. | Aceite |
|---|---|---:|---|
| RF-01 | menu iniciar/instruções/continuar/sair | Must | teclado e mouse funcionam |
| RF-02 | movimento, salto e colisão | Must | não atravessa tiles sólidos |
| RF-03 | 20 ocorrências em 15 categorias | Must | tipos, contagem e dicas conferem |
| RF-04 | scanner direcional | Must | resolve apenas área atingida |
| RF-05 | orientação específica por categoria | Must | título e três ações corretos |
| RF-06 | integridade, dano e recarga | Must | limites 0–100 |
| RF-07 | HUD com progresso, fase e status | Must | reflete estado atual e não corta texto |
| RF-08 | save local versionado | Must | V2 válido restaura; inválido rejeita |
| RF-09 | pausa e retorno | Must | mundo não atualiza na pausa/dica |
| RF-10 | falha e reinício | Must | reinicia sem resíduos |
| RF-11 | vitória e protocolo final | Must | após leitura do 20º alerta |
| RF-12 | screenshot F12 e modo captura | Should | PNG no caminho documentado |
| RF-13 | quiz de quinze itens | Should | backlog P1, sem identidade do usuário |
| RF-14 | remapear controles | Should | backlog P1 |
| RF-15 | fases com setores do DF | Must | mapa comunica Base, Escola, Esplanada, Lago e Operação Final |

## 9. Requisitos não funcionais

| ID | Requisito | Meta verificável |
|---|---|---|
| RNF-01 | desempenho | 60 FPS alvo em 1280×720 no hardware de referência |
| RNF-02 | inicialização | utilizável em até 3 s no hardware de referência |
| RNF-03 | portabilidade | C99/raylib, Windows validado e plano WebAssembly |
| RNF-04 | manutenibilidade | `main` sem regra; módulos com responsabilidade única |
| RNF-05 | segurança | nenhum segredo/dado pessoal; build sem novos avisos relevantes |
| RNF-06 | privacidade | zero telemetria no MVP |
| RNF-07 | acessibilidade | teclado e leitura controlada; WCAG 2.2 AA na web |
| RNF-08 | confiabilidade | save inválido não causa crash/estado impossível |
| RNF-09 | usabilidade | meta: ≥80% concluem teste sem ajuda |
| RNF-10 | auditabilidade | mudança vinculada a issue/commit |
| RNF-11 | consistência visual | HUD, menu e dicas mantêm alinhamento em 1280×720 |

Requisitos complementares: releases com hash; dependências documentadas; MFA e branch protection; CSP/headers na web; avaliação de privacidade antes de qualquer dado; cor nunca como único sinal; foco visível; linguagem não culpabilizante; alto contraste e redução de movimento no roadmap.

## 10. Ameaças educativas cobertas

| Categoria | Aprendizado esperado |
|---|---|
| Phishing | desconfiar de urgência, links e remetentes falsos |
| Malware | evitar anexos/programas desconhecidos e manter sistema atualizado |
| Perfil falso | confirmar identidade antes de enviar dinheiro ou informações |
| Ransomware | manter backup e preservar evidências |
| Golpe de pagamento/QR | conferir destinatário e contexto antes de pagar |
| Violência digital | bloquear, denunciar e buscar apoio sem revide |
| Invasão de conta | usar senhas fortes e verificação em duas etapas |
| Vazamento de dados | minimizar exposição e monitorar acessos suspeitos |
| Engenharia social | reconhecer manipulação por medo, pressa ou confiança |
| Wi-Fi falso | evitar contas sensíveis em redes desconhecidas |
| Loja falsa | verificar reputação, CNPJ, URL e meios de pagamento |
| Deepfake/IA fraudulenta | confirmar pedidos por canal confiável |
| Doxxing | não divulgar dados de terceiros e preservar provas |
| Suporte técnico falso | não instalar acesso remoto por pressão |
| Aliciamento online | reconhecer segredo/pressão e pedir ajuda a adulto confiável |

## 11. Custo computacional

### Cliente

- CPU: loop 2D, até 20 ameaças e tilemap 210×22;
- GPU: primitivas geométricas, sem texturas externas pesadas;
- memória: estruturas fixas; expectativa de dezenas de MB incluindo runtime/driver;
- armazenamento: executável de poucos MB, screenshot PNG e save textual abaixo de 20 KB;
- rede: zero no modo offline.

Estimativas devem ser validadas por profiling em hardware escolar. O maior custo é humano: revisão de conteúdo, segurança, UX, acessibilidade e pesquisa. Hosting estático tende a baixo custo, mas deve ser cotado na calculadora oficial do provedor.

## 12. Rastreabilidade

| Objetivo | Requisitos | Evidência |
|---|---|---|
| reconhecer riscos | RF-03, RF-05, RF-13 | walkthrough e pré/pós-teste |
| concluir missão | RF-01, RF-02, RF-04, RF-11 | teste ponta a ponta e screenshot |
| explorar DF cartunesco | RF-15, RNF-11 | captura 1280×720 e inspeção visual |
| proteger privacidade | RNF-05, RNF-06 | inspeção de rede/código |
| manter/evoluir | RNF-04, RNF-10 | arquitetura, issues e PRs |
| incluir | RNF-07 e requisitos UX | auditoria e teste com usuários |

## 13. Aceite para a banca

Compilar sem novos erros; iniciar estável; demonstrar ocorrência, orientação, progresso, fase e save; apresentar screenshot e roteiro de vitória; manter documentos coerentes; não incluir save, segredo ou dado pessoal no commit; declarar IA e caráter não oficial.

## 14. Questões em aberto

- Quem validará institucionalmente o conteúdo?
- Qual hardware e navegadores representam o cliente?
- Haverá autorização para usar o nome PCDF externamente?
- Qual protocolo será seguido diante de relato real?
- O piloto precisa de comitê de ética, consentimento e RIPD?

São gates de decisão e não devem ser preenchidos por suposição técnica.
