<script>
  import { getQrPreview, downloadQr } from '../services/qrService';

  let data = '';
  let qrImage = null;
  let showModal = false;
  let scale = 10;
  let format = '';

  $: if (data.trim()) {
    getQrPreview(data)
      .then(blobUrl => qrImage = blobUrl)
      .catch(error => console.error(error.message));
  }

  function handleDownload() {
    downloadQr(format, data, scale)
      .catch(error => console.error(error.message));
  }
</script>


<main class="flex flex-col w-full h-full justify-center items-center gap-8 mx-40">
  <!-- Title -->
  <h1 class="font-bold uppercase text-3xl">QR Code Generator</h1>

  <div class="flex w-full flex-col justify-start items-center rounded-xl p-6 bg-white">
    <div class="w-full rounded-2xl p-8">
      <!-- Text -->
      <div class="flex flex-col gap-4">
        <input
          class="py-4 px-8 rounded-full outline-1"
          bind:value={data}
          placeholder="Enter text"
        />
      </div>
    </div>

    {#if qrImage}
      <div class="flex flex-col gap-8 items-center">
        <img class="w-80 h-80" src={qrImage} alt="QR Code" />

        <!-- PNG Button -->
        <button on:click={() =>{
          format = 'png';
          showModal = true;
          }} 
          class="bg-blue-500 text-white px-6 py-2 rounded-full hover:bg-blue-600 cursor-pointer">
          PNG
        </button>
        <button on:click={() =>{
          format = 'svg';
          showModal = true;
          }} 
          class="bg-blue-500 text-white px-6 py-2 rounded-full hover:bg-blue-600 cursor-pointer">
          SVG
        </button>
      </div>
    {/if}
  </div>
</main>

<!-- Modal -->
{#if showModal}
  <div class="fixed inset-0 bg-black bg-opacity-40 flex items-center justify-center z-50">
    <div class="bg-white p-8 rounded-2xl w-[400px] flex flex-col gap-6 items-center">

      <!-- Model Title -->
      <h1 class="text-xl font-bold">Download QR Code</h1>

      {#if qrImage}
        <img class="w-60 h-60" src={qrImage} alt="QR Preview" />
      {/if}

      <!-- Slider de Qualidade -->
      <div class="w-full flex gap-6">
        <label for="quality" class="block mb-2 font-medium">LOW</label>

        <input id="quality" type="range" min="10" max="100" step="10" 
          bind:value={scale} class="w-full cursor-pointer" />

        <label for="quality" class="block mb-2 font-medium">HIGH</label>
      </div>
      
      <!-- Botões do Modal -->
      <div class="flex gap-4">
        <!-- Download -->
        <button on:click={handleDownload} 
          class="bg-green-600 text-white px-6 py-2 rounded-full hover:bg-green-700 cursor-pointer">
          Download
        </button>
        <!-- Cancelar -->
        <button 
          on:click={() => showModal = false} 
          class="bg-gray-400 text-white px-6 py-2 rounded-full hover:bg-gray-500 cursor-pointer">
          Cancel
        </button>
      </div>
    </div>
  </div>
{/if}

<style>
</style>
