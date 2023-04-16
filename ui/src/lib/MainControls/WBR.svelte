<script>
  import { Label } from 'flowbite-svelte'
import MainControlRange from '../components/MainControlRange.svelte'
  import { get } from 'svelte/store'
  import { wbr } from '../store/cameraState.js'

  let value = 0;
  wbr.subscribe((v) => {
    value = v;
  });

  function handleChange(e) {
    window.client.setWBR(e.target.value);
  }

  

</script>
<div class="flex justify-between md:grid grid-cols-12 grow">
  <Label class="col-span-1">WBR</Label>
    <div class="col-span-10">
      <MainControlRange klass="w-60 col-span-11" id="WBR" min="0" max="511" value={value} onChange={handleChange}  />
    </div>
  
</div>
<style>
  
</style>