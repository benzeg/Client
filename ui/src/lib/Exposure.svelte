<script>
  import { exposure } from "./store/exposure.js";
  import MainControlRange from './components/MainControlRange.svelte'

</script>

<label>
  Exposure
  <MainControlRange klass="w-60"
    id="exposure"
    min=1
    max=60
    value={$exposure}
  />
</label>

<style>
</style>