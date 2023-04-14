<script>
  import { Range, Label } from 'flowbite-svelte'
  import { get } from 'svelte/store'
  import { gain } from '../store/mainControls.js'

  const value = get(gain);
  function handleChange(e) {
    window.client.setGain(e.target.value);
  }

  console.log(window)
</script>
<div class="grid grid-cols-12 grow">
  <Label class="col-span-1">Gain</Label>
    <div class="col-span-10">
      <Range size="lg" id="gain" min="0" max="720" value={value} on:change={handleChange} />
    </div>
  <span class="col-span-1">{value}</span>
</div>
<style>
 
</style>