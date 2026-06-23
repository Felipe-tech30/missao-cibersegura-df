# Planejamento de produto

## 1. Resumo executivo

**PCDF: Missão Cibersegura** é um jogo educativo 2D para adolescentes de 12 a 17 anos. Em uma Brasília cartunesca, o jogador investiga incidentes simulados e recebe orientações acionáveis sobre segurança digital. O produto transforma recomendações abstratas em decisões, repetição e feedback imediato.

O protótipo é acadêmico, não oficial e funciona localmente. A hipótese central é que uma experiência curta, contextualizada e sem linguagem punitiva melhora o reconhecimento de riscos quando comparada à exposição passiva ao mesmo conteúdo.

## 2. Visão e posicionamento

**Visão:** adolescentes capazes de identificar sinais de fraude e violência digital, interromper ações impulsivas e buscar ajuda com evidências preservadas.

**Proposta de valor:** aprender segurança digital por meio de uma missão curta, visual e situada no DF, sem transformar o adolescente em culpado pelo crime sofrido.

**Princípios:** prevenção sem medo; linguagem clara; nenhuma arma; privacidade por padrão; transparência sobre caráter fictício; acessibilidade; conteúdo revisável.

## 3. Problema e oportunidades

Adolescentes convivem com mensagens urgentes, perfis falsos, arquivos, pagamentos, exposição pública e tentativas de tomada de conta. Materiais tradicionais podem ser longos, genéricos ou desconectados do contexto cotidiano. O jogo oferece:

- exemplos reconhecíveis e feedback no momento da ação;
- repetição de um protocolo: parar, verificar, preservar e pedir ajuda;
- espaço seguro para errar sem consequência real;
- suporte para discussão em sala ou apresentação mediada.

## 4. Públicos e trabalhos a realizar

| Público | Necessidade / Job to be Done |
|---|---|
| Adolescente jogador | “Quando algo estranho surgir online, quero reconhecer o sinal e saber meu próximo passo.” |
| Professor | “Quero iniciar uma discussão concreta e verificar compreensão sem expor casos pessoais.” |
| Responsável | “Quero conversar sobre riscos digitais sem vigilância invasiva ou moralismo.” |
| Especialista em segurança | “Quero garantir que a prevenção seja correta, atual e não prometa proteção absoluta.” |
| Banca acadêmica | “Quero rastrear problema, requisitos, decisões, evidências e viabilidade técnica.” |

## 5. Escopo atual

### Incluído no protótipo

- movimentação lateral, salto, câmera, colisão, plataformas e ameaças com comportamento simples;
- 20 ocorrências em 15 categorias: phishing, malware, perfil falso, ransomware, golpe de pagamento/QR, violência digital, invasão de conta, vazamento de dados, engenharia social, Wi-Fi falso, loja falsa, deepfake/IA, doxxing, suporte falso e aliciamento online;
- mapa ampliado em 5 fases inspiradas no DF, com Base PCDF, escola, Setor Bancário, Congresso Nacional, Catedral, Lago Paranoá/Ponte JK e operação final;
- scanner não violento, painel de orientação, HUD, pausa, vitória e falha;
- save local, captura de tela e compilação Windows;
- documentação de produto, engenharia e operação.

### Fora do escopo atual

- autenticação, ranking, chat, coleta de telemetria e multiplayer;
- denúncias reais ou integração com sistemas policiais;
- aconselhamento jurídico individual;
- aplicativo móvel nativo;
- uso de logotipo, brasão ou identidade institucional oficial.

## 6. Objetivos e resultados-chave propostos

Os valores abaixo são **metas de validação**, não resultados já medidos.

### O1 — Entregar uma experiência compreensível e concluível

- KR1: pelo menos 80% dos participantes concluem a missão sem ajuda do facilitador.
- KR2: mediana de conclusão entre 10 e 20 minutos.
- KR3: pelo menos 90% identificam o scanner e o objetivo até 60 segundos após iniciar.

### O2 — Produzir aprendizagem observável

