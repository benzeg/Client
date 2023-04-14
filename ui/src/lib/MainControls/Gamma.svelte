<script>
  import { Range, Label } from 'flowbite-svelte'
  import { get } from 'svelte/store'
  import { gamma } from '../store/mainControls.js' 

  const value = get(gamma);

  function handleChange(e) {
    window.client.setGamma(e.target.value);
  }

</script>
<div class="grid grid-cols-12 grow">
  <Label class="col-span-1">Gamma</Label>
    <div class="col-span-10">
      <Range size="lg" id="Gamma" min="0" max="100" value={value} on:change={handleChange} />
    </div>
  <span class="col-span-1">{value}</span>
</div>
<style>
 
</style>