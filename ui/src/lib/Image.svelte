<script>
  window.updateImage = (filePath) => {
    const fileBinary = window.Module.FS.readFile(filePath);
    const fileHeaderLen = fileBinary.length - (1920 * 1080);
    const fileBody = fileBinary.slice(fileHeaderLen);

    // element img
    //const objURL = URL.createObjectURL(
    //  new Blob(fileBinary, { type: 'image/png' })
    //);

    //const img = document.getElementById("image");
    //img.src = objURL; 

    // element canvas
    const canvas = document.getElementById('canvas');
    const ctx = canvas.getContext('2d');
    const imageData = new ImageData(new Uint8ClampedArray(fileBody), 1920);
    ctx.putImageData(imageData, 0, 0);
  }
</script>

<canvas id="canvas" class="sm:w-full lg:w-10/12"/>

<style>
</style>