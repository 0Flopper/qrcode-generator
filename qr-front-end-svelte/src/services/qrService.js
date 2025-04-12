// BaseURL
const baseUrl = 'http://localhost:5555';

export async function getQrPreview(data) {
  if (!data || !data.trim()) {
    throw new Error('Dados inválidos para gerar QR Code');
  }

  const response = await fetch(`${baseUrl}/generate?data=${encodeURIComponent(data)}`);
  if (!response.ok) throw new Error('Falha ao gerar QR Code');

  const blob = await response.blob();
  return URL.createObjectURL(blob);
}

export async function downloadQr(format, data, scale = 10) {
  if (!data || !data.trim()) {
    throw new Error('Dados inválidos para download do QR Code');
  }

  const response = await fetch(`${baseUrl}/generate/download/${format}?data=${encodeURIComponent(data)}&scale=${encodeURIComponent(scale)}`);
  if (!response.ok) throw new Error('Falha ao baixar QR Code');

  const blob = await response.blob();
  const link = document.createElement('a');
  link.href = URL.createObjectURL(blob);
  link.download = `qrcode.${format}`;
  link.click();
}
