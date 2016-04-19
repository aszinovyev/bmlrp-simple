Simple implicit implementation of Binary Multi-Level Routing Protocol ([paper](https://github.com/aszinovyev/bmlrp))

[Screenshots](pics/)

Generate the Average Node Degree figure from the paper:

    $ R
    > source('paper.r')

Run manually:
  
    R
    > source('control.r')
    
    # Distribute 10 nodes uniformly on a [0;1]x[0;1] map;
    # connect those pairs of nodes that have distance less that r = 1.5 / sqrt(10). 
    # If you change number of nodes, but leave the second parameter constant, 
    # the average node degree will stay approximately the same.
    Random(10, 1.5, 0, label=5)
    
    # Similar to the previous one, but makes a larger graph, with larger average node degree. 
    # Also, vertex.size=3 makes the nodes smaller (default is 15).
    Random(1024, 2.3, 0, vertex.size=3)
    
    # Same as above, but also randomly connect 10% of the nodes
    # independently from their location
    Random(1024, 2.3, 0.1, vertex.size=3)
    
    # Build two types of level-1 graphs
    Random(10, 1.5, 0, 1, "", label=5)
    
    # Build level-1 graph with nodes that have the first bit 0
    Random(10, 1.5, 0, 1, "0", label=5)
    # Build level-1 graph with nodes that have the first bit 1
    Random(10, 1.5, 0, 1, "1", label=5)
    
    # Build level-2 graph with nodes, whose addresses start with 01
    Random(10, 1.5, 0, 2, "01", label=5)
    
    # Create a graph, but do not draw it
    Random(10, 1.5, 0, draw=F)
    
    # Draw a graph, but arrange the positions of nodes automatically by igraph package
    Random(10, 1.5, 0, label=5, layout=F)
    
    # Set different seed
    SetSeed(42)
    # Set default seed
    ResetSeed()
