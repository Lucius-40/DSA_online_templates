import heapq
from collections import defaultdict

def second_shortest_paths(graph, s, n):
    """
    Compute shortest (dist1) and second shortest (dist2) distances from s to all nodes.
    
    Args:
    - graph: list of lists [(neighbor, weight), ...] for each node (size n).
    - s: source node index.
    - n: number of nodes.
    
    Returns:
    - dist1: list of shortest distances.
    - dist2: list of second shortest distances (inf if none).
    """
    dist1 = [float('inf')] * n
    dist2 = [float('inf')] * n
    dist1[s] = 0
    
    # Priority queue: (distance, node)
    pq = [(0, s)]
    
    while pq:
        d, u = heapq.heappop(pq)
        
        # Skip if this is worse than our known second best for u
        if d > dist2[u]:
            continue
        
        # Relax all neighbors
        for v, w in graph[u]:
            alt = d + w
            
            if alt < dist1[v]:
                # New shortest: shift old shortest to second
                dist2[v] = dist1[v]
                dist1[v] = alt
                heapq.heappush(pq, (alt, v))
            elif dist1[v] < alt < dist2[v]:
                # Better second shortest (strictly > dist1)
                dist2[v] = alt
                heapq.heappush(pq, (alt, v))
            # Note: If alt == dist1[v], do nothing (not strictly longer)
    
    return dist1, dist2
