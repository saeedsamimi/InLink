# InLink

![InLink](./icons/icons/icon-animated-light.gif)

InLink is an open-source platform designed to connect users through companies, universities, schools, and more. Whether you're a worker searching for a job or an employer seeking talent, InLink provides a seamless way to find and connect with each other. The application is built using C++ for the client-side and Node.js (JavaScript) for the server-side, ensuring high performance and real-time features.

## Features

- **User Connections**: Connect with users across various organizations like companies, universities, and schools.
- **Job Matching**: Easily find job opportunities or potential employees.
- **Real-Time Chat**: Communicate instantly with other users.
- **Secure Authentication**: Robust security features to keep your data safe.
- **High Performance**: Fast running application ensuring smooth user experience.
- **Open Source**: Fully open source, allowing users to build and customize the platform on their local systems.

## Installation

### Prerequisites

- **C++ Tools**: Required for building the client-side application
  - **CMake**: A modular build system.
  - **C++ Compiler**: A C++ compiler such as GNU `g++` or Microsoft `msvc`
  - **Make Tool**: A make tool such as `ninja`, `make` and `Mingw Make`. *preferred: `ninja`*
- **Qt6**: Required for building the Qt librar.
i have used these libraries in the application, you can also download and instal it from [Qt website](https://www.qt.io/dowmload-dev).
  - **Widgets**: for reperesenting the UI
  - **GUI**: for building the high level styled and beatiful Graphical user interface
  - **Core**: for Qt Algorithms and Core Features and processes
  - **SQL**: a connector api created by Qt to handle standard query language.
  - **Network**: for handling the network requests.
  - **LinguistTools**: for building multi language application
  - **WebSockets**: this is a required library for performing the real time chat features
  Gui Core Widgets Sql Network LinguistTools WebSockets
- **OpenSSL**: because this platform is secure i have used this library for encrypting the user informations
- **PostgreSQL**: A high performance database i have used in this project, but you can use another databases you need as easy as you want. but you first have import the inital database in your database before run.
- **Node.js**: Required for the server-side application.
- **npm**: Node package manager for managing dependencies.
- **Git**: For cloning the repository.

### Client-Side (C++)

we preffer you to install `OpenSSL` library by `vcpkg`.

1. **Clone the Repository:** at first you have to clone the repository:
   ```bash
   git clone https://github.com/saeedsamimi/InLink.git
   cd InLink
   ```
2. **Install the OpenSSL library:** at first you should install the `vcpkg` from [here](https://github.com/microsoft/vcpkg) and after the installtion sucessed you have to install the `OpenSSL` library:
   ```bash
   vcpkg install openssl
   ```
   and then configure the `VCPKG_ROOT` environment to the location of installed vcpkg.
3. **Configure the CMake:** you can use the `qt-cmake` that is provided by qt:
    ```bash
    qt-cmake -S . -B build
    ```
    or if you did not find the qt-cmake you can do it with simple cmake instead by running:
    ```bash
    cmake -DCMAKE_PREFIX_PATH="../path/to/QTDIR" -DCMAKE_TOOLCAIN_FILE="VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
    ```
4. **Build the configuration:** now by running this command in your command line interface the app is going to build:
    ```bash
    cmake --build . --target InLink --parallel 4
    ```
### Server-Side (JavaScript)
1. **Running the server:** please go back to the project's root and run this to install the Server(node.js) requirement libraries:
    ```bash
    cd Server & npm i
    ```
    and then you can start the server by doing this:
    ```bash
    npm run start
    ```
    if you see the successfully running the server, you can run the client executable.

## Contact us:
 For any questions or suggestions, feel free to open an issue or contact the project maintainer at [my email](doob.fooy@gmail.com).

