import streamlit as st
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
def main():
    st.title("DFA Simulator")

    # User inputs for DFA
    states = st.text_input("Enter states (comma-separated):").split(',')
    alphabet = st.text_input("Enter alphabet (comma-separated):").split(',')
    start_state = st.text_input("Enter start state:")
    accept_states = st.text_input("Enter accept states (comma-separated):").split(',')

    # Transition function input
    st.subheader("Define transition function")
    transitions = {}
    for state in states:
        for letter in alphabet:
            next_state = st.text_input(f"Transition from {state} on {letter}:", key=f"{state}_{letter}")
            if next_state:
                transitions[(state, letter)] = next_state

    # DFA creation and visualization
    if st.button("Create DFA"):
        try:
            dfa = create_dfa(states, alphabet, transitions, start_state, accept_states)
            st.graphviz_chart(str(dfa))
        except Exception as e:
            st.error(f"Error creating DFA: {e}")

if __name__ == "__main__":
    main()