#pragma once

//#include <drogon/HttpSimpleController.h>
#include <drogon/HttpController.h>

using namespace drogon;

class QRController : public drogon::HttpController<QRController>
{
  public:

    METHOD_LIST_BEGIN
      ADD_METHOD_TO(QRController::previewQRCode, "/generate", Get);
      ADD_METHOD_TO(QRController::downloadQRCodePNG, "/generate/download/qrcode/png", Get);  
    METHOD_LIST_END

    void previewQRCode(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> 
    &&callback);

    void downloadQRCodePNG(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    private:
    // Função auxiliar para criar e configurar uma resposta de erro
    drogon::HttpResponsePtr createErrorResponse(drogon::HttpStatusCode status, const std::string& message);
};
