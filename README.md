# Wordle Game and Solver

A C implementation of the popular Wordle game with an automated solver.

## Project Description

This project implements:
- **Wordle Game**: A playable version where users guess a 5-letter word with feedback
- **Wordle Solver**: An automated solver that uses frequency analysis and information gain to efficiently guess words

The solver uses a frequency-based strategy for the first guess ("soare") and then filters remaining possibilities based on feedback, selecting the next guess that maximizes information gain.

## Compilation

To compile the project, run:

```bash
make