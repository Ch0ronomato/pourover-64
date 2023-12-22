Making progress here. Still getting some of the basics down.

[x] Do basic drawing
[x] Animate via sprite map
[x] Move sprite guy with controller
[ ] Build a bit collision logic
[ ] Start the rigid body


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
