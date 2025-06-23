# Syllabus

The following is a tentative syllabus for the Summer of 2025.
Please check this site frequently for the most up-to-date information.

## Course Overview

**Instructor:** Jacob Koziej (EE '25)

**Teaching Assistants:** Marco Chen (EE '28), Matthew Jeong (EE '28), Charles Wan (STEM '25)

**Location**: 41 Cooper Square, Room 603 (ICE Lab)

**Time:** Monday--Thursday, 09:00--15:00

**Office Hours:** On request

**Contact:** TEAMs message or email ([`<jacob.koziej@cooper.edu>`])

## Prerequisite Skills

Proficiency in any programming language; this could be something as simple as a block-based language[^snap].

## Course Goals

The ultimate goal of this course is to familiarize you enough with embedded development that you can continue exploring beyond Arduino or move away from embedded as a more informed engineer.
By the end of the summer, you should be able to:

- Identify & establish engineering problem requirements.
- Decompose problems into digestible sub-problems.
- Find and parse datasheets and reference manuals for relevant information.
- Make sense of unfamiliar code.
- Organize a programming project.
- Write clean, effective, and defensive C code.
- Debug with software and hardware.
- Work with others on an engineering problem.
- Understand the social implications of your work.
- Be comfortable with being uncomfortable.

This course aims to address the following [ABET] student outcomes:

1. An ability to identify, formulate, and solve complex engineering problems by applying principles of engineering, science, and mathematics.
2. An ability to apply engineering design to produce solutions that meet specified needs with consideration of public health, safety, and welfare, as well as global, cultural, social, environmental, and economic factors.
3. An ability to communicate effectively with a range of audiences.
4. An ability to recognize ethical and professional responsibilities in engineering situations and make informed judgments, which must consider the impact of engineering solutions in global, economic, environmental, and societal contexts.
5. An ability to function effectively on a team whose members together provide leadership, create a collaborative environment, establish goals, plan tasks, and meet objectives.
6. An ability to develop and conduct appropriate experimentation, analyze and interpret data, and use engineering judgment to draw conclusions.
7. An ability to acquire and apply new knowledge as needed, using appropriate learning strategies.

## Policy

Overall, I am a *very* understanding and flexible person, but please don't force my hand.

### Ask Questions

> The man who asks a question is a fool for a minute, the man who does not ask is a fool for life. (Confucius)

At times, my mind moves too fast for my own good, and I may skip steps.
**If you are confused at any moment for any reason, please stop me.**
I can guarantee you are not the only person in the room feeling that way.
I do understand it may be difficult to come forward with questions in a class environment, so I'll also be providing a real-time anonymous question board you can take advantage of.
Finally, if you're so confused that you cannot compose a meaningful question, **please reach out**, and we'll work together to identify the root of the problem.

### Attendance

Attendance is mandatory.
We'll be starting at 09:00 sharp as starting later is unfair to the students who made an effort to get to class on time.
If you are running late, please inform me at least 15 minutes before the start of class so that I can take note.
In the event of an absence, please inform both me and Dr. Thevenot.

### Course Work

I expect all relevant work from the day to be submitted (even if incomplete).
Work will not be explicitly graded, however, I plan to return a commented diff by the start of the next class.
At the start of each class, we might spend some time reviewing any common errors made in assignments.

### Academic Integrity

**I do not tolerate cheating of any kind.**
If I have reasonable suspicion that you have cheated, I will report you to Cooper Union's administration for a formal review.

It is painfully obvious when I read code that includes code not written by you.
That is not to say you cannot use online resources or LLMs, but I do expect proper attribution.
**If you’re using just a snippet of code, type it out, and if possible, refactor it to fit the flow of your code.**
I intend for such a practice to get you in the habit of understanding the code you read so that you can grow as a programmer.
That said, using larger snippets becomes problematic due to licensing, which could land you in legal trouble!

**tldr:** write everything yourself!

## Course Structure

This course is segmented into three, two-week units.
With the exception of the last unit, we'll try to stick to the following daily schedule:

- 09:00--10:00 - Lecture for background/motivation
- 10:00--12:00 - Interactive lesson
- 12:00--13:00 - Lunch
- 13:00--15:00 - In-class assignment(s)

At the end of each week, we will spend less time on learning and instead focus more on a single-day project.
The goal of this project is to encompass everything we covered during the week but also to prepare you for your open-ended final project.

### Background

In this unit, we'll do a run-through of how to interact with Arduinos.
The first week will primarily focus on the basics of Arduino and useful parts of the C programming language when working in an embedded setting.
In the second week, we'll set up a debugger to effectively navigate timers, interrupts, and communication peripherals.

### C-ing Beyond Arduino

In this unit, we'll leave the Arduino framework behind and will start programming the ATmega328P on the Arduino Uno Rev3 directly.
In the first week, we'll familiarize ourselves with interacting with the ATmega328P without a GUI or libraries; doing so entails becoming comfortable with the terminal, along with reading datasheets and sample code.
In the second week, we'll explore the peripheral systems of the ATmega328P and learn how to work around its limitations.

### Final Project

In this final unit, we'll work on an open-ended two-week final project in small groups.
This project will revolve around using the ATmega328P in a "real world" application where you'll have the chance to work with sensors and hardware not covered in class; however, do keep in mind that some parts have long lead times.
We'll also have drop-in lessons as necessary to ensure we finish in time for the final showcase.

## Student Resources

**Accommodations:** <https://cooper.edu/students/student-affairs/disability>

**Mental Health Services:** <https://cooper.edu/students/student-affairs/health/counseling>

**Title IX:** <https://cooper.edu/students/student-affairs/sexual-misconduct>

[^snap]: I actually got started programming Arduinos with only a background in [Snap!]

[abet]: https://abet.org
[snap!]: https://snap.berkeley.edu
[`<jacob.koziej@cooper.edu>`]: mailto:jacob.koziej@cooper.edu
