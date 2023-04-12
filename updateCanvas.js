function updateCanvas(filePath) {
  const uInt8Arr = Module.FS.readFile(filePath);
  const clampedArr = new Uint8ClampedArray(uInt8Arr);
  const canvas = document.getElementById('exposure');
  const ctx = canvas.getContext('2d');
  const imageData = new ImageData(clampedArr, 1440);
  ctx.putImageData(imageData, 0, 0);
}