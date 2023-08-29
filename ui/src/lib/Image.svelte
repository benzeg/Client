<script>
  import { onMount } from 'svelte';
  import { get } from 'svelte/store';
  import { roi } from './store/cameraState.js';

  let image;
  let canvas;

  onMount(() => {
    image = document.getElementById('image');
    image.style.height = image.offsetWidth * (1080 / 1920) + 'px';
    canvas = document.getElementById('canvas');
    canvas.style.height = canvas.offsetWidth * (1080 / 1920) + 'px';
  });

  window.updateImage = (blobP, blobLen, formatP) => {
    renderImage(blobP, blobLen);    
  }

  function renderImage(blobP, blobLen) {
    const fileBody = new Uint8ClampedArray(window.Module.HEAPU8.slice(blobP, blobP + blobLen));
    const canvas = document.getElementById('canvas');
    const ctx = canvas.getContext('2d');
    const {width} = get(roi);
    const imageData = new ImageData(fileBody, width);
    ctx.putImageData(imageData, 0, 0);
  }

</script>

<canvas id="canvas" class="w-full md:w-2/4"/>
<!--<div id="debug"/> -->
<img id="image" class="w-full md:w-2/4" />
<style>
</style>