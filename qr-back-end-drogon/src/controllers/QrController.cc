#include "QrController.h"
#include "src/utils/CorsUtils.h"
#include "src/services/QrService.h"
#include "src/services/PngService.h"


// Função auxiliar para criar e configurar uma resposta de erro
drogon::HttpResponsePtr QrController::createErrorResponse(drogon::HttpStatusCode status, const std::string& message) {
    auto res = drogon::HttpResponse::newHttpResponse();
    res->setStatusCode(status);
    res->setBody(message);
    res->setContentTypeCode(drogon::CT_TEXT_PLAIN); // Definir como texto puro para respostas de erro
    addCorsHeaders(res);  
    return res;
}

void QrController::previewQRCode(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback)
{
    std::string data = req->getParameter("data");

    // Verifica se há dados na URL
    if (data.empty()) {
        callback(createErrorResponse(drogon::HttpStatusCode::k400BadRequest, "Parâmetros inválidos ou ausentes."));
        return;
    }

    // Gera o QR Code com o texto recebido
    auto qrCode = QrService::generate(data);
    if (!qrCode) {
        callback(createErrorResponse(drogon::HttpStatusCode::k500InternalServerError, "Erro ao gerar QR Code"));
        return;
    }

    // Service que Gera a Imagem PNG
    std::vector<unsigned char> pngBuffer = PngService::generatePng(qrCode->data, qrCode->width);

    if (pngBuffer.empty()) {
        callback(createErrorResponse(drogon::HttpStatusCode::k500InternalServerError, "Erro ao gerar PNG"));
        return;
    }

    std::cout << "QR Code gerado com sucesso!" << std::endl;
    std::cout << "Tamanho do QR Code: " << qrCode->width << "x" << qrCode->width << std::endl;

    // Prepara a resposta HTTP com o conteúdo do PNG
    auto res = drogon::HttpResponse::newHttpResponse();
    res->setContentTypeCode(drogon::CT_IMAGE_PNG);
    res->setBody(std::string(reinterpret_cast<const char*>(pngBuffer.data()), pngBuffer.size())); 
    addCorsHeaders(res);
    callback(res);
}
