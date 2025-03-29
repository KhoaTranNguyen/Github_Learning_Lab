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
def main():
    st.title("DFA Simulator")

    # User inputs for DFA
    num_states = int(st.number_input(
        label="Enter number of states:",
        min_value = 0,
        max_value = 10,
        ))
    states = ['q{}'.format(i) for i in range(1+num_states)]

    #Alphabet
    text = st.text_input(
        label="Enter unique alphabet:",

    )
    alphabet = list(''.join(text.split()))

    #Start_state
    placeholder_text = (
        "Select among q0 and q{}...".format(num_states)
        if num_states > 0
        else "It seems that q0 is the only choice"
    )
    start_state = st.selectbox(
        label="Enter start state:",
        options=states,
        index=None,
        placeholder=placeholder_text,
    )
    
    #Accept_states
    accept_states = st.multiselect(
        label="Enter accept states:",
        options=states,
        placeholder=placeholder_text,
    )

    # Transition function input
    st.subheader("Define transition function")
    transitions = {}
    for state in states:
        for letter in alphabet:
            next_state = st.text_input(f"Transition from {state} on {letter}:", key=f"{state}_{letter}")
            if next_state:
                transitions[(state, letter)] = next_state

    import pandas as pd

    # Sample Data
    data = pd.DataFrame(index=states, columns=alphabet)

    # Editable Table
    edited_data = st.data_editor(data, num_rows="dynamic")

    # DFA creation and visualization
    if st.button("Create DFA"):
        try:
            dfa = create_dfa(states, alphabet, transitions, start_state, accept_states)
            st.graphviz_chart(str(dfa))
        except Exception as e:
            st.error(f"Error creating DFA: {e}")

if __name__ == "__main__":
    main()