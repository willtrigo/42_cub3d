# 42_cub3d


- [x] Display different wall textures (the choice is yours) that vary depending on which
side the wall is facing (North, South, East, West).
- [x] Your program must be able to set the floor and ceiling colors to two different ones
- [x] The left and right arrow keys of the keyboard must allow you to look left and
right in the maze.
- [x] The W, A, S, and D keys must allow you to move the point of view through
the maze.
- [x] Pressing ESC must close the window and quit the program cleanly.
- [x] Clicking on the red cross on the window’s frame must close the window and
quit the program cleanly

- Your program must take as a first argument a scene description file with the .cub
extension
  - [ ] config file
    - [ ] Except for the map content, each type of element (color or texture line) can be separated by one or
more empty line(s)
    - [ ] Except for the map content which always has to be the last, each type of
element can be set in any order in the file.
    - [ ] Except for the map, each type of information from an element can be separated
by one or more space(s).
  - [ ] build map
    - [ ]  The map must be parsed as it looks in the file. Spaces are a valid part of the
map and are up to you to handle. You must be able to parse any kind of map,
as long as it respects the rules of the map
    - [ ] Take player position and direction (N, E, S, W)
  - [ ] validation
    - [X] cofig file extension should be .cub
    - [X] validate elements (color line and texture line)
    - [X] If any misconfiguration of any kind is encountered in the file, the program
must exit properly and return "Error\n" followed by an explicit error message
of your choice.
    - [ ] The map must be composed of only 6 possible characters: 0 for an empty space,
1 for a wall, and N,S,E or W for the player’s start position and spawning
    - [ ] The map must be closed/surrounded by walls, if not the program must return
an error.
- [ ] Do not leak nor segfault

Bonus

- [ ] Wall collisions.
- [ ] A minimap system.
- [ ] Doors which can open and close.
- [ ] animated sprite.
- [ ] Rotate the point of view with the mouse
