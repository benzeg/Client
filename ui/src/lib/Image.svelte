<script>
  import { onMount } from 'svelte';
  let image;
  let canvas;

  let frames = null;
  let framesEnd = null;
  onMount(() => {
    image = document.getElementById('image');
    image.style.height = image.offsetWidth * (1080 / 1920) + 'px';
    canvas = document.getElementById('canvas');
    canvas.style.height = canvas.offsetWidth * (1080 / 1920) + 'px';
  });

  let frameCount = 0;

  window.updateImage = (blobP, blobLen, formatP) => {
    frameCount++;
    const newFrame = [blobP, blobLen, null];
    if (frames === null) {
      frames = newFrame;
      framesEnd = newFrame;
    } else {
      framesEnd[2] = newFrame;
      framesEnd = newFrame;
    }

    if (blobLen < 1080 * 1920) {
      return renderStream();
    }

    renderImage();    
  }

  function renderImage() {
    const [blobP, blobLen, next] = frames;
    frames = next;
    if (frames === null) {
      framesEnd = null;
    }

    const fileBody = new Uint8ClampedArray(window.Module.HEAPU8.slice(blobP, blobP + blobLen));
    const canvas = document.getElementById('canvas');
    const ctx = canvas.getContext('2d');
    const imageData = new ImageData(fileBody, 1920);
    ctx.putImageData(imageData, 0, 0);

    frameCount--;
  }

  function renderStream() {
    if (!image.complete) {
      setTimeout(renderStream, 100);
      return;
    }

    if (frames === null) {
      return;
    }

    const [blobP, blobLen, next] = frames;
    frames = next;
    if (frames === null) {
      framesEnd = null;
    }

    const fileBody = new Uint8ClampedArray(window.Module.HEAPU8.slice(blobP, blobP + blobLen));
    let frame = URL.createObjectURL(new Blob([fileBody], {type: 'image/stream_jpg'})) 
    image.src = frame;
    setTimeout(()=> {
      URL.revokeObjectURL(frame);
    },1000);

    frameCount--;
    return setTimeout(renderStream, 500);
  }
</script>

<canvas id="canvas" class="w-full md:w-2/4"/>
<!--<div id="debug"/> -->
<img id="image" class="w-full md:w-2/4" />
<style>
</style>