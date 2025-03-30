import streamlit as st
import pandas as pd
import re

def extract_state_number(state):
    """Extracts the numeric part from a state string like 'q3'."""
    match = re.match(r"q(\d+)", str(state))
    return int(match.group(1)) if match else -1

def main():
    st.title("DFA Simulator")

    # Number of states input
    num_states = st.number_input("Enter number of states:", min_value=0, max_value=10, value=0)

    # Generate initial state names
    states = [f"q{i}" for i in range(num_states + 1)]
    
    # Define alphabet
    text = st.text_input("Enter unique alphabet:")
    alphabet = list(''.join(text.split()))

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
                help="State names follow the format q{number}.",
                default=f"q{num_states+1}",  # Dynamically sets default for new rows
                max_chars=10,
                validate=r"^q\d+$",
            )
        },
        num_rows="dynamic",
        hide_index=True,
    )

    # **Find the max q{number} from the edited table**
    if "state" in edited_data.columns and not edited_data.empty:
        state_numbers = edited_data["state"].apply(extract_state_number)
        max_state = state_numbers.max() if not state_numbers.empty else -1
        num_states = max_state  # Update num_states to reflect the highest q{number}
    else:
        num_states = 0  # Reset if table is empty

    st.write("Updated Data:")
    st.write(edited_data)
    st.write(f"Updated Number of States: {num_states}")

if __name__ == "__main__":
    main()
