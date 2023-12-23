#Week of 2023/12/23
Okay, we've got some basic stuff setup. The next "big" task is to do some work on 
2d fluid simulation. Most of this is just somehow implementing [Navier-Stokes](https://en.wikipedia.org/wiki/Navier%E2%80%93Stokes_equations#:~:text=The%20Navier%E2%80%93Stokes%20equations%20(%2F,and%20mathematician%20George%20Gabriel%20Stokes.) 
equations. These are just pretty computationally intensive. There are two ways we 
can go about this, we can go about particle based fluid simulation, or we can do
the average of neighbors approach. There are two references I've found on
YouTube for those so far
1. [Particles](https://youtu.be/rSKMYc1CQHE?si=wc-2geFawf84RUVQ)
2. [Average of grids](https://youtu.be/qsYE1wMEMPA?si=dsqSyP_B3I5yN6em)

Both of them have a lot of papers referenced in the descriptions which I guess
we could read? [This
one](http://graphics.cs.cmu.edu/nsp/course/15-464/Fall09/papers/StamFluidforGames.pdf) was presented at GDC 2004

[ ] Look at [liquidfun](https://google.github.io/liquidfun/)
[ ] Try to do a simple version yourself of the above paper

===========================================================
# Week of 2023/12/22
Making progress here. Still getting some of the basics down.

[x] Do basic drawing
[x] Animate via sprite map
[x] Move sprite guy with controller
[x] Build a bit collision logic


## Dev progress notes

In the current project, `guy` is kind of this omni entity that has all of it's components baked in.
We probably don't really want that if we have more than one thing rendered to the screen. Something
like an [entity component system](https://austinmorlan.com/posts/entity_component_system/) might make sense

I play the sprite animation on A being pressed which I mapped in ares to the a key. It's a little janky
but it works pretty stinking well if I do say so myself. For some reason there is filler that my sprite has
meaning I have to multiply it's index by 2; that could be a result of how I got it in there but not sure.

Okay, for physics there are really two paths.
1. Write your own
2. Use a library.

There are libraries, here is one used a lot in [game jams](https://box2d.org) so I'm going to start with that. 

===========================================================
