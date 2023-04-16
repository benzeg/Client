<script>
  import { Label } from 'flowbite-svelte'
import MainControlRange from '../components/MainControlRange.svelte'
  import { get } from 'svelte/store' 
  import { contrast } from '../store/cameraState.js'
  let value = 0;

  contrast.subscribe((v) => {
    value = v;
  });

  function handleChange(e) {
    window.client.setContrast(e.target.value);
  }

  

</script>
<div class="flex justify-between md:grid grid-cols-12 grow">
  <Label class="col-span-1">Contrast</Label>
  <MainControlRange klass="w-60 col-span-11" id="Contrast" min="0" max="100" value={value} onChange={handleChange}/>
  
</div>
<style>
</style>