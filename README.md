Cognitive Screening System (C++ OOP) — Version 1

Overview

This project is a console-based cognitive screening system designed to evaluate user traits using weighted question-response mapping.

The goal of this project was to move beyond basic programming and apply Object-Oriented Programming (OOP) concepts to design a structured evaluation system.

---

Core Features

- Multi-trait evaluation:
  - Pattern Hunter
  - Social Smart
  - Explorer
  - Stabilizer
- Questions contribute to multiple traits using weighted scoring
- User responses captured on a 1–5 scale
- Aggregation of raw trait scores
- Normalization of scores to percentage scale
- Rule-based classification of dominant traits
- Basic interpretation of results

---

System Flow

Questions → User Responses → Score Aggregation → Normalization → Classification → Output

---

Key Design Concepts

1. Weighted Trait Mapping

Each question contributes to multiple traits with different weights.

Reasoning:
Human behavior is multi-dimensional. A single response can reflect more than one cognitive trait.

---

2. Score Normalization

Scores are normalized using:

(rawScore / maxScore) × 100

Reasoning:
Different traits may have different maximum possible scores depending on how many questions contribute to them.
Normalization ensures fair comparison.

---

3. Step-Based Processing Pipeline

The system is designed as a sequence of stages:

- Input collection
- Score computation
- Normalization
- Classification

Reasoning:
Breaking the system into stages improves clarity and maintainability.

---

4. Rule-Based Classification

Classification is based on fixed thresholds applied to normalized scores.

Reasoning:
A simple and interpretable starting model.

Limitation:

- Hardcoded thresholds
- Not easily extendable
- Not adaptive to new datasets

---

Current Limitations

- Entire system is implemented in a single file ("main.cpp")
- Limited modular separation at file level
- Classification logic is tightly coupled and hardcoded
- Output logic is not separated from system logic
- No abstraction for replacing scoring or classification strategies

---

Future Improvements (Version 2)

- Split system into multiple classes and files (".h" / ".cpp")
- Introduce a Classification Strategy pattern
- Separate:
  - RawScoreProfile
  - NormalizedProfile
- Add a dedicated Result Presentation layer
- Improve configurability (dynamic thresholds)
- Support external data formats (e.g., JSON)

---

How to Run

Compile:
g++ src/main.cpp -o app

Run:
./app

---

Example Output
===== RESULTS =====

                Raw Trait Scores:
                        Pattern Hunter: 56
                        Social Smart: 51
                        Explorer: 3
                        Stabilizer: 15

                Normalized Scores:
                        Pattern Hunter: 51.85%
                        Social Smart: 45.54%
                        Explorer: 2.70%
                        Stabilizer: 13.39%

                Profile Type: Dual
                        Dominant Trait: Pattern Hunter
                        Secondary Trait: Social Smart

                Interpretation:
                        You have two strong cognitive drivers that shape your behavior.

                Your cognitive style:
                        Strategic Communicator - You combine logic with social awareness.

                Dominant Trait Insight:
                        You naturally analyze patterns and systems.
---

Purpose

This project was built to transition from theoretical OOP concepts to practical system design, focusing on data flow, modular thinking, and structured problem-solving.

---

Author
Muhammad Rafay

Rafay
