<script>
  import { FloatingLabelInput } from 'flowbite-svelte'
  import { roi } from './store/cameraState.js'
  let x = 0;
  let y = 0;
  let width = 0;
  let height = 0;

  roi.subscribe((value) => {
    x = value.x;
    y = value.y;
    width = value.width;
    height = value.height;
  });

  function handleXChange(e) {
    console.log(e.target.value)
    window.client.setROI(Number(e.target.value), y, width, height);
  }

  function handleYChange(e) {
    window.client.setROI(x, e.target.value, width, height); 
  }

  function handleWidthChange(e) {
    window.client.setROI(x, y, e.target.value, height); 
  }

  function handleHeightChange(e) {
    window.client.setROI(x, y, width, e.target.value); 
  }

</script>
<div class="flex flex-col">
  <FloatingLabelInput style="outlined" label="X" type="number" min="0" max="1920" step="1" value={x} on:change={handleXChange}/>
  <FloatingLabelInput style="outlined" label="Y" type="number" min="0" max="1080" step="1" value={y} on:change={handleYChange}/>
  <FloatingLabelInput style="outlined" label="WIDTH" type="number" min="0" max="1920" step="1" value={width} on:change={handleWidthChange}/>
  <FloatingLabelInput style="outlined" label="HEIGHT" type="number" min="0" max="1080" step="1" value={height} on:change={handleHeightChange}/>
</div>
<style>
</style>