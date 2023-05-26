#!/bin/bash

echo "Installing Vulkan for Fedora..."
sudo dnf update -y && dnf install -y vulkan-tools vulkan-headers vulkan-loader-devel vulkan-validation-layers-devel glfw-devel glm-devel
