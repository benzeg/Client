<script>
  import Image from './lib/Image.svelte'
  import Client from './lib/Client.svelte'
  import Exposure from './lib/Exposure.svelte'
  import ExposureBtn from './lib/ExposureBtn.svelte';
  import ControlDrawer from './lib/ControlDrawer.svelte';
</script>

<main class="flex flex-col items-center">
  <Client />
  <Image />
  <Exposure />
  <ExposureBtn />
  <ControlDrawer />
</main>

<style>
</style>
