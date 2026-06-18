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
        default:
            return (DicaEducativa){ "ALERTA DIGITAL", "Pare e verifique antes de clicar.",
                                    "Proteja seus dados pessoais.", "Peca ajuda a uma pessoa de confianca." };
    }
}
