<script>
  import { onMount } from 'svelte';
  let data = '';
  // Stores the generated QR code
  let qrImage = null;

  async function generateQRPreview() {
    if (!data || !data.trim()) return;

    try {
      const response = await fetch(`http://localhost:5555/generate?data=${encodeURIComponent(data)}`);
      if (!response.ok) throw new Error('Failed to generate QR Code');

      const blob = await response.blob();
      qrImage = URL.createObjectURL(blob);
    } catch (error) {
      console.error(error.message);
    }
  }

  // Re-generates QR when data or qrImage changes
  $: if (data.trim()) {
    generateQRPreview();
  }
</script>

<main class="flex flex-col w-full h-full justify-center items-center gap-8 mx-40">
  <!-- Page Title -->
  <h1 class="font-bold uppercase text-3xl">QR Code Generator</h1>

  <!-- QR Code Configuration Area -->
  <div class="flex w-full flex-col justify-start items-center rounded-xl p-6 bg-white">
    <!-- Input Field -->
    <div class="w-full rounded-2xl p-8">
      <div class="flex flex-col gap-4">
        <input
          class="py-4 px-8 rounded-full outline-1"
          bind:value={data}
          placeholder="Enter text"
        />
      </div>
    </div>

    <!-- QR Code Display -->
    {#if qrImage}
      <div class="flex flex-col gap-8">
        <img class="w-80" src={qrImage} alt="QR Code" />
      </div>
    {/if}
  </div>
</main>

<style>
  /* Add custom styles here if needed */
</style>
