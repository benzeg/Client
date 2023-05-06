<script>
  import { Button } from "flowbite-svelte"; 
  let lock = false;
  const callRest = async (direction) => {
    const response = await fetch(`/updateControl`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({ data: direction }),
    });

    lock = false;
  };

  const handleClick = (direction) => {
    if (lock) {
      return false;
    }
    
    try {
      window.navigator.vibrate(200);
    } catch(e) {
      const userAgent = window.navigator.userAgent;
      console.log(userAgent)
      // do nothign
    }
    
    lock = true;
    return callRest(direction);
  }

</script>
<div class="grid grid-rows-3 grid-cols-3">
  <Button disabled={lock} id="up" class="row-start-1 row-span-1 col-start-2 col-span-1" on:click={handleClick.bind(null, 'u')}>
    <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="w-6 h-6">
      <path stroke-linecap="round" stroke-linejoin="round" d="M4.5 10.5L12 3m0 0l7.5 7.5M12 3v18" />
    </svg>
  </Button>
  <Button disabled={lock} id="left" class="row-start-2 row-span-1 col-start-1 col-span-1" on:click={handleClick.bind(null, 'l')}>
    <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="w-6 h-6">
      <path stroke-linecap="round" stroke-linejoin="round" d="M10.5 19.5L3 12m0 0l7.5-7.5M3 12h18" />
    </svg>
  </Button>
  <Button disabled={lock} id="right" class="row-start-2 row-span-1 col-start-3 col-span-1" on:click={handleClick.bind(null, 'r')}>
    <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="w-6 h-6">
    <path stroke-linecap="round" stroke-linejoin="round" d="M13.5 4.5L21 12m0 0l-7.5 7.5M21 12H3" />
  </svg>
  </Button>
  <Button disabled={lock} id="down" class="row-start-3 row-span-1 col-start-2 col-span-1" on:click={handleClick.bind(null, 'd')}>
    <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="w-6 h-6">
      <path stroke-linecap="round" stroke-linejoin="round" d="M19.5 13.5L12 21m0 0l-7.5-7.5M12 21V3" />
    </svg>
  </Button>
</div>


