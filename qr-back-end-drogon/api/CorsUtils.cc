#include "api/CorsUtils.h"
#include <drogon/HttpResponse.h>

void addCorsHeaders(const drogon::HttpResponsePtr& res) {
    res->addHeader("Access-Control-Allow-Origin", "*");
    res->addHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    res->addHeader("Access-Control-Allow-Headers", "Content-Type, Authorization");
}