- KR1: aumento médio de pelo menos 25 pontos percentuais entre pré e pós-teste de 15 itens.
- KR2: pelo menos 80% citam espontaneamente “verificar por outro canal” após a sessão.
- KR3: pelo menos 75% escolhem preservar evidências em cenários simulados.

### O3 — Ser seguro, inclusivo e confiável

- KR1: nenhuma coleta de dado pessoal no MVP.
- KR2: 100% das orientações revisadas por especialista antes da publicação externa.
- KR3: zero achados críticos abertos na revisão de segurança da release.
- KR4: pontuação SUS alvo igual ou superior a 75 após teste com amostra definida.

## 7. Métricas e método

| Dimensão | Métrica | Como medir sem invadir privacidade |
|---|---|---|
| Alcance | sessões iniciadas | contagem agregada apenas se houver consentimento |
| Engajamento | conclusão e tempo | observação de teste ou telemetria opcional anonimizada |
| Aprendizagem | pré/pós-teste | formulário separado, sem conteúdo pessoal |
| Compreensão | acertos por categoria | cenário hipotético, não relato de vitimização |
| Usabilidade | SUS, erros e pedidos de ajuda | teste moderado e notas agregadas |
| Segurança | vulnerabilidades por severidade | revisão técnica por release |
| Acessibilidade | violações e barreiras observadas | checklist WCAG adaptado e teste com usuários |

Não haverá leaderboard, perfil comportamental nem retenção de histórico individual no MVP.

## 8. Roadmap orientado por evidências

| Fase | Entregas | Critério de passagem |
|---|---|---|
| 0 — Fundação | código modular, 15 categorias, 5 fases, docs, screenshot e build | compilação limpa e walkthrough completo |
| 1 — Validação especialista | revisão pedagógica, segurança, jurídica e linguagem | pendências críticas resolvidas |
| 2 — Teste formativo | 5–8 sessões moderadas com representantes do público | barreiras principais identificadas e priorizadas |
| 3 — MVP web | loop compatível com WebAssembly, publicação estática e acessibilidade | teste nos navegadores-alvo e threat model aprovado |
| 4 — Piloto escolar | roteiro do professor, pré/pós-teste e consentimentos | aprovação institucional e plano de dados |
| 5 — Evolução | áudio opcional, controles remapeáveis, novos capítulos | evidência de ganho sem regressão de segurança |

## 9. Priorização do backlog

### Must

- concluir todas as categorias e orientações;
- revisão humana do conteúdo;
- controles por teclado e feedback legível;
- aviso de projeto fictício;
- build reproduzível e documentação rastreável.

### Should

- remapeamento de teclas, modo alto contraste e redução de movimento;
- quiz curto ao final com feedback;
- versão WebAssembly sem backend;
- testes automatizados de regras sem renderização.

### Could

- narração opcional, português simples e Libras em vídeos separados;
- capítulos por contexto: escola, família e serviços públicos;
- painel do facilitador sem dados identificáveis.

### Won't now

- chat, anúncios, compras, ranking público, login social e denúncia real dentro do jogo.

## 10. Riscos de produto

| Risco | Prob. | Impacto | Resposta |
|---|---:|---:|---|
| Confusão com produto oficial | M | A | aviso visível, nome acadêmico e ausência de marcas oficiais |
| Conteúdo desatualizado | M | A | proprietário de conteúdo e revisão por release |
| Excesso de texto | A | M | teste de leitura, fragmentação e opção de áudio futura |
| Abordagem culpabilizante | M | A | revisão pedagógica e linguagem centrada em apoio |
| Dificuldade motora | M | M | remapeamento e alternativas a reflexos rápidos |
| Escopo crescer antes da validação | A | M | roadmap por gates e MoSCoW |

## 11. Governança

- **Product Owner:** prioriza valor, escopo e critérios de aceite.
- **Tech Lead:** responde por arquitetura, qualidade e releases.
- **Responsável de conteúdo:** mantém orientações e histórico de revisão.
- **Security Champion:** revisa ameaças, dependências e cloud.
- **UX Lead:** conduz pesquisa, acessibilidade e Design System.

Toda release candidata à banca deve incluir commit identificado, build validado, checklist de segurança, screenshot atual e revisão dos documentos afetados.
