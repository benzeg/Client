<script>
  import { Label } from 'flowbite-svelte'
  import MainControlRange from '../components/MainControlRange.svelte';
  import { get } from 'svelte/store'
  import { wbb } from '../store/cameraState.js'

  let value = 0;
  wbb.subscribe((v) => {
    value = v;
  });
  function handleChange(e) {
    console.log(e.target.value)
    window.client.setWBB(e.target.value);
  }

</script>
<div class="flex justify-between md:grid grid-cols-12 grow">
  <Label class="col-span-1">WBB</Label>
  <MainControlRange min="0" max="511" value={value} id="wbb" klass="w-60 col-span-11" onChange={handleChange} /> 
</div>
<style>
 
</style>