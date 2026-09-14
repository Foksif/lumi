{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
packages = with pkgs; [
llvmPackages.libcxx

cmake
gnumake
git
pkg-config
nlohmann_json

];

buildInputs = with pkgs; [
glib
gtk4
webkitgtk_6_0
libsoup_3

libselinux
libsepol
fribidi
libthai
lerc
xz
zstd
libwebp
sqlite
libpsl
libdatrie
expat
libxdmcp
libdeflate
util-linux
pcre2
libsysprof-capture

gst_all_1.gstreamer
gst_all_1.gst-plugins-base

];

shellHook = ''
export CC=clang
export CXX=clang++

```
export CPLUS_INCLUDE_PATH="${pkgs.llvmPackages.libcxx}/include/c++/v1"
```

'';
}

