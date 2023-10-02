# 3D Wireframe Model Visualization Program

## Overview

This C++ program is designed to visualize 3D wireframe models. It follows the Google C++ Style Guide and adheres to the C++17 standard. The code is organized in the `src` folder and includes a Makefile with standard GNU-program targets.

## Program Features

- Load a wireframe model from an obj file (vertices and surfaces list support only).
- Translate the model by a given distance along the X, Y, and Z axes.
- Rotate the model by a given angle around its X, Y, and Z axes.
- Scale the model by a given value.
- Supports the display of model details such as file name, number of vertices, and edges.
- The program is designed for Linux and can use GUI libraries like GTK+, CEF, Qt, JUCE, SFML, Nanogui, or Nngui.

## Program Structure

The program follows object-oriented programming principles and is implemented using the Model-View-Controller (MVC) pattern. Here are some key aspects of the program's structure:

- Business logic is separated from the view code.
- The interface code is isolated from both the controller and the model.
- Controllers are kept thin, focusing on handling user input and interacting with the model.

## Design Patterns

The program incorporates three different design patterns:

1. **Singleton Pattern**: A Singleton pattern is used to ensure that only one instance of the main application exists. This prevents multiple instances from conflicting with each other.

2. **Strategy Pattern**: The program employs a strategy pattern to allow for various affine transformations, such as translation, rotation, and scaling. Different strategies can be applied based on user input.

3. **Command Pattern**: Each transformation action is encapsulated in a command object, allowing for easy execution and reversal.

## Unit Testing

The program includes comprehensive unit tests that cover modules related to model loading and affine transformations. This ensures the reliability and correctness of the program.

## Performance

The program is optimized to handle wireframe models with varying levels of detail, ranging from 100 vertices to 1,000,000 vertices. It ensures smooth user interactions without freezing (defined as inactivity of more than 0.5 seconds).

## Installation

- The program can be built using the provided Makefile.
- The installation directory can be chosen arbitrarily, excluding the build directory.

## Namespace

All classes and components are implemented within the `s21` namespace as required.

---

With these specifications, the program provides a robust and user-friendly interface for visualizing 3D wireframe models while adhering to best practices in software design and architecture.