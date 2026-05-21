## What is `bool enter` in menu.c?

### Here is the [Ref](../src/menu.c#L202)

- When the user click on the play button it creates [this] invisible window that
  let create a sort of bound box,
  - we could check if the user clicked any where in the screen

#### but that created a new issue whenever the user click on the play it imdeatly triggers and open the file picker, the rsn was simple by the time the screen draws the menu, the Hitbox were already hitted and so it opens the file pickedr

#

### - To fix this i came up with this idea

- we have the `enter` var that was only true after the full screen was drawn so it was like a seal it didn't let the hitbox triggers unless the whole menu was drawn
