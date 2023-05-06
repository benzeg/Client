<script>
  import { Tabs, TabItem } from 'flowbite-svelte';
  import Gain from './MainControls/Gain.svelte'
  import { Drawer, Button, CloseButton } from 'flowbite-svelte'
  import WBR from './MainControls/WBR.svelte'
  import Contrast from './MainControls/Contrast.svelte'
  import Gamma from './MainControls/Gamma.svelte'
  import Saturation from './MainControls/Saturation.svelte'
  import Sharpness from './MainControls/Sharpness.svelte'
  import WBB from './MainControls/WBB.svelte'
  import WBG from './MainControls/WBG.svelte'
  import Offset from './MainControls/Offset.svelte'
  import MotorControl from './MotorControl.svelte'
  let hidden = true;
  import ZoomControl from './ZoomControl.svelte'
  import ROIControl from './ROIControl.svelte'

  let transitionParamsBottom = {
    duration: 200,
  };
</script>

<div class="text-center">
  <Button class="fixed left-0 right-0 bottom-0 h-24" on:click={() => (hidden = false)}>Show drawer</Button>
</div>
<Drawer class="overflow-y-hidden" position="fixed" placement='bottom' width='w-full' transitionType="fly" transitionParams={transitionParamsBottom} bind:hidden={hidden}>
  <div class='flex grow-0'>
    <CloseButton on:click={() => (hidden = true)} class='mb-4 dark:text-white' />
  </div>
  <Tabs>
    <TabItem title="MainControl">
      <div class="wrapper overflow-y-scroll">
        <div class="flex flex-col gap-y-5">
          <Gain />
          <Contrast />
          <Gamma />
          <Saturation />
          <Sharpness />
          <WBB />
          <WBG />
          <WBR />
          <Offset />
        </div>
      </div>
    </TabItem>
    <TabItem title="MotorControl">
      <MotorControl />
    </TabItem>
    <TabItem title="ZoomControl">
      <ZoomControl />
    </TabItem>
    <TabItem title="ROIControl">
      <ROIControl />
    </TabItem>
  </Tabs>
  
</Drawer>

<style>
  .wrapper {
    height: 300px;
  }
</style>