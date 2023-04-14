<script>
  import { Range, Label } from 'flowbite-svelte'
  import { get } from 'svelte/store'
  import { wbr } from '../store/mainControls.js'

  const value = get(wbr);

  function handleChange(e) {
    window.client.setWBR(e.target.value);
  }

</script>
<div class="grid grid-cols-12 grow">
  <Label class="col-span-1">WBR</Label>
    <div class="col-span-10">
      <Range size="lg" id="WBR" min="0" max="100" value={value} on:change={handleChange} />
    </div>
  <span class="col-span-1">{value}</span>
</div>
<style>
  
</style>