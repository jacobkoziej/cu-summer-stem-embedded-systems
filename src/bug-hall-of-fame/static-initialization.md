# Static Initialization

While working through our quadrature encoder activity, I gave a hint to the class that by applying a bitwise XOR to channels A and B on a [`CHANGE` interrupt], you could quickly determine the direction of rotation.
The trouble started soon thereafter with three different situations:

- the encoder step count could increment or decrement
- the encoder step count only increments or decrements, but not both
- or the encoder step count would oscillate around a value.

What I'd like to do is introduce two similar, but *very* different acting bits of code:

#### [`static.cc`]

```cpp
{{#include static-initialization.d/static.cc:6:}}
```

#### [`int.cc`]

```cpp
{{#include static-initialization.d/int.cc:6:}}
```

---

In this case, [`int.cc`] works while [`static.cc`] does not!

## A Deep Dive

The astute reader may have already spotted the mistake; I for one did not on my first time around.[^tunnel-vission]
Part of why this code had me pulling my hair out was the expression `steps += A ^ B ? 1 : -1`, which did different things between people in the class.
Initially, I suspected some strange integer promotion being done by the compiler, but this necessitated a deeper analysis!

### Assembly Output

What I ended up doing was extracting *some* of the [compilation flags from the Arduino AVR core] and [manually compiling] a code sample with `avr-g++`.
Conveniently, GCC offers the `-S` and `-fverbose-asm` flags, which output assembly and add verbose assembly comments, respectively.
Throwing this together, we get the following (unoptimized) output for a subset of `channel_a_isr`:

#### [`static.s`]

```
{{#include static-initialization.d/static.s:60:136}}
```

#### [`int.s`]

```
{{#include static-initialization.d/int.s:43:85}}
```

This output can be hard to interpret if you've never read or written assembly before, but I'd like to draw your attention to one thing: the difference in function body length for the `static` case.
Again, for the seasoned C programmer, this hint might be a dead giveaway; however, let us probe a bit further.

Let's take a closer look at the following block in [`static.s`]:

```
{{#include static-initialization.d/static.s:60:84}}
```

In particular, `cp r24, __zero_reg__` followed by `brne .L2`.

This bit of assembly essentially skips over our call to [`digitalWrite()`] when the byte stored at `_ZGVZ13channel_a_isrvE1A.0_1`[^name-mangling] is a non-zero value.
Unfortunately for us, this byte is always set to `1` following a call to [`digitalWrite()`].
The emission of these instructions stems from the [`static` storage class specifier], the [dynamic initialization of variables with the `static` storage class], and their [storage duration].

## So What Does this Mean?

Converting the C++17 draft to plain English: **initialization of `static` variables in the function scope is done once**.
In particular, the first time the function executes.
What this means for [`static.cc`] is that the values of `A` and `B` do not change following the first invocation of the [`CHANGE` interrupt].
As you can imagine, we can either get stuck counting in one direction, or we have the channel A and B ISRs fighting with one another, and `steps` oscillates![^oscillations]

[^tunnel-vission]: It's crazy what kind of tunnel vision you can have while mortified at the thought of misguiding everyone with a hint!

[^name-mangling]: The reason why our `static` variable `A` has such a strange name is due to C++ name mangling.

[^oscillations]: For the few of you that experienced this bug, you may have noticed that the encoder count slowly changed given enough aggressive spinning of the encoder. Skipped interrupts are to blame!

[compilation flags from the arduino avr core]: https://github.com/arduino/ArduinoCore-avr/blob/1.8.6/platform.txt
[dynamic initialization of variables with the `static` storage class]: https://timsong-cpp.github.io/cppwp/n4659/stmt.dcl#4
[manually compiling]: https://github.com/jacobkoziej/cu-summer-stem-embedded-systems/blob/master/src/bug-hall-of-fame/static-initialization.d/Makefile
[storage duration]: https://timsong-cpp.github.io/cppwp/n4659/basic.stc.static#def:static_storage_duration
[`change` interrupt]: https://docs.arduino.cc/language-reference/en/functions/external-interrupts/attachInterrupt/#parameters
[`digitalwrite()`]: https://docs.arduino.cc/language-reference/en/functions/digital-io/digitalwrite/
[`int.cc`]: https://github.com/jacobkoziej/cu-summer-stem-embedded-systems/blob/master/src/bug-hall-of-fame/static-initialization.d/int.cc
[`int.s`]: https://github.com/jacobkoziej/cu-summer-stem-embedded-systems/blob/master/src/bug-hall-of-fame/static-initialization.d/int.s
[`static.cc`]: https://github.com/jacobkoziej/cu-summer-stem-embedded-systems/blob/master/src/bug-hall-of-fame/static-initialization.d/static.cc
[`static.s`]: https://github.com/jacobkoziej/cu-summer-stem-embedded-systems/blob/master/src/bug-hall-of-fame/static-initialization.d/static.s
[`static` storage class specifier]: https://timsong-cpp.github.io/cppwp/n4659/dcl.stc#4
