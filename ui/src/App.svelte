<script>
  import Image from './lib/Image.svelte'
  import Client from './lib/Client.svelte'
  import Exposure from './lib/Exposure.svelte'
  import ExposureBtn from './lib/ExposureBtn.svelte';
  import ControlDrawer from './lib/ControlDrawer.svelte';
  import StreamBtn from './lib/StreamBtn.svelte';
</script>

<main class="flex flex-col items-center">
  <Client />
  <Image />
  <Exposure />
  <ExposureBtn />
  <StreamBtn />
  <ControlDrawer />
</main>

<style>
</style>
