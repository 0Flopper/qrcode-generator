#pragma once

//#include <drogon/HttpSimpleController.h>
#include <drogon/HttpController.h>

using namespace drogon;

class QrController : public drogon::HttpController<QrController>
{
  public:

    METHOD_LIST_BEGIN
      ADD_METHOD_TO(QrController::previewQRCode, "/generate", Get);
      ADD_METHOD_TO(QrController::downloadQRCodePNG, "/generate/download/png", Get);
      ADD_METHOD_TO(QrController::downloadQrCodeSvg, "/generate/download/svg", Get);
    METHOD_LIST_END

    void previewQRCode(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> 
    &&callback);

    void downloadQRCodePNG(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> 
    &&callback);

    void downloadQrCodeSvg(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> 
    &&callback);

    private:
    // Função auxiliar para criar e configurar uma resposta de erro
    drogon::HttpResponsePtr createErrorResponse(drogon::HttpStatusCode status, const std::string& message);
};
