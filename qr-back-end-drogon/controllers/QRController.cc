#include "QRController.h"
#include "services/QRGeneratorService.h"
#include "services/PNGWriterService.h"
#include "services/QRPreviewService.h"
#include "api/CorsUtils.h"

// Função auxiliar para criar e configurar uma resposta de erro
drogon::HttpResponsePtr QRController::createErrorResponse(drogon::HttpStatusCode status, const std::string& message) {
    auto res = drogon::HttpResponse::newHttpResponse();
    res->setStatusCode(status);
    res->setBody(message);
    addCorsHeaders(res);  // Adiciona os cabeçalhos CORS para a resposta de erro
    return res;
}

void QRController::previewQRCode(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback)
{
    std::string data = req->getParameter("data");

    // Verifica se há dados na URL
    if (data.empty()) {
        callback(createErrorResponse(drogon::HttpStatusCode::k400BadRequest, "Parâmetros inválidos ou ausentes."));
        return;
    }

    // Gera o QR Code com o texto recebido
    auto qrcode = std::unique_ptr<QRcode, decltype(&QRcode_free)>(QRGeneratorService::generate(data), QRcode_free);

    if (!qrcode) {
        callback(createErrorResponse(drogon::HttpStatusCode::k500InternalServerError, "Erro ao gerar QR Code"));
        return;
    }

    QRPreviewService qrPreviewService;
    std::vector<png_byte> pngBuffer = qrPreviewService.generateQRPreview(qrcode.get());

    // Verifica se a imagem foi gerada com sucesso
    if (pngBuffer.empty()) {
        callback(createErrorResponse(drogon::HttpStatusCode::k500InternalServerError, "Erro ao gerar PNG do QR Code"));
        return;
    }

    std::cout << "QR Code gerado com sucesso!" << std::endl;
    std::cout << "Tamanho do QR Code: " << qrcode->width << "x" << qrcode->width << std::endl;

    // Prepara a resposta HTTP com o conteúdo do PNG
    auto res = drogon::HttpResponse::newHttpResponse();
    addCorsHeaders(res);
    res->setContentTypeCode(drogon::CT_IMAGE_PNG);
    res->setBody(std::string(pngBuffer.begin(), pngBuffer.end()));
    callback(res);
    
}

void QRController::downloadQRCodePNG(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback)
{
    std::string data = req->getParameter("data");
    std::string fileName = req->getParameter("filename");
    std::string sizeStr = req->getParameter("size");


    // URL parameters verifications
    if (sizeStr.empty() || fileName.empty() || data.empty()) {
        callback(createErrorResponse(drogon::HttpStatusCode::k400BadRequest, "Parâmetros inválidos ou ausentes."));
        return;
    }

    int size = 0; // Valor padrão caso a conversão falhe
    try {
        size = std::stoi(sizeStr);
    } catch (const std::exception &e) {
        std::cerr << "Erro ao converter size para inteiro: " << e.what() << std::endl;
        // Em caso de erro, definimos um valor inválido ou tomamos uma ação apropriada.
        callback(createErrorResponse(drogon::HttpStatusCode::k400BadRequest, "Parametro 'size' inválido."));
        return;
    }

    // Gera o QR Code com o texto recebido
    auto qrcode = std::unique_ptr<QRcode, decltype(&QRcode_free)>(QRGeneratorService::generate(data), QRcode_free);

    if (!qrcode) {
        callback(createErrorResponse(drogon::HttpStatusCode::k500InternalServerError, "Erro ao gerar QR Code PNG"));
        return;
    }    

    // Gera o PNG
    std::string savedPath = PNGWriterService::saveToPNG(qrcode.get(), fileName, size);

    if (savedPath.empty()) {
        callback(createErrorResponse(drogon::HttpStatusCode::k500InternalServerError, "Erro ao salvar QR Code."));
        return;
    }

    // Informações do QR Code gerado
    std::cout << "QR Code PNG gerado com sucesso!" << std::endl;
    std::cout << "Tamanho do QR Code: " << qrcode->width << "x" << qrcode->width << std::endl;

    // Envia a resposta com o arquivo PNG gerado
    auto res = drogon::HttpResponse::newFileResponse(
        savedPath,                          // Caminho do arquivo (std::string)
        fileName,         // Nome do arquivo como std::string
        drogon::CT_IMAGE_PNG               // Tipo MIME correto para PNG
    );
    addCorsHeaders(res);
    callback(res);

    if (std::filesystem::exists(savedPath)) {
        std::remove(savedPath.c_str());  // Remove o arquivo após o envio
    }    
}

/* void QRController::asyncHandleHttpRequest(const drogon::HttpRequestPtr& req, 
    std::function<void (const drogon::HttpResponsePtr &)> &&callback)
{
    // Pega os parâmetros 'data' e 'file_name'
    std::string data = req->getParameter("data");

    // Verifica se os parâmetros são válidos e retorna erro caso contrário
    if (data.empty()) {
        callback(createErrorResponse(drogon::HttpStatusCode::k400BadRequest, "Parametro 'data' não fornecido."));
        return;
    }

    // Gera o QR Code com o texto recebido
    auto qrcode = std::unique_ptr<QRcode, decltype(&QRcode_free)>(QRGeneratorService::generate(data), QRcode_free);

    if (!qrcode) {
        callback(createErrorResponse(drogon::HttpStatusCode::k500InternalServerError, "Erro ao gerar QR Code"));
        return;
    }

    // Logando informações do QR Code gerado
    std::cout << "QR Code gerado com sucesso!" << std::endl;
    std::cout << "Tamanho do QR Code: " << qrcode->width << "x" << qrcode->width << std::endl;


    // Imprimir os dados binários do QR Code (opcional)
    std::cout << "Dados do QR Code (módulos):" << std::endl;
    for (int y = 0; y < qrcode->width; ++y) {
        for (int x = 0; x < qrcode->width; ++x) {
            std::cout << (qrcode->data[y * qrcode->width + x] & 1 ? "1" : "0");
        }
        std::cout << std::endl;
    }


    // Gera a imagem PNG do QR Code em um buffer
    std::vector<char> pngData = PNGWriterService::save(qrcode.get());

    if (pngData.empty()) {
        callback(createErrorResponse(drogon::HttpStatusCode::k500InternalServerError, "Erro ao gerar a imagem PNG"));
        return;
    }

    // Retorna a imagem PNG gerada como resposta HTTP
    auto res = drogon::HttpResponse::newHttpResponse();
    res->setStatusCode(drogon::HttpStatusCode::k200OK);
    res->setBody(std::string(pngData.begin(), pngData.end()));  // Converte o buffer para string
    res->setContentTypeCode(drogon::CT_IMAGE_PNG);  // Define o tipo de conteúdo como imagem PNG

    addCorsHeaders(res);  // Adiciona os cabeçalhos CORS para a resposta bem-sucedida
    callback(res);
} */
