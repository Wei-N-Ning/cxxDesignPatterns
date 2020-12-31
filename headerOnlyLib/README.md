# Header-Only Library Patterns

## inline variable

### background: c++ 17 the complete guide

c++ 17 introduces the inline global variable that can be defined in the header and included in
multiple translation units.

this is explained in detail in c++ 17 the complete guide book P/24

it works as they advertised;

### the problem of a single global state across multiple layers

however, I wanted to be able to model a **global singleton state** that persists among several translation units or
architecture layers using this feature and it didn't work.

see [inlineState](./inlineState)

the idea is, if I were to provide a scheduler system in the form of a header-only library, can it compose well?

NOTE: the term **compose** is borrowed from Intel's TBB. A simplified explanation is: a library stays aware of its
resource usage (and won't go oversubscription) even when it is invoked by several inter-connected components, such as
a tiered architecture. Example is: A, B and C use library L, and there are functions that directly or indirectly invoke
L's resource-consuming subroutines (such as launching pthreads) that result in nested invocation.

imagine a slightly complex scenario where this scheduler library, `common`, is included by several other
libraries in separate layers:

```text
application (mutate common's global state)
business logic shared lib (mutate common's global state)
utility static lib (mutate common's global state)
common (mutate global state)
```

- will there be any link error (violating one-definition-rule, ODR)?
- will `utility`, `biz-logic` and `app` see the same unique state in the common (scheduler) library?

my experiment shows that, the first concern is resolved by this c++ 17 feature, as all the libraries happily compile
and link to its dependencies;

with the second concern, I see a **strange behavior**: mutating the global state from different layers
gives me inconsistent result;

see [myLibTest.cpp](./inlineState/myLibTest.cpp) for this behavior;

it seems that, even though all the libraries that use `common` see a single definition of its global state, when they
mutate this object, they actually modify a local version of it which does not clash with other local versions
of this "unique global image"

I can not find any explanation to this. But knowing that the inline variable is a replacement to the inline global state
getter:

```
State& getState() {
    static State s{...};
    return s;
}
```

it makes sense that it behaves like a file-scope static object, meaning each file/translation unit has its own copy,
hence modification will not propagate to other translation units or layers.

### going forward with options

I can not use this feature to ship the scheduler library, but I have other options:

#### make it clear that this library does not compose at all

I can still keep it in the header only form, but must make it clear to the end users (particularly library writers) that
this library is supposed to be used in a scoped fashion, and it DOES NOT compose - meaning that if invoked by other
lib that also uses this scheduler it won't be aware of the nested invocation and the inevitable oversubscription.

#### make it a shared library instead

I can also build it as a shared library (similar to how TBB handle this situation). But even this won't perfectly
prevent multiple copies of the global state, such in the case when the user incorrectly links in multiple version of
this shared library.

#### or, just use TBB

