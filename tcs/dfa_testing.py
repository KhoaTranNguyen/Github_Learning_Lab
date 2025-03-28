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

dfa = create_dfa(
    states=['q0', 'q1'],
    alphabet=['a', 'b'],
    transitions={
        ('q0', 'a'): 'q1',
        ('q0', 'b'): 'q0',
        ('q1', 'a'): 'q0',
        ('q1', 'b'): 'q1'
    },
    start_state='q0',
    accept_states=['q1']
)
dfa.render('dfa', view=True) 