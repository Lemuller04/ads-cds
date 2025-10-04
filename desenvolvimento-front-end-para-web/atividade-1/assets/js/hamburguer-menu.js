/*
 *  Set up the hamburguer menu button functionality by
 *  toggling back and forth classes that trigger css styles,
 *  and aria attributes with the help of a helper variable
 */

const menuButton = document.querySelector(".page-header .header-nav-button");
const menuXIcon = document.querySelector(".page-header .header-menu-close");
const menuHamburguerIcon = document.querySelector(
  ".page-header .header-menu-open",
);
const menuBackdrop = document.querySelector(".page-header .backdrop");
const menuContainer = document.querySelector(".page-header .header-mobile-nav");
const firstLink = menuContainer.querySelector("a");
let isOpen = false;

function toggleMenu() {
  isOpen = !isOpen;
  menuButton.setAttribute("aria-expanded", isOpen);
  menuContainer.setAttribute("aria-hidden", !isOpen);
  menuButton.classList.toggle("hamburguer-menu-opened");
  menuXIcon.classList.toggle("hidden");
  menuHamburguerIcon.classList.toggle("hidden");
  menuBackdrop.classList.toggle("hidden");
  menuContainer.classList.toggle("mobile-nav-slide");
}

menuBackdrop.addEventListener("click", () => {
  toggleMenu();

  if (isOpen && firstLink) {
    firstLink.focus();
  }

  if (!isOpen) {
    menuButton.focus();
  }
});

menuButton.addEventListener("click", () => {
  toggleMenu();
});

document.addEventListener("keydown", (e) => {
  if (e.key === "Escape" && isOpen) {
    toggleMenu();
  }
});
