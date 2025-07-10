# debugWire

You'll need two Arduino Uno Rev3s.
One will serve as our target, which will get debugged, while the other will act as the actual debugger.
To make this possible, we'll be taking advantage of [`dw-link`] to turn one of the Arduinos into a debugger.

1. Grab the [latest release] of [`dw-link`].
   1. **(Optionally)** Feel free to read the [`dw-link` manual].
2. Compile and upload the sketch to your designated Arduino debugger.
3. [Install] [MiniCore] using the board manager.
4. Set your board to be the MiniCore ATmega328, disable compiler LTO, and optimize sketches for debugging.
5. We have already enabled debugWire on all of the target boards, so it is sufficient to connect pin 8 of the debugger board to the reset pin of the target, along with power and ground to their respective locations.
6. Verify your sketch at least once before starting debugging.

[install]: https://github.com/MCUdude/MiniCore#how-to-install
[latest release]: https://github.com/felias-fogg/dw-link/releases
[minicore]: https://github.com/MCUdude/MiniCore
[`dw-link`]: https://github.com/felias-fogg/dw-link
[`dw-link` manual]: https://github.com/felias-fogg/dw-link/blob/master/docs/manual.md
