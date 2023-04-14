<script>
  import { get } from 'svelte/store';
  import { exposure } from "./store/exposure.js";
</script>

<label>
  Exposure
  <input
    type="number"
    min=1
    max=60
    value={$exposure}
  />
</label>

<style>

</style>