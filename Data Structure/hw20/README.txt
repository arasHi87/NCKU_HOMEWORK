# Homework #20

Compare the performance of leftist trees and min heaps under the assumption
that the only operations to be performed are insert and delete min.

For this, do the following:

1. Create a random list of n elements and a random sequence of insert and delete-min operations of length m. The latter
   sequence is created such that the probability of an insert or delete-min operation is approximately 0.5. Initialize a
   min leftist tree and a min heap to contain the n elements in the first random list. Now, measure the time to perform
   the m operations using the min leftist tree as well as the min heap. Divide this time by m to get the average time per
   operation. Do this for n = 100, 500, 1000, 2000, …,5000. Let m be 5000. Tabulate your computing times.
2. Based on your experiments, make some statements about the relative merits of the two priority-queue schemes.

# Technical Specification

1. Perform this experiment, tabulate the result in the homework report.
2. Based on your experiments, make some statements about the relative merits
   of the two priority-queue schemes in the homework report.