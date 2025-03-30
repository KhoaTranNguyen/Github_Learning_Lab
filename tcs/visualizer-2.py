#Graphviz Drawing
from graphviz import Digraph
def create_dfa(states, alphabet, transitions, start_state, accept_states):
    dfa = Digraph()
    
    # Add states
    for state in states:
        if state in accept_states:
            dfa.attr('node', shape='doublecircle')
        else:
            dfa.attr('node', shape='circle')
        dfa.node(state)

    # Mark start state
    dfa.attr('node', shape='plaintext')
    dfa.node('start', label='')
    dfa.edge('start', start_state)

    # Add transitions
    for (src, via), dst in transitions.items():
        dfa.edge(src, dst, label=via)
    
    return dfa# Function to create and display DFA

# Streamlit UI
import streamlit as st
import pandas as pd

def main():
    st.title("DFA Simulator")

    # Number of states input
    num_states = st.number_input(label="Enter number of states:", min_value = 0, max_value = 10, value=0)

    # Generate initial state names
    states = [f'q{i}' for i in range(num_states + 1)]

    # Define alphabet
    text = st.text_input(label="Enter unique alphabet:",)
    alphabet = list(''.join(text.split()))

    # Other inputs (for demonstration)
    placeholder_text = (f"Select among q0 and q{num_states}..." if num_states > 0 else "It seems that q0 is the only choice")
    start_state = st.selectbox(label="Enter start state:", options=states, index=None, placeholder=placeholder_text)
    accept_states = st.multiselect(label="Enter accept states:", options=states, placeholder=placeholder_text)

    # Transition function input
    st.subheader("Define transition function")
    transitions = {}
    for state in states:
        for letter in alphabet:
            next_state = st.text_input(f"Transition from {state} on {letter}:", key=f"{state}_{letter}")
            if next_state:
                transitions[(state, letter)] = next_state

    # Create DataFrame with state labels as a column
    data = pd.DataFrame(index=states, columns=alphabet)
    data.index.name = "state"
    data_reset = data.reset_index()

    # Editable table with dynamic default for new rows
    edited_data = st.data_editor(
        data=data_reset,
        column_config={
            "state": st.column_config.TextColumn(
                "State",
                help="State names must follow the format q{number} (e.g., q0, q1, q2).",
                default=f"q{num_states+1}",  # Dynamically sets default for new rows
                max_chars=10,
                validate=r"^q\d+$",
                )
            },
        num_rows="dynamic",
        hide_index=True,
    )
    
    # DFA creation and visualization
    if st.button("Create DFA"):
        try:
            dfa = create_dfa(states, alphabet, transitions, start_state, accept_states)
            st.graphviz_chart(str(dfa))
        except Exception as e:
            st.error(f"Error creating DFA: {e}")

if __name__ == "__main__":
    main()