<br/>
<div align="center">
  <h3 align="center">Fractal Playground</h3>

  <p align="center">
    A simple fractal playground using SFML and C++
    <br/>
    <br/>
    <a href="https://github.com/Gagonlaire/fractal-playground">View Demo</a>
    .
    <a href="https://github.com/Gagonlaire/fractal-playground/issues">Report Bug</a>
    .
    <a href="https://github.com/Gagonlaire/fractal-playground/issues">Request Feature</a>
  </p>
</div>

![Stargazers](https://img.shields.io/github/stars/Gagonlaire/fractal-playground?style=social) ![Issues](https://img.shields.io/github/issues/Gagonlaire/fractal-playground) ![License](https://img.shields.io/github/license/Gagonlaire/fractal-playground)

## Table Of Contents

* [About the Project](#about-the-project)
* [Getting Started](#getting-started)
    * [Prerequisites](#prerequisites)
* [Usage](#usage)
* [Known Issues](#known-issues)
* [Contributing](#contributing)
    * [Creating A Pull Request](#creating-a-pull-request)
* [License](#license)

## About The Project

![Screen Shot](https://raw.githubusercontent.com/Gagonlaire/fractal-playground/main/resources/example.jpg)

Welcome to my fractal playground ! In this program, you can explore the world of fractals and find intricate designs. Fractals are never-ending patterns that are created by repeating a simple rule over and over again. They can be found in nature and are often used in computer graphics and art. You have access to different controls that let you adjust the level of iterations and switch between different fractals to create a wide range of patterns.

## Getting Started

Nothing special, just install all the dependencies.

### Prerequisites

For this project you need to install the following dependencies:

* C++ (std++ 17)
* CMake (3.14, could be lowered)
* SFML (2.5)

Macos
```sh
brew install cmake
brew install sfml
```

## Usage

To run the project, do the following:

1. Clone the project and install all dependencies.
2. Run the script provided or enter the following command in the terminal:
```sh
cmake -Bbuild -H. && cd build && make && cd ../ && ./fractal-playground
```

The program offer several controls:

1. "Reset view" restores the default view of the fractal.
2. "Go back" undoes the last zoom you made.
3. The "[fractal name]" option in the selection menu allows you to choose the fractal to view.
4. The "iterations +/-" buttons let you increase or decrease the maximum number of iterations used to generate the fractal image, which can improve the precision of the image but may also negatively impact performance.
5. "Reset iterations" restores the default maximum number of iterations.

## Known issues

the program as some known issues:

1. The program is not really optimized for low performance computers.
2. There is an issue with SFML window resizing causing weird behavior.

## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create.
Any contributions you make are **greatly appreciated**. If you have any suggestions (new features, code improvements), feel free to [open an issue](https://github.com/Gagonlaire/fractal-playground/issues/new).

### Creating A Pull Request

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

Distributed under the GNU License. See [LICENSE](https://github.com/Gagonlaire/fractal-playground/blob/main/LICENSE) for more information.
