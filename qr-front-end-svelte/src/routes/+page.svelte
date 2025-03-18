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
  
  <main class="flex flex-col w-full justify-center items-center gap-8 mx-40">

    <!-- Title -->
    <h1 class="font-bold uppercase text-3xl">qr code generator</h1>

    <!-- QR Infos -->
    <div class="flex w-full flex-col justify-center items-center rounded-xl p-8 bg-white ">
    <!-- QR Inputs -->
      <div class="w-full rounded-2xl p-8">
        <div class="flex flex-col gap-4">
          <input class="py-4 px-8 rounded-full outline-1" id="data" type="text" bind:value={data} placeholder="Digite o texto" />
          <input class="py-4 px-8 rounded-full outline-1" id="fileName" type="text" bind:value={fileName} placeholder="Ex: meu_qrcode" />
        </div>
      </div>

      <!-- Generation Button -->
      <div>
        <button class="p-4 rounded-full outline-1" on:click={generateQRCode}>Gerar QR Code</button>
      </div>
    
      <!-- QR Error Message -->
      {#if errorMessage}
        <p class="font-bold py-5 text-red-400">{errorMessage}</p>
      {/if}
      
      <!-- QR CODE -->
      {#if qrImage}
        <div class="flex flex-col gap-8 py-8">
          <img src={qrImage} alt="QR Code" />
        </div>
      {/if}
    </div>
  </main>
  
  <style>
  </style>
  