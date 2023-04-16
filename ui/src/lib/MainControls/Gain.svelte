<script>
  import { Label } from 'flowbite-svelte'
  import MainControlRange from '../components/MainControlRange.svelte'
  import { gain } from '../store/cameraState.js'

  let value = 0;
  gain.subscribe((v) => {
    value = v;
  });

  function handleChange(e) {
    console.log(e.target.value)
    window.client.setGain(e.target.value);
  }

  

</script>
<div class="flex justify-between md:grid grid-cols-12 grow">
  <Label id="gain" class="md:col-span-1">Gain</Label>
  <div class="md:col-span-10">
    <MainControlRange klass="w-60 col-span-11" id="gain" min="0" max="720" value={value} onChange={handleChange}  />
  </div>
  
</div>
<style>
 
</style>