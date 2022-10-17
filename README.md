# Deepak's Algorithm

Introduction
Deepak's algorithm is a generic idea. It applies to the following class of problems:

      You are given array Arr of length N and Q queries. Each query is represented by two numbers L and R, and it asks you to compute some function Func with subarray Arr[L..R] as its argument.
      
      
For the sake of brevity we will denote Func([L, R]) as the value of Func on subarray Arr[L..R].
If this sounds too abstract, let’s look at specific example:

       There is an integer array Arr of length N and Q queries. For each i, query #i asks you to output the sum of numbers on subarray [Li, Ri], i.e. Arr[Li] + Arr[Li + 1] + … + Arr[Ri].
       
       
Here we have Func([L, R]) = Arr[L] + Arr[L + 1] + ... + Arr[R].

This does not sound so scary, does it? You’ve probably heard of solutions to this problem using Segment Trees or Binary Indexed Trees, or even prefix sums.

Mo’s algorithm provides a way to answer all queries in O((N + Q) * sqrt(N) * F) time with at least O(Q) additional memory. Meaning of F is explained below.

The algorithm is applicable if all following conditions are met:

        Arr is not changed by queries;

        All queries are known beforehand (techniques requiring this property are often called “offline algorithms”);

        If we know Func([L, R]), then we can compute Func([L + 1, R]), Func([L - 1, R]), Func([L, R + 1]) and Func([L,          R - 1]), each in O(F) time.
        
        
        
Arr is not changed by queries;
All queries are known beforehand (techniques requiring this property are often called “offline algorithms”);
If we know Func([L, R]), then we can compute Func([L + 1, R]), Func([L - 1, R]), Func([L, R + 1]) and Func([L, R - 1]), each in O(F) time.

Basic overviewoverview
We have Q queries to answer. Suppose we answer them in order they are asked in the following manner:

               for i = 0..Q-1:

               L, R = query #i

                for j = L..R:

               do some work to compute Func([L, R])
               
               
               
This can take Ω(N * Q) time. If N and Q are of order 105, then this would lead to time limit exceeded.

But what if we answer queries in different order? Can we do better then?

Definition #1:
Segment [L, R] is a continuous subarray Arr[L..R], i.e. array formed by elements Arr[L], Arr[L + 1], …, Arr[R]. We call L left endpoint and R right endpoint of segment [L, R]. We say that index i belongs to segment [L, R] if L ≤ i ≤ R.

Notation

Throughout this tutorial “x⁄y” will mean “integer part of x divided by y”. For instance, 10⁄4 = 2, 15⁄3 = 5, 27⁄8 = 3;
By “sqrt(x)” we will mean “largest integer less or equal to square root of x”. For example, sqrt(16) = 4, sqrt(39) = 6;
Suppose a query asks to calculate Func([L, R]). We will denote this query as [L, R] - the same way as the respective argument to Func;
Everything is 0-indexed.
We will describe Mo’s algorithm, and then prove its running time.


This can take Ω(N * Q) time. If N and Q are of order 105, then this would lead to time limit exceeded.

But what if we answer queries in different order? Can we do better then?

Definition #1:
Segment [L, R] is a continuous subarray Arr[L..R], i.e. array formed by elements Arr[L], Arr[L + 1], …, Arr[R]. We call L left endpoint and R right endpoint of segment [L, R]. We say that index i belongs to segment [L, R] if L ≤ i ≤ R.

Notation

Throughout this tutorial “x⁄y” will mean “integer part of x divided by y”. For instance, 10⁄4 = 2, 15⁄3 = 5, 27⁄8 = 3;
By “sqrt(x)” we will mean “largest integer less or equal to square root of x”. For example, sqrt(16) = 4, sqrt(39) = 6;
Suppose a query asks to calculate Func([L, R]). We will denote this query as [L, R] - the same way as the respective argument to Func;
Everything is 0-indexed.
We will describe Mo’s algorithm, and then prove its running time.


Time complexitycomplexity
Let’s view Arr as a union of disjoint segments of size BLOCK_SIZE, which we will call “blocks”. Take a look at the picture for better understanding:

Suppose we’ve just started processing queries from Qr for some r, and we’ve already answered first (following Mo’s order) query from it. Let that query be [L, R0]. This means that now mo_right = R0.

Let R0, R1, ..., R|Qr| - 1 be right endpoints of queries from Qr, in order they appear in Mo’s order. From proposition #3 we know that

   R0 ≤ R1 ≤ R2 ≤ … ≤ R|Qr| - 1

Changes to mo_right

From proposition #2 and definition of Qr we know that

   r * BLOCK_SIZE ≤ L

