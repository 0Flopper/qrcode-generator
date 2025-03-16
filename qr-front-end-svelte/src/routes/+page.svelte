<script>
    let data = '';
    let fileName = '';
    let qrImage = null;
    let errorMessage = '';
  
    async function generateQRCode() {
      errorMessage = '';
      qrImage = null;
  
      if (!data.trim() || !fileName.trim()) {
        errorMessage = 'Por favor, preencha ambos os campos!';
        return;
      }
  
      try {
        // Faz a requisição GET para o back-end
        const response = await fetch(`http://localhost:5555/qrcode?data=${encodeURIComponent(data)}&file_name=${encodeURIComponent(fileName)}`);
  
        if (!response.ok) {
          throw new Error('Erro ao gerar o QR Code');
        }
  
        // Converte a resposta para blob (imagem)
        const blob = await response.blob();
  
        // Cria uma URL temporária para a imagem
        qrImage = URL.createObjectURL(blob);
  
      } catch (error) {
        errorMessage = `Erro ao gerar QR Code: ${error.message}`;
      }
    }
  </script>
  
  <main>
    <h1>QR CODE GENERATOR</h1>
  
    <div>
      <label for="data">Texto para QR Code:</label>
      <input id="data" type="text" bind:value={data} placeholder="Digite algo..." />
    </div>
  
    <div>
      <label for="fileName">Nome do Arquivo:</label>
      <input id="fileName" type="text" bind:value={fileName} placeholder="Ex: meu_qrcode" />
    </div>
  
    <button on:click={generateQRCode}>Gerar QR Code</button>
  
    {#if errorMessage}
      <p class="error">{errorMessage}</p>
    {/if}
  
    {#if qrImage}
      <h2>QR Code Gerado:</h2>
      <img src={qrImage} alt="QR Code" />
    {/if}
  </main>
  
  <style>

    main{
        display: flex;
        flex-direction: column;
        align-items: center;
    }
    .error {
      color: red;
    }
  
    img {
      margin-top: 20px;
      width: 200px;
      height: 200px;
      object-fit: contain;
    }
  </style>
  