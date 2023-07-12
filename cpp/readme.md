![](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d5/Inscription_on_Broom_Bridge_%28Dublin%29_regarding_the_discovery_of_Quaternions_multiplication_by_Sir_William_Rowan_Hamilton.jpg/800px-Inscription_on_Broom_Bridge_%28Dublin%29_regarding_the_discovery_of_Quaternions_multiplication_by_Sir_William_Rowan_Hamilton.jpg)

# squaternion.cpp

This is a c++ version of my python `squaternion` library.

## Install Arduino

You can either put it in your `Documents/Arduino/libraries` folder or make a symbolic link from where you keep the folder to where the Arduino IDE expects it to be. I store all of my github repo's in a `github` folder, so I know where they are.

```bash
ln -s <where you keep it> ~/Documents/Arduino/libraries
```

## Install Computer

You can use standard `cmake` commands to use this.

```bash
cd squaternion.cpp
mkdir build
cd build
cmake ..
build
```

## Todo

- [ ] Make a CPM
- [x] Should I make this header only? It is pretty simple
- [ ] Add `gtest` tests like `python` version
- [x] Add a simple Arduino compile test

# MIT License

**Copyright (c) 2022 Mom's Friendly Robot Company**

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
