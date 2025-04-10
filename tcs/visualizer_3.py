import streamlit as st
import pandas as pd
import numpy as np
import re
import time

def main():
    st.title("DFA Simulator")

    # --- State Configuration ---
    num_states = st.slider(
        label="Number of states:",
        min_value=0, max_value=10, value=0,  # default > 0 for testing
        key="num_states"
    )
    state_labels = (
        [f'q{i}' for i in range(num_states)]
        if num_states > 0 
        else ['⏸️ No states defined']
    )
    st.session_state.show_warning = False

    # --- Alphabet Configuration ---
    alphabet_input = st.text_input(
        label="Input symbols:",
        key="alphabet_input",
        help="Only accept letters (A-Z, a-z) and digits (0-9), e.g: aB01"
    )
    transition_symbols = (
        [ch for ch in ''.join(alphabet_input.split()) if re.match(r'[A-Za-z0-9]', ch)]
        if alphabet_input 
        else ['⏸️ No symbols defined']
    )

    # --- Initialize Matrix in Session if needed ---
    if "transition_matrix" not in st.session_state:
        st.session_state.transition_matrix = pd.DataFrame(
            index=state_labels,
            columns=transition_symbols
        )
        st.session_state.cache_matrix = st.session_state.transition_matrix.copy()
        st.session_state.last_state_config = (num_states, state_labels.copy())
        st.session_state.last_symbol_config = transition_symbols.copy()

    # --- Detect Configuration Changes ---
    state_changed = st.session_state.last_state_config != (num_states, state_labels)
    symbol_changed = st.session_state.last_symbol_config != transition_symbols
    structure_changed = state_changed or symbol_changed

    # --- Update Matrix only if configuration has changed ---
    if structure_changed:
        st.session_state.cache_matrix = st.session_state.transition_matrix.copy()
        new_matrix = pd.DataFrame(index=state_labels, columns=transition_symbols)
        old_matrix = st.session_state.cache_matrix

        # Preserve existing values if keys are shared
        shared_states = new_matrix.index.intersection(old_matrix.index)
        shared_symbols = new_matrix.columns.intersection(old_matrix.columns)
        for state in shared_states:
            for symbol in shared_symbols:
                new_matrix.loc[state, symbol] = old_matrix.loc[state, symbol]

        st.session_state.show_warning = True
        st.session_state.cache_matrix = new_matrix

    # --- Define Column Config for Selectboxes ---
    column_config = {}
    if ('⏸️ No symbols defined' not in transition_symbols
        and '⏸️ No states defined' not in state_labels):
        for symbol in transition_symbols:
            column_config[symbol] = st.column_config.SelectboxColumn(
                label=symbol,
                help=f"Transition on '{symbol}'",
                options=state_labels,
                required=False
            )

    # --- Show Interactive Editor ---
    edited_matrix = st.data_editor(
        st.session_state.cache_matrix, #st.session_state.transition_matrix,
        key="matrix_editor",
        column_config=column_config,
        use_container_width=True,
    )

    # --- Cleanup Placeholder States/Symbols ---
    if num_states > 0 and '⏸️ No states defined' in edited_matrix.index:
        edited_matrix = edited_matrix.drop('⏸️ No states defined', errors='ignore')
    if transition_symbols and '⏸️ No symbols defined' in edited_matrix.columns:
        edited_matrix = edited_matrix.drop('⏸️ No symbols defined', axis=1, errors='ignore')

    # --- Detect if there are any changes in the matrix ---
    def matrix_has_changed(old_matrix, new_matrix):
        old_matrix_filled = old_matrix.fillna(0)  # Replace NaN with 0
        new_matrix_filled = new_matrix.fillna(0)  # Replace NaN with 0
        return not old_matrix_filled.equals(new_matrix_filled)

    matrix_changed = matrix_has_changed(st.session_state.cache_matrix, edited_matrix)
    config_changed = matrix_changed or structure_changed

    if config_changed:
        st.session_state.show_warning = True

    # --- Save Edited Matrix ---
    confirm = st.button("Confirm", type="primary")
    if confirm:
        progress_text = "Operation in progress. Please wait."
        my_bar = st.progress(0, text=progress_text)
        for percent_complete in range(100):
            time.sleep(0.000001)
            my_bar.progress(percent_complete + 1, text=progress_text)
        time.sleep(1)
        my_bar.empty()

        st.session_state.transition_matrix = edited_matrix
        st.session_state.last_state_config = (num_states, state_labels.copy())
        st.session_state.last_symbol_config = transition_symbols.copy()
        #st.session_state.last_values_config = st.session_state.transition_matrix.fillna(0).values.copy().tolist()
        st.success('Your change has been saved.', icon="✅")
        st.session_state.show_warning = False
        # if not config_changed: st.info('Nothing has been edited recently', icon="ℹ️")

    if st.session_state.show_warning:
        st.warning("Your edit has not been saved.", icon="⚠️")

if __name__ == "__main__":  
    main()

    # # --- Validation: Detect Invalid Transitions ---
    # invalid_transitions = []
    # for state in edited_matrix.index:
    #     for symbol in edited_matrix.columns:
    #         val = edited_matrix.loc[state, symbol]
    #         if isinstance(val, str) and val and val not in state_labels:
    #             invalid_transitions.append((state, symbol, val))

    # if invalid_transitions:
    #     st.warning(f"⚠️ {len(invalid_transitions)} invalid transition(s) detected. These point to undefined states.")
    #     with st.expander("View invalid transitions"):
    #         for row, col, val in invalid_transitions:
    #             st.write(f"🔸 Transition from `{row}` on symbol `{col}` points to undefined state `{val}`.")
