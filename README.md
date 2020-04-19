---
title: Luv + ReasonML, the Straight Dune Build
published: false
description: Debugging the build system
tags: reason, dune, ocaml, esy, spin
series: ReasonML, Dune, Pesy and Spin
---

I am trying to use the [aantron/luv](https://github.com/aantron/luv) library to try to build something and I ran into all kinds of build system issues mostly because I still haven't grokked the reason-native build system yet. That's ok. This note is my way of getting better and having a reference I understand when I need to come back to it. The `reason-native` build environment has a list of great tools you can use. Most prominent among them are [`Dune`](https://dune.build), [`Esy/Pesy`](https://github.com/esy/pesy) and [`Spin`](https://github.com/tmattio/spin). The last two use `dune` so you end up learning about `dune` whatever you do.

Let's start with `dune`. Assuming you have `opam` and `dune` installed this is easy. Go [here](https://opam.ocaml.org) if you don't then head back.

Make a directory and `cd` into it.

```sh
mkdir straight-dune-luv && cd straight-dune-luv
```

Add a `.gitignore` file for `ocaml` using the [gitignore-cli](https://docs.gitignore.io/install/command-line).

```sh
gi ocaml > .gitignore
```

Create a switch with `ocaml 4.08.1`. `luv` requires at least that.
```sh
opam switch create . ocaml-base-compiler.4.08.1
```

Add `reason` and `luv`. `dune` will tell you nicely if you forget to do this.

```sh
opam install reason luv
```

Create you `dune` file and run install.

```sh
touch dune && dune install
```
Create a `Makefile`, optional. I just copied the one from a previous post [here](https://dev.to/idkjs/the-postman-rides-ocaml-part-1-2a44). 

```sh
touch Makefile
```
Which didn't work because of the tabs being off from the paste. Ran `cat -e -t -v Makefile` which I found on [`stackoverflow`](https://stackoverflow.com/questions/16931770/makefile4-missing-separator-stop).

Add the code from [aantron/luv/example/progress.ml](https://github.com/aantron/luv/blob/master/example/progress.ml).

```sh
touch progress.ml
```

Convert it to `.re` and delete the `.ml` version.
```sh
bsrefmt --parse ml progress.ml --print re > progress.re
rm progress.ml
```

Run `make` to build it.

```sh
make
```

Run `progress.exe`.

```sh
dune exec ./progress.exe
```

Output:

```
❯ dune exec ./progress.exe
33%                  
66%
Done
```

Honestly, that was very easy. This has to be your go to build for a simple project.

Let's try with `Pesy` next.

```sh
mkdir straight-ocaml-luv && cd straight-ocaml-luv
opam install reason luv
opam switch create . ocaml-base-compiler.4.08.1
touch dune && dune install
touch Makefile
touch progress.ml
bsrefmt --parse ml progress.ml --print re
dune
cat -e -t -v Makefile
dune build @install
make
dune exec ./progress.exe
```