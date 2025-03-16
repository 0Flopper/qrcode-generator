# QR Code Generator

This is a simple application to generate QR Codes, built using **C++ (Drogon)** for the backend and **Svelte** for the frontend. The project allows you to generate and download QR Codes in PNG format from a custom input string.

## Features

- Generate a QR Code from a custom string.
- Download the QR Code as a PNG image.

## Installation

### Prerequisites

Before getting started, make sure you have the following tools installed:

#### Backend

- **Drogon** (C++ framework)
- **C++ compiler** (with support for C++17 or later)
- **CMake** (version 3.5 or later)
- **libpng** (for PNG image generation)
- **libqrencode** (for QR Code generation)

#### Frontend

- **Node.js**
- **npm**

### How to test the application locally:

1. Clone the repository:

    ```bash
    git clone https://github.com/0Flopper/qrcode-generator.git
    ```

2. **Backend (Drogon)**

    Navigate to the backend build folder, compile and run the server:

    ```bash
    cd qrcode-generator/qr-back-end-drogon/build
    cmake ..
    make
    ./qr-server-drogon
    ```

3. **Frontend (Svelte)**

    Navigate to the frontend folder, install dependencies and start the server:

    ```bash
    cd qrcode-generator/qr-front-end-svelte/
    npm install
    npm run dev
    ```
