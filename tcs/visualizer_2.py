import streamlit as st
import pandas as pd
from graphviz import Digraph

# Function to create and display DFA
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
    
    return dfa

def main():
    st.title("DFA Simulator")

    # Initialize session state for transition data
    if 'transition_data' not in st.session_state:
        st.session_state.transition_data = pd.DataFrame(columns=["state"])

    # Number of states input
    num_states = st.number_input(
        label="Enter number of initial states:",
        min_value=0,
        max_value=10,
        value=0,
        key="num_states"
    )

    # Generate initial state names
    initial_states = [f'q{i}' for i in range(num_states + 1)]

    # Define alphabet
    text = st.text_input(label="Enter unique alphabet:", key="alphabet_input")
    alphabet = list(''.join(text.split())) if text else []

    # Update transition data when number of states or alphabet changes
    if st.session_state.transition_data.empty or 'prev_states' not in st.session_state:
        data = pd.DataFrame(index=initial_states, columns=alphabet)
        data.index.name = "state"
        st.session_state.transition_data = data.reset_index()
        #st.session_state.prev_states = initial_states
        #st.session_state.prev_alphabet = alphabet

    # Transition function input
    st.subheader("Define transition function")
    
    # Editable table with dynamic rows
    edited_data = st.data_editor(
        data=st.session_state.transition_data,
        column_config={
            "state": st.column_config.TextColumn(
                "State",
                help="State names must follow the format q{number}",
                default=f"q{st.session_state.transition_data.shape[0]}",  # Dynamically sets default for new rows
                max_chars=10,
                validate=r"^q\d+$",
                required=True
            ),
            **{col: st.column_config.SelectboxColumn(
                col,
                help=f"Select transition state for {col}",
                options=st.session_state.transition_data["state"].tolist(),
                required=True
            ) for col in alphabet}
        },
        #num_rows="dynamic",
        hide_index=True,
        key="transition_editor"
    )

    # Update session state with edited data
    st.session_state.transition_data = edited_data

    # Extract current states from edited data
    current_states = edited_data['state'].unique().tolist()

    # State selection widgets
    if current_states:

        placeholder_text = (
            f"Select among q0 and q{num_states}..."
            if num_states > 0 else "It seems that q0 is the only choice")
        start_state = st.selectbox(
            "Select start state:",
            options=current_states,
            index=None,
            placeholder=placeholder_text,
            #help="Select the start state",
            key="start_state"
        )

        accept_states = st.multiselect(
            "Select accept states:",
            options=current_states,
            placeholder=placeholder_text,
            #help="Select the accept states",
            key="accept_states"
        )
    
    transition_dict = {}
    for state in current_states:
        for letter in alphabet:
            next_state = st.session_state.transition_data.loc[
                st.session_state.transition_data['state'] == state, letter].values[0]
            if pd.notna(next_state):
                transition_dict[(state, letter)] = next_state

    # DFA creation and visualization
    if st.button("Create DFA") and not edited_data.isnull().values.any():
            try:
                dfa = create_dfa(initial_states, alphabet, transition_dict, start_state, accept_states)
                st.graphviz_chart(str(dfa))
            except Exception as e:
                st.error(f"Error creating DFA.")

    else:
        st.warning(
            "Please define all states in the transition table. DFA cannot be created if the fields are empty.")

if __name__ == "__main__":
    main()