<script>
  import { onMount } from 'svelte';

  let data = 'Nothing to see here';
  let fileName = 'example';
  let qrImage = null;

  // Função para gerar o QR Code
  async function generateQRCode() {
    const currentImage = qrImage;  // Mantém a imagem atual visível enquanto a nova é gerada.

    if (!data.trim() || !fileName.trim()) {
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

      // Cria uma URL temporária para a nova imagem
      qrImage = URL.createObjectURL(blob);
    } catch (error) {
      console.error(error.message);
    }
  }

  // Reatividade do Svelte: sempre que data ou fileName mudarem, chamamos generateQRCode
  $: {
    if (data.trim() && fileName.trim()) {
      generateQRCode();
    }
  }

  // Chamada inicial para garantir que o QR code seja gerado ao carregar a página
  onMount(() => {
    generateQRCode();
  });
</script>

<main class="flex flex-col w-full h-full justify-center items-center gap-8 mx-40">
  <!-- Title -->
  <h1 class="font-bold uppercase text-3xl">qr code generator</h1>

  <!-- QR Infos -->
  <div class="flex w-full flex-col justify-start items-center rounded-xl p-6 bg-white">
    <!-- QR Inputs -->
    <div class="w-full rounded-2xl p-8">
      <div class="flex flex-col gap-4">
        <input
          class="py-4 px-8 rounded-full outline-1"
          bind:value={data}
          placeholder="Digite o texto"
        />
        <input
          class="py-4 px-8 rounded-full outline-1"
          bind:value={fileName}
          placeholder="Ex: meu_qrcode"
        />
      </div>
    </div>

    <!-- QR CODE (Mantendo a imagem anterior enquanto a nova é gerada) -->
    {#if qrImage}
      <div class="flex flex-col gap-8">
        <img class="w-80" src={qrImage} alt="QR Code" />
      </div>
    {/if}
  </div>
</main>

<style>
  /* Adicione seus estilos aqui, se necessário */
</style>
