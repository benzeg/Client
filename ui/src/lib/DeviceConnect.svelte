<script>
  import { deviceId } from './store/device.js';
  let value = null;
  deviceId.subscribe((v) => {
    value = v;
  });

  function handleClick() {
    console.log(`connecting to device id: ${value}`);
    window.client = new window.Module.Client(value);
    window.client.connect();
  }

</script>
<button class="w-24 h-24" on:click={handleClick} size="lg">Connect</button>
  
  
  