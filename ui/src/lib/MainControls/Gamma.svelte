<script>
  import { Label } from 'flowbite-svelte'
import MainControlRange from '../components/MainControlRange.svelte'
  import { get } from 'svelte/store'
  import { gamma } from '../store/cameraState.js' 

  let value = 0;
  gamma.subscribe((v) => {
    value = v;
  });

  function handleChange(e) {
    window.client.setGamma(e.target.value);
  }

  

</script>
<div class="flex justify-between md:grid grid-cols-12 grow">
  <Label class="col-span-1">Gamma</Label>
    <div class="col-span-10">
      <MainControlRange klass="w-60 col-span-11" id="Gamma" min="0" max="1000" value={value} onChange={handleChange}  />
    </div>
  
</div>
<style>
 
</style>