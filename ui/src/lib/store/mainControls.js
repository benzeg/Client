import { writable } from "svelte/store";

export const gain = writable(0);
window.syncGain = (value) => {
  console.log("syncGain", value);
  gain.set(value);
}

export const contrast = writable(0);
window.syncContrast = (value) => {
  console.log("syncContrast", value);
  contrast.set(value);
}

export const gamma = writable(0);
window.syncGamma = (value) => {
  console.log("syncGamma", value);
  gamma.set(value);
}

export const saturation = writable(0);
window.syncSaturation = (value) => {
  console.log("syncSaturation", value);
  saturation.set(value);
} 

export const sharpness = writable(0);
window.syncSharpness = (value) => {
  console.log("syncSharpness", value);
  sharpness.set(value);
}

export const wbb = writable(0);
window.syncWBB = (value) => {
  console.log("syncWBB", value);
  wbb.set(value);
}

export const wbg = writable(0);
window.syncWBG = (value) => {
  console.log("syncWBG", value);
  wbg.set(value);
}

export const wbr = writable(0);
window.syncWBR = (value) => {
  console.log("syncWBR", value);
  wbr.set(value);
}

export const offset = writable(0);
window.syncOffset = (value) => {
  console.log("syncOffset", value);
  offset.set(value);
}
