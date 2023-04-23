<script>
  import { Label } from 'flowbite-svelte'
import MainControlRange from '../components/MainControlRange.svelte'
  import { get } from 'svelte/store'
  import { saturation } from '../store/cameraState.js'

  let value = 0;
  saturation.subscribe((v) => {
    value = v;
  });
  function handleChange(e) {
    window.client.setSaturation(e.target.value);
  }

  

</script>
<div class="flex justify-between md:grid grid-cols-12 grow">
  <Label class="col-span-1">Saturation</Label>
    <div class="col-span-10">
      <MainControlRange klass="w-60 col-span-11" id="Saturation" min="0" max="255" value={value} onChange={handleChange}  />
    </div>
  
</div>
<style>
 
</style>