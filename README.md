# console

cross-platform console library

---

## version

beta 2.0: add Console::Color

---

license: *LGPL-3.0*

*GitHub* address: https://github.com/lrcno6/console

---

*Console* is a cross-platform console library. You can move the cursor, use colors and so on.

it runs everywhere (in theory) (tested on *Windows (MSVC)*, *Windows (MinGW)* and *linux (g++)*)

---

## how to use it

you should make first:

```bash
make linux # for linux (g++)
make windows_msvc # for Windows (Visual C++)
make windows_mingw # for Windows (MinGW)
```

and then link to *libconsole.a* or *console.lib*:

```bash
# for example
g++ user.cpp -o user -Lconsole -lconsole -lcurses # for linux (g++), remember to link to libcurses
cl user.cpp console/console.lib # for Windows (MSVC)
g++ user.cpp -o user -Lconsole -lconsole # for Windows (MinGW)
```

---

welcome to contribute to [console](https://github.com/lrcno6/console)

by [lrcno6](https://github.com/lrcno6)