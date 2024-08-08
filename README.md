# SortVisualizer

Lets you visualize various sorting algorithms after creating an example dataset.

# Known issues

### Text class

Since this is a UI component, this takes a size proportion vector. Yet this should actually just have the size 
that the text box (localBounds of sf::Text) takes up. Sadly, here I can't figure out how to make this work since 
the UIComponents positioning is handled by the logic implemented in the library (SwiftifySFML).
