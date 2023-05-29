#!/bin/bash

# Get OS information
OS=$(awk -F= '/^NAME/{print $2}' /etc/os-release)

echo "Operating System: $OS"

# Install Vulkan
case $OS in
  '"Ubuntu"')
    echo "Installing Vulkan for Ubuntu..."
    sudo apt update -y && apt install -y ogre
    ;;
  '"Fedora Linux"')
    echo "Installing Vulkan for Fedora..."
    sudo dnf update -y && dnf install -y ogre
    ;;
  '"Arch Linux"')
    echo "Installing Vulkan for Arch Linux..."
    sudo pacman -Syu --noconfirm ogre
    ;;
  '"Garuda Linux"')
    echo "Installing Vulkan for Garuda Linux..."
    sudo pacman -Syu --noconfirm ogre
    ;;
  *)
    echo "Sorry, this script doesn't support your OS."
    ;;
esac
