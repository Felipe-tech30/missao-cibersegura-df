# Roteiro de Banca e Simulação do Jogo

## 1. Formato sugerido

Duração total: **15 minutos** — 9 min de apresentação, 4 min de demonstração e 2 min de margem. Quatro integrantes/professores podem interromper; por isso cada bloco deve fechar uma ideia completa.

| Tempo | Conteúdo | Evidência |
|---:|---|---|
| 0:00–0:45 | problema e público | visão do produto |
| 0:45–2:00 | proposta e objetivo | screenshot/game loop |
| 2:00–3:30 | crimes abordados | sete categorias |
| 3:30–5:00 | arquitetura | módulos e estado |
| 5:00–6:30 | UX e acessibilidade | Design System/jornada |
| 6:30–7:45 | segurança e privacidade | arquitetura sem backend |
| 7:45–9:00 | roadmap e métricas | GitHub Project/OKRs |
| 9:00–13:00 | demonstração | executável validado |
| 13:00–15:00 | conclusão e perguntas | protocolo final |

## 2. Mensagem de abertura

“Adolescentes tomam decisões digitais sob urgência, pressão social e excesso de informação. Missão Cibersegura transforma sete categorias de risco em uma experiência curta: identificar, interromper, verificar, preservar evidências e buscar ajuda. É um projeto acadêmico fictício, inspirado no contexto do DF e sem afiliação oficial.”

## 3. Roteiro da demonstração

### Preparação

1. fechar notificações e aplicativos sobrepostos;
2. usar build correspondente ao commit da banca;
3. iniciar em 1280×720 e testar áudio do ambiente, mesmo sem áudio no jogo;
4. apagar/renomear save anterior se a demonstração exigir nova missão;
5. deixar screenshot e vídeo curto de contingência disponíveis;
6. abrir o README e a arquitetura em abas separadas.

### Execução narrada

1. No menu, destacar o aviso de projeto educativo fictício.
2. Abrir “Como jogar” e apontar scanner, objetivo e sete categorias.
3. Iniciar e mostrar HUD: proteção, progresso `0/12` e controles.
4. Aproximar-se do phishing e usar `Espaço`.
5. Ler uma orientação: conferir remetente/URL, não fornecer códigos e preservar evidências.
6. Explicar que o mundo pausa para respeitar o tempo de leitura.
7. Mostrar malware e dados corrompidos como riscos visualmente diferentes.
8. Acionar `F5`, pausar e retomar; explicar save local sem dados pessoais.
9. Usar a tela de vitória no slide/screenshot se não houver tempo para 12 alertas.
10. Fechar com o protocolo: parar, verificar por outro canal, proteger a conta, preservar e pedir ajuda.

## 4. Metas da missão

- investigar 12 ocorrências;
- ler a orientação de cada ocorrência;
- preservar a proteção acima de zero;
- concluir as sete categorias;
- chegar à tela final e recordar ações preventivas.

## 5. Plano de contingência

| Falha | Ação |
|---|---|
| executável não abre | mostrar screenshot e seguir o roteiro, depois evidenciar build log |
| resolução/projetor corta HUD | usar captura 1280×720 no slide |
| save interfere | iniciar nova missão ou usar backup limpo |
| sem tempo | demonstrar uma ocorrência e usar slide de vitória |
| pergunta jurídica/institucional | reforçar caráter acadêmico e indicar validação pendente |
| pergunta sobre eficácia | apresentar metas de teste, não alegar resultado ainda não medido |

## 6. Perguntas prováveis

**Por que um jogo?** Porque permite prática, feedback e repetição; a hipótese ainda será validada por pré/pós-teste.

**O jogo usa IA?** Codex/GPT-5 apoiou desenvolvimento e documentação; não existe IA no executável nem envio de dados.

**É oficial da PCDF?** Não. É projeto acadêmico fictício e não usa marca oficial. Parceria futura exigiria autorização.

**Como protege menores?** O MVP não coleta dados, não pede casos reais, usa linguagem não culpabilizante e prevê governança LGPD antes de piloto.

**Por que não há backend?** Não é necessário para o objetivo atual; removê-lo reduz custo, dados e superfície de ataque.

**Como medir aprendizagem?** Pré/pós-teste de cenários, conclusão, compreensão e SUS, sempre com protocolo e dados mínimos.

**Qual a próxima entrega?** Revisão especializada, teste formativo, acessibilidade P1 e port WebAssembly.

## 7. Checklist final da banca

- [ ] commit/tag e repositório acessíveis;
- [ ] executável compilado e smoke test realizado;
- [ ] screenshot atual no README e no deck;
- [ ] apresentação abre offline e tem fontes legíveis;
- [ ] nomes, números e categorias consistentes;
- [ ] nenhuma promessa de eficácia sem evidência;
- [ ] uso de IA e caráter não oficial declarados;
- [ ] perguntas divididas entre os apresentadores;
- [ ] backup local do PPTX, PDF opcional e screenshot.
