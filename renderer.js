import { auth } from './firebase-config.js';
import { createUserWithEmailAndPassword, signInWithEmailAndPassword } from "firebase/auth";

const email = document.getElementById("email");
const password = document.getElementById("password");
const message = document.getElementById("message");

document.getElementById("register").addEventListener("click", async () => {
  try {
    await createUserWithEmailAndPassword(auth, email.value, password.value);
    message.textContent = "Registered successfully!";
  } catch (error) {
    message.textContent = error.message;
  }
});

document.getElementById("login").addEventListener("click", async () => {
  try {
    await signInWithEmailAndPassword(auth, email.value, password.value);
    message.textContent = "Logged in successfully!";
  } catch (error) {
    message.textContent = error.message;
  }
});
