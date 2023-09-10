<script>

  //const wait = setInterval(() => {
  //  console.log("waiting")
  //  if (window.Module) {
  //    clearInterval(wait);
  //    console.log("Module loaded");
  //    window.client = new window.Module.Client("SVBONY SV305 0");
  //    window.client.connect();
  //    window.client.setStreamEncoder("MJPEG")
  //  }
  //}, 1000);


  import { Select } from 'flowbite-svelte';
  import { DEVICE_DATA, deviceId } from './store/device.js';

  const DEVICE_IDS = DEVICE_DATA.id.map((id) => ({
    value: id,
    name: id
  }));

  function handleChange(e) {
    console.log(e.target.value);
    deviceId.set(e.target.value);
  }
</script>
<Select
  items={DEVICE_IDS}
  on:change={handleChange}>
</Select>
