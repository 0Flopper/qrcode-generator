#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class QRController : public drogon::HttpSimpleController<QRController>
{
  public:
    void asyncHandleHttpRequest(const HttpRequestPtr& req, 
      std::function<void (const HttpResponsePtr &)> &&callback) override;
      
    PATH_LIST_BEGIN
      // list path definitions here;
      PATH_ADD("/qrcode", Get);
    PATH_LIST_END

    private:
    // Função auxiliar para criar e configurar uma resposta de erro
    drogon::HttpResponsePtr createErrorResponse(drogon::HttpStatusCode status, const std::string& message);
};
