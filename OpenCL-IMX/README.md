# OpenCL Overview on iMX

A short statement can define OpenCL as a `low-level` language for `high-performance`
heterogeneous data-parallel computation. `Low-level` means that as lower it gets the
effort increases, and the user/developer is forced to handle the entire code by itself.
For insuring a `high-performance` the code must be matched to the hardware, with that
we can really get a strong performance leveraging the hardware into its maximum power
processing.

`Heterogenous` is an often concept to describe a system that supports (run across) multiples
types of devices, currenty we can compile identical codes using `OpenCL` to run on GPUs,
and although it was developed for GPUs, it has found a use in CPUs, and even FPGAs.
Data-parallel is a model of parallelism, and as GPUs are set for it, `OpenCL` has it at
its best feature distributing data across different nodes, which operate on the data in
parallel.

This framework specifies programming languages based on `C99`, `C++11`, it means the code
can be written in programming languages as C, C++ which are similar to this standards. It's
possible to write them and compile it at runtime, or get compiled binaries already to shorten
the preparations. This typical way of coding has its issues, it is not very user friendly,
and also it is not portable across devices. That's the reason `OpenCL` offers a unified parallel
programming model across heterogeneous devices while abstracting away many implementation details.

To be continued.


