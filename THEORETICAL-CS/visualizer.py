import streamlit as st
import pandas as pd
import numpy as np
import re
import time
from graphviz import Digraph

def create_dfa(states, alphabet, transitions, start_state, accept_states):
    dfa = Digraph()
    dfa.attr(rankdir='LR')  # Horizontal layout

    # Add states
    for state in states:
        if state in accept_states:
            dfa.attr('node', shape='doublecircle')
        else:
            dfa.attr('node', shape='circle')
        dfa.node(state)

    # Start state
    dfa.attr('node', shape='plaintext')
    dfa.node('start', label='')
    dfa.edge('start', start_state)

    # Transitions
    for (src, via), dst in transitions.items():
        dfa.edge(src, dst, label=via)

    return dfa

def main():
    st.set_page_config(layout="wide")
    st.title("DFA Simulator")

    col1, col2 = st.columns([2, 2])

    with col1:
        num_states = st.slider("Number of states:", 0, 10, 0, key="num_states")
        state_labels = [f'q{i}' for i in range(num_states)] if num_states > 0 else ['⏸️ No states defined']

        alphabet_input = st.text_input("Input symbols:", key="alphabet_input", help="Only letters/digits, e.g. aB01")
        transition_symbols = [ch for ch in ''.join(alphabet_input.split()) if re.match(r'[A-Za-z0-9]', ch)] if alphabet_input else ['⏸️ No symbols defined']

        if "transition_matrix" not in st.session_state:
            st.session_state.transition_matrix = pd.DataFrame(index=state_labels, columns=transition_symbols)
            st.session_state.cache_matrix = st.session_state.transition_matrix.copy()
            st.session_state.last_state_config = (num_states, state_labels.copy())
            st.session_state.last_symbol_config = transition_symbols.copy()

        state_changed = st.session_state.last_state_config != (num_states, state_labels)
        symbol_changed = st.session_state.last_symbol_config != transition_symbols
        structure_changed = state_changed or symbol_changed

        if structure_changed:
            new_matrix = pd.DataFrame(index=state_labels, columns=transition_symbols)
            old_matrix = st.session_state.cache_matrix
            shared_rows = new_matrix.index.intersection(old_matrix.index)
            shared_cols = new_matrix.columns.intersection(old_matrix.columns)
            for row in shared_rows:
                for col in shared_cols:
                    new_matrix.loc[row, col] = old_matrix.loc[row, col]
            st.session_state.cache_matrix = new_matrix

        column_config = {}
        if '⏸️ No symbols defined' not in transition_symbols and '⏸️ No states defined' not in state_labels:
            for symbol in transition_symbols:
                column_config[symbol] = st.column_config.SelectboxColumn(
                    label=symbol,
                    help=f"Transition on '{symbol}'",
                    options=state_labels,
                    required=False
                )

        edited_matrix = st.data_editor(
            st.session_state.cache_matrix,
            key="matrix_editor",
            column_config=column_config,
            use_container_width=True,
        )

        if num_states > 0 and '⏸️ No states defined' in edited_matrix.index:
            edited_matrix = edited_matrix.drop('⏸️ No states defined', errors='ignore')
        if transition_symbols and '⏸️ No symbols defined' in edited_matrix.columns:
            edited_matrix = edited_matrix.drop('⏸️ No symbols defined', axis=1, errors='ignore')

        def matrix_has_changed(old_matrix, new_matrix):
            return not old_matrix.fillna(0).equals(new_matrix.fillna(0))

        matrix_changed = matrix_has_changed(st.session_state.cache_matrix, edited_matrix)
        config_changed = matrix_changed or structure_changed

        if config_changed:
            st.session_state.show_warning = True

        confirm = st.button("Confirm", type="primary")
        if confirm:
            my_bar = st.progress(0, text="Saving configuration...")
            for pct in range(100):
                time.sleep(0.000001)
                my_bar.progress(pct + 1, text="Saving configuration...")
            time.sleep(0.2)
            my_bar.empty()

            st.session_state.transition_matrix = edited_matrix
            st.session_state.cache_matrix = edited_matrix.copy()
            st.session_state.last_state_config = (num_states, state_labels.copy())
            st.session_state.last_symbol_config = transition_symbols.copy()
            st.session_state.show_warning = False
            st.success('Configuration saved.', icon="✅")

        if st.session_state.show_warning:
            st.warning("Edits not yet saved.", icon="⚠️")

    with col2:
        st.subheader("DFA Matrix (Transition Table)")
        st.dataframe(st.session_state.transition_matrix.fillna(""), use_container_width=True)

        st.subheader("DFA Configuration")
        start_state = st.selectbox("Start state", state_labels, key="start_state")
        accept_states = st.multiselect("Accepting states", state_labels, key="accept_states")

        transition_dict = {}
        matrix = st.session_state.transition_matrix.fillna("")
        for src in matrix.index:
            for symbol in matrix.columns:
                dst = matrix.at[src, symbol]
                if dst and dst in state_labels:
                    transition_dict[(src, symbol)] = dst

        if st.button("Visualize DFA"):
            dfa_graph = create_dfa(state_labels, transition_symbols, transition_dict, start_state, accept_states)
            st.graphviz_chart(dfa_graph)

if __name__ == "__main__":
    main()
