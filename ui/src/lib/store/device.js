import { writable } from "svelte/store";

export const DEVICE_DATA = {
  id: ["SVBONY SV305 0", "SVBONY SV305 1"]
};

export const deviceId = writable(null);