import streamlit as st
import pandas as pd

def main():
    st.title("DFA Simulator")

    # State configuration
    num_states = st.slider(
        label="Number of states:",
        min_value=0, max_value=10, value=0,
        key="num_states"
    )
    
    # Generate state labels or placeholder
    state_labels = (
        [f'q{i}' for i in range(num_states)] 
        if num_states > 0 
        else ['⏸️ No states defined']
    )

    # Alphabet configuration
    alphabet_input = st.text_input(
        label="Input symbols:",
        key="alphabet_input",
        help="All symbols is accepted, e.g: abc,<@!"
    )
    transition_symbols = (
        list(''.join(alphabet_input.split())) 
        if alphabet_input 
        else ['⏸️ No symbols defined']
    )

    # Initialize transition matrix
    if "transition_matrix" not in st.session_state:
        st.session_state.transition_matrix = pd.DataFrame(
            index=state_labels,
            columns=transition_symbols
        )
        st.session_state.last_state_config = (num_states, state_labels.copy())
        st.session_state.last_symbol_config = transition_symbols.copy()

    # Detect configuration changes
    state_changed = (
        (st.session_state.last_state_config[0] != num_states) or
        (st.session_state.last_state_config[1] != state_labels)
    )
    
    symbols_changed = (
        st.session_state.last_symbol_config != transition_symbols
    )

    # Update matrix structure when configuration changes
    if state_changed or symbols_changed:
        new_matrix = pd.DataFrame(
            index=state_labels,
            columns=transition_symbols
        )
        
        # Preserve existing values where possible
        common_states = new_matrix.index.intersection(
            st.session_state.transition_matrix.index
        )
        common_symbols = new_matrix.columns.intersection(
            st.session_state.transition_matrix.columns
        )
        
        for state in common_states:
            for symbol in common_symbols:
                new_matrix.loc[state, symbol] = st.session_state.transition_matrix.loc[state, symbol]

        st.session_state.transition_matrix = new_matrix
        st.session_state.last_state_config = (num_states, state_labels.copy())
        st.session_state.last_symbol_config = transition_symbols.copy()

    # Interactive editor
    edited_matrix = st.data_editor(
        st.session_state.transition_matrix,
        key="matrix_editor",
    )

    # Maintain logical state labels in background
    if num_states > 0 and '⏸️ No states defined' in edited_matrix.index:
        edited_matrix = edited_matrix.drop('⏸️ No states defined', errors='ignore')
    
    if transition_symbols and '⏸️ No symbols defined' in edited_matrix.columns:
        edited_matrix = edited_matrix.drop('⏸️ No symbols defined', axis=1, errors='ignore')

    st.session_state.transition_matrix = edited_matrix

if __name__ == "__main__":
    main()