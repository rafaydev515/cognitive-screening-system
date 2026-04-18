# Cognitive Screening System (C++ OOP) — Version 1

## Overview

This project is a console-based cognitive screening system designed to evaluate user traits using weighted question-response mapping.

The goal of this project was not just implementation, but understanding **system design using Object-Oriented Programming (OOP)**.

## Core Features

* Multi-trait evaluation:

  * Pattern Hunter
  * Social Smart
  * Explorer
  * Stabilizer
* Weighted scoring per question
* Score normalization
* Trait classification (dominant & secondary)
* Interpretation engine

## System Flow

Questions → Responses → Scoring → Normalization → Classification → Interpretation → Output

## OOP Concepts Applied

* Encapsulation
* Separation of Concerns
* Single Responsibility Principle (partially enforced)
* Modular design

## Project Status

This is **Version 1** of the system.

### Current Limitations

* Classification logic is rule-based and hardcoded
* Tight coupling between some components
* Output layer is not fully abstracted
* Limited configurability

## Future Improvements (Version 2)

* Introduce Strategy Pattern for classification
* Decouple data models (Raw vs Normalized profiles)
* Configurable scoring and thresholds
* Dedicated presentation layer
* Improved extensibility

## How to Run

Compile:
g++ src/*.cpp -o app

Run:
./app

## Purpose

This project was built to transition from theoretical OOP concepts to practical system design.

## Author

Muhammad Rafay
