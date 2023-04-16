<script>
  import { onMount } from 'svelte';
  let videoSourceBuffer;
  //onMount(() => {
  //  const videoTag = document.getElementById("my-video");
  //  const myMediaSource = new MediaSource();
  //  const url = URL.createObjectURL(myMediaSource);
  //  videoTag.src = url;

  //  videoSourceBuffer = myMediaSource
  //  .addSourceBuffer('video/raw; sampling=RGB; width=1920; height=1080; colorimetry=bt709-2; pixel-aspect-ratio=1/1; interlace-mode=progressive; chroma-site=left; transfer-characteristics=bt709-2; matrix-coefficients=bt709-2; bits-per-sample=8;');

  //  videoSourceBuffer.mode = "sequence";
  //})
  

  window.updateImage = (blobP, blobLen) => {
    console.log('blob pointer ', blobP);
    console.log('blob length ', blobLen);

    let fileBody;
    if (blobLen === 1920 * 1080) {
      fileBody = new Uint8ClampedArray(window.Module.HEAPU8.slice(blobP, blobP + blobLen));
    } else {
      fileBody = new Uint8ClampedArray(window.Module.HEAPU8.slice(blobP + (blobLen - 1920 * 1080), blobP + blobLen));
    }
    
   const canvas = document.getElementById('canvas');
   const ctx = canvas.getContext('2d');
   const imageData = new ImageData(fileBody, 1920);
   ctx.putImageData(imageData, 0, 0);
   
   // videoSourceBuffer.appendBuffer(fileBody.buffer);
   window._free(blobP);

  }
</script>

<canvas id="canvas" class="sm:w-full lg:w-10/12"/>
<video id="my-video" class="sm:w-full lg:w-10/12"></video>

<style>
</style>