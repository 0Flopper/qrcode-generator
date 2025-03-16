#ifndef CORS_UTILS_H
#define CORS_UTILS_H

#include <drogon/HttpResponse.h>

void addCorsHeaders(const drogon::HttpResponsePtr& res);

#endif