Since right endpoint is not lower that left endpoint (i.e. L ≤ R), we conclude that

   r * BLOCK_SIZE ≤ R0

We have N elements in Arr, so any query has right endpoint less than N. Therefore,

   R|Qr| - 1 ≤ N - 1

Since R’s are not decreasing, the total amount of times mo_right changes is

   R|Qr| - 1 - R0 ≤ N - 1 - r * BLOCK_SIZE = O(N)

(we’ve substituted R|Qr| - 1 with its highest possible value, and R0 with its lowest possible value to maximize the subtraction).

There are O(sqrt(N)) different values of r (proposition #1), so in total we will have O(N * sqrt(N)) changes, assuming that we’ve already started from the first query of each Qr.

Now suppose we’ve just ended processing queries from Qr and we must process first query from Qr + 1 (assuming that it is not empty. If it is, then choose next non-empty set). Currently, mo_right is constrained to be:

   r * BLOCK_SIZE ≤ mo_right ≤ N - 1

Let the first query from Qr + 1 be [L', R']. We know (similarly to previous paragraph) that

   (r + 1) * BLOCK_SIZE ≤ R' ≤ N - 1

Hence, mo_right must be changed at most

   max(|r * BLOCK SIZE - (N - 1)|, N - 1 - (r + 1) * BLOCK SIZE)

times (we took lowest value of mo_right with highest value of R’ and vice-versa). This is clearly O(N) (and it does not matter whether it is r+1’th set of r+k’th for some k > 1).

There are O(sqrt(N)) switches from r to r + 1 (and it's true even if we skip some empty sets), so in total we will have O(N * sqrt(N)) mo_right changes to do this.

There are no more cases when mo_right changes. Overall, we have O(N * sqrt(N)) + O(N * sqrt(N)) = O(N * sqrt(N)) changes of mo_right.

Corollary #3: All mo_right changes combined take O(N * sqrt(N) * F) time (because each change is done in O(F) time).

Theorem #2:

Mo_left changes its value O(Q * sqrt(N)) times throughout the run of Mo’s algorithm.

Proof:

Suppose, as in the proof of Theorem #1, we’ve just started processing queries from Qr for some r, and currently mo_left = L, mo_right = R0, where [L, R0] ∈ Qr. For every query [L', R'] ∈ Qr by definition #2 and proposition #2 we have:

   r * BLOCK_SIZE ≤ L' ≤ (r + 1) * BLOCK_SIZE - 1

So, when we change mo_left from one query to other (both queries ∈ Qr), we must do at most

   (r + 1) * BLOCK_SIZE - 1 - r * BLOCK_SIZE = BLOCK_SIZE - 1 = O(sqrt(N))

changes to mo_left. At the picture below we represented leftpoints that lie in block #r, where the subscript shows relative order of queries: 





There are |Qr| queries in Qr. That means, that we can estimate upper bound on number of changes for single r as O(|Qr| * sqrt(N)). Let’s sum it over all r:

   O(sqrt(N) * (|Q0| + |Q1| + ... + |QK|)) = O(sqrt(N) * Q)

(because each query's leftpoint belongs to exactly one block, and we have Q queries in total).

Now suppose we’re done with queries from Qr and want to process queries from non-empty set Qr + k (for some k > 0). Any query [L', R'] ∈ Qr + k has

   (r + k) * BLOCK_SIZE ≤ L' ≤ (r + k + 1) * BLOCK_SIZE - 1

Similarly, any query [L, R] ∈ Qr has

   r * BLOCK_SIZE ≤ L ≤ (r + 1) * BLOCK_SIZE - 1

We can see that the maximum number of changes needed to transit from some query from Qr to some query from Qr + k is

   (r + k + 1) * BLOCK_SIZE - 1 - r * BLOCK_SIZE = k * BLOCK_SIZE - 1

Now if we sum this over all r, we will get at most

   K * BLOCK_SIZE = O(sqrt(N)) * O(sqrt(N)) = O(N),

because sum of all possible k’s does not exceed K.

There are no more cases when mo_left changes. Overall, we have O(sqrt(N) * Q) + O(N) = O(sqrt(N) * Q) changes of mo_left.

Corollary #4: All mo_left changes combined take O(Q * sqrt(N) * F) time (because each change is done in O(F) time).

Corollary #5: Time complexity of Mo’s algorithm is O((N + Q) * sqrt(N) * F).


Example problemproblem

           You have an array Arr of N numbers ranging from 0 to 99. Also you have Q queries [L, R]. For each such query            you must print

            V([L, R]) = ∑i=0..99 count(i)2 * i

            where count(i) is the number of times i occurs in Arr[L..R].
            
            
            

