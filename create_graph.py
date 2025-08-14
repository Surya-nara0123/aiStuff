import random
import string

def generate_random_graph(filename, num_nodes=5, num_edges=7, weighted=False):
    """
    Generate a random graph and write it to a text file.
    Uses letters for node names, but two nodes are replaced by 'S' and 'G'.

    Parameters:
    filename (str): Output text file name.
    num_nodes (int): Number of nodes in the graph (>= 2).
    num_edges (int): Number of edges in the graph.
    weighted (bool): If True, edges will have random weights.
    """

    if num_nodes < 2:
        raise ValueError("Graph must have at least 2 nodes for S and G.")

    if num_nodes > 26:
        raise ValueError("Maximum 26 nodes supported with letter names.")

    # Generate letter node names
    nodes = list(string.ascii_uppercase[:num_nodes])

    # Choose two positions to be S and G
    s_index, g_index = random.sample(range(num_nodes), 2)
    nodes[s_index] = "S"
    nodes[g_index] = "G"

    # Ensure edges don't exceed possible unique pairs
    max_edges = num_nodes * (num_nodes - 1) // 2
    num_edges = min(num_edges, max_edges)

    # Generate all possible edges (undirected, no self-loops)
    possible_edges = [(u, v) for i, u in enumerate(nodes) for v in nodes[i+1:]]
    
    # Pick random edges
    chosen_edges = random.sample(possible_edges, num_edges)

    # Generate heuristic values (estimation to goal) — smaller for closer nodes
    heuristics = {}
    for node in nodes:
        if node == "G":
            heuristics[node] = 0
        else:
            heuristics[node] = random.randint(1, 20)  # heuristic range 1–20

    # Write graph to file
    with open(filename, "w") as f:
        f.write(f"{num_nodes} {num_edges}\n")
        for u, v in chosen_edges:
            if weighted:
                weight = random.randint(1, 10)  # weight range 1-10
                f.write(f"{u} {v} {weight}\n")
            else:
                f.write(f"{u} {v}\n")

        if weighted:
            # Append heuristic values
            for node, h_val in heuristics.items():
                f.write(f"{node} {h_val}\n")

    print(f"Graph with heuristics saved to {filename}")


# Example usage:
# Without weights (still assigns heuristic)
generate_random_graph("graph_unweighted.txt", num_nodes=6, num_edges=8, weighted=False)

# With weights
generate_random_graph("graph_weighted.txt", num_nodes=6, num_edges=8, weighted=True)
