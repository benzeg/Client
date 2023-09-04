import "./app.postcss";
import App from "./App.svelte";

window.addEventListener('DOMContentLoaded', () => {
  console.log("DOMContentLoaded")
  new App({
    target: document.getElementById("main"),
  });
});
