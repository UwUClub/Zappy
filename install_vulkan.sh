#!/bin/bash

# Get OS information
OS=$(awk -F= '/^NAME/{print $2}' /etc/os-release)

echo "Operating System: $OS"

# Install Vulkan
case $OS in
  '"Ubuntu"')
    echo "Installing Vulkan for Ubuntu..."
    apt update -y && apt install -y vulkan-tools vulkan-dev vulkan-validationlayers-dev
    ;;
  '"Fedora"')
    echo "Installing Vulkan for Fedora..."
    dnf update -y && dnf install -y vulkan-tools vulkan-headers vulkan-loader-devel mesa-vulkan-devel vulkan-validation-layers-devel
    ;;
  '"Arch Linux"')
    echo "Installing Vulkan for Arch Linux..."
    pacman -Syu --noconfirm vulkan-devel
    ;;
  *)
    echo "Sorry, this script doesn't support your OS."
    ;;
esac
