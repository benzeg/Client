<script>
  const wait = setInterval(() => {
    console.log("waiting")
    if (window.Module) {
      clearInterval(wait);
      console.log("Module loaded");
      window.client = new window.Module.Client("SVBONY SV305 0");
      window.client.connect();
      window.client.setStreamEncoder("MJPEG")
    }
  }, 1000);
</script>