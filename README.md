
## get the code:

```
git clone https://github.com/subatomicglue/MinimalSynthVST2.4.git --recursive
```

## setup dependencies

For Windows Cross Compile:
- `brew install llvm` - latest Clang+LLVM 6.0.0 for cross compiling to Windows.  Binaries for other platforms there too.
- MSVC toolchain inc/lib dirs
  * Copy MSVC 2015 include & lib directories to `~/MSVC/`
  * See [Modules/cmake_example/README.md](https://github.com/subatomicglue/cross-compile-macosx-clang-windows-msvc/tree/master/cmake_example) for how to

Setup MrsWatson (for testing):
- `cd MrsWatson && git submodule init && git submodule update && cd -`
- `mkdir build-mrs && cd build-mrs && cmake ../MrsWatson && make -j 6 && cd -`

## build:

Under MacOSX bash shell:
- Generate MacOSX VST
```
$  ./cmake_native
```
- Generate Windows VST (cross compile)
```
$  ./cmake_windows
```

Under Windows cmd.exe shell:
- Generate Windows VST
```
C:/minimal> win-cmake.bat
C:/minimal> win-build32.bat
C:/minimal> win-build64.bat
```

## test:
```
$  ./test32
$  ./test64
```


## troubleshooting:

* Problem:
`clang-cl` giving error during cross compile:
```
vstgui/vstgui/lib/controls/../cstring.h(26,2):  error:
      exception specification of explicitly defaulted default constructor does not match the
      calculated one
        UTF8CodePointIterator () noexcept = default;
```
* Solution:
Change
```
UTF8CodePointIterator () noexcept = default;
```
To
```
//UTF8CodePointIterator () noexcept = default;          // KEVIN: doesnt compile under clang-cl

//UTF8CodePointIterator () /*noexcept*/ = default;      // KEVIN: this resulted in error under clang-cl

UTF8CodePointIterator () noexcept /*=default*/: it() {} // KEVIN: removed default, replace with {}

```

## NOTES:

- add a new submodule, fixed to a commit:
  * `git submodule add https://github.com/steinbergmedia/vstgui.git vstgui`
  * `cd vstgui && git checkout 13ab945 && cd -`
  * `git ci -m "comment"`

- Update `git submodule update` or `git submodule update --rebase --remote`

