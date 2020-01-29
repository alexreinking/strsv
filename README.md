# STRSV

![Test workflow](https://github.com/alexreinking/strsv/actions/workflows/test.yml/badge.svg)

This repository is a companion to my blog
post, ["Building a Faster Triangular Solver than MKL"](https://alexreinking.com/blog/building-a-faster-triangular-solver-than-mkl.html)
where I explain how I discovered a triangular solver that beats MKL (on
multiple-of-8 matrix sizes, on AVX2, single-threaded). The code for that solver,
as well as a proof-of-concept divide-and-conquer solver, is here. It should be
compiled with GCC or Clang on Linux. The GHA workflow should be your guide to
trying this out locally.

Note that if you have a CPU with AVX-512 support, you will likely see BLAS
perform _much_ better than my implementation. This is meant to be educational.

Please read the blog post for the full story and context of this repository.

---

If this example helps you with your work, consider saying thank you by buying me
a coffee!

[![Buy me a coffee](https://img.buymeacoffee.com/button-api/?text=Buy%20me%20a%20coffee&emoji=&slug=alexreinking&button_colour=40DCA5&font_colour=ffffff&font_family=Lato&outline_colour=000000&coffee_colour=FFDD00)](https://www.buymeacoffee.com/alexreinking)
