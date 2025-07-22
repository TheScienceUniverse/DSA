# Data Structures and Algorithms
Custom C Library for data-structures and algorithms

[![Version](https://markdown-badge-crafter.netlify.app/.netlify/functions/app/?type=version&user=SayanShankhari&acc=TheScienceUniverse&repo=DSA&branch=master)](https://github.com/TheScienceUniverse/DSA)
[![Commit Activity](https://img.shields.io/github/commit-activity/m/TheScienceUniverse/DSA)](https://github.com/TheScienceUniverse/DSA/pulse)
[![GitHub Issues](https://img.shields.io/github/issues/TheScienceUniverse/DSA.svg?style=flat-square&label=Issues&color=d77982)](https://github.com/TheScienceUniverse/DSA/issues)
[![Tests](./aft/test_status.svg)](https://raw.githubusercontent.com/TheScienceUniverse/DSA/refs/heads/master/log/passmark.log)
[![Coverage](./aft/code_coverage.svg)](https://raw.githubusercontent.com/TheScienceUniverse/DSA/refs/heads/master/log/coverage.log)
[![Discord](https://img.shields.io/discord/869557815780470834?color=738adb&label=Discord&logo=discord&logoColor=white&style=flat-square)](https://discord.gg/DEYW7vZkm7)

## Overview

- Data Structures is a minimal object generator that is written and run in C language.


### Included Data-Structures & Utility Functions =>

Click on the links below to know details about them.

- [Basic](/doc/basic.md)
- [String](/doc/string.md)
- [Data](/doc/data.md)
- [Bare_List](/doc/bare_list.md)
- [Chunk](/doc/chunk.md)
- [List](/doc/list.md)
- [Node](/doc/node.md)
- [Linked_List](/doc/linked_list.md)
- [Stack](/doc/stack.md)
- [Queue](/doc/queue.md)
- [Tree](/doc/tree.md)
- [Graph](/doc/graph.md)


### Dependency Diagram =>

![Image](./media/library_structure.svg "Library Structure")
___

## Installation

Please install git, (wget or curl) through official package managers of your operating system; then run the following in your favorite terminal.

```sh
wget -O- "https://raw.githubusercontent.com/TheScienceUniverse/DSA/refs/heads/master/install.sh" | sh
```

or

```sh
curl "https://raw.githubusercontent.com/TheScienceUniverse/DSA/refs/heads/master/install.sh" | sh
```

Please note,
- the contents will be copied in 'DSA' directory
- there will be 4 more extra folder created in your project directory, 'inc' (location of interfaces), 'lib' (location for libraries) and 'log' (memory usage logging).
- you may delete the 'DSA' folder from your project if not required any longer
- you must exclude 'DSA' folder in '.gitignore' file from version control system to reduce extra overhead.
___

## Usage

Please note that you need to use the shared object library as per C compilation, linking and execution standards.

Please observe following example and notice the following,

- 'inc' (include) folder from DSA project having all interfaces (header files) should be present to resolve symbols during compile time, notice you have already kept it in place during installation, just neither delete it nor edit it without understanding the full codebase
- compiler and linker is `gcc`
- outputting all warnings with `-Wall`
- providing local library location (`$(pwd)/lib`) to linker with option `-L`
- calling the dynamic shared object library with standard, `-ldsa` expands to `libdsa.so` (dynamic shared object) or `libdsa.a` (static archive) whichever is available in the linker informed location
- generating executable file with option `-o exec`
- giving input files including `main.c` and other pre-compiled object files (having '.o' extension) required to build full program like just-in-time compilation

```sh
gcc -Wall -L$(pwd)/lib -ldsa -o exec [other-object-files...] main.c
```

Also please note that we could have copied the libray into standard locations like '/lib/', '/usr/lib/' or '/usr/share/lib/'; but for security conflicts we do not want to install it there.

That is why we chose a workaround (environment variable LD_LIBRARY_PATH) that have highest precedence while looking for libraries, even before standard library locations.

Notice that during execution the LD_LIBRARY_PATH need to set with the library location _i.e._ `./lib/` without hampering old values of this environment variable. There is no export command, not even doller ($) while setting the value.

```sh
LD_LIBRARY_PATH=./lib/:$LD_LIBRARY_PATH ./exec
```
___

## History

- Hi, this is the inititiator of this repo. From the college days it was a trial to create a general purpose data-structure and algorithm (DSA) in C programming language.
- Please try this tool on systems (computer, mobile, embded systems) after installing GCC (GNU Compiler Collections) or Clang compiler; compile and run it natively or in servers.


## [🤝 Contributing](./.github/CONTRIBUTING.md)

## [📜 Code of Conduct](./.github/CODE_OF_CONDUCT.md)

## [🔒 Security](./.github/SECURITY.md)
___

## Credits

## 💝 Support

If you like this DSA Project and would like to support & appreciate it via donation then I'll gladly accept it. 

[![Ko-Fi](https://img.shields.io/badge/Ko--fi-F16061?style=for-the-badge&logo=ko-fi&logoColor=white)](https://ko-fi.com/sayan_shankhari)
[![Buy Me a Coffee](https://img.shields.io/badge/Buy_Me_A_Coffee-FFDD00?style=for-the-badge&logo=buy-me-a-coffee&logoColor=black)](https://www.buymeacoffee.com/sayan.shankhari)

[![Patreon](https://img.shields.io/badge/Patreon-F96854?style=for-the-badge&logo=patreon&logoColor=white)]()
[![Paypal](https://img.shields.io/badge/PayPal-00457C?style=for-the-badge&logo=paypal&logoColor=white)](https://www.paypal.com/paypalme/the01guy)
[![BHIM UPI](https://img.shields.io/badge/bhim-e9661c?style=for-the-badge&logo=bhim&logoColor=e9661c&color=27803b)]()
[![Google Pay](https://img.shields.io/badge/Google%20Pay-%233780F1.svg?style=for-the-badge&logo=Google-Pay&logoColor=white)]()
[![Razor Pay](https://img.shields.io/badge/Razorpay-02042B?style=for-the-badge&logo=razorpay&logoColor=3395FF)]()
[![Stripe](https://img.shields.io/badge/Stripe-626CD9?style=for-the-badge&logo=Stripe&logoColor=white)]()
