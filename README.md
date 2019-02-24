# Reagents.C++ [![Build Status](https://travis-ci.org/polytypic/reagents.cpp.svg?branch=master)](https://travis-ci.org/polytypic/reagents.cpp)

This is my _hobby_ programming project with the goal to implement Reagents for
C++.

<blockquote>
<a target="_blank" href="http://aturon.github.io/academic/reagents.pdf">Reagents: expressing and composing fine-grained concurrency</a></br>
<a target="_blank" href="https://aturon.github.io/">Aaron Turon</a></br>
<a target="_blank" href="https://github.com/aturon/ChemistrySet/">in Scala</a>
</blockquote>

Note that I have no plans to invest time in turning anything in this project
into reusable libraries and I make absolutely no promises of any kind regarding
the future of this project.

## Plan

- Implement both
  [MCS lock](http://web.mit.edu/6.173/www/currentsemester/readings/R06-scalable-synchronization-1991.pdf)
  based CASN and
  [RDCSS](https://www.cl.cam.ac.uk/research/srg/netos/papers/2002-casn.pdf)
  based CASN in order to be able to compare their performance
- Implement Reagents parameterized with CASN

## References

- [A Practical Multi-Word Compare-and-Swap Operation](https://www.cl.cam.ac.uk/research/srg/netos/papers/2002-casn.pdf)
  - [Lock-Free Linked Lists Using Compare-and-Swap](http://people.csail.mit.edu/bushl2/rpi/portfolio/lockfree-grape/documents/lock-free-linked-lists.pdf)
  - [Easy Lock-Free Indexing in Non-Volatile Memory](http://justinlevandoski.org/papers/mwcas.pdf)
  - [Persistent Multi-Word Compare-and-Swap (PMwCAS) for NVRAM](https://github.com/Microsoft/pmwcas)
- [A Practical Wait-Free Multi-Word Compare-and-Swap Operation](https://www.osti.gov/servlets/purl/1110662)
- [Algorithms for Scalable Synchronization on Shared-Memory Multiprocessors](http://web.mit.edu/6.173/www/currentsemester/readings/R06-scalable-synchronization-1991.pdf)
- [Reagents: expressing and composing fine-grained concurrency](http://aturon.github.io/academic/reagents.pdf)
- [`std::atomic`](https://en.cppreference.com/w/cpp/atomic/atomic)
