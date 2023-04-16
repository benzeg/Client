<script>
  import { onDestroy } from "svelte";
  import { Button } from "flowbite-svelte"
  import { videoStreamOn } from "./store/cameraState";

  let streamOn = 0;
  videoStreamOn.subscribe((value) => {
    streamOn = value;
  });

  function handleClick() {
    window.client.toggleStream();
  }

  onDestroy(() => {
    // turn off stream when component is destroyed
    window.client.toggleStream(0);
  });

</script>

<Button color={streamOn ? null: "alternative"} class="w-24 h-24" on:click={handleClick}>
  {streamOn ? "Stop stream" : "Start stream"}
</Button>

<style>
</style>