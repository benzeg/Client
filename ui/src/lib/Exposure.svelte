<script>
  import { exposure } from "./store/exposure.js";
  import MainControlRange from './components/MainControlRange.svelte'

  function handleChange(e) {
    window.client.setExposure(Number(e.target.value));
  }

</script>

<label>
  Exposure
  <MainControlRange klass="w-60"
    id="exposure"
    step=0.01
    min=0.01
    max=60
    value={$exposure}
    onChange={handleChange}
  />
</label>

<style>
</style>