````markdown
# DFA Simulator

A visual and interactive Deterministic Finite Automaton (DFA) simulator built with [Streamlit](https://streamlit.io/). This tool allows you to define DFA components, configure transitions, and visualize the automaton using Graphviz.

## Features

- Define a set of DFA states (`q0`, `q1`, ...).
- Input a custom alphabet (e.g., `a`, `b`, `0`, `1`, etc.).
- Create and edit the DFA transition table using an interactive UI.
- Set a start state and one or more accepting states.
- Visualize the DFA as a directed graph using Graphviz.

## Installation

### Requirements

- Python 3.8+
- `pip`

### Install Dependencies

```bash
pip install streamlit pandas graphviz
````

> **Note:** You may also need to install Graphviz system binaries:
>
> * **Ubuntu/Debian**: `sudo apt install graphviz`
> * **Mac (Homebrew)**: `brew install graphviz`
> * **Windows**: Download from [graphviz.org](https://graphviz.org/download/)

## Run the App

```bash
streamlit run app.py
```

Then open `http://localhost:8501` in your web browser.

## How to Use

1. Select the number of DFA states.
2. Enter input symbols (e.g., `ab01`).
3. Use the transition table editor to define transitions.
4. Set the start and accepting states.
5. Click **"Visualize DFA"** to see the graph representation.

## TODO / Improvements

* Add DFA minimization support.
* Support for simulating input strings.
* Export DFA configuration to JSON.

## License

MIT License © 2025 KhoaTranNguyen

```
