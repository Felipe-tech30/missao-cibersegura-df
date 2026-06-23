#include "dicas.h"

DicaEducativa DicasParaAmeaca(TipoAmeaca tipo)
{
    switch (tipo)
    {
        case AMEACA_PHISHING:
            return (DicaEducativa){
                "ALERTA IDENTIFICADO: PHISHING",
                "Desconfie de mensagens urgentes pedindo senha, codigo ou pagamento.",
                "Confira o remetente e o endereco do site antes de clicar.",
                "Se houver golpe, guarde mensagens e links como evidencia."
            };
        case AMEACA_MALWARE:
            return (DicaEducativa){
                "ALERTA IDENTIFICADO: MALWARE",
                "Nao instale programas ou anexos enviados por desconhecidos.",
                "Mantenha o sistema atualizado e use protecao de seguranca.",
                "Um arquivo 'gratis' pode esconder um programa malicioso."
            };
        case AMEACA_PERFIL_FALSO:
            return (DicaEducativa){
                "ALERTA IDENTIFICADO: PERFIL FALSO",
                "Confirme pedidos de dinheiro por outro canal antes de agir.",
                "Evite publicar dados que facilitem a imitacao da sua identidade.",
                "Bloqueie, denuncie na plataforma e preserve as conversas."
            };
        case AMEACA_RANSOMWARE:
            return (DicaEducativa){
                "ALERTA IDENTIFICADO: RANSOMWARE",
                "Faca copias de seguranca e nao deixe todas no mesmo dispositivo.",
                "Ao notar algo estranho, desconecte o aparelho da rede e busque ajuda.",
                "Nao apague evidencias: elas podem ajudar uma investigacao."
            };
        case AMEACA_GOLPE_PAGAMENTO:
            return (DicaEducativa){
                "ALERTA: GOLPE DE PAGAMENTO OU QR CODE",
                "Confira o nome do destinatario antes de confirmar qualquer pagamento.",
                "Nao pague por pressao e desconfie de QR Codes enviados sem contexto.",
                "Confirme o pedido por outro canal e guarde o comprovante e a conversa."
            };
        case AMEACA_VIOLENCIA_DIGITAL:
            return (DicaEducativa){
                "ALERTA: VIOLENCIA DIGITAL",
                "Humilhacao, ameaca e perseguicao online nao sao apenas brincadeiras.",
                "Nao revide: bloqueie, denuncie e preserve mensagens e capturas de tela.",
                "Converse com um adulto de confianca e procure ajuda especializada."
            };
        case AMEACA_INVASAO_CONTA:
            return (DicaEducativa){
                "ALERTA: INVASAO DE CONTA",
                "Use uma senha longa e diferente em cada servico que voce utiliza.",
                "Ative a verificacao em duas etapas e nunca compartilhe codigos de acesso.",
                "Se perder o acesso, use a recuperacao oficial e avise seus contatos."
            };
        case AMEACA_VAZAMENTO_DADOS:
            return (DicaEducativa){
                "ALERTA: VAZAMENTO DE DADOS",
                "Dados pessoais como CPF, telefone e endereco podem ser usados em golpes.",
                "Compartilhe o minimo necessario e revise privacidade em redes sociais.",
                "Se seus dados vazarem, troque senhas e monitore acessos suspeitos."
            };
        case AMEACA_ENGENHARIA_SOCIAL:
            return (DicaEducativa){
                "ALERTA: ENGENHARIA SOCIAL",
                "Golpistas manipulam confianca, medo ou pressa para conseguir informacoes.",
                "Antes de responder, pare e confirme a historia por outro canal.",
                "Codigos, senhas e dados de conta nunca devem ser enviados por chat."
            };
        case AMEACA_WIFI_FALSO:
            return (DicaEducativa){
                "ALERTA: WI-FI FALSO",
                "Redes abertas com nome parecido podem capturar dados e senhas.",
                "Evite acessar banco, e-mail ou contas importantes em Wi-Fi desconhecido.",
                "Prefira rede confiavel e confira se o site usa conexao segura."
            };
        case AMEACA_LOJA_FALSA:
            return (DicaEducativa){
                "ALERTA: LOJA FALSA",
                "Preco muito baixo, urgencia e loja sem reputacao sao sinais de risco.",
                "Confira CNPJ, avaliacoes, endereco do site e formas seguras de pagamento.",
                "Nao conclua compra por link recebido em mensagem sem verificar a origem."
            };
        case AMEACA_DEEPFAKE:
            return (DicaEducativa){
                "ALERTA: DEEPFAKE E IA FRAUDULENTA",
                "Audio, imagem ou video podem ser manipulados para imitar pessoas reais.",
                "Desconfie de pedidos urgentes mesmo quando parecem vir de alguem conhecido.",
                "Confirme por chamada ou canal oficial antes de enviar dinheiro ou dados."
            };
        case AMEACA_DOXXING:
            return (DicaEducativa){
                "ALERTA: EXPOSICAO DE DADOS (DOXXING)",
                "Publicar dados de alguem para intimidar ou perseguir pode causar dano real.",
                "Nao compartilhe endereco, escola, telefone ou rotina de outra pessoa.",
                "Preserve prints, denuncie na plataforma e procure apoio responsavel."
            };
        case AMEACA_SUPORTE_FALSO:
            return (DicaEducativa){
                "ALERTA: SUPORTE TECNICO FALSO",
                "Pop-ups e ligacoes podem fingir que seu aparelho esta infectado.",
                "Nao instale programas de acesso remoto por pedido de desconhecidos.",
                "Procure canais oficiais e converse com um adulto antes de permitir acesso."
            };
        case AMEACA_ALICIAMENTO_ONLINE:
            return (DicaEducativa){
                "ALERTA: ALICIAMENTO ONLINE",
                "Perfis podem criar intimidade falsa para pedir segredo, fotos ou encontros.",
                "Nao aceite pressao para esconder conversas de familia ou responsaveis.",
                "Bloqueie, guarde evidencias e peca ajuda a um adulto de confianca."
            };
        default:
            return (DicaEducativa){ "ALERTA DIGITAL", "Pare e verifique antes de clicar.",
                                    "Proteja seus dados pessoais.", "Peca ajuda a uma pessoa de confianca." };
    }
}
