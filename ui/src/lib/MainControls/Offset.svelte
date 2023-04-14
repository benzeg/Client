<script>
  import { Range, Label } from 'flowbite-svelte'
  import { get } from 'svelte/store'
  import { offset } from '../store/mainControls.js' 

  const value = get(offset);

  function handleChange(e) {
    window.client.setOffset(e.target.value);
  }

</script>
<div class="grid grid-cols-12 grow">
  <Label class="col-span-1">Offset</Label>
    <div class="col-span-10">
      <Range size="lg" id="Offset" min="0" max="100" value={value} on:change={handleChange} />
    </div>
  <span class="col-span-1">{value}</span>
</div>
<style>
 
</style>