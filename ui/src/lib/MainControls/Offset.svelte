<script>
  import { Label } from 'flowbite-svelte'
import MainControlRange from '../components/MainControlRange.svelte'
  import { get } from 'svelte/store'
  import { offset } from '../store/cameraState.js' 

  let value = 0;
  offset.subscribe((v) => {
    value = v;
  });
  function handleChange(e) {
    window.client.setOffset(e.target.value);
  }

  

</script>
<div class="flex justify-between md:grid grid-cols-12 grow">
  <Label class="col-span-1">Offset</Label>
    <div class="col-span-10">
      <MainControlRange klass="w-60 col-span-11" id="Offset" min="0" max="255" value={value} onChange={handleChange}  />
    </div>
  
</div>
<style>
 
</style>