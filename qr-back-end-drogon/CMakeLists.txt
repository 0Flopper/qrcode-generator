cmake_minimum_required(VERSION 3.5)
project(qr-server-drogon CXX)

include(CheckIncludeFileCXX)

check_include_file_cxx(any HAS_ANY)
check_include_file_cxx(string_view HAS_STRING_VIEW)
check_include_file_cxx(coroutine HAS_COROUTINE)

if (NOT "${CMAKE_CXX_STANDARD}" STREQUAL "")
    # Do nothing
elseif (HAS_ANY AND HAS_STRING_VIEW AND HAS_COROUTINE)
    set(CMAKE_CXX_STANDARD 20)
elseif (HAS_ANY AND HAS_STRING_VIEW)
    set(CMAKE_CXX_STANDARD 17)
else ()
    set(CMAKE_CXX_STANDARD 14)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Adiciona o código-fonte do seu projeto
add_executable(${PROJECT_NAME} main.cc)

# ##############################################################################
# Se você incluir o código-fonte do drogon localmente no seu projeto, use este método
# para adicionar o drogon 
# add_subdirectory(drogon) 
# target_link_libraries(${PROJECT_NAME} PRIVATE drogon)
#
# E comente as linhas a seguir
find_package(Drogon CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)

# ##############################################################################

# Procurar a biblioteca PNG
find_package(PNG REQUIRED)

# Vincular a biblioteca PNG ao seu projeto
target_link_libraries(${PROJECT_NAME} PRIVATE ${PNG_LIBRARIES})

# Incluir o diretório de cabeçalhos do libpng
target_include_directories(${PROJECT_NAME} PRIVATE ${PNG_INCLUDE_DIRS})

# Verificar a versão do C++ padrão
if (CMAKE_CXX_STANDARD LESS 17)
    message(FATAL_ERROR "c++17 or higher is required")
elseif (CMAKE_CXX_STANDARD LESS 20)
    message(STATUS "use c++17")
else ()
    message(STATUS "use c++20")
endif ()

# Adicionar diretórios de fontes
aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(models MODEL_SRC)
aux_source_directory(services SERVICE_SRC)
aux_source_directory(api API_SRC)

drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
                    ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                                   ${CMAKE_CURRENT_SOURCE_DIR}/models)
target_sources(${PROJECT_NAME}
               PRIVATE
               ${SRC_DIR}
               ${CTL_SRC}
               ${FILTER_SRC}
               ${PLUGIN_SRC}
               ${MODEL_SRC}
               ${SERVICE_SRC}
               ${API_SRC})

# ##############################################################################
# Descomente a linha a seguir para carregar views dinamicamente
# set_property(TARGET ${PROJECT_NAME} PROPERTY ENABLE_EXPORTS ON)
# ##############################################################################

# Removido o subdiretório "test"
# add_subdirectory(test)

# ##############################################################################
# Integração com libqrencode
# Primeiro, tentamos encontrar a biblioteca usando pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(QRCode REQUIRED libqrencode)

# Vincular a biblioteca QRCode ao seu projeto
target_link_libraries(${PROJECT_NAME} PRIVATE ${QRCode_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${QRCode_INCLUDE_DIRS})

# Verificar se a biblioteca foi encontrada
if (NOT QRCode_FOUND)
    message(FATAL_ERROR "libqrencode not found!")
endif ()
