<script>
  import { Label } from 'flowbite-svelte'
import MainControlRange from '../components/MainControlRange.svelte'
  import { get } from 'svelte/store'
  import { wbg } from '../store/cameraState.js'

  let value = 0;
  wbg.subscribe((v) => {
    value = v;
  });

  function handleChange(e) {
    console.log(e.target.value)
    window.client.setWBG(e.target.value);
  }

  

</script>
<div class="flex justify-between md:grid grid-cols-12 grow">
  <Label class="col-span-1">WBG</Label>
    <div class="col-span-10">
      <MainControlRange klass="w-60 col-span-11" id="WBG" min="0" max="511" value={value} onChange={handleChange}  />
    </div>
  
</div>
<style>
 
</style>