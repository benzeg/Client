import { writable } from "svelte/store";

export const exposure = writable(0.01);
window.syncExposure = (value) => {
  console.log("exposure", value);
  exposure.set(value);
}