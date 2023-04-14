<script>
  import { Drawer, Button, CloseButton, A } from 'flowbite-svelte'
  import Gain from './MainControls/Gain.svelte'
  import Contrast from './MainControls/Contrast.svelte'
  import Gamma from './MainControls/Gamma.svelte'
  import Saturation from './MainControls/Saturation.svelte'
  import Sharpness from './MainControls/Sharpness.svelte'
  import WBB from './MainControls/WBB.svelte'
  import WBG from './MainControls/WBG.svelte'
  import WBR from './MainControls/WBR.svelte'
  import Offset from './MainControls/Offset.svelte'
  import * as mainControls from './store/mainControls.js'

  let hidden = true;
  let transitionParamsBottom = {
    y: 700,
    duration: 200,
  };
</script>

<div class="text-center">
  <Button class="fixed left-0 right-0 bottom-0 h-24" on:click={() => (hidden = false)}>Show drawer</Button>
</div>
<Drawer class="flex flex-col h-modal" placement='bottom' width='w-full' height="h-modal" transitionType="fly" transitionParams={transitionParamsBottom} bind:hidden={hidden} id='sidebar8'>
  <div class='flex grow-0'>
    <CloseButton on:click={() => (hidden = true)} class='mb-4 dark:text-white' />
  </div>
  <Gain />
  <Contrast />
  <Gamma />
  <Saturation />
  <Sharpness />
  <WBB />
  <WBG />
  <WBR />
  <Offset />
</Drawer>
