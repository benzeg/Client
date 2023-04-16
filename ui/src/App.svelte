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
  <div class="w-full flex justify-evenly items-center">
    <Exposure />
    <!--<ExposureBtn /> -->
    <StreamBtn />
  </div>
  <ControlDrawer />
</main>

<style>
</style>
