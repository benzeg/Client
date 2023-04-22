<script>
  export let min = 0;
  export let max = 0;
  export let value = 0;
  export let id = '';
  export let klass = '';
  export let step = 0.1;
  export let onChange = (e) => console.log;
  let x0 = 0;
  let originalValue = Number(value);
  let moving = false;

  function handleTouchStart(e) {
    // record initial positioning
    originalValue = Number(value);
    x0 = e.pageX;
    e.target.focus();
    e.preventDefault();
  }
  
  function handleTouchMove(e) {
    const x1 = e.pageX;
    const dx = x1 - x0;
    const dValue = dx * step;
    value = Number(Math.min(Math.max(originalValue + dValue, min), max).toFixed(2));
    e.preventDefault();
  }

  function handleTouchEnd() {
    onChange({ target: { value } });
  }

  function handleMouseDown(e) {
    // record initial positioning
    originalValue = Number(value);
    x0 = e.pageX;
    e.target.focus();
    e.preventDefault();
    moving = true;
  } 

  function handleMouseUp(e) {
    if (!moving) {
      return;
    }
    onChange({target: { value }});
    moving = false;
  }

  function handleMouseMove(e) {
    if (!moving) {
      return;
    }

    const x1 = e.pageX;
    const dx = x1 - x0;
    const dValue = dx * step;
    value = Number(Math.min(Math.max(originalValue + dValue, min), max).toFixed(2));
    e.preventDefault();
  }

</script>

<input
  readonly
  contenteditable="false"
  type="number" 
  id={id}
  class={klass}
  min={min}
  max={max}
  value={value}
  step={step}
  on:mousedown={handleMouseDown}
  on:mouseup={handleMouseUp}
  on:mouseleave={handleMouseUp}
  on:mousemove={handleMouseMove}
  on:touchstart={handleTouchStart}
  on:touchmove={handleTouchMove}
  on:touchend={handleTouchEnd} /> 