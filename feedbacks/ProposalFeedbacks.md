### Grade 
Incomplete (0%), must resubmit for regrade. 

### Comments 
**Leading questions** Well-written, it is clear to me what type of question you are trying to solve. 

**Dataset** Well-described, the only thing that is missing is a description of the edges. Are the edges directed? Weighted? If so, what are the directions and weights? In particular,
if some of this information is not readily available in the dataset, what are the steps you would take to fill in that information. As an example, it is not uncommon to use the distance
between two airports as the weight of the edge connecting those two airports, but since OpenFlights doesn't provide that information directly, one needs to use the GPS coordinates
between two airports to calculate that distance. 

**Algorithms** This is the major reason that you are getting a 0. The two algorithms you proposed look fine, but what about DFS/BFS? You need to select one from these two, and describe 
it the same way you described the other two. Speficially, this means you need to specify the input, output, run time, and preferrably a brief discussion on some implementation details.

**Timeline** Looks fine to me. 
