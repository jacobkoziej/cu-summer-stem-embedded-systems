# Shift Registers

*Why worry about IO when you can throw more at the problem?*

## Outline

- Shift registers

## Exercises

1. Take your quad seven-segment project and port it over to AVR C.
   Instead of setting the state of each segment individually, map them to PORT D so that they can all update in one write.
2. Now, take your code from the previous exercise, but instead use a shift register to control the individual segments.
