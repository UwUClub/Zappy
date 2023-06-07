# Zappy

The zappy project is a compilation of 3 different projects, a server, a client and an ai.

## Contents

- [Requirements](#requirements)
- [Communication](#communication)
- [Installation](#installation)
- [Compilation](#compilation)
- [Usage](#usage)
- [Controls](#controls)
- [More Details](#more-details)
- [Testing](#testing)
- [Credits](#credits)
- [License](#license)

## Requirements

- g++ 20+ is required

## Communication

- If you have a bug or an issue, please contact us.

## Installation

### SSH

> G++ 20+ is required
> Other dependencies : Ogre3D, Catch
> Other dependencies are installed automatically if not found

```bash
git clone git@github.com:UwUClub/Zappy.git
```

### HTTPS

Use any tools that can clone by HTTPS, use
```markdown
https://github.com/UwUClub/Zappy.git
```

## Compilation

### Using the script (recommended)

```bash
./build.sh
```
or

```bash
bash build.sh
```

### Using CMake

```bash
mkdir build
cd build
cmake ..
make -j
```

## Usage
- Start the server
```bash
./zappy_server -p <port> -x <width> -y <height> -n <team> [<team>] [<team>] [<team>] ... -c <nb> -f <freq>
```
- Start the graphical client
```bash
./zappy_gui -p <port> -h <hostname>
```
- Start the AI
```bash
./zappy_ai -p <port> -n <team> -h <hostname>
```

If everything is working, you should see a window with a map and maybe more.

## Controls

- Move the camera by pressing right click and moving the mouse.
- Zoom in and out with the mouse wheel.
- Press left shift and left click to rotate the camera around a central point (can be moved, see above)
- Press the space bar to reset the camera.

- Press left click on a tile or player to select it.
- Press the escape key to quit the game.

## More Details

 * [Dependency Setup](README_dependencies.md)
 * [Building Details](README_building.md)
 * [![ci](https://github.com/UwUClub/Zappy/actions/workflows/Testing.yml/badge.svg)](https://github.com/cpp-best-practices/cmake_template/actions/workflows/ci.yml)
 ``` txt
    can add that to see coverage % in github
    * [![codecov](https://codecov.io/gh/UwUClub/Zappy/branch/main/graph/badge.svg)](https://codecov.io/gh/cpp-best-practices/cmake_template)
 ```
## Testing

See [Catch2 tutorial](https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md)

## Credits

- Valentin Gegoux
- Baptiste Laran
- Mathéo Martin
- Christophe Chhor
- Maxence Labourel

## License

Zappy is developped by the UwUClub for Epitech.
