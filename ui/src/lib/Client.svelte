<script>
  const wait = setInterval(() => {
    if (window.Module) {
      clearInterval(wait);
      window.client = new window.Module.Client("SVBONY SV305 0");
      window.client.connect();
    }
  }, 1000);
</script>