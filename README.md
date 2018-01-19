# shapeSignature
Shape signature using centroid function.

## shape comparison
Several techniques to compare shapes are available. Simplest and most popular ones are 1D functions which represent the shape signatures. The function represents the variation of
one specific characteristic of the shape. This can be:
- Complex coordinates
- Centroid distance function
- Tangent angle
- Contour curvature
- Area function
- Triangle area representation
- Chord length function
More approaches to specify polygons are available, simplifying their comparison depending on the purpose.

## shape signature
The implemented signature is centroid distance function. This signature was chosen due of its simplicity and because it also targets concave polygons without needing to specify any special
cases. It returns an array of distances to the center of a set of equally spaced contour points. This signature function is translation independent and, if the shape is normalized, it can be scale
independent as well. Comparing polygons with the same shape but different rotations may require to shift one of the distance arrays in order for them to match.
In order to simplify calculations and save memory, the function does not perform the distance to the centroid calculation for all equally spaced contour points. Instead, it calculates distances to the centroid only for each polygon vertex as well as its distance to the previous vertex. 
This way, only the vertices distances to the centroid are computed, ignoring all other contour points that constitute the sides of the polygon.
